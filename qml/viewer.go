package qml

// #cgo CFLAGS: -g
// #cgo CPPFLAGS: -g
// #cgo LDFLAGS: -L${SRCDIR}/qml -lqmlapp
// #include "viewer.h"
// #include <stdlib.h>
import "C"
import (
	"log"
	"net/url"
	"runtime"
	"unsafe"

	"github.com/fsnotify/fsnotify"
)

func NewViewer(source *string) Viewer {
	url := (*C.char)(nil)
	if source != nil {
		url = C.CString(*source)
	}
	defer C.free(unsafe.Pointer(url))
	bus := make(chan Event)

	var pinner runtime.Pinner
	busPtr := unsafe.Pointer(&bus)
	pinner.Pin(busPtr)
	ptr := C.NewViewer(C.size_t(uintptr(busPtr)), url)
	defer C.free(*ptr)
	tuple := (*[2]unsafe.Pointer)(*ptr)
	return Viewer{tuple[0], tuple[1], bus, pinner}
}

func NewViewerFromQml(qml string) Viewer {
	url := "data:text/plain;charset=UTF-8," + url.QueryEscape(qml)
	return NewViewer(&url)
}

func (view Viewer) SetSource(url string) {
	if view.ptr == nil {
		return
	}

	cURL := C.CString(url)
	defer C.free(unsafe.Pointer(cURL))
	C.SetSource(view.ptr, cURL)
}

func (view Viewer) SetSourceFromQml(qml string) {
	if view.ptr == nil {
		return
	}

	cStr := C.CString(qml)
	defer C.free(unsafe.Pointer(cStr))
	C.SetSourceFromQml(view.ptr, cStr)
}

func (view Viewer) SetResizeMode(resizeMode ResizeMode) {
	if view.ptr == nil {
		return
	}

	C.SetResizeMode(view.ptr, C.int(resizeMode))
}

func (view Viewer) SetHeight(height int32) {
	if view.ptr == nil {
		return
	}

	C.SetHeight(view.ptr, C.int(height))
}

func (view Viewer) SetWidth(width int32) {
	if view.ptr == nil {
		return
	}

	C.SetWidth(view.ptr, C.int(width))
}

func (view Viewer) Show() {
	if view.ptr == nil {
		return
	}

	view.StartBridge()
	C.Show(view.ptr)
}

func (view Viewer) Reload() {
	if view.ptr == nil {
		return
	}

	C.Reload(view.ptr)
}

func (view Viewer) LiveReload(path string) {
	watcher, err := fsnotify.NewWatcher()
	watcher.Add(path)
	if err != nil {
		log.Fatal(err)
	}

	go func() {
		for {
			select {
			case event, ok := <-watcher.Events:
				if !ok {
					return
				}
				if event.Has(fsnotify.Write) {
					log.Printf("Live Reload: %s", event.Name)
					view.Reload()
				}
			case _, ok := <-watcher.Errors:
				if !ok {
					return
				}
			}
		}
	}()
}

func (view Viewer) StartBridge() {
	go func() {
		for {
			e := <-view.Bus
			C.ReceiveEvent(view.bridge, C.CString(e.Name), C.CString(e.Payload))
		}
	}()
}

func (view Viewer) StopBridge() {

}

//export receive
func receive(ptr unsafe.Pointer, name *C.char, payload *C.char) {
	bus := (*Bus)(ptr)

	if bus == nil {
		return
	}

	*bus <- Event{
		Name:    C.GoString(name),
		Payload: C.GoString(payload),
	}
}
