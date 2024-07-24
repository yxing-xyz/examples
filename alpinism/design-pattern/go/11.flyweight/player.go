package flyweight

type Player struct {
	dress    IDress
	playType string
	lat      int
	long     int
}

func NewPlayer(playType, dressType string) *Player {
	// dress, _ :=
	dress, _ := GetDressSingleInstance().GetDressByType(dressType)
	return &Player{
		playType: playType,
		dress:    dress,
	}
}

func (p *Player) NewLocation(lat, long int) {
	p.lat = lat
	p.long = long
}
