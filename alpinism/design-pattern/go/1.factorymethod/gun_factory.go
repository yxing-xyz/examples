package factorymethod

import (
	"fmt"
)

func getGun(gunType string) (iGun, error) {
	if gunType == "ak47" {
		return NewAk47(), nil
	}
	if gunType == "musket" {
		return NewMusket(), nil
	}
	return nil, fmt.Errorf("Wrong gun type passwd")
}
