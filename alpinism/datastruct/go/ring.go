package main

type Ring struct {
	Prev  *Ring
	Next  *Ring
	Value interface{}
}

func NewRing(n int) *Ring {
	if n <= 0 {
		return nil
	}
	first := new(Ring)
	p := first
	for i := 1; i <= n; i++ {
		n := new(Ring)
		n.Prev = p
		p.Next = n
		p = n
	}
	p.Next = first
	first.Prev = p
	return first
}

func (r *Ring) Link(new *Ring) {
	next := r.Next
	if new != nil {
		r.Next = new
		new.Prev = r.Next
		new.Next = next
		next.Prev = new
	}
}
