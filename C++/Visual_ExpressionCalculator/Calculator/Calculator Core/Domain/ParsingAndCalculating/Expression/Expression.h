#ifndef _EXPRESSION_H
#define _EXPRESSION_H

#include "Errors.h"
#include "Value.h"
#include "Answer.h"
#include <string>
using namespace std;

class Expression
{
  public:
    Expression();
    virtual void        calculate_answer()               const;
    virtual const       Answer& get_answer()             const;
    virtual void        set_answer_format(string format);
    virtual bool        has_assigment_operator()         const;
    virtual Expression* clone()                          const=0;
  protected:
    virtual Value calculate_value() const= 0;
    mutable bool has_answer;
    mutable Answer ans;
};
#endif
