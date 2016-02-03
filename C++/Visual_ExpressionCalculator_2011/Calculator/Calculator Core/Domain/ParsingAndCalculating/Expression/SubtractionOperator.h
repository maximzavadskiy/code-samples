#ifndef _SUBTRACTIONOPERATOR_H
#define _SUBTRACTIONOPERATOR_H


#include "ExpressionBinaryOperator.h"
#include "Value.h"
#include "Errors.h"

class Expression;

class SubtractionOperator : public ExpressionBinaryOperator {
  public:
     SubtractionOperator();
     virtual Value calculate(Expression & left_op, Expression & right_op);
     virtual SubtractionOperator* clone() const;
};
#endif
