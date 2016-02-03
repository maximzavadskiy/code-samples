//#include "ExpressionHistory.h"
//#include "ComplexExpression.h"
//#include "ExpressionNumber.h"
//#include "AdditionOperator.h"
//#include "PreExpression.h"
//
//#include  <iostream>
//using
//namespace std;
//class A:public PreExpression
//{
//  public:
//  A()
//  {
//     static int d=1;
//     id=d;
//     d++;
//  }
//  string to_string(){return "";}
//  virtual A* clone() const {return new A(*this);}
//  int get_id()const {return id;}
//  int id;
//};
//
//
//int main()
//{
//  ExpressionHistory hist;
//  ExpressionNumber n2(1);
//  ExpressionNumber& n1=n2;
//  ExpressionNumber* n3=&n1;
//  A a1;
//  n3->calculate_answer();
//  hist.add(a1,*n3);
//  const Answer& ans=n3->get_answer();
//  cout<<ans.get_value()<<ans.get_format();
//  History h=hist.get_history();
//  while(!h.empty())
//  {
//    cout<<"source().get_id()="<<dynamic_cast<const A&>(h.top().source()).get_id()<<"answer.format="<<h.top().answer().get_format()<<" value="<<h.top().answer().get_value()<<endl ;
//    h.pop();
//  }
////  ExpressionNumber* n1 = new ExpressionNumber(1); A* a1 = new A;
////  ExpressionNumber* n2 = new ExpressionNumber(2); A* a2= new A;
////  ExpressionNumber* n3 = new ExpressionNumber(3); A* a3= new A;
////  ExpressionNumber* n4 = n1->clone();
////  A               * a4 = a1->clone();
////  hist.add(*a1,*n1);
////  n1->set_answer_format("double");
////  cout<<hist.get_curr_expression().get_answer().get_value()<<" "<<hist.get_curr_expression().get_answer().get_format()<<endl;
////  cout<<"n1: "; hist.add(*a2,*n2);
////  cout<<hist.get_curr_expression().get_answer().get_value()<<" "<<hist.get_curr_expression().get_answer().get_format()<<endl;
////  cout<<"n2: "; hist.add(*a3,*n3);
////  cout<<hist.get_curr_expression().get_answer().get_value()<<" "<<hist.get_curr_expression().get_answer().get_format()<<endl;
////  cout<<"n3: "; hist.add(*a3,*n1);
////  n1->set_answer_format("double");
////  cout<<hist.get_curr_expression().get_answer().get_value()<<" "<<hist.get_curr_expression().get_answer().get_format()<<endl;
////  delete a3;
////  cout<<"n1: "; hist.add(*a4,*n3);
////  n3->set_answer_format("double");
////  cout<<"n3: "; hist.add(*a1,*n2);
////  n2->set_answer_format("n2");
////
////  n4->set_answer_format("n4");
////  hist.add(*a4,*n4);
////  cout<<"------------";
////  cout<<hist.get_curr_expression().get_answer().get_value()<<" "<<hist.get_curr_expression().get_answer().get_format()<<endl;
////  History h=hist.get_history();
////  while(!h.empty()) {cout<<dynamic_cast<const A&>(h.top().source()).get_id()<<" "<<h.top().answer().get_value()<<" "<<h.top().answer().get_format()<<endl; h.pop();}
////  return 0;
//}
