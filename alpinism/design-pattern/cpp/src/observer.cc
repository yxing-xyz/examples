#include "observer.h"
#include <iostream>

namespace observer
{
  IObserver::~IObserver() {}

  Subject::~Subject()
  {
    std::cout << "Goodbye, I was the Subject.\n";
  }

  void Subject::Attach(IObserver *observer)
  {
    list_observer_.push_back(observer);
  }
  void Subject::Detach(IObserver *observer)
  {
    list_observer_.remove(observer);
  }
  void Subject::Notify()
  {
    std::list<IObserver *>::iterator iterator = list_observer_.begin();
    HowManyObserver();

    while (iterator != list_observer_.end())
    {
      (*iterator)->Update(message_);
      ++iterator;
    }
  }

  void Subject::CreateMessage(std::string message)
  {
    this->message_ = message;
    this->Notify();
  }

  void Subject::HowManyObserver()
  {
    std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
  }
  void Subject::SomeBusinessLogic()
  {
    this->message_ = "change message message";
    Notify();
    std::cout << "I'm about to do some thing important\n";
  }

  Observer::Observer(Subject &subject) : subject_(subject)
  {
    this->subject_.Attach(this);
    std::cout << "Hi, I'm the Observer \"" << ++Observer::static_number_ << "\".\n";
    this->number_ = Observer::static_number_;
  }
  Observer::~Observer()
  {
    std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
  }

  void Observer::Update(const std::string &message_from_subject)
  {
    message_from_subject_ = message_from_subject;
    PrintInfo();
  }
  void Observer::RemoveMeFromTheList()
  {
    subject_.Detach(this);
    std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
  }
  void Observer::PrintInfo()
  {
    std::cout << "Observer \"" << this->number_ << "\": a new message is available --> " << this->message_from_subject_ << "\n";
  }
  
  int Observer::static_number_ = 0;  

  void ClientCode()
  {
    Subject *subject = new Subject;
    Observer *observer1 = new Observer(*subject);
    Observer *observer2 = new Observer(*subject);
    Observer *observer3 = new Observer(*subject);
    Observer *observer4;
    Observer *observer5;

    subject->CreateMessage("Hello World! :D");
    observer3->RemoveMeFromTheList();

    subject->CreateMessage("The weather is hot today! :p");
    observer4 = new Observer(*subject);

    observer2->RemoveMeFromTheList();
    observer5 = new Observer(*subject);

    subject->CreateMessage("My new car is great! ;)");
    observer5->RemoveMeFromTheList();

    observer4->RemoveMeFromTheList();
    observer1->RemoveMeFromTheList();

    delete observer5;
    delete observer4;
    delete observer3;
    delete observer2;
    delete observer1;
    delete subject;
  }

  void Run()
  {
    ClientCode();
  }
}
