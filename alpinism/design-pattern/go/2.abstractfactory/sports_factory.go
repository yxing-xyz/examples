package abstractfactory

import "github.com/pkg/errors"

type iSportsFactory interface {
	makeShoe() iShoe
	makeShirt() iShirt
}

func getSportsFactory(brand string) (iSportsFactory, error) {
	if brand == "adidas" {
		return &adiasFactory{}, nil
	} else if brand == "nick" {
		return &nickFactory{}, nil
	}
	return nil, errors.Wrap(errors.New("未知的工厂类型"), "get sports factory failed")
}
