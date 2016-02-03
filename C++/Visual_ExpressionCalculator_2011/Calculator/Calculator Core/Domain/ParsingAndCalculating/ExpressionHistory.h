#ifndef _EXPRESSIONSHISTORY_H
#define _EXPRESSIONSHISTORY_H
#include <stack>
#include "Expression.h"
#include "PreExpression.h"
#include <utility>
#include "system_error.h"
using namespace std;



class ExpressionHistory;
//struct ExpressionHistory::history_res;

//################################################
//ATTENTION!!! Do not add() one Expression twice!!!!
//################################################

class ExpressionHistory// problems with memory
{
public:

  struct history_res
  {
    history_res(const PreExpression& s,const Answer& a);
     const PreExpression& source(){return *_source;}
//    const ExpressionHistory::history_res&   operator=(const ExpressionHistory::history_res&);
       const Answer&   answer(){return *_answer;}
     private:
       const Answer* _answer;
       const PreExpression*  _source;
  };

  typedef stack<ExpressionHistory::history_res> History;
  ExpressionHistory();
  ~ExpressionHistory();

  void add(const PreExpression& pe, const Expression&  exp);
  const Expression& get_curr_expression() throw (system_error);
  History get_history() const;
private:
  typedef stack<pair< const PreExpression*,const Expression*> > _History;
  Expression const* curr_exp;
  _History hist;
};
typedef stack<ExpressionHistory::history_res> History;
#endif
