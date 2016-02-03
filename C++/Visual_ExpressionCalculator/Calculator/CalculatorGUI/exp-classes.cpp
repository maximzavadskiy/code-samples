#ifndef EXP-CLASSES_H
  #define EXP-CLASSES_H
  #include "exp-classes.h"
#endif

/*extern class CalculatorFrame;
extern  CalculatorFrame* Curr_Frame;*/

#ifndef CALCULATORMAIN_H
  #define CALCULATORMAIN_H
  #include"CalculatorMain.h"
#endif


//-------------class FractCtrlItem---------------------------
FractCtrl* FractCtrlItem::get_top_item(const FractCtrl* loc) const
{
  return parent->get_top_item(this);
}

FractCtrl*   FractCtrlItem::get_bottom_item(const FractCtrl* loc) const
{
  return parent->get_bottom_item(this);
}

//-------------class TextCtrlItem---------------------------
TextCtrlItem::TextCtrlItem(FractCtrl* par,point p ,wxString text)throw (debug_err)
{
  parent=par;
  textctrl=new wxTextCtrl(/*CalculatorFrame::*/CalculatorFrame::Panel, wxNewId(),text, wxDefaultPosition,wxDefaultSize,wxNO_BORDER|wxTE_CENTRE|wxTE_PROCESS_ENTER);
  if(p.x!=-1&&p.y!=-1) textctrl->Move(p.x,p.y-textctrl->GetSize().GetHeight()/2);
  textctrl->Connect(textctrl->GetId(),wxEVT_LEFT_DOWN,wxMouseEventHandler(TextCtrlItem::OnMouseClick),NULL,this);
  textctrl->Connect(textctrl->GetId(),wxEVT_KEY_DOWN,wxKeyEventHandler(TextCtrlItem::OnChar),NULL,this);
  textctrl->Connect(textctrl->GetId(),wxEVT_COMMAND_TEXT_UPDATED,wxCommandEventHandler(TextCtrlItem::OnTextEvent),NULL,this);

  CalculatorFrame::ActiveCtrl=this;

  SetOptimalSize();
}


TextCtrlItem::~TextCtrlItem()
{
  delete textctrl;
}

size TextCtrlItem::get_size() const
{
  return size(textctrl->GetSize().GetWidth(),textctrl->GetSize().GetHeight());
}

point TextCtrlItem::get_location() const
{
  return  point(textctrl->GetPosition().x,textctrl->GetPosition().y+get_size().h/2);
}

wxPoint TextCtrlItem::get_wx_location() const
{
  return textctrl->GetPosition();
}

std::string TextCtrlItem::get_str_val() const
{
  return std::string(textctrl->GetLineText(0).mb_str(wxConvLocal));
}

void TextCtrlItem::SetActive()
{
  textctrl->SetFocus();
  textctrl->SetSelection(1,1);
  textctrl->SetInsertionPoint(0);
  CalculatorFrame::ActiveCtrl=this;
}
void TextCtrlItem::SetEndActive()
{
  textctrl->SetFocus();
  textctrl->SetSelection(1,1);
  textctrl->SetInsertionPointEnd();
  CalculatorFrame::ActiveCtrl=this;
}
void TextCtrlItem::SetStrVal(wxString s)
{
 // wxMessageBox(_("SetStrVal(wxString s)"));
//  s.Printf(_("%d"),textctrl);
  //wxMessageBox(s);
  textctrl->SetValue(s);
//  wxMessageBox(_("end"));
}

void TextCtrlItem::ShowBorder()
{
  textctrl->SetBackgroundColour(*wxLIGHT_GREY);
}

void TextCtrlItem::HideBorder()
{
  textctrl->SetBackgroundColour(*wxWHITE);
}

