#include"my_fractionlib.h"
#define debug

  /*=========================== my_fraction ===========================*/
  long long NOD(long long a,long long b)
  {
    if((a%b)==0) return b;
    return NOD(b,a%b);
  }

  my_fraction::my_fraction(long long num,long long den) throw(zero_divide)
   {
    if(den!=0)
    {
      if(den<0 && num>=0)
      {
        den=-den;
        num=-num;
      }
      if(den<0 && num<0){den=-den;num=-num;}
      numerator=num;
      denominator=den;
      contract();
      return;
    }
    else throw zero_divide();
  }

  my_fraction::my_fraction(long double a)
  {
    std::ostringstream oss;
    oss.setf(std::ios_base::fixed);
    oss << a;
    std::string str(oss.str());
    my_regex doub("^([+-]?[0-9]+)(\\.)?([0-9]*)$");
    if(doub.match(str))
    {
      std::string num_str = doub.get_match(3);
      denominator = static_cast<long long>(pow(10.0f, static_cast<long long>(num_str.length())));
//      std::cout<<"doub.get_match(0).c_str() "<<doub.get_match(0).c_str()<<std::endl;
//      std::cout<<"doub.get_match(1).c_str() "<<doub.get_match(1).c_str()<<std::endl;
//      std::cout<<"doub.get_match(2).c_str() "<<doub.get_match(2).c_str()<<std::endl;
//      std::cout<<"doub.get_match(3).c_str() "<<doub.get_match(3).c_str()<<std::endl;
     if(atoi(doub.get_match(1).c_str())>=0) numerator   = atoi(doub.get_match(1).c_str())*denominator+atoi(num_str.c_str());
      else numerator   = atoi(doub.get_match(1).c_str())*denominator-atoi(num_str.c_str());
    }

    contract();
  }


  my_fraction::my_fraction(my_mixnum a)
  {
    *this=my_fraction(a.fract.getnumerator()+a.number*a.fract.getdenominator(),a.fract.getdenominator());
  }


  long long my_fraction::make_int()const{return numerator/denominator;}

  long double my_fraction:: make_double()const { return (long double)(numerator)/(long double)(denominator);}

 // my_fraction::operator my_mixnum() const {return my_mixnum(0,*this);}





  long long my_fraction::getnumerator()const{return numerator;}

  long long my_fraction::getdenominator()const{return denominator;}



  my_fraction& my_fraction::contract()
  {
    if(numerator==0) {denominator=1; return *this;}
    long long nod=NOD(abs(numerator),abs(denominator));//чтобы не поменять знаки при делении ниже
    numerator=numerator/nod;
    denominator=denominator/nod;
    return *this;
  }



  void make_common_denominator (my_fraction& a,my_fraction& b)
  {
    my_fraction buffer=a;
    a.denominator=a.denominator*b.denominator;
    a.numerator=a.numerator*b.denominator;

    b.denominator=b.denominator*buffer.denominator;
    b.numerator=b.numerator*buffer.denominator;
  }



  my_fraction& my_fraction::operator+=(my_fraction a)
  {
    make_common_denominator(*this,a);
    numerator=numerator+a.numerator;
    contract();
    return *this;
  }

  my_fraction& my_fraction::operator-=(my_fraction a)
  {
    make_common_denominator(*this,a);
    numerator=numerator-a.numerator;
    contract();
    return *this;
  }

  my_fraction& my_fraction::operator*=(my_fraction a)
  {
    my_fraction c(numerator*a.numerator,denominator*a.denominator);
    *this=c;
    return *this;
  }

  my_fraction& my_fraction::operator/=(my_fraction a) throw(zero_divide)
  {
    if(a.numerator==0) throw zero_divide();
    long long bufer=a.numerator;
    a.numerator=a.denominator;
    a.denominator=bufer;
    *this*=a;
    return *this;
  }





  /*******************************************************************************************/


  my_fraction operator+(my_fraction a, my_fraction b){return a+=b;}


  my_fraction operator-(my_fraction a, my_fraction b){return a-=b;}


  my_fraction operator*(my_fraction a, my_fraction b){return a*=b;;}


  my_fraction operator/(my_fraction a, my_fraction b) throw (zero_divide)
  {
    try{ return a/=b; } catch(zero_divide){ throw; }
  }


  bool operator<(my_fraction a,my_fraction b)
  {
    make_common_denominator(a,b);
    return a.getnumerator()<b.getnumerator();
  }
  bool operator<(my_fraction a,long long b)
  {
    return a<my_fraction(b);
  }

  bool operator>(my_fraction a,my_fraction b)
  {
    make_common_denominator(a,b);
    return a.getnumerator()>b.getnumerator();
  }
  bool operator>(my_fraction a,long long b)
  {
    return  a>my_fraction(b);
  }

  bool operator==(const my_fraction& a,const my_fraction& b)
  {
    return not ( (a>b) || (a<b) );
  }
  bool operator==(my_fraction a,long long b)
  {
    return  a==my_fraction(b);
  }

  bool operator!=(const my_fraction& a,const my_fraction& b)
  {
    return not (a==b);
  }
  bool operator!=(my_fraction a,long long b)
  {
    return a!=my_fraction(b);
  }

  my_fraction operator-(const my_fraction& a)
  {
    my_fraction b(-a.getnumerator(),a.getdenominator());
    return b;
  }

  my_fraction abs_fract(const my_fraction& a)
  {
    if(a<my_fraction(0)) return -a;
    return a;
  }


  std::istream& operator>>(std::istream& a, my_fraction& b)
  {
    long long nu,de;
    a>>nu>>de;
    b=my_fraction(nu,de);
    return a;
  }

  std::ostream& operator<<(std::ostream& a,const my_fraction& b)
  {
    if(b.numerator==0) a<<0;
    else a<<b.numerator<<'#'<<b.denominator;
    return a;
  }

  /*=========================== my_mixnum ===========================*/

  void my_mixnum::make_correct_fraction()
  {
    number+=fract.getnumerator() / fract.getdenominator();
    fract.numerator=fract.getnumerator() % fract.getdenominator();
    if(
        (  (getnum()<0) && (getfract()>my_fraction(0) )  )
        ||
        (  (getnum()>0) && (getfract()<my_fraction(0) )  )
      )//если разные знаки
    {
      *this=fract+my_fraction(number);// явно вызываю my_fraction(number)чтобы было преобразование num в my_fraction а не fract в int
    }
  }

  my_mixnum::my_mixnum(long long num, long long numerator, long long denominator) throw (zero_divide)
  {
    fract=my_fraction(numerator,denominator);
    number=num;

    if(num<0) fract=-fract;
    fract.contract();
    make_correct_fraction();
  }

  my_mixnum::my_mixnum(long long num, my_fraction frac)                  throw (zero_divide)
  {
    fract=frac;
    number=num;

    if(num<0) fract=-fract;
    fract.contract();
    make_correct_fraction();
  }

  my_mixnum::my_mixnum(my_fraction frac)
  {
     *this=my_mixnum(0,frac);
  }

  /*my_mixnum::operator my_fraction() const
  {
    return my_fraction(fract.getnumerator()+number*fract.getdenominator(),fract.getdenominator());
  }*/


  long long my_mixnum::getnum() const
  {
    return number;
  }

  my_fraction my_mixnum::getfract() const
  {
    return fract;
  }





  my_mixnum& my_mixnum::operator+=(const my_mixnum& a)
  {
    *this=*this/a;
    return *this;
  }
  my_mixnum& my_mixnum::operator-=(const my_mixnum& a)
  {
    *this=*this/a;
    return *this;
  }

  my_mixnum& my_mixnum::operator*=(const my_mixnum& a)
  {
    *this=*this*a;
    return *this;
  }

  my_mixnum& my_mixnum::operator/=(const my_mixnum& a) throw (zero_divide)
  {
    *this=*this/a;
    return *this;
  }




  /*****************************************************************************/

  //может быть можно будет сравнивать с помощью  bool operator>(my_fraction a,my_fraction b)
  // bool operator>(my_mixnum,my_mixnum){}

  //может быть можно будет сравнивать с помощью  bool operator<(my_fraction a,my_fraction b)
  //  bool operator<(my_mixnum,my_mixnum){}

  my_mixnum abs_fract(const my_mixnum& a){return abs_fract(my_fraction(a));} ;
  my_mixnum operator-(const my_mixnum& a){return -my_fraction(a);} ;


  my_mixnum operator+(const my_mixnum& a, const my_mixnum& b){ return my_fraction(a)+my_fraction(b); };

  my_mixnum operator-(const my_mixnum& a, const my_mixnum& b){ return my_fraction(a)-my_fraction(b); };

  my_mixnum operator*(const my_mixnum& a, const my_mixnum& b){ return my_fraction(a)*my_fraction(b); };

  my_mixnum operator/(const my_mixnum& a, const my_mixnum& b) throw (zero_divide){ return my_fraction(a)/my_fraction(b); };



  std::ostream& operator<<(std::ostream& a,const my_mixnum& b)
  {
    my_fraction out=-b.fract;

    if(b!=0)
    {
      if(b.number!=0) a<<b.number;
      if(b.fract!=my_fraction(0))
      {
        if(b.number<0) a<<" "<<out;
        else       a<<" "<<b.fract;
      }
    }
    else a<<0;
    return a;
  }

  std::istream& operator>>(std::istream& a,my_mixnum& b)
  {
    long long n; my_fraction f;
    a>>n>>f;
    b=my_mixnum(n,f);
    return a;
  }


