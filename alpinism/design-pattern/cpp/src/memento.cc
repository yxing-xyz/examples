#include "memento.h"
#include <ctime>
#include <iostream>

namespace memento
{

  ConcreteMemento::ConcreteMemento(std::string state) : state_(state)
  {
    this->state_ = state;
    std::time_t now = std::time(0);
    this->date_ = std::ctime(&now);
  }
  std::string ConcreteMemento::GetName() const
  {
    return this->date_ + " / (" + this->state_.substr(0, 9) + "...)";
  }
  std::string ConcreteMemento::date() const
  {
    return this->date_;
  }
  std::string ConcreteMemento::state() const
  {
    return this->state_;
  }

  std::string Originator::GenerateRandomString(int length)
  {
    const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    int stringLength = sizeof(alphanum) - 1;

    std::string random_string;
    for (int i = 0; i < length; i++)
    {
      random_string += alphanum[std::rand() % stringLength];
    }
    return random_string;
  }

  Originator::Originator(std::string state) : state_(state)
  {
    std::cout << "Originator: My initial state is: " << this->state_ << "\n";
  }
  void Originator::DoSomething()
  {
    std::cout << "Originator: I'm doing something important.\n";
    this->state_ = this->GenerateRandomString(30);
    std::cout << "Originator: and my state has changed to: " << this->state_ << "\n";
  }

  Memento *Originator::Save()
  {
    return new ConcreteMemento(this->state_);
  }

  void Originator::Restore(Memento *memento)
  {
    this->state_ = memento->state();
    std::cout << "Originator: My state has changed to: " << this->state_ << "\n";
  }

  Caretaker::Caretaker(Originator *originator) : originator_(originator)
  {
    this->originator_ = originator;
  }

  void Caretaker::Backup()
  {
    std::cout << "\nCaretaker: Saving Originator's state...\n";
    this->mementos_.push_back(this->originator_->Save());
  }

  void Caretaker::Undo()
  {
    if (!this->mementos_.size())
    {
      return;
    }
    Memento *memento = this->mementos_.back();
    this->mementos_.pop_back();
    std::cout << "Caretaker: Restoring state to: " << memento->GetName() << "\n";
    try
    {
      this->originator_->Restore(memento);
    }
    catch (...)
    {
      this->Undo();
    }
  }

  void Caretaker::ShowHistory() const
  {
    std::cout << "Caretaker: Here's the list of mementos:\n";
    for (Memento *memento : this->mementos_)
    {
      std::cout << memento->GetName() << "\n";
    }
  }

  void ClientCode()
  {
    Originator *originator = new Originator("Super-duper-super-puper-super.");
    Caretaker *caretaker = new Caretaker(originator);
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    std::cout << "\n";
    caretaker->ShowHistory();
    std::cout << "\nClient: Now, let's rollback!\n\n";
    caretaker->Undo();
    std::cout << "\nClient: Once more!\n\n";
    caretaker->Undo();

    delete originator;
    delete caretaker;
  }

  void run()
  {
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    ClientCode();
  }
}
