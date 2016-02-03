#ifndef _DIVISIONOPERATOR_H
#define _DIVISIONOPERATOR_H


#include "ExpressionBinaryOperator.h"
#include "Value.h"
#include "Errors.h"

class Expression;

class DivisionOperator : public ExpressionBinaryOperator {
  public:
    DivisionOperator();
    virtual Value calculate( Expression & left_op, Expression & right_op) throw (ZeroDivide);
    virtual DivisionOperator* clone() const;
};
#endif
