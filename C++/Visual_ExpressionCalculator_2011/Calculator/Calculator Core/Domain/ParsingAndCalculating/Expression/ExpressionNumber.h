#ifndef _EXPRESSIONNUMBER_H
#define _EXPRESSIONNUMBER_H


#include "Value.h"
#include  "ExpressionItem.h"

class ExpressionNumber : public ExpressionItem
{
  public:
    ExpressionNumber(Value  val);
    virtual ExpressionNumber* clone() const;
  protected:
    virtual Value calculate_value() const throw(ZeroDivide);
  private:
    Value value;
};
#endif
