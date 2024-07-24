/*
让接口不兼容的对象能够相互合作.

是什么:
适配器模式是一种结构型设计模式， 它能使接口不兼容的对象能够相互合作。

为什么:
充电标准不一致,美国插头不能在德国插座上用,比如你的客户端传参数是json,微信支付接口是xml.

怎么做:
对象适配器: 通常来说都是客户端代码依赖提供功能的接口,具体的适配器依赖需要转换的对象,然后实现接口, 通过客户端通过接口调用就实现了对不兼容对象的调用.
类适配器: 有多继承的语言比如cpp,同时继承两个对象的接口.

*/

#ifndef DESIGN_PATTERNS_ADAPTER_H
#define DESIGN_PATTERNS_ADAPTER_H

#include <string>
namespace adapter
{
    class Target
    {
    public:
        virtual ~Target() = default;

        virtual std::string Request() const;
    };

    class Adaptee
    {
    public:
        std::string SpecificRequest() const;
    };

    class Adapter : public Target
    {
    private:
        Adaptee *adaptee_;

    public:
        Adapter(Adaptee *);
        std::string Request() const override;
    };

    void ClientCode(const Target *);
    void run();
}
#endif //DESIGN_PATTERNS_ADAPTER_H

/*
类适配器,多重继承实现
// The Target defines the domain-specific interface used by the client code.

class Target {
public:
    virtual ~Target() = default;
    virtual std::string Request() const {
        return "Target: The default target's behavior.";
    }
};

// The Adaptee contains some useful behavior, but its interface is incompatible
// with the existing client code. The Adaptee needs some adaptation before the
// client code can use it.
class Adaptee {
public:
    std::string SpecificRequest() const {
        return ".eetpadA eht fo roivaheb laicepS";
    }
};


// The Adapter makes the Adaptee's interface compatible with the Target's
// interface using multiple inheritance.

class Adapter : public Target, public Adaptee {
public:
    Adapter() {}
    std::string Request() const override {
        std::string to_reverse = SpecificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "Adapter: (TRANSLATED) " + to_reverse;
    }
};

// The client code supports all classes that follow the Target interface.
void ClientCode(const Target *target) {
    std::cout << target->Request();
}

int main() {
    std::cout << "Client: I can work just fine with the Target objects:\n";
    Target *target = new Target;
    ClientCode(target);
    std::cout << "\n\n";
    Adaptee *adaptee = new Adaptee;
    std::cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
    std::cout << "Adaptee: " << adaptee->SpecificRequest();
    std::cout << "\n\n";
    std::cout << "Client: But I can work with it via the Adapter:\n";
    Adapter *adapter = new Adapter;
    ClientCode(adapter);
    std::cout << "\n";

    delete target;
    delete adaptee;
    delete adapter;

    return 0;
}
*/
