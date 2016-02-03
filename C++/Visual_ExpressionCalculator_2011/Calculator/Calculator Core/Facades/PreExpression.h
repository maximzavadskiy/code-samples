#ifndef _PREEXPRESSION_H
#define _PREEXPRESSION_H


#include <string>
using namespace std;

class PreExpression
{
  public:
    virtual string to_string() const= 0;
    virtual PreExpression* clone() const=0;
};
#endif
