
#include "ExpressionHistory.h"
#include <iostream>
using namespace std;

ExpressionHistory::history_res::history_res(const PreExpression& s,const Answer& a):_source(&s),_answer(&a){}
//const ExpressionHistory::history_res&   ExpressionHistory::history_res::operator=(const history_res& h)
//{
//  const_cast<PreExpression&>(_source)=const_cast<PreExpression&>(h._source);
//  const_cast<Answer&>(_answer)=const_cast<Answer&>(h._answer);
//  return *this;
//}

ExpressionHistory::ExpressionHistory()
{
  curr_exp=NULL;
}

ExpressionHistory::~ExpressionHistory()
{
  //delete curr_exp;

  if(!hist.empty())
  {
    delete hist.top().first;
    hist.pop();
  }
  //a hist.top().first то  указатель на ссылку!!!
  while(!hist.empty())
  {
    delete hist.top().first;
    delete hist.top().second;
    hist.pop();
  }
}

void ExpressionHistory::add( const PreExpression& pe,const Expression&  exp)
{
// FIXME (maxim#1#): неоптимально
  //if(curr_exp!=NULL) delete curr_exp;  if(!hist.empty()) hist.top().second=curr_exp->clone();//сохроняю в истории  выражение, которое больше не будет изменяться
  curr_exp=&exp;
  PreExpression* pre_exp=pe.clone();
  hist.push(make_pair(pre_exp,curr_exp));
}

const Expression& ExpressionHistory::get_curr_expression() throw (system_error)
{
  if(curr_exp==NULL) throw system_error("there is no current expression yet!");
  return *curr_exp;
}

History ExpressionHistory::get_history() const
{
  History history;
  _History buf=hist;
//while(!buf.empty()) {cout<<buf.top().second->get_answer().get_value()<<" "<<buf.top().second->get_answer().get_format()<<endl; buf.pop();}
 // buf=hist;
  History buf_2;

  while(!buf.empty())
  {
    buf_2.push(history_res(*buf.top().first,buf.top().second->get_answer()));
    buf.pop();
  }

  while(!buf_2.empty())
  {
    history.push(history_res(buf_2.top().source(),buf_2.top().answer()));
    buf_2.pop();
  }
  return history;
}
