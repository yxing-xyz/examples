#include "visitor.h"
#include <iostream>

namespace visitor
{
  Component::~Component() {}

  void ConcreteComponentA::Accept(Visitor *visitor) const
  {
    visitor->VisitConcreteComponentA(this);
  }

  std::string ConcreteComponentA::ExclusiveMethodOfConcreteComponentA() const
  {
    return "A";
  }

  void ConcreteComponentB::Accept(Visitor *visitor) const
  {
    visitor->VisitConcreteComponentB(this);
  }

  std::string ConcreteComponentB::SpecialMethodOfConcreteComponentB() const
  {
    return "B";
  }

  void ConcreteVisitor1::VisitConcreteComponentA(const ConcreteComponentA *element) const
  {
    std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor1\n";
  }

  void ConcreteVisitor1::VisitConcreteComponentB(const ConcreteComponentB *element) const
  {
    std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor1\n";
  }

  void ConcreteVisitor2::VisitConcreteComponentA(const ConcreteComponentA *element) const
  {
    std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor2\n";
  }

  void ConcreteVisitor2::VisitConcreteComponentB(const ConcreteComponentB *element) const
  {
    std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor2\n";
  }

  void ClientCode(std::array<const Component *, 2> components, Visitor *visitor)
  {
    // ...
    for (const Component *comp : components)
    {
      comp->Accept(visitor);
    }
    // ...
  }

  void run()
  {
    std::array<const Component *, 2> components = {new ConcreteComponentA, new ConcreteComponentB};
    std::cout << "The client code works with all visitors via the base Visitor interface:\n";
    ConcreteVisitor1 *visitor1 = new ConcreteVisitor1;
    ClientCode(components, visitor1);
    std::cout << "\n";
    std::cout << "It allows the same client code to work with different types of visitors:\n";
    ConcreteVisitor2 *visitor2 = new ConcreteVisitor2;
    ClientCode(components, visitor2);

    for (const Component *comp : components)
    {
      delete comp;
    }
    delete visitor1;
    delete visitor2;
  }
}
