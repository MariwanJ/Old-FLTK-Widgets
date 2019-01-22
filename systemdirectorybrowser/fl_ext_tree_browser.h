//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Fl_Ext_TreeBrowser.h  v 0.0.1                              2006-06-19 
//
//         for the Fast Light Tool Kit (FLTK) 1.1.x .
//
// Copyright 1998-2003 by Mariwan Jalal, Don Zimmer, Bill Spitzak   & others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems to "fltk_kurdi@yahoo.com".
//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////



#ifndef FL_EXT_TREE_BROWSER_H
#define FL_EXT_TREE_BROWSER_H
#ifndef Fl_Group_H
#include "FL/Fl_Group.H"
#endif
#include <FL/Fl_Scrollbar.H>

#define FL_NORMAL_BROWSER	0
#define FL_SELECT_BROWSER	1
#define FL_HOLD_BROWSER		2
#define FL_MULTI_BROWSER	3


#include "fl_ext_tree_item.h"


class Fl_Ext_TreeBrowser : public Fl_Group
{
private:    

  int position_;	// where user wants it scrolled to
  int real_position_;	// the current vertical scrolling position
  int hposition_;	// where user wants it panned to
  int real_hposition_;	// the current horizontal scrolling position
  int offset_;		// how far down top_ item the real_position is
  int max_width;	// widest object seen so far
  uchar has_scrollbar_;	// which scrollbars are enabled
  uchar textfont_, textsize_;
  unsigned textcolor_;
  
  Fl_Ext_TreeItem* top_;		// which item scrolling position is in
  Fl_Ext_TreeItem* selection_;	// which is selected (except for FL_MULTI_BROWSER)
  void *redraw1,*redraw2; // minimal update pointers
  void* max_width_item;	// which item has max_width_

  static int scrollbar_width_;

  void update_top();
  
protected:
   
  // All of the following must be supplied by the subclass:
  virtual int item_quick_height(Fl_Ext_TreeItem *)  ;

 // virtual void item_draw(void *,int,int,int,int) const = 0;
  // you don't have to provide these but it may help speed it up:

  virtual int full_width()  ;	// current width of all items
  virtual int full_height() ;	// current height of all items
  virtual int incr_height() ;	// average height of an item

  // These only need to be done by subclass if you want a multi-browser:
  virtual void item_select(Fl_Ext_TreeItem *,int=1);
  virtual int item_selected(Fl_Ext_TreeItem *) const ;

  // things the subclass may want to call:
  Fl_Ext_TreeItem *top()  {return top_;}
  Fl_Ext_TreeItem **selection() {return &selection_;}

  void new_list(); // completely clobber all data, as though list replaced
  void deleting(Fl_Ext_TreeItem *a); // get rid of any pointers to a
  void replacing(Fl_Ext_TreeItem *a,Fl_Ext_TreeItem *b); // change a pointers to b
  int displayed(Fl_Ext_TreeItem *) ; // true if this line is visible
  void redraw_line(Fl_Ext_TreeItem *); // minimal update, no change in size
  void redraw_lines() {damage(FL_DAMAGE_SCROLL);} // redraw all of them
  void bbox(int&,int&,int&,int&) const;
  int leftedge() const;	// x position after scrollbar & border
  Fl_Ext_TreeItem *find_item(int my); // item under mouse
  void draw(int,int,int,int);
  int handle(int,int,int,int,int);
  void draw();
  
public:

// User Callbacks      
   virtual int   HandleInvoke(Fl_Ext_TreeItem *ItemSquareClicked);              // A Callback function pointer left for the user :  Clicked + or - callback 
   virtual int   HandleMenu(void *pData);       
   virtual int   HandleSelect(Fl_Ext_TreeItem* pData, int bState);

   void SetLastItem(Fl_Ext_TreeItem*); /// change the plast select item .. so we can add under the new item
   int  cb_GetGrey(Fl_Ext_TreeItem *ItemToget);    // A Callback function pointer left for the user : 

  Fl_Ext_TreeBrowser(int x, int y, int w, int h, const char *l=0);
  virtual ~Fl_Ext_TreeBrowser();
  
