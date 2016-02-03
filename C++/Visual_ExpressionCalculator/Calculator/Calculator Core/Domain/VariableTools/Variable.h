#ifndef _VARIABLE_H
#define _VARIABLE_H


#include "Value.h"
#include <string>
using namespace std;

class Variable {
  private:
    string name;
    Value value;
  public:
    Variable( string name="unnamed",Value val=0) ;
    Value get_value() const;
    string get_name() const;
};
#endif
