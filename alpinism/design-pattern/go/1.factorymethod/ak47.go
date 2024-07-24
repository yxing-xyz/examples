package factorymethod

type ak47 struct {
	gun
}

func NewAk47() iGun {
	return &ak47{
		gun: gun{
			name:  "Ak47 gun",
			power: 30,
		},
	}
}
