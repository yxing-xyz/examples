package iterator

type UserCollection struct {
	Users []*User
}

func (u *UserCollection) CreateIterator() IIterator {
	return &UserIterator{
		Users: u.Users,
	}
}
