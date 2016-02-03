//#include "ComplexExpression.h"
//#include "ExpressionNumber.h"
//#include "AdditionOperator.h"
//
//#include  <iostream>
//
//using namespace std;
//
//int main()
//{
//  ExpressionNumber* n1=new ExpressionNumber(7);
//  ExpressionNumber* n3=new ExpressionNumber(3);
//  ExpressionNumber* n2=new ExpressionNumber(-7.7);
//  ExpressionNumber* n4=new ExpressionNumber(3);
//  AdditionOperator* op=new AdditionOperator();
//  AdditionOperator* op2=new AdditionOperator();
// AdditionOperator* op3=new AdditionOperator();
// ComplexExpression* num=new ComplexExpression(n1,op,n2);
//  Answer ans=num->get_answer();
//  num->calculate_answer();
//  ComplexExpression* num2=new ComplexExpression(n3,op2,n4);
//  ComplexExpression* num3=new ComplexExpression(num,op3,num2);
//  ComplexExpression* num4=num3->clone();
//
//  num2->calculate_answer();
//  num2->set_answer_format("fraction");
//  Answer ans2=num2->get_answer();
//  Answer ans3=num3->get_answer();
//  delete num3;
//  Answer ans4=num4->get_answer();
//  cout<<ans.get_value()<<" "<<ans.get_format()<<endl<<ans2.get_value()<<" "<<ans2.get_format()<<endl;
//  cout<<ans3.get_value()<<" "<<ans3.get_format()<<endl;
//  cout<<ans4.get_value()<<" "<<ans4.get_format()<<endl;
//  return 0;
//}
