#include <iostream>
#include <fstream>
#include <thread>

#include "factory_method.h"
#include "abstract_factory.h"
#include "builder.h"
#include "prototype.h"
#include "singleton.h"

#include "adapter.h"
#include "bridge.h"
#include "composite.h"
#include "decorator.h"
#include "facade.h"
#include "flyweight.h"
#include "proxy.h"

#include "chain_of_responsibility.h"
#include "command.h"
#include "iterator.h"
#include "mediator.h"
#include "memento.h"
#include "observer.h"
#include "state.h"
#include "strategy.h"
#include "template_method.h"
#include "visitor.h"
#include "interpreter.h"

int main(int argc, char *argv[])
{
    // facotry_method::run();            // 工厂模式
    // abstract_factory::run();          // 抽象工厂模式
    // builder::run();                   // 建筑模式
    // prototype::run();                 // 原型模式
    // singleton::run();                 // 单例模式

    // adapter::run();                   // 适配器模式
    // bridge::run();                    // 桥接模式
    // composite::run();                 // 组合模式
    // decorator::run();                 // 装饰器模式
    // facacde::run();                   // 外观模式(门面模式)
    // flyweight::run();                 // 享元模式
    // proxy::run();                     // 代理模式

    // chain_of_responsibility::run();   // 责任链模式
    // command::run();                   // 命令模式
    // iterator::run();                  // 迭代器模式
    // mediator::run();                  // 中介者模式
    // memento::run();                   // 备忘录模式
    // observer::Run();                  // 观察者模式 
    // state::run();                     // 状态模式
    // strategy::run();                  // 策略模式
    // template_method::run();           // 模板方法模式
    // visitor::run();                   // 访问者模式
    interpreter::run();                  // 解释器模式
}

/* 类图关系:

   泛化 = 实现 > 组合 > 聚合 > 关联 > 依赖

   1. 泛化(Generalization):
   形状: 带三角箭头的实线，箭头指向父类
   是一种继承关系,它指定了子类如何特化父类的所有特征和行为例如：老虎是动物的一种.

   2. 实现(Realization):
   形状: 带三角箭头的虚线，箭头指向接口
   是一种类与接口的关系，表示类是接口所有特征和行为的实现

   3. 关联(Association):
   形状: 带普通箭头的实心线，指向被拥有者
   是一种拥有的关系,它使一个类知道另一个类的属性和方法；如：老师与学生，丈夫与妻子关联可以是双向的，也可以是单向的。双向的关联可以有两个箭头或者没有箭头，单向的关联有一个箭头。
   代码: 丈夫和妻子成员变量互相拥有对方

   4. 聚合(Aggregation):
   形状: 带空心菱形的实心线，菱形指向整体
   是整体与部分的关系.如车和轮胎是整体和部分的关系.聚合关系是关联关系的一种，是强的关联关系；关联和聚合在语法上无法区分，必须考察具体的逻辑关系。
   代码: 车的成员变量List<轮胎>

   5. 组合(Composition):
   形状: 带实心菱形的实线，菱形指向整体
   是整体与部分的关系.没有公司就不存在部门,组合关系是关联关系的一种，是比聚合关系还要强的关系，它要求普通的聚合关系中代表整体的对象负责代表部分的对象的生命周期
   代码: 鸟的成员变量翅膀

   6. 依赖(Dependency)
   形状: 带箭头的虚线，指向被使用者
   是一种使用的关系,所以要尽量不使用双向的互相依赖。
   代码: 局部变量、方法的参数或者对静态方法的调用

*/

/* SOLID
单一职责原则The Single-Responsibility Principle (SRP): 一个类仅有一个引起它变化的原因。虽然这一原则明确是在说类的设计，但是实际中在一个模块或者一个方法上同样适用.
开放封闭原则The Open/Closed Principle (OCP): 开放闭合原则同样适用于类、模块和方法等，它强调对扩展开放，对修改闭合。看起来说了两点实际上就是一点：为了适应新的需求，尽量不要修改原始代码，而是扩展原有的代码。
里氏替换原则The Liskov Substitution Principle (LSP):子类型必须能够替换它的基类型。OCP的实现机制是抽象和多态，而它们的关键是继承。LSP所强调的就是继承的实现规则。
接口隔离原则The Interface Segregation Principle (ISP):客户端不应该被迫依赖于它不会用到的方法。
依赖导致原则he Dependency-Inversion Principle (DIP): 高层模块不应该依赖低层模块，两者都应该依赖其抽象；抽象不应该依赖细节，细节应该依赖于抽象。
 */
