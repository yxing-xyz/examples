#include "command.h"
#include <iostream>
namespace command
{
  Command::~Command()
  {
  }

  void Command::Execute() const {}

  SimpleCommand::SimpleCommand(std::string pay_load) : pay_load_(pay_load)
  {
  }

  void SimpleCommand::Execute() const
  {
    std::cout << "SimpleCommand: See, I can do simple things like printing (" << this->pay_load_ << ")\n";
  }

  void Receiver::DoSomething(const std::string &a)
  {
    std::cout << "Receiver: Working on (" << a << ".)\n";
  }

  void Receiver::DoSomethingElse(const std::string &b)
  {
    std::cout << "Receiver: Also working on (" << b << ".)\n";
  }

  ComplexCommand::ComplexCommand(Receiver *receiver, std::string a, std::string b) : receiver_(receiver), a_(a), b_(b)
  {
  }

  void ComplexCommand::Execute() const
  {
    std::cout << "ComplexCommand: Complex stuff should be done by a receiver object.\n";
    this->receiver_->DoSomething(this->a_);
    this->receiver_->DoSomethingElse(this->b_);
  }

  Invoker::~Invoker()
  {
    delete on_start_;
    delete on_finish_;
  }

  void Invoker::SetOnStart(Command *command)
  {
    this->on_start_ = command;
  }

  void Invoker::SetOnFinish(Command *command)
  {
    this->on_finish_ = command;
  }
  void Invoker::DoSomethingImportant()
  {
    std::cout << "Invoker: Does anybody want something done before I begin?\n";
    if (this->on_start_)
    {
      this->on_start_->Execute();
    }
    std::cout << "Invoker: ...doing something really important...\n";
    std::cout << "Invoker: Does anybody want something done after I finish?\n";
    if (this->on_finish_)
    {
      this->on_finish_->Execute();
    }
  }
  void run()
  {

    Invoker *invoker = new Invoker;
    invoker->SetOnStart(new SimpleCommand("Say Hi!"));
    Receiver *receiver = new Receiver;
    invoker->SetOnFinish(new ComplexCommand(receiver, "Send email", "Save report"));
    invoker->DoSomethingImportant();

    delete invoker;
    delete receiver;
  }
}
