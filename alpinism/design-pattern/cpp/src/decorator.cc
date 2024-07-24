#include "decorator.h"
#include <iostream>

namespace decorator
{
    Component::~Component() {}

    std::string ConcreteComponent::Operation() const
    {
        return "ConcreteComponent";
    }

    Decorator::Decorator(Component *component) : component_(component)
    {
    }

    std::string Decorator::Operation() const
    {
        return this->component_->Operation();
    }

    ConcreteDecoratorA::ConcreteDecoratorA(Component *component) : Decorator(component)
    {
    }

    ConcreteDecoratorA::~ConcreteDecoratorA()
    {
    }

    std::string ConcreteDecoratorA::Operation() const
    {
        return "ConcreteDecoratorA(" + Decorator::Operation() + ")";
    }

    ConcreteDecoratorB::ConcreteDecoratorB(Component *component) : Decorator(component)
    {
    }

    ConcreteDecoratorB::~ConcreteDecoratorB()
    {
    }

    std::string ConcreteDecoratorB::Operation() const
    {
        return "ConcreteDecoratorB(" + Decorator::Operation() + ")";
    }

    void ClientCode(Component *component)
    {
        // ...
        std::cout << "RESULT: " << component->Operation();
        // ...
    }
    void run()
    {
        Component *simple = new ConcreteComponent;
        std::cout << "Client: I've got a simple component:\n";
        ClientCode(simple);
        std::cout << "\n\n";
        /**
         * ...as well as decorated ones.
         *
         * Note how decorators can wrap not only simple components but the other
         * decorators as well.
         */
        Component *decorator1 = new ConcreteDecoratorA(simple);
        Component *decorator2 = new ConcreteDecoratorB(decorator1);
        std::cout << "Client: Now I've got a decorated component:\n";
        ClientCode(decorator2);
        std::cout << "\n";

        delete simple;
        delete decorator1;
        delete decorator2;
    }
}
