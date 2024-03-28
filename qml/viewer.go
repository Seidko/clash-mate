package qml

// // #cgo CFLAGS: -x c++
// #cgo CXXFLAGS: -I/usr/include/qt6
// #cgo LDFLAGS: -L${SRCDIR}/qml -lqmlapp
// #include "viewer.hpp"
// #include <stdlib.h>
import "C"
import "unsafe"

type Viewer struct {
	ptr unsafe.Pointer
}

func NewViewer() Viewer {
	ptr := C.NewViewer()
	return Viewer{ptr}
}

func NewViewerWithSource(source string) Viewer {
	ptr := C.NewViewerWithSource(C.CString(source))
	return Viewer{ptr}
}

func (view Viewer) SetSource(url string) {
	if view.ptr == nil {
		return
	}

	cURL := C.CString(url)
	defer C.free(unsafe.Pointer(cURL))
	C.SetSource(view.ptr, cURL)
}
