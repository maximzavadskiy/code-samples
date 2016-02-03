#ifndef _VARIABLESET_H
#define _VARIABLESET_H

#include "Value.h"
#include "Variable.h"
#include <string>
#include <map>
using namespace std;


class VariableSet
{
  private:
    mutable map<string,Variable> vars;
  public:
    void set_var(string name, Value  value);
    Value get_var_value(string  name) const;
};
#endif
