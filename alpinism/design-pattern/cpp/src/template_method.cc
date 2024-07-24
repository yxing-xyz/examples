//
// Created by Jennica on 2017/1/3.
//

#include "template_method.h"
#include <iostream>

namespace template_method
{
  void AbstracClass::TemplateMethod() const
  {
    this->BaseOperation1();
    this->RequiredOperations1();
    this->BaseOperation2();
    this->Hook1();
    this->RequiredOperation2();
    this->BaseOperation3();
    this->Hook2();
  }

  void AbstracClass::BaseOperation1() const
  {
    std::cout << "AbstractClass says: I am doing the bulk of the work\n";
  }
  void AbstracClass::BaseOperation2() const
  {
    std::cout << "AbstractClass says: But I let subclasses override some operations\n";
  }

  void AbstracClass::BaseOperation3() const
  {
    std::cout << "AbstractClass says: But I am doing the bulk of the work anyway\n";
  }

  void AbstracClass::Hook1() const
  {
  }
  void AbstracClass::Hook2() const
  {
  }

  void ConcreteClass1::RequiredOperations1() const
  {
    std::cout << "ConcreteClass1 says: Implemented Operation1\n";
  }

  void ConcreteClass1::RequiredOperation2() const
  {
    std::cout << "ConcreteClass1 says: Implemented Operation2\n";
  }

  void ConcreteClass2::RequiredOperations1() const
  {
    std::cout << "ConcreteClass2 says: Implemented Operation1\n";
  }

  void ConcreteClass2::RequiredOperation2() const
  {
    std::cout << "ConcreteClass2 says: Implemented Operation2\n";
  }

  void ConcreteClass2::Hook1() const
  {
    std::cout << "ConcreteClass2 says: Overridden Hook1\n";
  }

  void ClientCode(AbstracClass *class_)
  {
    class_->TemplateMethod();
  }
  void run()
  {
    std::cout << "Same client code can work with different subclasses:\n";
    ConcreteClass1 *concreteClass1 = new ConcreteClass1;
    ClientCode(concreteClass1);
    std::cout << "\n";
    std::cout << "Same client code can work with different subclasses:\n";
    ConcreteClass2 *concreteClass2 = new ConcreteClass2;
    ClientCode(concreteClass2);
    delete concreteClass1;
    delete concreteClass2;
  }
}
