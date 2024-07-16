package qml

import (
	"runtime"
	"unsafe"
)

type Application struct {
	ptr unsafe.Pointer
}

type Viewer struct {
	ptr    unsafe.Pointer
	bridge unsafe.Pointer
	Bus    Bus
	pinner runtime.Pinner
}

type Attribute int64

type FontWeight int32

// ResizeMode specifies how to resize the view.
type ResizeMode int32

const (
	// SizeViewToRootObject makes the view resizes with the root item in the QML.
	SizeViewToRootObject ResizeMode = 1 << iota

	// SizeRootObjectToView makes the view will automatically resize
	// the root item to the size of the view.
	SizeRootObjectToView
)

type Event struct {
	Name    string
	Payload string
}

type Bus chan Event