  Fl_Scrollbar scrollbar;		// Vertical scrollbar
  Fl_Scrollbar hscrollbar;		// Horizontal scrollbar
  
  void resize(int,int,int,int);

  int select(Fl_Ext_TreeItem *,int=1,int docallbacks=0);
  int select_only(Fl_Ext_TreeItem *,int docallbacks=0);
  int deselect(int docallbacks=0);
  int position() const {return position_;}
  int hposition() const {return hposition_;}
  void position(int); // scroll to here
  void hposition(int); // pan to here
  void display(Fl_Ext_TreeItem*); // scroll so this item is shown

  uchar has_scrollbar() const {return has_scrollbar_;}
  void has_scrollbar(uchar i) {has_scrollbar_ = i;}
  enum { // values for has_scrollbar()
    HORIZONTAL = 1,
    VERTICAL = 2,
    BOTH = 3,
    ALWAYS_ON = 4,
    HORIZONTAL_ALWAYS = 5,
    VERTICAL_ALWAYS = 6,
    BOTH_ALWAYS = 7
  };

  Fl_Font textfont() const {return (Fl_Font)textfont_;}
  void textfont(uchar s) {textfont_ = s;}
  uchar textsize() const {return textsize_;}
  void textsize(uchar s) {textsize_ = s;}
  Fl_Color textcolor() const {return (Fl_Color)textcolor_;}
  void textcolor(unsigned n) {textcolor_ = n;}

  static void scrollbar_width(int b) {scrollbar_width_ = b;}
  static int scrollbar_width() {return scrollbar_width_;}

  // for back compatability:
  void scrollbar_right() {scrollbar.align(FL_ALIGN_RIGHT);}
  void scrollbar_left() {scrollbar.align(FL_ALIGN_LEFT);}
  

        //Add Item                                                         /* Add after this item*/ 
     virtual Fl_Ext_TreeItem*  add_item(int nLevel, char *label, uchar ItemType, Fl_Ext_TreeItem* ); //by mariwan

  void clear();

  virtual Fl_Ext_TreeItem *item_first();
  virtual Fl_Ext_TreeItem *item_last();
  virtual Fl_Ext_TreeItem *item_next(Fl_Ext_TreeItem *);
  virtual Fl_Ext_TreeItem *item_prev(Fl_Ext_TreeItem *);
  virtual int item_width(Fl_Ext_TreeItem *) ;
  virtual int item_height(Fl_Ext_TreeItem *) ;
  virtual void item_draw(Fl_Ext_TreeItem *,int,int,int,int) ;
  virtual int handle(int event);

  // add item 
  int Add(Fl_Ext_TreeItem *pItem, int bSelect=0);
  
  // Add after the pItemBase the pItemNew item ... return the added items pointer
  Fl_Ext_TreeItem* Add(Fl_Ext_TreeItem *pItemBase, Fl_Ext_TreeItem* pItemNew, int bSelect );

  int Remove(Fl_Ext_TreeItem *pItem);
  int Prune(Fl_Ext_TreeItem *pItem);
  
  // This could be negelected ... do not depend on this .. it call add with base item
  int InsertAfter(Fl_Ext_TreeItem *pPrev, Fl_Ext_TreeItem *pItem, int bSelect = 0);

  int Select(Fl_Ext_TreeItem *pItem);
  int Select(int nLine);
  int SelectLast(int nLevel);


  Fl_Ext_TreeItem *Selection(void) ;

  Fl_Ext_TreeItem *Find(int (*pFunc)(void *a, void*b), void *pArg); // this should be virtual as it needs to be 
                                                                             //re-written when the way of building of the tree is changed
  static int _s_DefaultFindFunc(void *a, void *b);

  // default do-nothing callback, user template
  static void _s_DefaultCallback(Fl_Widget *, void *);

private:
  int _Remove(Fl_Ext_TreeItem *pItem, int bFree); // return 1 if changed

  Fl_Ext_TreeItem *m_pFirst;
  Fl_Ext_TreeItem *m_pLast;
};


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


#endif // FL_EXT_TREE_BROWSER_H
