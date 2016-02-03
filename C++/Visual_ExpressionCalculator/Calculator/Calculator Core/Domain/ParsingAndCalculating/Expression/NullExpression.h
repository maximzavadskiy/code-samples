#ifndef _NULLEXPRESSION_H
#define _NULLEXPRESSION_H


#include "Expression.h"
#include "Value.h"

class NullExpression : public Expression {
  public:
    NullExpression();
    virtual Expression* clone() const;
  protected:
    virtual Value calculate_value() const throw (ZeroDivide);
};
#endif