void TextCtrlItem::OnChar(wxKeyEvent& event)throw (debug_err)
{
  long from,to;
  textctrl->GetSelection(&from, &to);
 //bool cont=true;
  if(from==to)//is selected anything?
  {
  //  cont=false;
  if(event.GetKeyCode()==WXK_BACK)
 {
   if(textctrl->GetInsertionPoint()==0)  { parent->DelLeftItem(this);return;}
 }
 else if(event.GetKeyCode()==WXK_DELETE)
 {
  // wxMessageBox(textctrl->GetValue());
   if(textctrl->GetInsertionPoint()==textctrl->GetLineLength(0)) {parent->DelRightItem(this);return;}
   //wxMessageBox(textctrl->GetValue());
 }
 else if(event.GetKeyCode()==WXK_LEFT)
 {
    if(textctrl->GetInsertionPoint()==0)  {parent->get_prev_item(this)->SetEndActive();return;}

 }
 else if(event.GetKeyCode()==WXK_RIGHT)
 {
    if(textctrl->GetInsertionPoint()==textctrl->GetLineLength(0)) {parent->get_next_item(this)->SetActive();return;}

 }
 else if(event.GetKeyCode()==WXK_DOWN)
 {
    parent->get_bottom_item(this)->SetActive();

 }
 else if(event.GetKeyCode()==WXK_UP)
 {
    parent->get_top_item(this)->SetActive();
 }
 //else cont=true;
}
 CalculatorFrame::curr_frame->OnChar(event);
 //if(/*!(event.GetKeyCode()==61&&!event.ShiftDown())&&*/!event.ControlDown())
 event.Skip();
}


void TextCtrlItem::OnMouseClick(wxMouseEvent& event)throw (debug_err)
{
  CalculatorFrame::ActiveCtrl=this; /*wxMessageBox(textctrl->GetLineText(0));*/
  event.Skip();
}

void TextCtrlItem::OnTextEvent(wxCommandEvent& e) throw (debug_err)
{
  CalculatorFrame::Answer.clear();
  try
  {
    SetOptimalSize();
    parent->OnChildrenChanged(this);
  }
  catch(debug_err& a){ wxMessageBox( wxString(a.what(),wxConvLocal)); }
}

void TextCtrlItem::SetOptimalSize()
{
  int w,h;
  if(!textctrl->GetLineText(0).IsEmpty())textctrl->GetTextExtent(textctrl->GetLineText(0),&w,&h);
  else textctrl->GetTextExtent(_("a"),&w,&h);
  textctrl->SetSize(wxSize(w+bit,h));
  if(textctrl->GetLineLength(0)==0&&parent->Items.size()<=1) ShowBorder();
  else HideBorder();
}
void TextCtrlItem::OnChildrenChanged()throw (debug_err)
{
  textctrl->Refresh();
}
void TextCtrlItem::redraw(point loc)throw (debug_err)
{
  textctrl->Move(wxPoint(loc.x,loc.y-textctrl->GetSize().GetHeight()/2));
  if(textctrl->GetValue()==_("")) {textctrl->Refresh();}
}

//-------------class FractCtrl---------------------------
FractCtrl::FractCtrl(FractCtrlItem* par,point location,wxString s)throw (debug_err)
{
  loc=location;
  parent=par;
  //if(is_editable) {TextCtrlItem* a=new TextCtrlItem(this,location);
  Items.push_back(new TextCtrlItem(this,location,s));
}

point FractCtrl::get_location() const
{
  //if(!check()) wxMessageBox(_("oops!"));
  return Items.front()->get_location();
}
FractCtrl::~FractCtrl()
{
  // wxMessageBox(_("~FractCtrl("));
  for(std::vector<FractCtrlItem*>::iterator p=Items.begin();p!=Items.end();++p) delete *p;
}
bool FractCtrl::check()const
{
  //for(std::vector<FractCtrlItem*>::const_iterator p=Items.begin()+1;p!=Items.end();++p) if((*p)->get_location().y!=(*(p-1))->get_location().y) return false;
  return true;
}
wxPoint FractCtrl::get_wx_location() const
{
      if(!(check())) wxMessageBox(_("oops!"));
    int min_h=10000;
    for(std::vector<FractCtrlItem*>::const_iterator p=Items.begin();p!=Items.end();++p)
    {
      int h=(*p)->get_wx_location().y;
      min_h=std::min(min_h,h);
    }
  return wxPoint(get_location().x,min_h);
}

