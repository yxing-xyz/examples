//
// Created by Jennica on 2016/12/29.
//

#include "facade.h"
#include <iostream>

namespace facacde
{
    std::string Subsystem1::Operation1() const
    {
        return "Subsystem1: Ready!\n";
    }

    std::string Subsystem1::OperationN() const
    {
        return "Subsystem1: Go!\n";
    }

    std::string Subsystem2::Operation1() const
    {
        return "Subsystem2: Get ready!\n";
    }

    std::string Subsystem2::OperationZ() const
    {
        return "Subsystem2: Fire!\n";
    }

    Facade::Facade(Subsystem1 *subsystem1, Subsystem2 *subsystem2)
    {
        this->subsystem1_ = subsystem1 ?: new Subsystem1();
        this->subsystem2_ = subsystem2 ?: new Subsystem2();
    }
    Facade::~Facade()
    {
        delete this->subsystem1_;
        delete this->subsystem2_;
    }
    std::string Facade::Operation() const
    {
        std::string result = "Facade initializes subsystems:\n";
        result += this->subsystem1_->Operation1();
        result += this->subsystem2_->Operation1();
        result += "Facade orders subsystems to perform the action:\n";
        result += this->subsystem1_->OperationN();
        result += this->subsystem2_->OperationZ();
        return result;
    }
    void ClientCode(Facade *facade)
    {
        std::cout << facade->Operation() << std::endl;
    }
    void run()
    {
        Subsystem1 *subsystem1 = new Subsystem1;
        Subsystem2 *subsystem2 = new Subsystem2;
        Facade *facade = new Facade(subsystem1, subsystem2);
        ClientCode(facade);

        delete facade;
    }
}
