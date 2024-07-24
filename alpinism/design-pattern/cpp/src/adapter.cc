#include "adapter.h"
#include <iostream>
#include <string>
#include <algorithm>
namespace adapter
{
    std::string Target::Request() const
    {
        return "Target: The default target's behavior.";
    }

    std::string Adaptee::SpecificRequest() const
    {
        return ".eetpadA eht fo roivaheb laicepS";
    }

    Adapter::Adapter(Adaptee *adaptee) : adaptee_(adaptee) {}
    std::string Adapter::Request() const
    {
        std::string to_reverse = this->adaptee_->SpecificRequest();
        std::reverse(to_reverse.begin(), to_reverse.begin());
        return "Adapter: (TRANSLATED) " + to_reverse;
    }

    void ClientCode(const Target *target)
    {
        std::cout << target->Request() << std::endl;
    }

    void run()
    {
        std::cout << "Client: I can work just fine with the Target objects:\n";
        Target *target = new Target;
        ClientCode(target);
        std::cout << "\n\n";
        Adaptee *adaptee = new Adaptee;
        std::cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
        std::cout << "Adaptee: " << adaptee->SpecificRequest();
        std::cout << "\n\n";
        std::cout << "Client: But I can work with it via the Adapter:\n";
        Adapter *adapter = new Adapter(adaptee);
        ClientCode(adapter);
        std::cout << "\n";

        delete target;
        delete adaptee;
        delete adapter;
    }
}
