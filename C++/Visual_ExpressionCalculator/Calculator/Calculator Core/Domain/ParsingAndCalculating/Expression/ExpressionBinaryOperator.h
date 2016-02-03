#ifndef _EXPERSSIONBINARYOPERATOR_H
#define _EXPERSSIONBINARYOPERATOR_H


#include "ExpressionOperator.h"
#include "Value.h"
class Expression;

class ExpressionBinaryOperator : public ExpressionOperator
{
  public:
   //операнды вычислять в строгой последовательности: сначала left_op потом right_op , вычисляя в разных инструкциях
    virtual Value calculate(Expression & left_op, Expression & right_op)=0;
    virtual ExpressionBinaryOperator* clone() const=0;
};
#endif
