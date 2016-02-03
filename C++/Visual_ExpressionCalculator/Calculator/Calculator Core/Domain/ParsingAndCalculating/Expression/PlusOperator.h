#ifndef _PLUSOPERATOR_H
#define _PLUSOPERATOR_H


#include "ExperssionBinaryOperator.h"

class PlusOperator : public ExperssionBinaryOperator {
  public:
    virtual Value calculate();

};
#endif
