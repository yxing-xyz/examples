//
// Created by Jennica on 2017/1/3.
//

#include "mediator.h"

namespace mediator
{
  BaseComponent::BaseComponent(Mediator *mediator) : mediator_(mediator)
  {
  }

  void BaseComponent::set_mediator(Mediator *mediator)
  {
    mediator_ = mediator;
  }

  void Component1::DoA()
  {
    std::cout << "Component 1 does A.\n";
    this->mediator_->Notify(this, "A");
  }

  void Component1::DoB()
  {
    std::cout << "Component 1 does B.\n";
    this->mediator_->Notify(this, "B");
  }

  void Component2::DoC()
  {
    std::cout << "Component 2 does C.\n";
    this->mediator_->Notify(this, "C");
  }

  void Component2::DoD()
  {
    std::cout << "Component 2 does D.\n";
    this->mediator_->Notify(this, "D");
  }

  ConcreteMediator::ConcreteMediator(Component1 *c1, Component2 *c2) : component1_(c1), component2_(c2)
  {
    this->component1_->set_mediator(this);
    this->component2_->set_mediator(this);
  }

  void ConcreteMediator::Notify(BaseComponent *sender, std::string event) const
  {
    if (event == "A")
    {
      std::cout << "Mediator reacts on A and triggers following operations:\n";
      this->component2_->DoC();
    }
    if (event == "D")
    {
      std::cout << "Mediator reacts on D and triggers following operations:\n";
      this->component1_->DoB();
      this->component2_->DoC();
    }
  }

  void ClientCode()
  {
    Component1 *c1 = new Component1;
    Component2 *c2 = new Component2;
    ConcreteMediator *mediator = new ConcreteMediator(c1, c2);
    std::cout << "Client triggers operation A.\n";
    c1->DoA();
    std::cout << "\n";
    std::cout << "Client triggers operation D.\n";
    c2->DoD();

    delete c1;
    delete c2;
    delete mediator;
  }

  void run()
  {
    ClientCode();
  }
}
