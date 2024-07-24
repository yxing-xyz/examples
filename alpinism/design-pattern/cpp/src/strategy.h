/*
是什么:
策略模式是一种行为设计模式， 它能让你定义一系列算法， 并将每种算法分别放入独立的类中， 以使算法的对象能够相互替换。

为什么:
一天， 你打算为游客们创建一款导游程序。 该程序的核心功能是提供美观的地图， 以帮助用户在任何城市中快速定位。
用户期待的程序新功能是自动路线规划： 他们希望输入地址后就能在地图上看到前往目的地的最快路线。
程序的首个版本只能规划公路路线。 驾车旅行的人们对此非常满意。 但很显然， 并非所有人都会在度假时开车。 因此你在下次更新时添加了规划步行路线的功能。 此后， 你又添加了规划公共交通路线的功能。
而这只是个开始。 不久后， 你又要为骑行者规划路线。 又过了一段时间， 你又要为游览城市中的所有景点规划路线。
尽管从商业角度来看， 这款应用非常成功， 但其技术部分却让你非常头疼： 每次添加新的路线规划算法后， 导游应用中主要类的体积就会增加一倍。 终于在某个时候， 你觉得自己没法继续维护这堆代码了。
无论是修复简单缺陷还是微调街道权重， 对某个算法进行任何修改都会影响整个类， 从而增加在已有正常运行代码中引入错误的风险。
此外， 团队合作将变得低效。 如果你在应用成功发布后招募了团队成员， 他们会抱怨在合并冲突的工作上花费了太多时间。 在实现新功能的过程中， 你的团队需要修改同一个巨大的类， 这样他们所编写的代码相互之间就可能会出现冲突。

怎么做:
1. 从上下文类中找出修改频率较高的算法 （也可能是用于在运行时选择某个算法变体的复杂条件运算符）。
2. 声明该算法所有变体的通用策略接口。
3. 将算法逐一抽取到各自的类中， 它们都必须实现策略接口。
4. 在上下文类中添加一个成员变量用于保存对于策略对象的引用。 然后提供设置器以修改该成员变量。 上下文仅可通过策略接口同策略对象进行交互， 如有需要还可定义一个接口来让策略访问其数据。
5. 客户端必须将上下文类与相应策略进行关联， 使上下文可以预期的方式完成其主要工作。
*/

#ifndef DESIGN_PATTERNS_STRATEGY_H
#define DESIGN_PATTERNS_STRATEGY_H

#include <string>
#include <vector>
namespace strategy
{
  class Strategy
  {
  public:
    virtual ~Strategy();
    virtual std::string DoAlgorithm(const std::vector<std::string> &) const = 0;
  };

  class Context
  {
  private:
    Strategy *strategy_;

  public:
    Context(Strategy * = nullptr);
    ~Context();
    void set_strategy(Strategy *);
    void DoSomeBusinessLogic() const;
  };

  class ConcreteStrategyA : public Strategy
  {
    std::string DoAlgorithm(const std::vector<std::string> &) const override;
  };

  class ConcreteStrategyB : public Strategy
  {
    std::string DoAlgorithm(const std::vector<std::string> &) const override;
  };

  void ClientCode();
  void run();
}

#endif //DESIGN_PATTERNS_STRATEGY_H
