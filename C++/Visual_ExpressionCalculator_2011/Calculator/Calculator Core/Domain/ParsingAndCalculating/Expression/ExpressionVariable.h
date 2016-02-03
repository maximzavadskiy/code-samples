#ifndef _EXPRESSIONVARIABLE_H
#define _EXPRESSIONVARIABLE_H

#include "ExpressionItem.h"
#include "Value.h"
#include <string>
using namespace std;

class Calculator;

class ExpressionVariable : public ExpressionItem
{
  public:
    ExpressionVariable(string _name,const Calculator& calc);
    virtual string get_name()const;
    ExpressionVariable* clone() const;
  protected:
    virtual Value calculate_value() const ;
  private:
    string name;
    const Calculator& calculator;
};
#endif
