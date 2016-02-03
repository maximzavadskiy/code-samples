#ifndef _ASSIGMENTOPERATOR_H
#define _ASSIGMENTOPERATOR_H


#include "ExpressionBinaryOperator.h"
#include "Value.h"

class Expression;
class Calculator;

class AssigmentOperator : public ExpressionBinaryOperator
{
  public:
    virtual Value calculate( Expression & left_op,  Expression & right_op);
    AssigmentOperator(Calculator & calc);
    AssigmentOperator* clone() const;
  private:
    Calculator& calculator;
};
#endif
