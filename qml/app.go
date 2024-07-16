package qml

// #cgo CXXFLAGS: -g -I/usr/include/qt6
// #cgo LDFLAGS: -L${SRCDIR} -L/usr/lib -lQt6Qml -lQt6Core -lQt6Gui -lQt6Quick -lQt6Widgets -lqmlapp
// #include "app.h"
// #include <stdlib.h>
import "C"
import "unsafe"

func NewApplication(argv []string) Application {
	argc := len(argv)
	// https://stackoverflow.com/questions/42530538/how-to-pass-pointer-to-slice-to-c-function-in-go
	cArray := C.malloc(C.size_t(argc) * C.size_t(unsafe.Sizeof(uintptr(0))))
	goArray := (*[1<<30 - 1]*C.char)(cArray)
	for i, v := range argv {
		goArray[i] = C.CString(v)
	}

	ptr := C.NewApplication(C.int(argc), (**C.char)(cArray))

	return Application{ptr}
}

func (app Application) SetAttribute(attr Attribute, on bool) {
	C.SetAttribute(C.longlong(attr), C.bool(on))
}

func (app Application) SetFont(fontFamily string, pointSize int, weight FontWeight, italic bool) {
	cFontFamily := C.CString(fontFamily)
	defer C.free(unsafe.Pointer(cFontFamily))
	C.SetFont(cFontFamily, C.int(int32(pointSize)), C.int(weight), C.bool(italic))
}

func (app Application) SetQuitOnLastWindowClosed(quit bool) {
	C.SetQuitOnLastWindowClosed(C.bool(quit))
}

func (app Application) SetApplicationDisplayName(name string) {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))
	C.SetApplicationDisplayName(cName)
}

func (app Application) SetWindowIcon(fileName string) {
	cFileName := C.CString(fileName)
	defer C.free(unsafe.Pointer(cFileName))
	C.SetWindowIcon(cFileName)
}

func (app Application) SetApplicationName(name string) {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))
	C.SetApplicationName(cName)
}

func (app Application) SetApplicationVersion(version string) {
	cVersion := C.CString(version)
	defer C.free(unsafe.Pointer(cVersion))
	C.SetApplicationVersion(cVersion)
}

func (app Application) SetOrganizationName(name string) {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))
	C.SetOrganizationName(cName)
}

func (app Application) SetOrganizationDomain(domain string) {
	cDomain := C.CString(domain)
	defer C.free(unsafe.Pointer(cDomain))
	C.SetOrganizationDomain(cDomain)
}

func (app Application) Exec() int {
	return int(int32(C.Exec()))
}
