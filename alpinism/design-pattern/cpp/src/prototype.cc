//
// Created by Jennica on 2016/12/28.
//

#include "prototype.h"
#include <iostream>
#include <string>

namespace prototype
{
    Prototype::Prototype() {}
    Prototype::~Prototype() {}
    void Prototype::Method(float prototype_field)
    {
        this->prototype_field_ = prototype_field;
        std::cout << "Call Method from " << prototype_name_ << " with field : " << this->prototype_field_ << std::endl;
    }
    Prototype *ConcretePrototype1::Clone() const
    {
        return new ConcretePrototype1(*this);
    }

    Prototype *ConcretePrototype2::Clone() const
    {
        return new ConcretePrototype2(*this);
    }

    PrototypeFactory::PrototypeFactory()
    {
        prototypes_[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1", 50.f);
        prototypes_[Type::PROTOTYPE_2] = new ConcretePrototype1("PROTOTYPE_2", 60.f);
    }
    PrototypeFactory::~PrototypeFactory()
    {
        delete prototypes_[Type::PROTOTYPE_1];
        delete prototypes_[Type::PROTOTYPE_2];
    }

    Prototype *PrototypeFactory::CreatePrototype(Type type)
    {
        return prototypes_[type]->Clone();
    }

    void Client(PrototypeFactory &prototype_factory)
    {
        std::cout << "let's create  Prototype 1" << std::endl;
        Prototype *prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
        prototype->Method(90);
        delete prototype;

        std::cout << "let's create  Prototype 2" << std::endl;

        prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
        prototype->Method(10);
        delete prototype;
    }

    void run()
    {
        PrototypeFactory *prototype_factory = new PrototypeFactory();
        Client(*prototype_factory);

        delete prototype_factory;
    }
}
