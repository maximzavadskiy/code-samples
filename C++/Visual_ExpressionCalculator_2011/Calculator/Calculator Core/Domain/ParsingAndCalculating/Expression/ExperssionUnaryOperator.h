#ifndef _EXPERSSIONUNARYOPERATOR_H
#define _EXPERSSIONUNARYOPERATOR_H


#include "Value.h"

class ExperssionUnaryOperator : public ExpressionOperator {
  public:
    virtual Value calculate(const Expression & a);

};
#endif
