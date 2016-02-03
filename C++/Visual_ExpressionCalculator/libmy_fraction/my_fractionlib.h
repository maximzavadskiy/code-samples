#ifndef MY_FRACTION
  #define MY_FRACTION

  #include <stdexcept>
  #include <string>
  #include <sstream>
  #include <cstdlib>
  #include <cmath>
  #include <iostream>
  #include "my_regexlib.h"
  class zero_divide : public std::exception{};
  /*----------------------my_fraction----------------------*/
  class my_mixnum;
  class my_fraction
  {
  private:
    friend class my_mixnum;//получение доступа к private части my_fraction из my_mixnum
    long long numerator;
    long long denominator;
  public:
    my_fraction(long long num=0,long long den=1) throw(zero_divide);
    my_fraction(my_mixnum);
    my_fraction(long double);
    my_fraction(double d){*this=my_fraction((long double)(d));}
    my_fraction(int d){*this=my_fraction((long long)(d));};

    //operator long long() const;
    //operator long double() const;
    long long make_int() const;
    long double make_double() const;
    //operator my_mixnum() const;

    my_fraction& contract();

    my_fraction& operator+=(my_fraction);
    my_fraction& operator-=(my_fraction);
    my_fraction& operator*=(my_fraction);
    my_fraction& operator/=(my_fraction) throw(zero_divide);

    long long getnumerator() const;
    long long getdenominator() const;
    bool is_int(){contract();return(getdenominator()==1||getnumerator()==0);}

    friend void make_common_denominator(my_fraction&,my_fraction&);

    friend std::ostream& operator<<(std::ostream&,const my_fraction&);
    friend std::istream& operator>>(std::istream&,my_fraction&);
  };

  my_fraction operator+(my_fraction ,my_fraction);
  my_fraction operator-(my_fraction ,my_fraction);
  my_fraction operator*(my_fraction, my_fraction);
  my_fraction operator/(my_fraction, my_fraction) throw(zero_divide);

  bool operator>(my_fraction,long long);
  bool operator>(my_fraction,int );
  bool operator>(my_fraction, my_fraction);

  bool operator<(my_fraction,long long);
  bool operator<(my_fraction, my_fraction);
 // bool operator<(my_fraction a,int b) {return a<my_fraction(b);}

  bool operator==(my_fraction,long long);
  bool operator==(const my_fraction&,const my_fraction&);

  bool operator!=(my_fraction,long long);
  bool operator!=(const my_fraction&,const my_fraction&);

  my_fraction operator-(const my_fraction&) ;
  my_fraction abs_fract(const my_fraction&) ;

  /*---------------------my_mixnum----------------------*/

  class my_mixnum
  {
  private:
    friend class my_fraction;//получение доступа к private части my_mixnum из my_fraction
    long long number;       //целая часть
    my_fraction fract;//дробная часть
    void make_correct_fraction();
  public:
    my_mixnum(long long num=0, long long numerator=0, long long denominator=1) throw (zero_divide);
    my_mixnum(long long num, my_fraction frac)                     throw (zero_divide);

    my_mixnum(my_fraction);
    //operator my_fraction() const;

    long long getnum() const;
    my_fraction getfract() const;

    my_mixnum& operator+=(const my_mixnum&);
    my_mixnum& operator-=(const my_mixnum&);
    my_mixnum& operator*=(const my_mixnum&);
    my_mixnum& operator/=(const my_mixnum&) throw (zero_divide);

    friend std::ostream& operator<<(std::ostream&,const my_mixnum&);
    friend std::istream& operator>>(std::istream&,my_mixnum&);
  };

  my_mixnum abs_fract(const my_mixnum& );
  my_mixnum operator-(const my_mixnum& ) ;

  my_mixnum operator+(const my_mixnum& , const my_mixnum& );
  my_mixnum operator-(const my_mixnum& , const my_mixnum& );
  my_mixnum operator*(const my_mixnum& , const my_mixnum& );
  my_mixnum operator/(const my_mixnum& , const my_mixnum& ) throw (zero_divide);

#endif

