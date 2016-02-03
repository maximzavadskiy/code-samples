#include <wx/object.h>
#include <wx/statline.h>
#include <wx/dcclient.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/msgdlg.h>

#include <vector>
#include <typeinfo>
#include <algorithm>
#include <ctype.h>
#include "my_regexlib.h"

#define  EXP-CLASSES_H


/*#ifndef CALCULATORMAIN_H
  #define CALCULATORMAIN_H
  #include"CalculatorMain.h"
#endif*/
struct ans{
    wxStaticText* s;
    wxStaticLine* l;
    wxTextCtrl* den;
    wxTextCtrl* num;
    wxTextCtrl* n;
    void clear()
    {
      delete s;s=NULL;
      delete l;l=NULL;
      delete num;num=NULL;
      delete den;den=NULL;
      delete n;n=NULL;
    }
};


struct size
{
  int w;int h;
  size(int _w=0,int _h=0):w(_w),h(_h){}
};

struct point
{
  int x;int y;
  point(int _x=0,int _y=0):x(_x),y(_y){}
  //point(double  _x=0,double _y=0):x(_x),y(_y){}
  point(wxPoint p):x(p.x),y(p.y){}
  void operator=(wxPoint p){x=p.x;y=p.y;}
};

class debug_err     :public std::exception
{
  private:
    std::string  error;
  public:
    debug_err (std::string mes):error(mes) {}
    ~debug_err() throw() {}
    virtual const char* what() const throw() { return error.c_str(); }
};

class FractCtrl;

class FractCtrlItem
{
  protected:
  #ifdef __WXMSW__
    static const int bit=8;
  #endif
  #ifdef __UNIX__
    static const int bit=4;
  #endif
  public:
    FractCtrl* parent;

    virtual ~FractCtrlItem(){};
    virtual size get_size() const=0;
    virtual point get_location() const=0;
    virtual wxPoint get_wx_location() const=0;
    virtual std::string get_str_val() const=0;
    virtual bool has_fraction()const {return false;}

    virtual void SetActive()=0;
    virtual void SetEndActive()=0;
    virtual void SetStrVal(wxString)=0;

    virtual FractCtrl* get_bottom_item(const FractCtrl* ) const;
    virtual FractCtrl* get_top_item(const FractCtrl* ) const;

    virtual void redraw(point)throw (debug_err)   =0;
    virtual void OnChildrenChanged()throw (debug_err)=0;
};

class TextCtrlItem:public FractCtrlItem, private wxEvtHandler
{
    wxPaintDC* dc;
  public:
    wxTextCtrl* textctrl;
    TextCtrlItem(FractCtrl* par,point=point(-1,-1),wxString text=_(""))throw (debug_err);
    ~TextCtrlItem();

    void redraw(point)throw  (debug_err);


  size get_size() const;
  point get_location() const;
  wxPoint get_wx_location() const;
  std::string get_str_val() const;

  void SetActive();
  void SetEndActive();
  void SetOptimalSize();
  void SetStrVal(wxString);

  void ShowBorder();
  void HideBorder();


  void OnChildrenChanged()throw (debug_err);
  void OnChar(wxKeyEvent& )throw (debug_err);
  void OnMouseClick(wxMouseEvent& )throw (debug_err);
  void OnTextEvent(wxCommandEvent& )throw (debug_err);
};

class FractCtrl
{
  private:
    static const int bit=5;
    point loc;
    bool check()const;
  public:
    std::vector<FractCtrlItem*> Items;
    FractCtrlItem* parent;

    FractCtrl(FractCtrlItem*,point=point(-1,-1) ,wxString=_("") )throw (debug_err);
    FractCtrl(FractCtrlItem* p,wxString s=_("")){FractCtrl(p,point(-1,-1),s);}
    ~FractCtrl();

    point get_location() const;
    wxPoint get_wx_location() const;
    size get_size()const;
    void redraw(point)throw (debug_err);

    void insert(TextCtrlItem*,FractCtrlItem* )throw (debug_err);
    void insert_in_Items(const FractCtrlItem* ,FractCtrlItem* )throw (debug_err);

    void DelRightItem(TextCtrlItem*) throw (debug_err);
    void DelLeftItem (TextCtrlItem*) throw (debug_err);
    void AddBracketItem (TextCtrlItem*) throw (debug_err);
    void AddFractionItem( TextCtrlItem*) throw (debug_err);

    void SetActive()const;
    void SetEndActive()const;

    FractCtrl*   get_bottom_item(const FractCtrlItem*) const;
    FractCtrl*     get_top_item   (const FractCtrlItem*) const;
    FractCtrlItem* get_prev_item  (FractCtrlItem* ) const;
    FractCtrlItem* get_next_item  (FractCtrlItem* )  const;
    std::string get_str_val();

    bool has_fraction()const;

    void OnChildrenChanged(FractCtrlItem* loc)throw (debug_err);
};

class BracketItem:public FractCtrlItem
{
    wxStaticText* l_bracket;
    wxStaticText* r_bracket;
    FractCtrl* fractctrl;
  public:
    BracketItem(FractCtrl*,wxString=_(""))throw (debug_err);
    ~BracketItem();

    size get_size() const;
    point get_location() const;
    wxPoint get_wx_location() const;
    void redraw(point)throw (debug_err);

    std::string get_str_val() const;

    bool has_fraction()const;

    void SetActive();
    void SetEndActive();
    void SetStrVal(wxString);

   void OnChildrenChanged()throw (debug_err);
};

class FractionItem: public FractCtrlItem
{
  wxStaticLine* line;
  int line_width;
public:
  FractCtrl* numerator;
  FractCtrl* denominator;
  FractionItem(FractCtrl* ,wxString=_("")) throw (debug_err);
  ~FractionItem() throw (debug_err);

  point get_location() const ;
  wxPoint get_wx_location() const;
  size get_size() const;
  void redraw(point loc) throw(debug_err);

  std::string get_str_val() const;

  bool has_fraction()const;

  void SetActive();
  void SetEndActive();
  void SetStrVal(wxString);

  FractCtrl* get_bottom_item(const FractCtrl* loc) const;
  FractCtrl* get_top_item   (const FractCtrl* loc) const;

  void OnChildrenChanged() throw (debug_err);
};