size FractCtrl::get_size() const
{
 // if(!check()) wxMessageBox(_("oops!"));
  int max_h=0;int min_h=10000;
  for(std::vector<FractCtrlItem*>::const_iterator p=Items.begin();p!=Items.end();++p)
  {
    max_h=std::max( max_h,(*p)->get_wx_location().y+(*p)->get_size().h);
    min_h=std::min(min_h,(*p)->get_wx_location().y);
  }
  return size(Items.back()->get_location().x + Items.back()->get_size().w-Items.front()->get_location().x,
  max_h-min_h);
}

std::string FractCtrl::get_str_val()
{
  std::string a="";
  for(std::vector<FractCtrlItem*>::iterator p=Items.begin();p!=Items.end();++p)
  {
    a+=(*p)->get_str_val();
    if((p+1)!=Items.end())
    {
      if(typeid(**(p+1))==typeid(FractionItem)&&!a.empty())
      {
        if(isdigit(a[a.size()-1]))
        {
          int add=1;
          for(int i=a.size()-1;i>=0;i--)
          {
            if(a[i]=='.') {add=0;break;}
            if(!isdigit(a[i]))
            {
             if(a[i]=='+') add=1;
             else if(a[i]=='-') add=-1;
             break;
            }
          }
            my_regex re("^[0-9]*$");
          FractionItem* fi=dynamic_cast<FractionItem*>(*(p+1));
          std::string s1=fi->numerator->get_str_val();
          std::string s2=fi->denominator->get_str_val();
          if(!(re.match(s1)&&re.match(s2))) add=0;
          if(add==1) a+='+';
          else if(add==-1)a+='-';

          else a+="err";
        }
      }
    }
  }
  return a;
}

void FractCtrl::SetActive()const
{
  Items.front()->SetActive();
}

void FractCtrl::SetEndActive()const
{
  Items.back()->SetEndActive();
}

 FractCtrl* FractCtrl::get_bottom_item(const FractCtrlItem* loc) const
{
  if(parent!=NULL) return parent->get_bottom_item(this);
  else return const_cast<FractCtrl*>(this);
}

 FractCtrl* FractCtrl::get_top_item(const FractCtrlItem* loc) const
{
  if(parent!=NULL) return parent-> get_top_item(this);
  else return const_cast<FractCtrl*>(this);
}

FractCtrlItem* FractCtrl::get_prev_item(FractCtrlItem* loc) const
{
  std::vector<FractCtrlItem*>::const_iterator p=std::find(Items.begin(),Items.end(),loc);
  if(p==Items.begin())
  {
    if(parent==NULL)
    {
      return loc;
    }
    else return parent->parent->get_prev_item(parent);
  }
  else return *(--p);
}

FractCtrlItem* FractCtrl::get_next_item(FractCtrlItem* loc)  const
{
  std::vector<FractCtrlItem*>::const_iterator p=std::find(Items.begin(),Items.end(),loc);
  if(p==Items.end()-1)
  {
    if(parent==NULL)
    {
      return loc;
    }
    else return parent->parent->get_next_item(parent);
  }
  else return *(++p);
}

bool FractCtrl::has_fraction()const
{
  for(std::vector<FractCtrlItem*>::const_iterator p=Items.begin();p!=Items.end();p++) if((*p)->has_fraction()) return true;
  return false;
}



FractCtrl* FractionItem::get_top_item(const FractCtrl* loc) const
{
  if(loc==denominator)  return numerator;
  else return parent->get_top_item(this);
}

FractCtrl* FractionItem::get_bottom_item(const FractCtrl* loc) const
{
  if(loc==numerator)  return denominator;
  else return parent->get_bottom_item(this);
}



void FractCtrl::AddBracketItem( TextCtrlItem* loc)throw (debug_err)
{
  BracketItem* b_item=new BracketItem(this);
  insert(loc,b_item);
}

void FractCtrl::AddFractionItem( TextCtrlItem* loc)throw (debug_err)
{
  FractionItem* f_item=new FractionItem(this);
  insert(loc,f_item);
}

