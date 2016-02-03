#include<iostream>
#include"my_fractionlib.h"
using namespace std;

int main()
{
  my_mixnum b,a;
  int num,numerator,denominator;my_fraction fr;
//  try{
//  cout<<"1. my_mixnum a(int num=0, int numerator=0, int denominator=1) throw (zero_divide);"<<endl;
//   cin>>num>>numerator>>denominator;  a=my_mixnum(num,numerator,denominator);
//  cout<<"Результат "<<a<<endl;
//  } catch(zero_divide){cout<<"Результат "<<"Перехвачена ошибка деления на 0"<<endl;}
//
//  try{
//  cout<<"2. my_mixnum a(int num, my_fraction frac)throw (zero_divide);"<<endl;
//   cin>>num>>fr; a=my_mixnum(num,fr);
//  cout<<"Результат "<<a<<endl;
//  } catch(zero_divide){cout<<"Результат "<<"Перехвачена ошибка деления на 0"<<endl;}
//
//  cout<<"3. my_mixnum a(my_fraction);"<<endl;
//  cin>>fr; a=my_mixnum(fr);
//  cout<<"Результат "<<a<<endl;

    cout<<"3b. my_mixnum a(double);"<<endl;
  double d=0.3; my_fraction aa=my_fraction(d);
  cout<<"Результат "<<aa<<endl;


  cout<<"4. a.operator my_fraction() const;"<<endl;
  fr=a;
  cout<<"Результат "<<my_fraction(a)<<endl;

  cout<<"5. int a.getnum() const;"<<endl;
  cout<<"Результат "<<a.getnum()<<endl;

  cout<<"6. a.operator+=(my_mixnum& b);"<<endl;
  cin>>b;
  a+=b;
  cout<<"Результат "<<a<<endl;

  cout<<"7. a.operator-=(my_mixnum& b);"<<endl;
  cin>>b;
  a-=b;
  cout<<"Результат "<<a<<endl;


  cout<<"8.  a.operator*=(my_mixnum& b);"<<endl;
  cin>>b;
  a*=b;
  cout<<"Результат "<<a<<endl;

  try{
  cout<<"9. a.operator/=(my_mixnum& b) throw (zero_divide);"<<endl;
  cin>>b;
  a/=b;
  cout<<"Результат "<<a<<endl;
  } catch(zero_divide){cout<<"Результат "<<"Перехвачена ошибка деления на 0"<<endl;}

  cout<<"10. bool operator>(my_mixnum a,my_mixnum b);"<<endl;
  cin>>b;//bool is=a>b;
  cout<<"Результат "<<(a>b)<<endl;

  cout<<"11. bool operator<(my_mixnum a,my_mixnum b) ;"<<endl;
  cin>>b;
  cout<<"Результат "<<(a<b)<<endl;

  cout<<"12. my_mixnum operator-(my_mixnum& a) ;"<<endl;
  cin>>a;
  cout<<"Результат "<<-a<<endl;

  cout<<"13. my_mixnum abs_fract(my_mixnum a)  ;"<<endl;
  cin>>a;//a=abs_fract(a);
  cout<<"Результат  "<<abs_fract(a)<<endl;

  cout<<"15. my_mixnum operator+(my_mixnum a,my_mixnum b);"<<endl;
  cin>>b; //my_mixnum c=a+b;
  cout<<"Результат "<<a+b<<endl;

  cout<<"16. my_mixnum operator-(my_mixnum a,my_mixnum b);"<<endl;
  cin>>b;
  cout<<"Результат  "<<a-b<<endl;

  cout<<"17. my_mixnum operator*(my_mixnum a,my_mixnum b);"<<endl;
  cin>>b;
  cout<<"Результат  "<<a*b<<endl;
  try
  {
  cout<<"18. my_mixnum operator/(my_mixnum a,my_mixnum b) throw (zero_divide);"<<endl;
  cin>>b;
  cout<<"Результат  "<<a/b<<endl;
  } catch(zero_divide){cout<<"Результат "<<"Перехвачена ошибка деления на 0"<<endl;}

  cout<<"19. friend std::ostream& operator<<(std::ostream&,my_mixnum&);"<<endl;
  cin>>num>>numerator>>denominator;
  a= my_mixnum(num,numerator,denominator);
  cout<<"Результат  "<<a<<endl;

  cout<<"19. friend std::istream& operator>>(std::istream&,my_mixnum&);"<<endl;
  cin>>a;num=a.getnum();fr=a.getfract();
  cout<<"Результат  "<<num<<" "<<fr<<endl;
  return 0;
}





