/*
让你能给保证一个类只有一个实例,并提供一个访问该实例的全局节点

是什么:
单例模式是一种创建型设计模式， 让你能够保证一个类只有一个实例， 并提供一个访问该实例的全局节点。

为什么:
1.如果程序中的某个类对于所有客户端只有一个可用的实例， 可以使用单例模式。
2.如果你需要更加严格地控制全局变量， 可以使用单例模式。

怎么做:
1.在类中添加一个私有静态成员变量用于保存单例实例。
2.声明一个公有静态构建方法用于获取单例实例。
3.在静态方法中实现"延迟初始化"。 该方法会在首次被调用时创建一个新对象， 并将其存储在静态成员变量中。 此后该方法每次被调用时都返回该实例。
4.将类的构造函数设为私有。 类的静态方法仍能调用构造函数， 但是其他对象不能调用。

*/

#ifndef DESIGN_PATTERNS_SINGLETON_H
#define DESIGN_PATTERNS_SINGLETON_H
#include <mutex>
#include <string>
namespace singleton
{
    class Singleton
    {
    private:
        static Singleton *pinstance_;
        static std::mutex mutex_;

    protected:
        std::string value_;
        Singleton(const std::string value) : value_(value) {}

    public:
        // 关闭编译器默认的拷贝构造函数,防止产生多个实例
        Singleton(const Singleton &) = delete;
        // 关闭编译器默认的赋值运算符重载, 防止产生多个实例
        void operator=(const Singleton &) = delete;

        static Singleton *GetInstance(const std::string &);
        void SomeBusinessLogic();

        std::string value() const;
    };

    void ThreadFoo();
    void ThreadBar();
    void run();
}

#endif //DESIGN_PATTERNS_SINGLETON_H
