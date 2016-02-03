#ifndef _COMPLEXEXPRESSION_H
#define _COMPLEXEXPRESSION_H


#include "Expression.h"
#include "Value.h"
#include "ExpressionBinaryOperator.h"


class ComplexExpression : public Expression {

  public:
    ComplexExpression(Expression* left_op, ExpressionBinaryOperator* bin_operator, Expression* right_op);
    ~ComplexExpression();
    virtual ComplexExpression* clone() const;
    virtual Value calculate_value() const throw(ZeroDivide);
    bool has_assigment_operator() const;
  protected:
    Expression* left_operand;
    Expression* right_operand;
    ExpressionBinaryOperator* binary_operator;
};
#endif
