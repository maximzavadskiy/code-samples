#ifndef _EXPRESSIONOPERATOR_H
#define _EXPRESSIONOPERATOR_H


class ExpressionOperator
{
  public:
    virtual ExpressionOperator* clone() const=0;
};
#endif
