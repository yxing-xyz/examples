package mediator

type StationManger struct {
	isPlatformFree bool
	trainQueue     []ITrain
}

func NewStationManger() *StationManger {
	return &StationManger{
		isPlatformFree: true,
	}
}

func (s *StationManger) CanArrive(t ITrain) bool {
	if s.isPlatformFree {
		s.isPlatformFree = false
		return true
	}
	s.trainQueue = append(s.trainQueue, t)
	return false
}

func (s *StationManger) NotifyAboutDeparture() {
	if !s.isPlatformFree {
		s.isPlatformFree = true
	}

	if len(s.trainQueue) > 0 {
		firstTrainInQueue := s.trainQueue[0]
		s.trainQueue = s.trainQueue[1:]
		firstTrainInQueue.PermitArrival()
	}
}
