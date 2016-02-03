#ifndef _MULTIPLICATIONOPERATOR_H
#define _MULTIPLICATIONOPERATOR_H


#include "ExpressionBinaryOperator.h"
#include "Value.h"

class Expression;

class MultiplicationOperator : public ExpressionBinaryOperator
{
  public:
    // MultiplicationOperator();
    virtual Value calculate( Expression & left_op,  Expression & right_op);
    virtual MultiplicationOperator* clone() const;
};
#endif
