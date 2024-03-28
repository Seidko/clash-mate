package config

import (
	MiHomoConfig "github.com/metacubex/mihomo/config"
)

type Theme int8

const (
	Light Theme = iota
	Dark
	Auto
)

type Config struct {
	MiHomoConfig.Config
	theme Theme
}
