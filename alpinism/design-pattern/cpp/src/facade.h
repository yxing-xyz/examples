/*
能为程序库, 框架或其他复杂类提供简单的接口
是什么:
外观模式是一种结构型设计模式， 能为程序库、 框架或其他复杂类提供一个简单的接口。

为什么:
假设你必须在代码中使用某个复杂的库或框架中的众多对象。 正常情况下， 你需要负责所有对象的初始化工作、 管理其依赖关系并按正确的顺序执行方法等。
最终， 程序中类的业务逻辑将与第三方类的实现细节紧密耦合， 使得理解和维护代码的工作很难进行。
外观类为包含许多活动部件的复杂子系统提供一个简单的接口。 与直接调用子系统相比， 外观提供的功能可能比较有限， 但它却包含了客户端真正关心的功能。
如果你的程序需要与包含几十种功能的复杂库整合， 但只需使用其中非常少的功能， 那么使用外观模式会非常方便，
例如， 上传猫咪搞笑短视频到社交媒体网站的应用可能会用到专业的视频转换库， 但它只需使用一个包含 encode­(filename, format)方法 （以文件名与文件格式为参数进行编码的方法） 的类即可。 在创建这个类并将其连接到视频转换库后， 你就拥有了自己的第一个外观。

怎么做:
1. 考虑能否在现有子系统的基础上提供一个更简单的接口。 如果该接口能让客户端代码独立于众多子系统类， 那么你的方向就是正确的。
2. 在一个新的外观类中声明并实现该接口。 外观应将客户端代码的调用重定向到子系统中的相应对象处。 如果客户端代码没有对子系统进行初始化， 也没有对其后续生命周期进行管理， 那么外观必须完成此类工作。
3. 如果要充分发挥这一模式的优势， 你必须确保所有客户端代码仅通过外观来与子系统进行交互。 此后客户端代码将不会受到任何由子系统代码修改而造成的影响， 比如子系统升级后， 你只需修改外观中的代码即可。
4. 如果外观变得过于臃肿， 你可以考虑将其部分行为抽取为一个新的专用外观类。

*/

#ifndef DESIGN_PATTERNS_FACADE_H
#define DESIGN_PATTERNS_FACADE_H
#include <string>

namespace facacde
{
    class Subsystem1
    {
    public:
        std::string Operation1() const;
        std::string OperationN() const;
    };

    class Subsystem2
    {
    public:
        std::string Operation1() const;
        std::string OperationZ() const;
    };

    class Facade
    {
    protected:
        Subsystem1 *subsystem1_;
        Subsystem2 *subsystem2_;

    public:
        Facade(Subsystem1 * = nullptr, Subsystem2 * = nullptr);
        virtual ~Facade();
        std::string Operation() const;
    };

    void ClientCode(Facade *);
    void run();
}

#endif //DESIGN_PATTERNS_FACADE_H
