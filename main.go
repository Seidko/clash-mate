package main

import (
	"clash-mate/qml"
	_ "embed"
	"flag"
	"os"
	"time"
)

//go:embed res/main.qml
var qmlCode string

var devMode bool

func init() {
	flag.BoolVar(&devMode, "dev", false, "Development Mode")
	flag.Parse()
}

func main() {
	app := qml.NewApplication(os.Args)
	app.SetApplicationDisplayName("Qml Example")

	view := qml.NewViewer(nil)
	if devMode {
		view.SetSource("res/main.qml")
		view.LiveReload("res")
	} else {
		view.SetSourceFromQml(qmlCode)
	}
	view.SetResizeMode(qml.SizeRootObjectToView)
	view.SetHeight(320)
	view.SetWidth(480)
	view.Show()
	go func() {
		time.Sleep(1000)
		view.Bus <- qml.Event{
			Name:    "goroutines",
			Payload: "{}",
		}
	}()
	app.Exec()
}
