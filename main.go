package main

import "C"

//export Launch
func Launch() *C.char {
	return C.CString("")
}

func main() {}
