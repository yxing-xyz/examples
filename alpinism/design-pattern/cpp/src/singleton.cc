//
// Created by Jennica on 2016/12/28.
//

#include "singleton.h"
#include <mutex>
#include <string>
#include <mutex>
#include <thread>
#include <iostream>

namespace singleton
{
    Singleton *Singleton::GetInstance(const std::string &value)
    {
        // 双重判断+互斥锁: 提高性能减少,减少锁力度
        if (pinstance_ == nullptr)
        {
            // 构造函数加锁, 析构函数解锁
            std::lock_guard<std::mutex> lock(mutex_);
            if (pinstance_ == nullptr)
            {
                pinstance_ = new Singleton(value);
            }
        }
        return pinstance_;
    }
    std::string Singleton::value() const
    {
        return value_;
    }

    // 静态成员初始化必须在类外初始化
    Singleton *Singleton::pinstance_ = nullptr;
    std::mutex Singleton::mutex_;

    void ThreadFoo()
    {
        // Following code emulates slow initialization.
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        Singleton *singleton = Singleton::GetInstance("FOO");
        std::cout << singleton->value() << "\n";
    }

    void ThreadBar()
    {
        // Following code emulates slow initialization.
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        Singleton *singleton = Singleton::GetInstance("BAR");
        std::cout << singleton->value() << "\n";
    }
    void run()
    {
        std::cout << "If you see the same value, then singleton was reused (yay!\n"
                  << "If you see different values, then 2 singletons were created (booo!!)\n\n"
                  << "RESULT:\n";
        std::thread t1(ThreadFoo);
        std::thread t2(ThreadBar);
        t1.join();
        t2.join();
    }
}
