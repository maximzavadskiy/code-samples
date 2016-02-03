////#define DEBUG
//#include "ExpressionVariable.h"
//#include  <iostream>
//#include  "Calculator.h"
//#include  "Answer.h"
//using namespace std;
//
//int main()
//{
//  Calculator calc;
//  calc.set_var("a",1);
//
//  ExpressionVariable a("a",calc);
//  ExpressionVariable b("b",calc);
//  ExpressionVariable* b2=b.clone();
//  calc.set_var("b",-2);
//  calc.get_var_value("b");
//    a.calculate_answer();
//  b.calculate_answer();
//  b2->calculate_answer();
//    b2->set_answer_format("b2");
//  cout<<"ExpressionVariable a: name="<<a.get_name()<<"  "<<a.get_answer()<<endl<<"ExpressionVariable b: name="<<b.get_name()<<"  "<<b.get_answer()<<endl<<"ExpressionVariable b2: name="<<b2->get_name()<<"  "<<b2->get_answer();
//  return 0;
//}