void FractCtrl::insert( TextCtrlItem* loc,FractCtrlItem* item)throw (debug_err)
{
  insert_in_Items(loc,item);

  int cur_pos=loc->textctrl->GetInsertionPoint();
  long int from, to;
  loc->textctrl->GetSelection(&from,&to);
  if(cur_pos>from) cur_pos-=to-from;

  wxString text1=loc->textctrl->GetLineText(0);

  if(from!=to)
  {
     wxString new_item_text=text1.substr(from,to-from);
    text1.erase(from,to-from);
  //  wxMessageBox(new_item_text);
    item->SetStrVal(new_item_text);
  }

  wxString text2=text1.substr(cur_pos);
 // wxMessageBox(text2);
  text1.erase(cur_pos);
//  wxMessageBox(_("erase cur_pos"));
 //   wxMessageBox(text1);
  loc->SetStrVal(text1);

 //WARNING BELOW IS BAG WINDOWS don't want to make textctrl white
  //loc->SetStrVal(_("f"));loc->SetStrVal(_(""));

 //  wxMessageBox(_("loc->textctrl->SetValue(text1);"));
//  wxMessageBox(text1);
  loc->HideBorder();
  std::vector<FractCtrlItem*>::iterator p=std::find(Items.begin(),Items.end(),item);
  ++p;

  //if(p==Items.end()||typeid(**p)!=typeid(TextCtrlItem))
  //{
    TextCtrlItem* t_item=new TextCtrlItem(this);
 //   wxMessageBox(_("TextCtrlItem* t_item=new TextCtrlItem(this);"));
    insert_in_Items(item,t_item);
 //   wxMessageBox(_("insert_in_Items(item,t_item);"));
    t_item->SetStrVal(text2);
 //   wxMessageBox(_(" t_item->textctrl->SetValue(text2);"));
    t_item->HideBorder();
  //}
  item->OnChildrenChanged();
 // wxMessageBox(_(" item->OnChildrenChanged();"));
  item->SetActive();
}

void FractCtrl::insert_in_Items(const FractCtrlItem* loc,FractCtrlItem* item)throw (debug_err)
{
  std::vector<FractCtrlItem*>::iterator p= std::find(Items.begin(),Items.end(),loc);
  if(p==Items.end()) throw debug_err("FractCtrl::insert : there isn't loc in Items");
  else {++p; Items.insert(p,item);}
}

void FractCtrl::DelRightItem(TextCtrlItem* loc)throw (debug_err)
{
  try
  {
    if(Items.back()!=loc)
    {
      std::vector<FractCtrlItem*>::iterator p=std::find(Items.begin(),Items.end(),loc);
      if(p==Items.end())  throw debug_err("FractCtrl::insert : there isn't loc in Items");
      ++p;
      delete *(p);
      p=Items.erase(p); --p;
      if(typeid(**p)==typeid(TextCtrlItem))
      {
        wxString val1=dynamic_cast<TextCtrlItem*>(*p)->textctrl->GetValue();
        wxString val2=dynamic_cast<TextCtrlItem*>(*(++p))->textctrl->GetValue();
        delete *(p);
        p=Items.erase(p);p--;
        dynamic_cast<TextCtrlItem*>(*(p))->textctrl->SetValue(val1+val2);
        dynamic_cast<TextCtrlItem*>(*(p))->textctrl->SetInsertionPoint(val1.size());

      }
      OnChildrenChanged(*p);
     // wxMessageBox( dynamic_cast<TextCtrlItem*>(*(p))->textctrl->GetValue());
    }

  }
  catch(std::bad_typeid){debug_err("bad_typeid");wxMessageBox(_("sdfr"));}

}

