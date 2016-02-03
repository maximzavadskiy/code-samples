#ifndef _ADDITIONOPERATOR_H
#define _ADDITIONOPERATOR_H


#include "ExpressionBinaryOperator.h"
#include "Value.h"

class Expression;

class AdditionOperator : public ExpressionBinaryOperator
{
  public:
    //AdditionOperator();
    virtual Value calculate(Expression & left_op, Expression & right_op);
    virtual AdditionOperator* clone() const;
};
#endif
