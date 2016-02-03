//#define DEBUG

#include"my_regexlib.h"
#include <string>
#include <vector>
using namespace std;

class ExpressionBinaryOperator;
class ExpressionItem;
class Calculator;

class ItemsFinder
{
public:
  virtual bool match(string exp);//заменять " " на "[:space:]"
  virtual string get_rest();
  virtual void set_item(const string name, const my_regex& reg)=0;
  virtual ~ItemsFinder(){};
protected:
  string rest;
  vector<pair<string,string> > item_patterns;
};

class OperatorsFinder: public ItemsFinder
{
  public:
    OperatorsFinder();
    virtual ExpressionBinaryOperator& get_matched_operator();
    virtual ~OperatorsFinder();
  protected:
   ExpressionBinaryOperator* matched_operator;
};


class OperandsFinder: public ItemsFinder
{
  public:
    OperandsFinder(Calculator& calc);
    virtual ~OperandsFinder();
    virtual ExpressionItem& get_matched_operand();
    //set_item должна конструировать с помощью виртуальных конструкторов
  protected:
    virtual void set_item(const string name,const my_regex& reg);
  private:
    ExpressionItem* matched_operand;
    Calculator& calculator;
};



class ThirdPriorityOperatorsFinder:public OperatorsFinder
{
  public:
    ThirdPriorityOperatorsFinder();
    virtual void set_item(const string name,const my_regex& reg);
};

class SecondPriorityOperatorsFinder:public OperatorsFinder
{
  public:
    SecondPriorityOperatorsFinder();
    virtual void set_item(string name,const my_regex& reg);
};

// class FirstPriorityOperatorsFinder
// {
//   public;
//     FirstPriorityOperatorsFinder()
//     {
//     }
//
//     bool match(string exp);
//     string get_rest();
//     ExpressionOperator get_matched_operator();
// };

