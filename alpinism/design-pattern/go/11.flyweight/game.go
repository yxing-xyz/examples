package flyweight

type Game struct {
	Terrorists       []*Player
	CounterTerrorist []*Player
}

func NewGame() *Game {
	return &Game{
		Terrorists:       make([]*Player, 1),
		CounterTerrorist: make([]*Player, 1),
	}
}

func (c *Game) AddTerrorist(dressType string) {
	player := NewPlayer("T", dressType)
	c.Terrorists = append(c.Terrorists, player)
	return
}

func (c *Game) AddCounterTerrorist(dressType string) {
	player := NewPlayer("CT", dressType)
	c.CounterTerrorist = append(c.CounterTerrorist, player)
	return
}
