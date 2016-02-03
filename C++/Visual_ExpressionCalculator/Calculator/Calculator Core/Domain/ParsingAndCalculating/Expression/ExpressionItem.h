#ifndef _EXPRESSIONITEM_H
#define _EXPRESSIONITEM_H


#include "Expression.h"

using namespace std;

class ExpressionItem : public Expression
{
  public:
    ExpressionItem* clone() const=0;
};
#endif
