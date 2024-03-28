package main

import (
	"clash-mate/qml"
	"os"
)

func main() {
	app := qml.NewApplication(os.Args)
	app.SetApplicationDisplayName("Qml Example")
	app.Exec()
}
