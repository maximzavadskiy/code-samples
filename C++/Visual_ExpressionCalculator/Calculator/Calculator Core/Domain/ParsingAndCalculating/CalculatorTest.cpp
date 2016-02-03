//#include <iostream>
//using namespace std;
//#include "Calculator.h"
//#include "Expressions.h"
//#include "PreExpression.h"
//
//class A:public PreExpression
//{
//  public:
//  A()
//  {
//     static int d=1;
//     id=d;
//     d++;
//  }
//  string to_string()const{return "";}
//  virtual A* clone() const {return new A(*this);}
//  int get_id()const {return id;}
//  int id;
//};
//
//
//int main()
//{
//  cout<<"Consructor&destr TEST....."<<endl<<endl;
//  Calculator* c=new Calculator();
//  delete c;
//  cout<<"OK"<<endl<<"-------------------------------------------------------------------------"<<endl;
//
//  cout<<"Calculating TEST.....(calculate & get)"<<endl<<endl;
//  A a;
//  Calculator calc;
//  ComplexExpression exp
//  (new ComplexExpression(new ExpressionNumber(1),new AdditionOperator(),new ExpressionNumber(2)),
//  new MultiplicationOperator(),
//  new ExpressionNumber(3));
//  calc.set_expression(&a,&exp);
//  calc.calculate_answer();
// cout<<"Answer expected: format=mixnum value=9#1"<<endl<<"Answer result: format="<<calc.get_answer().get_format()<<" value="<<calc.get_answer().get_value()<<endl;
//  if(calc.get_answer().get_format()=="mixnum"&&calc.get_answer().get_value()==9) cout<<" -------MATCH";
//  else cout<<"-----MISMATCH.....ERROR!!!";
//
//  cout<<endl<<"-------------------------------------------------------------------------"<<endl;
//
//  cout<<" set_answer(fraction) TEST....."<<endl<<endl;
//  calc.set_answer_format("fraction");
//  cout<<"Answer expected: format=fraction value=9#1"<<endl<<"Answer result: format="<<calc.get_answer().get_format()<<" value="<<calc.get_answer().get_value()<<endl;
//  if(calc.get_answer().get_format()=="fraction"&&calc.get_answer().get_value()==9) cout<<" -------MATCH";
//  else cout<<"-----MISMATCH.....ERROR!!!";
//
//cout<<endl<<"-------------------------------------------------------------------------"<<endl;
//
//  cout<<" History TEST....."<<endl<<endl;
//  History h=calc.get_expressions_history();
//  cout<<endl<<"size="<<h.size()<<endl;
//  cout<<"History expected: source().get_id()=1 answer.format=fraction answer.value=9#1 ";
//  cout<<endl<<"History result: ";
//  while(!h.empty())
//  {
//    cout<<"source().get_id()="<<dynamic_cast<const A&>(h.top().source()).get_id()<<"answer.format="<<h.top().answer().get_format()<<" value="<<h.top().answer().get_value()<<endl ;
//    h.pop();
//  }
//  h=calc.get_expressions_history();
//  cout<<endl;
//  if(h.size()==1&&dynamic_cast<const A&>(h.top().source()).get_id()==1&&h.top().answer().get_format()=="fraction"&&h.top().answer().get_value()==9) cout<<" -------MATCH";
//  else cout<<"-----MISMATCH.....ERROR!!!";
//
//  cout<<endl<<"-------------------------------------------------------------------------"<<endl;
//
//  cout<<"Calculating TEST.....(just get_answer)"<<endl<<endl;
//  A a2;
//  Expression* exp2=exp.clone();
//  calc.set_expression(&a2,exp2);
//  calc.set_answer_format("fraction");
//  cout<<"Answer expected: format=mixnum value=9#1"<<endl<<"Answer result: format="<<calc.get_answer().get_format()<<" value="<<calc.get_answer().get_value();
//  cout<<endl;
//  if(calc.get_answer().get_format()=="mixnum"&&calc.get_answer().get_value()==9) cout<<" -------MATCH";
//  else cout<<"-----MISMATCH.....ERROR!!!";
//
//  cout<<endl<<"-------------------------------------------------------------------------"<<endl;
//
//  cout<<" History  afer two calculatings TEST....."<<endl<<endl;
//  h=calc.get_expressions_history();
//  cout<<"History expected: 1) source().get_id()=2 answer.format=mixnum answer.value=9#1"<<endl<<"2) source().get_id()=1 answer.format=fraction answer.value=9# ";
//  cout<<endl<<"History result: ";
//  int i=1;
//  while(!h.empty())
//  {
//    cout<<i<<") source().get_id()="<<dynamic_cast<const A&>(h.top().source()).get_id()<<"answer.format="<<h.top().answer().get_format()<<" value="<<h.top().answer().get_value()<<endl;
//    h.pop();
//    i++;
//  }
//  h=calc.get_expressions_history();
//  bool ok=h.size()==2&&dynamic_cast<const A&>(h.top().source()).get_id()==2&&h.top().answer().get_format()=="mixnum"&&h.top().answer().get_value()==9;
//  h.pop();
//  cout<<endl;
//  if(ok&&dynamic_cast<const A&>(h.top().source()).get_id()==1&&h.top().answer().get_format()=="fraction"&&h.top().answer().get_value()==9)cout<<" -------MATCH";
//  else cout<<"-----MISMATCH.....ERROR!!!";
//
//  cout<<endl<<"-------------------------------------------------------------------------"<<endl;
//
//  cout<<"Calculating TEST with AssigmentOperator&ExpressionVariable....."<<endl<<endl;
//
//  ComplexExpression* exp3=
//  new ComplexExpression
//  (
//    new ComplexExpression
//    (
//      new ExpressionNumber(5),
//      new MultiplicationOperator(),
//      new ComplexExpression
//      (
//        new ExpressionVariable("var",calc),
//        new AssigmentOperator(calc),
//        new ComplexExpression
//        (
//          new ExpressionNumber(2),
//          new AdditionOperator(),
//          new ExpressionNumber(1)
//        )
//      )
//    ),
//    new AdditionOperator(),
//    new ExpressionVariable("var",calc)
//  );
//
//  calc.set_expression(&a,exp3);
//  calc.calculate_answer();
//
//  cout<<"Answer expected: format=mixnum value=18#1"<<endl<<"Answer result: format="<<calc.get_answer().get_format()<<" value="<<calc.get_answer().get_value();
//  cout<<endl;
//  if(calc.get_answer().get_format()=="mixnum"&&calc.get_answer().get_value()==18) cout<<" -------MATCH";
//  else cout<<"-----MISMATCH.....ERROR!!!";
//
//
//  cout<<endl<<"-------------------------------------------------------------------------"<<endl;
//
//  cout<<"set_var--get_var_value TEST....."<<endl<<endl;
//  calc.set_var("a",6.7);
//  calc.set_var("b",-8);
//  cout<<"vars expected: a=6.7 b=-8 c(unset)=0"<<endl;
//  cout<<"vars result: a="<<calc.get_var_value("a")<<" b="<<calc.get_var_value("b")<<" c="<<calc.get_var_value("c");
////  cout<<"vars result: a="<<calc.get_var_value("a")<<" b="<<calc.get_var_value("b")<<" c="<<calc.get_var_value("c");
//  cout<<endl;
//  if(calc.get_var_value("a")==Value(6.7)&&calc.get_var_value("b")==-8&&calc.get_var_value("c")==0) cout<<" -------MATCH";
//  else cout<<"-----MISMATCH.....ERROR!!!";
//  return 0;
//}
