/*
摒弃了每个对象中保存所有数据的方式, 通过共享多个对象所共有的相同状态, 让你能在有限的内存容量中载入更多的对象.

是什么:
享元模式是一种结构型设计模式， 它摒弃了在每个对象中保存所有数据的方式， 通过共享多个对象所共有的相同状态， 让你能在有限的内存容量中载入更多对象。

为什么:
假如你希望在长时间工作后放松一下， 所以开发了一款简单的游戏： 玩家们在地图上移动并相互射击。 你决定实现一个真实的粒子系统， 并将其作为游戏的特色。 大量的子弹、 导弹和爆炸弹片会在整个地图上穿行， 为玩家提供紧张刺激的游戏体验。

开发完成后， 你推送提交了最新版本的程序， 并在编译游戏后将其发送给了一个朋友进行测试。 尽管该游戏在你的电脑上完美运行， 但是你的朋友却无法长时间进行游戏： 游戏总是会在他的电脑上运行几分钟后崩溃。 在研究了几个小时的调试消息记录后， 你发现导致游戏崩溃的原因是内存容量不足。 朋友的设备性能远比不上你的电脑， 因此游戏运行在他的电脑上时很快就会出现问题。

真正的问题与粒子系统有关。 每个粒子 （一颗子弹、 一枚导弹或一块弹片） 都由包含完整数据的独立对象来表示。 当玩家在游戏中鏖战进入高潮后的某一时刻， 游戏将无法在剩余内存中载入新建粒子， 于是程序就崩溃了。

仅在程序必须支持大量对象且没有足够的内存容量时使用享元模式:
1. 程序需要生成数量巨大的相似对象, 消耗大量的内存
2. 对象中包含可抽取且能在多个对象间共享的重复状态。


怎么做:
1. 将需要改写为享元的类成员变量拆分为两个部分：
内在状态： 包含不变的、 可在许多对象中重复使用的数据的成员变量。
外在状态： 包含每个对象各自不同的情景数据的成员变量

2. 保留类中表示内在状态的成员变量， 并将其属性设置为不可修改。 这些变量仅可在构造函数中获得初始数值。

3. 找到所有使用外在状态成员变量的方法， 为在方法中所用的每个成员变量新建一个参数， 并使用该参数代替成员变量。

4. 你可以有选择地创建工厂类来管理享元缓存池， 它负责在新建享元时检查已有的享元。 如果选择使用工厂， 客户端就只能通过工厂来请求享元， 它们需要将享元的内在状态作为参数传递给工厂。

5. 客户端必须存储和计算外在状态 （情景） 的数值， 因为只有这样才能调用享元对象的方法。 为了使用方便， 外在状态和引用享元的成员变量可以移动到单独的情景类中。

*/
#ifndef DESIGN_PATTERNS_FLYWEIGHT_H
#define DESIGN_PATTERNS_FLYWEIGHT_H
#include <iostream>
#include <unordered_map>
namespace flyweight
{
  class flyweightFactory;

  class SharedState
  {
  private:
    std::string brand_;
    std::string model_;
    std::string color_;
    friend std::ostream &operator<<(std::ostream &, const SharedState &);

  public:
    friend class FlyweightFactory;
    SharedState(const std::string &, const std::string &, const std::string &);
  };

  class UniqueState
  {
  private:
    std::string owner_;
    std::string plates_;
    friend std::ostream &operator<<(std::ostream &, const UniqueState &);

  public:
    UniqueState(const std::string &, const std::string &);
  };

  class Flyweight
  {
  private:
    SharedState *shared_state_;

  public:
    Flyweight(const SharedState *);

    Flyweight(const Flyweight &);

    ~Flyweight();

    SharedState *shared_state() const;

    void Operation(const UniqueState &) const;
  };

  class FlyweightFactory
  {
  private:
    std::unordered_map<std::string, Flyweight> flyweights_;
    std::string GetKey(const SharedState &) const;

  public:
    FlyweightFactory(std::initializer_list<SharedState>);
    Flyweight GetFlyweight(const SharedState &);
    void ListFlyweights() const;
  };

  void AddCarToPoliceDatabase(FlyweightFactory &, const std::string &, const std::string &,
                              const std::string &, const std::string &, const std::string &);
  void run();
}

#endif //DESIGN_PATTERNS_FLYWEIGHT_H
