package adapter

import "testing"

func TestRun(t *testing.T) {

	client := &client{}
	mac := &mac{}
	client.insertLightningConnectorIntoComputer(mac)

	windowMachine := &windows{}

	windowsMachineAdapter := &windowsAdapter{
		windowMachine: windowMachine,
	}
	client.insertLightningConnectorIntoComputer(windowsMachineAdapter)
}
