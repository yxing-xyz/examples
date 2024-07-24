/*
是什么:
解释器模式： 给定一个语言，定义它的文法的一种表示 并 定义一个解释器，这个解释器使用该表示文法 来解释语言中的句子。

为什么:
如果一种特定类型的问题发生的频率很高，那么可能就值得将该问题的各个实例表述为一个简单语言中的句子，这样就可以构建一个解释器，该解释器通过解释这些句子来解决该问题。
当一个语言需要解释执行，并且你可以将该语言中的句子表示为一个抽象语法树时，可使用解释器模式。



*/

#ifndef DESIGN_PATTERNS_INTERPRETER_H
#define DESIGN_PATTERNS_INTERPRETER_H

#include <iostream>
#include <map>
namespace interpreter
{

#include <iostream>
#include <map>

  /*
 * Context
 * contains information that's global to the interpreter
 */
  class Context
  {
  public:
    void set(const std::string &var, const bool value)
    {
      vars.insert(std::pair<std::string, bool>(var, value));
    }

    bool get(const std::string &exp)
    {
      return vars[exp];
    }
    // ...

  private:
    std::map<std::string, bool> vars;
    // ...
  };

  /*
 * Abstract Expression
 * declares an abstract Interpret operation that is common to all nodes
 * in the abstract syntax tree
 */
  class AbstractExpression
  {
  public:
    virtual ~AbstractExpression() {}

    virtual bool interpret(Context *const)
    {
      return false;
    }
    // ...
  };

  /*
 * Terminal Expression
 * implements an Interpret operation associated with terminal symbols
 * in the grammar (an instance is required for every terminal symbol
 * in a sentence)
 */
  class TerminalExpression : public AbstractExpression
  {
  public:
    TerminalExpression(const std::string &val) : value(val) {}

    ~TerminalExpression() {}

    bool interpret(Context *const context)
    {
      return context->get(value);
    }
    // ...

  private:
    std::string value;
    // ...
  };

  /*
 * Nonterminal Expression
 * implements an Interpret operation for nonterminal symbols
 * in the grammar (one such class is required for every rule in the grammar)
 */
  class NonterminalExpression : public AbstractExpression
  {
  public:
    NonterminalExpression(AbstractExpression *left, AbstractExpression *right) : lop(left), rop(right) {}

    ~NonterminalExpression()
    {
      delete lop;
      delete rop;
    }

    bool interpret(Context *const context)
    {
      return lop->interpret(context) && rop->interpret(context);
    }
    // ...

  private:
    AbstractExpression *lop;
    AbstractExpression *rop;
    // ...
  };
  void run()
  {
    // An example of very simple expression tree
    // that corresponds to expression (A AND B)
    AbstractExpression *A = new TerminalExpression("A");
    AbstractExpression *B = new TerminalExpression("B");
    AbstractExpression *exp = new NonterminalExpression(A, B);

    Context context;
    context.set("A", true);
    context.set("B", false);

    std::cout << context.get("A") << " AND " << context.get("B");
    std::cout << " = " << exp->interpret(&context) << std::endl;

    delete exp;
  }
}

#endif //DESIGN_PATTERNS_INTERPRETER_H
