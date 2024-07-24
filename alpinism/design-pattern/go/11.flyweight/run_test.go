package flyweight

import (
	"testing"
)

func TestRun(t *testing.T) {
	game := NewGame()
	//Add Terrorist
	game.AddTerrorist(TerroristDressType)
	game.AddTerrorist(TerroristDressType)
	game.AddTerrorist(TerroristDressType)
	game.AddTerrorist(TerroristDressType)

	//Add CounterTerrorist
	game.AddCounterTerrorist(CounterTerroristDressType)
	game.AddCounterTerrorist(CounterTerroristDressType)
	game.AddCounterTerrorist(CounterTerroristDressType)

	dressFactoryInstance := GetDressSingleInstance()
	dressFactoryInstance.Print()
}
