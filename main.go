package main

import "C"
import (
	"github.com/metacubex/mihomo/constant"
	"github.com/metacubex/mihomo/hub/executor"
	"github.com/metacubex/mihomo/log"
)

var ()

//export Launch
func Launch() {
	if cfg, err := executor.ParseWithPath(constant.Path.Config()); err == nil {
		executor.ApplyConfig(cfg, true)
	} else {
		log.Errorln("Parse config error: %s", err.Error())
	}
}

func main() {}
