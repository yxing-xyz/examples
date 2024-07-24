package chain_of_responsibility

import "fmt"

type Reception struct {
	next IDepartMent
}

func (r *Reception) Execute(patient *Patient) {
	if patient.RegistrationDone {
		fmt.Println("Patient registration already done")
		r.next.Execute(patient)
		return
	}
	fmt.Println("Reception registering patient")
	patient.RegistrationDone = true
	r.next.Execute(patient)
	return
}

func (r *Reception) SetNext(next IDepartMent) {
	r.next = next
}
