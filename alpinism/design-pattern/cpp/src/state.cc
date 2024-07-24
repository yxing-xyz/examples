#include "state.h"
#include <iostream>

namespace state
{
  State::~State()
  {
  }

  void State::set_context(Context *context)
  {
    this->context_ = context;
  }

  Context::Context(State *state) : state_(nullptr)
  {
    this->TransitionTo(state);
  }

  Context::~Context()
  {
    delete this->state_;
  }

  void Context::TransitionTo(State *state)
  {
    std::cout << "Context: Transition to " << typeid(*state).name() << ".\n";
    if (this->state_ != nullptr)
      delete this->state_;
    this->state_ = state;
    this->state_->set_context(this);
  }

  void Context::Request1()
  {
    this->state_->Handle1();
  }

  void Context::Request2()
  {
    this->state_->Handle2();
  }

  void ConcreteStateA::Handle1()
  {
    std::cout << "ConcreteStateA handles request1.\n";
    std::cout << "ConcreteStateA wants to change the state of the context.\n";

    this->context_->TransitionTo(new ConcreteStateB);
  }

  void ConcreteStateA::Handle2()
  {
    std::cout << "ConcreteStateA handles request2.\n";
  }

  void ConcreteStateB::Handle1()
  {
    std::cout << "ConcreteStateB handles request1.\n";
  }

  void ConcreteStateB::Handle2()
  {
    std::cout << "ConcreteStateB handles request2.\n";
    std::cout << "ConcreteStateB wants to change the state of the context.\n";
    this->context_->TransitionTo(new ConcreteStateA);
  }

  void ClientCode()
  {
    Context *context = new Context(new ConcreteStateA);
    context->Request1();
    context->Request2();
    delete context;
  }

  void run()
  {
    ClientCode();
  }
}