void FractCtrl::DelLeftItem(TextCtrlItem* loc)throw (debug_err)
{
  try
  {
    if(Items.front()!=loc)
    {
      std::vector<FractCtrlItem*>::iterator p=std::find(Items.begin(),Items.end(),loc);
      if(p==Items.end())  throw debug_err("FractCtrl::insert : there isn't loc in Items");
      --p;
      delete *(p);
      p=Items.erase(p);
      if(/*p!=Items.end()&&*/typeid(**p)==typeid(TextCtrlItem))
      {
        wxString val2=dynamic_cast<TextCtrlItem*>(*p)->textctrl->GetValue();
        wxString val1=dynamic_cast<TextCtrlItem*>(*(--p))->textctrl->GetValue();
        delete *(p);
        p=Items.erase(p);
        dynamic_cast<TextCtrlItem*>(*(p))->textctrl->SetValue(val1+val2);
        dynamic_cast<TextCtrlItem*>(*(p))->textctrl->SetInsertionPoint(val1.size());
      }
      --p;
      OnChildrenChanged(*p);
    }
  }
  catch(std::bad_typeid){debug_err("bad_typeid");wxMessageBox(_("sdfr"));}
}

void FractCtrl::OnChildrenChanged(FractCtrlItem* item) throw (debug_err)
{
  std::vector<FractCtrlItem*>::iterator p=std::find(Items.begin(),Items.end(),item);
  point x;
  if(p!=Items.begin())
  {
    --p;
    x=(*p)->get_location();
    x.x+=(*p)->get_size().w+bit;
    ++p;
  }
  else
  {
     if(parent==NULL) {x=loc;}//is this root?
     else x=item->get_location();
  }
  while(p!=Items.end())
  {
    (*p)->redraw(x);
    x.x+=(*p)->get_size().w/*+bit*/;
    ++p;
  }


  if(parent!=NULL) parent->OnChildrenChanged();
}

void FractCtrl::redraw(point loc)throw (debug_err)
{
  for(std::vector<FractCtrlItem*>::iterator p=Items.begin();p!=Items.end();++p)
  {
    (*p)->redraw(loc);
    loc.x+=(*p)->get_size().w/*+bit*/;
    if(TextCtrlItem* ti=dynamic_cast<TextCtrlItem*>(*p)) ti->OnChildrenChanged();
  }
}

//-------------class BracketItem---------------------------
BracketItem::BracketItem(FractCtrl* par, wxString s)throw (debug_err)
{
  parent=par;
  l_bracket= new wxStaticText(CalculatorFrame::Panel,wxNewId(),_("("), wxDefaultPosition,wxDefaultSize,wxTE_READONLY|wxNO_BORDER);
  fractctrl= new FractCtrl(this,point(-1,-1),s);
  r_bracket= new wxStaticText(CalculatorFrame::Panel,wxNewId(),_(")"), wxDefaultPosition,wxDefaultSize,wxTE_READONLY|wxNO_BORDER);
}

size BracketItem::get_size() const
{
  return size(r_bracket->GetSize().GetWidth()+r_bracket->GetPosition().x- l_bracket->GetPosition().x,
  l_bracket->GetSize().GetHeight());
}

point BracketItem::get_location() const
{
  return point(l_bracket->GetPosition().x,l_bracket->GetPosition().y+get_size().h/2);
}

wxPoint BracketItem::get_wx_location() const
{
  return l_bracket->GetPosition();
}

std::string BracketItem::get_str_val() const
{
  return std::string("("+fractctrl->get_str_val()+")");
}

bool BracketItem::has_fraction()const
{
    return fractctrl->has_fraction();
}

void BracketItem::SetActive()
{
  fractctrl->SetActive();
}

void BracketItem::SetEndActive()
{
  fractctrl->SetEndActive();
}

void BracketItem::SetStrVal(wxString s)
{
  delete  fractctrl;
  fractctrl= new FractCtrl(this,point(-1,-1),s);
 // wxMessageBox(_("BracketItem::SetStrVal fractctr"));

}

BracketItem::~BracketItem()
{
  delete  l_bracket;
  delete  r_bracket;
  delete  fractctrl;
}

void BracketItem::OnChildrenChanged()throw (debug_err)
{
  wxFont f;
  f.SetWeight(wxLIGHT);
  f.SetPointSize(fractctrl->get_size().h/1.2);
  l_bracket->SetFont(f);
  r_bracket->SetFont(f);
  redraw(point(l_bracket->GetPosition().x,l_bracket->GetPosition().y+l_bracket->GetSize().GetHeight()/2));
  parent->OnChildrenChanged(this);
}

