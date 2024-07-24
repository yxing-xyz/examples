package flyweight

type CounterTerroristDress struct {
	color string
}

func (c *CounterTerroristDress) GetColor() string {
	return c.color
}

func NewCounterTerroristDress() *CounterTerroristDress {
	return &CounterTerroristDress{
		color: "green",
	}
}
