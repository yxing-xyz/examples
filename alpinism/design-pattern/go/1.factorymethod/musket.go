package factorymethod

type musket struct {
	gun
}

func NewMusket() iGun {
	return &musket{
		gun: gun{
			name:  "Musket gun",
			power: 30,
		},
	}
}