void BracketItem::redraw(point loc)throw (debug_err)
{
  double d=4;
  l_bracket->Move(wxPoint(loc.x, loc.y-l_bracket->GetSize().GetHeight()/2));
  loc.x+=l_bracket->GetSize().GetWidth()-l_bracket->GetSize().GetWidth()/d;
  fractctrl->redraw(loc);
  loc.x+=fractctrl->get_size().w-l_bracket->GetSize().GetWidth()/d;
  r_bracket->Move(wxPoint(loc.x , loc.y-r_bracket->GetSize().GetHeight()/2));
}
//-------------class FractionItem---------------------------

FractionItem::FractionItem(FractCtrl* par,wxString s) throw (debug_err)
{
#ifdef __WXMSW__
    line_width=2;
#endif
#ifdef __UNIX__
    line_width=0;
#endif
  parent=par;
  numerator=new FractCtrl(this,point(-1,-1),s);
  denominator=new FractCtrl(this,point(-1,-1));
  line=new wxStaticLine(CalculatorFrame::Panel,wxNewId(),wxPoint(50,50),wxSize(1,0));
  line->SetBackgroundColour(wxColour(0,0,0));
}

point FractionItem::get_location() const
{
  return point(line->GetPosition().x,line->GetPosition().y);
}

wxPoint FractionItem::get_wx_location() const
{
  return wxPoint(line->GetPosition().x,numerator->get_wx_location().y);
}

void FractionItem::redraw(point loc) throw(debug_err)
{
  int delta_x=loc.x-line->GetPosition().x;
  int delta_y=loc.y-line->GetPosition().y;
  numerator->redraw(point(numerator->get_location().x+delta_x,numerator->get_location().y+delta_y));
  denominator->redraw(point(denominator->get_location().x+delta_x,denominator->get_location().y+delta_y));
  line->Move(wxPoint(line->GetPosition().x+delta_x,line->GetPosition().y+delta_y));
}

size FractionItem::get_size() const
{
  return size(line->GetSize().GetWidth(),  denominator->get_wx_location().y+denominator->get_size().h-numerator->get_wx_location().y);
}

std::string FractionItem::get_str_val() const
{
  return std::string("(("+numerator->get_str_val()+")/("+denominator->get_str_val()+"))");
}

bool FractionItem::has_fraction()const
{
    return true;
}

void FractionItem::SetActive()
{
  numerator->SetActive();
}

void FractionItem::SetEndActive()
{
  denominator-> SetEndActive();
}

void FractionItem::SetStrVal(wxString s)
{
  delete numerator;
  numerator=new FractCtrl(this,point(-1,-1),s);
  //delete denominator;
 // delete line;
 //*this=FractionItem(parent,s);
}


void FractionItem::OnChildrenChanged() throw (debug_err)
{
  /*izmenaet drob chtobi ona viglidela korrektno otniositelno tekuchego polozenia numeratora*/

  point n_l=numerator->get_wx_location();//numerator location

  point d_l=n_l; //denominator location
  d_l.y+=(numerator->get_size().h+1+2*bit);
  d_l.x+=((numerator->get_size().w-denominator->get_size().w)/2);

  FractCtrl* max_item;
  if((numerator->get_size().w) >= (denominator->get_size().w)) max_item=numerator;
  else max_item=denominator;

  n_l.y+=(numerator->get_location().y-numerator->get_wx_location().y);
  d_l.y+=(denominator->get_location().y-denominator->get_wx_location().y);

  numerator->redraw(n_l);
  denominator->redraw(d_l);

  point l_l=max_item->get_wx_location();
  l_l.y=numerator->get_wx_location().y+numerator->get_size().h+bit;
  l_l.x-=max_item->get_size().w/5;

  line->Move(wxPoint(l_l.x,l_l.y));
  line->SetSize(wxSize(max_item->get_size().w*7/5,line_width));

  parent->OnChildrenChanged(this);
}

FractionItem::~FractionItem() throw (debug_err)
{
  delete numerator;
  delete denominator;
  delete line;
}
