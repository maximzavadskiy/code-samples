//#include "Expressions.h"
//#include "Calculator.h"
//#include <iostream>
//using namespace std;
//
//int main()
//{
//  Calculator calc;
//  AssigmentOperator oper(calc),oper2(calc);
//
//  //var=num
//  ExpressionVariable var1("a",calc);
//  ExpressionNumber num1(144);
//  cout<<"oper.calculate(var1,num1)="<<oper.calculate(var1,num1)<<"="<<"calc.get_var_value(""a"")=";
//  cout<<calc.get_var_value("a")<<endl;
//  //var=var
//  ExpressionVariable var2("b",calc);
//  cout<<"oper.calculate(var2,var1)="<<oper.calculate(var2,var1)<<"="<<"calc.get_var_value(""b"")=";
//  cout<<calc.get_var_value("b")<<endl;
//
//  //var=ComplexExpression
//  ExpressionNumber num2(-66);
//  ComplexExpression exp(num1.clone(),new AdditionOperator(),num2.clone());
//  cout<<"oper.calculate(var2,exp)="<<oper.calculate(var2,exp)<<"="<<"calc.get_var_value(""b"")=";
//  cout<<calc.get_var_value("b")<<endl;
//
//  //var=var=var
//  ExpressionVariable var3("c",calc),var4("d",calc);
//  ComplexExpression exp2(var3.clone(),new AssigmentOperator(calc),var1.clone());
//  cout<<"oper.calculate(var4,exp2)="<<oper.calculate(var4,exp2)<<"=";
//  cout<<"calc.get_var_value(""d"")="<<calc.get_var_value("d");
//  cout<<"="<<"calc.get_var_value(""c"")="<<calc.get_var_value("c")<<"="<<"calc.get_var_value(""a"")="<<calc.get_var_value("a");
//
//  //num=num
//  try
//  {
//    oper.calculate(num1,num2);
//  }
//  catch(system_error e)
//  {
//   cout<<endl<<e.what()<<endl;
//  }
//
//  //delete
//  AssigmentOperator* n_oper= oper.clone();
//  n_oper->calculate(var4,exp2);
//  delete n_oper;
//  return 0;
//}
