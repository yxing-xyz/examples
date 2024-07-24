
#include "bridge.h"
#include <iostream>
#include <string>
namespace bridge
{
  Implementation::~Implementation() {}

  std::string ConcreteImplementationA::OperationImplementation() const
  {
    return "ConcreteImplementationA: Here's the result on the platform A.\n";
  }

  std::string ConcreteImplementationB::OperationImplementation() const
  {
    return "ConcreteImplementationB: Here's the result on the platform B.\n";
  }

  Abstraction::Abstraction(Implementation *implementation) : implementation_(implementation)
  {
  }
  Abstraction::~Abstraction() {}
  std::string Abstraction::Operation() const
  {
    return "Abstraction: Base operation with:\n" +
           this->implementation_->OperationImplementation();
  }
  ExtendedAbstraction::ExtendedAbstraction(Implementation *implementation) : Abstraction(implementation)
  {
  }

  std::string ExtendedAbstraction::Operation() const
  {
    return "ExtendedAbstraction: Extended operation with:\n" +
           this->implementation_->OperationImplementation();
  }

  void ClientCode(const Abstraction &abstraction)
  {
    // ...
    std::cout << abstraction.Operation();
    // ...
  }

  void run()
  {
    Implementation *implementation = new ConcreteImplementationA;
    Abstraction *abstraction = new Abstraction(implementation);
    ClientCode(*abstraction);
    std::cout << std::endl;
    delete implementation;
    delete abstraction;

    implementation = new ConcreteImplementationB;
    abstraction = new ExtendedAbstraction(implementation);
    ClientCode(*abstraction);

    delete implementation;
    delete abstraction;
  }
}
