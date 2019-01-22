//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Fl_Ext_TreeBrowser.cpp  v 0.0.1                              2006-06-19 
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


#include <iostream>
using namespace std;
#define DISPLAY_SEARCH_BOTH_WAYS_AT_ONCE

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>

#include <FL/Fl_Pixmap.H>

#include "fl_ext_tree_browser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fl_systemdirectory_icons.h"
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


// this function is not implimented .. or left to the user
// at selecting or deselecting occure the callback depending on bState  1 is select 0 is deselect
 
   int   Fl_Ext_TreeBrowser::HandleSelect(Fl_Ext_TreeItem* pData, int bState)  // A Callback function pointer left for the user : + - clicked callback 
      {
   // Left to the user to write the functions
        return 1;
   }
//  When double click has been occured
   int   Fl_Ext_TreeBrowser::HandleInvoke(Fl_Ext_TreeItem *ItemSquareClicked)              // A Callback function pointer left for the user :  Clicked + or - callback 
      {
   // Left to the user to write the functions
     return 1; 
   }
   int   Fl_Ext_TreeBrowser::HandleMenu(void *pData)       

   {
   return 1;
   // Left to the user to write the functions
   }



//////////////////////////////////////////////////////////////////////
/// function for setting the last item's name
//////////////////////////////////////////////////////////////////////

void Fl_Ext_TreeBrowser::SetLastItem(Fl_Ext_TreeItem* pItem)
{
Fl_Ext_TreeBrowser::m_pLast=pItem;
}

//////////////////////////////////////////////////////////////////////
// Set the first item in the tree
//////////////////////////////////////////////////////////////////////

Fl_Ext_TreeItem* Fl_Ext_TreeBrowser::item_first()  
{
  return Fl_Ext_TreeBrowser::m_pFirst;
}

//////////////////////////////////////////////////////////////////////
// Get Last item in the tree 
//////////////////////////////////////////////////////////////////////


Fl_Ext_TreeItem* Fl_Ext_TreeBrowser::item_last()  
{
  return Fl_Ext_TreeBrowser::m_pLast;
}


//////////////////////////////////////////////////////////////////////
// Get the next item ... this is not nessesary 
//////////////////////////////////////////////////////////////////////


Fl_Ext_TreeItem *Fl_Ext_TreeBrowser::item_next(Fl_Ext_TreeItem *l) 
{
 if (l) // avoid error
  return l->m_pNext;
  else
  return 0;
}


//////////////////////////////////////////////////////////////////////
// Get the prev item ... this is not nessesary 
//////////////////////////////////////////////////////////////////////


Fl_Ext_TreeItem *Fl_Ext_TreeBrowser::item_prev(Fl_Ext_TreeItem *l) 
{
 if (l) // avoid error
    return l->m_pPrev; 
  else
  return 0;
}


//////////////////////////////////////////////////////////////////////
// Calculate Item width for an Item 
//////////////////////////////////////////////////////////////////////


int Fl_Ext_TreeBrowser::item_width(Fl_Ext_TreeItem *v)  
{
  Fl_Ext_TreeItem *pItem = v ; 

  if (!pItem->m_bVisible) 
      return 0;

  int w = 3 + pItem->m_nLevel*20;

  if (pItem->IsParent()) 
  {
    w += 14; // extra 4 for space after box
  }
  else if (pItem->m_nLevel)
  {
    w += 4; // extra 4 to line up with parent
  }

  int bGrey = 0;
  bGrey = pItem->GetGrey(); // check if the item is Greyed
  if(bGrey)
  {
    fl_font(textfont()+FL_ITALIC, textsize());
  }
  else
  {
    fl_font(textfont(), textsize());
  }
  
  w += int(fl_width(pItem->GetName()));
  return w;
}


//////////////////////////////////////////////////////////////////////
// Return the Item hight
//////////////////////////////////////////////////////////////////////


int Fl_Ext_TreeBrowser::item_height(Fl_Ext_TreeItem *l)  
{
  return (l->m_bVisible)?textsize()+4:0;  // +4 added by mariwan
}


//////////////////////////////////////////////////////////////////////
//Draw one item in the list
//////////////////////////////////////////////////////////////////////

void Fl_Ext_TreeBrowser::item_draw(Fl_Ext_TreeItem *v, int x, int y, int, int)  
{
  Fl_Ext_TreeItem *pItem = v;

  // left edge
  //
  x += 3 + pItem->m_nLevel * 10;

  // text x
  int tx = x;

  // parent x
  int px = x - 10;

  // colour
  //

  fl_color(FL_BLACK); // list's lines drawn black .. change here if you want another color for the list

  // tree branch lines
  //
  if(pItem->IsParent()) 
  {
    // box with '-' inside
    fl_rect(x, y+3, 9, 9);
    fl_line(x+2, y+7, x+6, y+7);

    if (pItem->IsOpen()) 
    {
      // south connector  to the box
      fl_line(x+4, y+11, x+4, y+13+4);  // Small line from the box to the next item Mariwan
    } 
    else 
    {
      // turn '-' into '+'
      fl_line(x+4, y+5, x+4, y+9); 
    }

    if(pItem->m_nLevel)
    {
      // west connector to parent // connenction between the vertical line and the rectangle.
        fl_line(px+4, y+7, x, y+7);
    }

    tx += 14; // extra 4 for space after box
  }
  else if(pItem->m_nLevel) 
  {
    tx += 14; // extra 4 to line up with parent // added 10 by Mariwan 

    // west connector to parent
    fl_line(px+4, y+7, px+8+10, y+7); // added 10 by mariwan  // connenction between the vertical line and the rectangle.
  }

  // north and south connetors to parent
  //
  if(pItem->m_nLevel)
  {
    if(pItem->IsLastSibling())
    {
       fl_line(px+4, y-2, px+4, y+7); 
    }
    else
    {
      fl_line(px+4, y-2, px+4, y+13+2); 
    }
  }

  // disconnected brach lines from previous levels, start up two
  //
  Fl_Ext_TreeItem *pParent = pItem->GetParent();
  while(pParent)
  {
    px -= 10;
    if(pParent->m_nLevel)
    {
      if(!pParent->IsLastSibling())
      {
        fl_line(px+4, y-2, px+4, y+13+2); // -2 Added by Mariwan and +2 after 13 added by Mariwan
      }
    }
    pParent = pParent->GetParent();
  }
  
  // draw text
  //
  int bGrey = 0;
  bGrey = pItem->GetGrey();
  if(bGrey) // Enable or dissable code is here for changing the color
  {
    if(pItem->m_bSelected)
    {
    //SAIRI AMA BIKA
      fl_color(fl_contrast(FL_INACTIVE_COLOR,FL_SELECTION_COLOR));
    }
    else 
    {
      fl_color(FL_INACTIVE_COLOR);
    }
    fl_font(textfont()+FL_ITALIC, textsize());  // Origional
  }
  else
  {
    if(pItem->m_bSelected)
    {
    // Decide which color should be used for selecting the text
      fl_color(FL_GRAY);
    }
    else 
    {
      fl_color(textcolor());
    }

    fl_font(textfont(), textsize());
  }


  {

   //draw text 
    if(pItem->m_bSelected)
    // draw the box under the text 
    // Selection in a new way .. this draw the selection box around the text.
          draw_box(box() ? box() : FL_DOWN_BOX, tx+24 , y+2 , (int)(fl_width(pItem->GetName())) ,15-2,color()); 



    fl_color(FL_BLACK);  /// This make Font of the Items black when it is selected. Mariwan
    fl_draw(pItem->GetName(), tx+24, y+13); // draw text 
    
    // Draw focus when the arrow key pressed
  if ((pItem == selection_) && (Fl::focus() == this))
      {
       draw_focus(FL_NO_BOX, tx+22 , y+2 , (int)(fl_width(pItem->GetName()))+4 ,15);       
      }
    
     if (!(pItem->m_PixmapPicture==0)) // Draw Icon
       pItem->m_PixmapPicture->draw(tx,y);// fl_draw_pixmap(Folder_xpm ,tx,y,FL_BACKGROUND2_COLOR );
         
  }
}




//////////////////////////////////////////////////////////////////////
// additions
//////////////////////////////////////////////////////////////////////

// Add item                                           1                     2
//       2 after item 1
Fl_Ext_TreeItem* Fl_Ext_TreeBrowser::Add(Fl_Ext_TreeItem *pItemBase, Fl_Ext_TreeItem* pItemNew, int bSelect )

{

  if((pItemNew==0))   // check if not the sent item is zero
  {
        return pItemBase;
  }
  if((pItemBase==0)) // check if not the base item is zero
  {
  if (!(Add(pItemNew, bSelect)) )  // nothing in the list so just add this item
	  {
        return pItemBase;  // if somting wrong happend 
	  }
  else 
	  {
       	return pItemNew;  // return the added
  
	  }
  }

  Fl_Ext_TreeItem *pHead = pItemBase; // Root
  Fl_Ext_TreeItem *pTail = pItemBase->m_pNext;// Sub

  pHead->m_pNext = pItemNew; // Add new  link to new item
  pItemNew->m_pPrev = pHead;  // Add newitem link to the old item
  Fl_Ext_TreeItem *pAddedItem = pItemNew;
 
  while(pAddedItem->m_pNext) // Check if no this item contain a chain of linked items if so go the the end Mariwan
  {
    pAddedItem = pAddedItem->m_pNext;
  }

  pAddedItem->m_pNext = pTail;   // Set the last added items next to the pTail (the old item saved before) mariwan
  if (pTail) 
	  pTail->m_pPrev = pAddedItem; // if not the last item is what we added ... link it together    mariwan
  else 
	  m_pLast = pAddedItem;

  int rc = 1;
  if(bSelect)  // if needs to be selected
     rc = Select(pItemNew);   // select the item
 if (this->visible())
    redraw();  /// redraw  the tree
 return pAddedItem;  // return the item (s) added
}




//////////////////////////////////////////////////////////////////////*********
// additions  --- this will remain for further development - Mariwan
//////////////////////////////////////////////////////////////////////*********

int Fl_Ext_TreeBrowser::Add(Fl_Ext_TreeItem *pItemNew, int bSelect /* =0 */)
{
if ((pItemNew==0))
  {

  return 0;   // Item sent was an error
  }
else
{

  Fl_Ext_TreeItem *pNext;
  int rc;

  if(!m_pFirst) // it is the first item
  {
      m_pFirst = pItemNew;//  first item is equal to the item will be added
      m_pLast = pItemNew; //  last item also equal to the item will be added
      pNext = pItemNew->m_pNext; // pnext .. temp item is equal to item added next
      while(pNext)               // if pnext available 
      { 
        m_pLast = pNext;        // find last item to the last item pointer
        pNext = pNext->m_pNext; // 
       }
  }
  else 
  {
      pItemNew->m_pPrev = m_pLast;  // m_pFirst not available .. zero .. Set added item previous to last item
      m_pLast->m_pNext = pItemNew;  // next to last item -is equil to item added

      m_pLast = pItemNew;            // last item is equal to item added
      pNext = pItemNew->m_pNext;     // temp pointer is iequal to 
      while(pNext)                   // set m_pLast to the end
      {
        m_pLast = pNext; 
        pNext = pNext->m_pNext; 
      }
 }

  // show siblings
  Fl_Ext_TreeItem *pParent = pItemNew->GetParent();

  rc = 1;
  if(bSelect) rc = Select(pItemNew);

   redraw();
  return rc;
 }
}



//////////////////////////////////////////////////////////////////////
// this function is useless ... because add will do the job.
//////////////////////////////////////////////////////////////////////


int Fl_Ext_TreeBrowser::InsertAfter(Fl_Ext_TreeItem *pItemBase, Fl_Ext_TreeItem *pItemNew, int bSelect /* =0 */)
{
        //                       1       2          select or not
 Fl_Ext_TreeItem *pItem=Add(pItemBase, pItemNew, bSelect );

if (pItem)
 return 1;
 else 
 return 0;
}



//////////////////////////////////////////////////////////////////////
// remove one item in the list
//////////////////////////////////////////////////////////////////////

int Fl_Ext_TreeBrowser::Remove(Fl_Ext_TreeItem *pItem) 
{ 
  return _Remove(pItem, 1); 
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

// this will cut the tree letting the pItem along withits branch
int Fl_Ext_TreeBrowser::Prune(Fl_Ext_TreeItem *pItem) 
{ 
  return _Remove(pItem, 0); 
}

//////////////////////////////////////////////////////////////////////
// remove pTreeItem and all children, freeing memory
// if bFree is One it will free the memory .. when bFree is zero .. unknown results will occure?? Mariwan
//////////////////////////////////////////////////////////////////////

int Fl_Ext_TreeBrowser::_Remove(Fl_Ext_TreeItem *pItem, int bFree)
{
  Fl_Ext_TreeItem *pNext;
  Fl_Ext_TreeItem *pSelected = selection_;

  if(!pItem) // entire tree (all the tree all the items)
  {
    pItem = m_pFirst;
    if(!pItem) return 0;

    Select((Fl_Ext_TreeItem*)(NULL));
    m_pFirst = m_pLast = NULL;
    new_list();

    if(bFree)
    {
      while(pItem)
      {
        pNext = pItem->m_pNext;
        pItem = pNext;
      }
    }
  }
  else // just this branch
  {
    Fl_Ext_TreeItem *pPrev = pItem->m_pPrev; // Get item before Mariwan
    int nLevel = pItem->m_nLevel;            // Get Item  level

    // cap off pruned branch at head
    // this will cut the branchs head ... why??? strange
    if(!bFree)  // if bFree is Zero
          pItem->m_pPrev = NULL;
    while(pItem)
    {
      pNext = pItem->m_pNext;
      if(pItem == pSelected) 

         pSelected=NULL;
         pItem->m_bSelected=0;

//       Select((Fl_Ext_TreeItem*)(NULL));              //       this cause Segmentation fault?????
      if(bFree) // if bFree is 1  so delete the item and free the memory
      {
   	    if (pItem)
	      delete pItem; // deletes data also
	      pItem=0;
      }
      pItem = pNext;

      if(pItem) // if the last item deleted was not the last one in the tree
      {
        if(pItem->m_nLevel <= nLevel) // when it is the end of the sub branch stop
        {
          // cap off pruned branch at tail
          if(!bFree) 
              pItem->m_pPrev->m_pNext = NULL;
          // end of branch - done
          break;
        }
      }
    }
    // fix up links
    if(pItem) // if still there itiems
    {
       pItem->m_pPrev = pPrev;
       if(pPrev) 
        {
          pPrev->m_pNext = pItem;
        }
      else
       {
         m_pFirst = pItem; 
       }
    }
    else
    {
      if(pPrev) 
      {
        pPrev->m_pNext = NULL;
        m_pLast = pPrev;
      }
      else
      {
        m_pFirst = m_pLast = NULL;
      }
    }
    // fix up selection
    if(!selection() && pSelected)
    {
      if(pPrev)
      {
        if(pPrev->m_pNext) Select(pPrev->m_pNext);
        else Select(pPrev);
      }
      else if(m_pFirst) 
      {
        Select(m_pFirst);
      }
    }

    redraw();
  }

  return 1;
}


//////////////////////////////////////////////////////////////////////
// Convert Item's selection condition  if selected --> deselect or reverse of that
//////////////////////////////////////////////////////////////////////


int Fl_Ext_TreeBrowser::Select(Fl_Ext_TreeItem *pItem)
{
Fl_Ext_TreeItem *pSelected = selection_;

  if(pSelected == pItem) return 1;

  // deselect old
  
  if(pSelected) // Old item to be deselected
  {
   
     // call handleSelect with the indication that unselect have done
      if(!HandleSelect(pSelected, 0)) // Changed by Mariwan
      {
        if(!pItem) 
           return 0; // allow Select(NULL) to pass
      }
    pSelected->m_bSelected = 0;
  }

  // select new
  //
  if(pItem)
  {
    {
      if(!HandleSelect(pItem, 1))
      {
        if(pSelected) // re-select old
        {
           HandleSelect(pSelected, 1);
           pSelected->m_bSelected = 1;
        }
        return 0;
      }
    }

    // make sure we can see the selection 
    
    Fl_Ext_TreeItem *pParent = pItem->GetParent();
    while(pParent) 
    {
     pParent->SetBranchVisible(1);
     pParent = pParent->GetParent(); 
     }
    
    pItem->m_bSelected = 1;
    select(pItem);
  }
  else
  {
    deselect();
  }

  redraw();
  return 1;
}


//////////////////////////////////////////////////////////////////////
// selects the nth visible line
//////////////////////////////////////////////////////////////////////

int Fl_Ext_TreeBrowser::Select(int nLine)
{
  Fl_Ext_TreeItem *pItem = m_pFirst;

  int i = 0;

  while(pItem)
  {
    if(pItem->m_bVisible) i++;

    if(i == nLine) break;

    pItem = pItem->m_pNext;
  }

  if(pItem) return Select(pItem);
  return 0;
}


//////////////////////////////////////////////////////////////////////
// selects the last visible line at a level
//////////////////////////////////////////////////////////////////////

int Fl_Ext_TreeBrowser::SelectLast(int nLevel)
{
  Fl_Ext_TreeItem *pItem = m_pLast;

  while(pItem)
  {
    if(pItem->m_bVisible && pItem->m_nLevel == nLevel) 
       break;

    pItem = pItem->m_pPrev;
  }

  if(pItem) 
    return Select(pItem);
  return 0;
}


//////////////////////////////////////////////////////////////////////
// Return current selected item or Last selected item
//////////////////////////////////////////////////////////////////////

Fl_Ext_TreeItem *Fl_Ext_TreeBrowser::Selection(void) 
{
  return *selection();
}

//////////////////////////////////////////////////////////////////////
// Find an item ... this works just when the whole list is available 
//////////////////////////////////////////////////////////////////////

Fl_Ext_TreeItem *Fl_Ext_TreeBrowser::Find(int (*pFunc)(void *a, void *b), void *pArg)
{
  if(!pFunc) 
      pFunc = _s_DefaultFindFunc;

  Fl_Ext_TreeItem *pItem = m_pFirst;

  while(pItem)
  {
    if(pFunc(pItem->m_pData, pArg)) break;
    pItem = pItem->m_pNext;
  }

  return pItem;
}


//////////////////////////////////////////////////////////////////////
// support
//////////////////////////////////////////////////////////////////////

int Fl_Ext_TreeBrowser::_s_DefaultFindFunc(void *a, void *b)
{
  return (a == b)?1:0;
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


// default do-nothing callback, user template
//
void Fl_Ext_TreeBrowser::_s_DefaultCallback(Fl_Widget *o, void *)
{
#ifdef DEBUG
// write you code here
;
#endif
}
//////  Ama chak bika halaya
void Fl_Ext_TreeBrowser::clear() 
{
Fl_Ext_TreeItem *pSaveItemBefore=0;
     Fl_Ext_TreeItem *pScanItem=item_last();

     while (pScanItem)
     {
      if (pScanItem->m_pPrev)
         pSaveItemBefore=pScanItem->m_pPrev;
        if (pScanItem->m_PixmapPicture)
           free (pScanItem->m_PixmapPicture);
        if (pScanItem)
           free(pScanItem);
  	   if (pScanItem)
           delete (pScanItem);
        pScanItem=pSaveItemBefore;
        new_list();
       }
}

// check this Mariwan
static void scrollbar_callback(Fl_Widget* s, void*) {
  ((Fl_Ext_TreeBrowser*)(s->parent()))->position(int(((Fl_Scrollbar*)s)->value()));
}

static void hscrollbar_callback(Fl_Widget* s, void*) {
  ((Fl_Ext_TreeBrowser*)(s->parent()))->hposition(int(((Fl_Scrollbar*)s)->value()));
}

int Fl_Ext_TreeBrowser::scrollbar_width_ = 16;

// return where to draw the actual box:
void Fl_Ext_TreeBrowser::bbox(int& X, int& Y, int& W, int& H) const {
  Fl_Boxtype b = box() ? box() : FL_DOWN_BOX;
  X = x()+Fl::box_dx(b);
  Y = y()+Fl::box_dy(b);
  W = w()-Fl::box_dw(b);
  H = h()-Fl::box_dh(b);
  if (scrollbar.visible()) {
    W -= scrollbar_width_;
    if (scrollbar.align() & FL_ALIGN_LEFT) X += scrollbar_width_;
  }
  if (W < 0) W = 0;
  if (hscrollbar.visible()) {
    H -= scrollbar_width_;
    if (scrollbar.align() & FL_ALIGN_TOP) Y += scrollbar_width_;
  }
  if (H < 0) H = 0;
}

int Fl_Ext_TreeBrowser::leftedge() const 
{
  int X, Y, W, H; 
  bbox(X, Y, W, H);
  return X;
}

// The scrollbars may be moved again by draw(), since each one's size
// depends on whether the other is visible or not.  This skips over
// Fl_Group::resize since it moves the scrollbars uselessly.
void Fl_Ext_TreeBrowser::resize(int X, int Y, int W, int H) 
{
  Fl_Widget::resize(X, Y, W, H);
  // move the scrollbars so they can respond to events:
  bbox(X,Y,W,H);
  scrollbar.resize(
  
	scrollbar.align()&FL_ALIGN_LEFT ? X-scrollbar_width_ : X+W,Y, scrollbar_width_, H);
  hscrollbar.resize(X, scrollbar.align()&FL_ALIGN_TOP ? Y-scrollbar_width_ : Y+H,W, scrollbar_width_);
  }

// Cause minimal update to redraw the given item:
void Fl_Ext_TreeBrowser::redraw_line(Fl_Ext_TreeItem* l) {
  if (!redraw1 || redraw1 == l) {redraw1 = l; damage(FL_DAMAGE_EXPOSE);}
  else if (!redraw2 || redraw2 == l) {redraw2 = l; damage(FL_DAMAGE_EXPOSE);}
  else damage(FL_DAMAGE_SCROLL);
}

// Figure out top() based on position():
void Fl_Ext_TreeBrowser::update_top() {
  if (!top_) top_ = item_first();
  if (position_ != real_position_) {
    Fl_Ext_TreeItem* l;
    int ly;
    int yy = position_;
    // start from either head or current position, whichever is closer:
    if (!top_ || yy <= (real_position_/2)) {
      l = item_first();
      ly = 0;
    } else {
      l = top_;
      ly = real_position_-offset_;
    }
    if (!l) {
      top_ = 0;
      offset_ = 0;
      real_position_ = 0;
    } else {
      int hh = item_quick_height(l);
      // step through list until we find line containing this point:
      while (ly > yy) {
	Fl_Ext_TreeItem* l1 = item_prev(l);
	if (!l1) {ly = 0; break;} // hit the top
	l  = l1;
	hh = item_quick_height(l);
	ly -= hh;
      }
      while ((ly+hh) <= yy) {
	Fl_Ext_TreeItem* l1 = item_next(l);
	if (!l1) {yy = ly+hh-1; break;}
	l = l1;
	ly += hh;
	hh = item_quick_height(l);
      }
      // top item must *really* be visible, use slow height:
      for (;;) {
	hh = item_height(l);
	if ((ly+hh) > yy) break; // it is big enough to see
	// go up to top of previous item:
	Fl_Ext_TreeItem* l1 = item_prev(l);
	if (!l1) {ly = yy = 0; break;} // hit the top
	l = l1; yy = position_ = ly = ly-item_quick_height(l);
      }
      // use it:
      top_ = l;
      offset_ = yy-ly;
      real_position_ = yy;
    }
    damage(FL_DAMAGE_SCROLL);
  }
}

// Change position(), top() will update when update_top() is called
// (probably by draw() or handle()):
void Fl_Ext_TreeBrowser::position(int yy) {
  if (yy < 0) yy = 0;
  if (yy == position_) return;
  position_ = yy;
  if (yy != real_position_) redraw_lines();
}

void Fl_Ext_TreeBrowser::hposition(int xx) {
  if (xx < 0) xx = 0;
  if (xx == hposition_) return;
  hposition_ = xx;
  if (xx != real_hposition_) redraw_lines();
}

// Tell whether item is currently displayed:
int Fl_Ext_TreeBrowser::displayed(Fl_Ext_TreeItem* p)  
{
  int X, Y, W, H; bbox(X, Y, W, H);
  int yy = H+offset_;
  for (Fl_Ext_TreeItem* l = top_; l && yy > 0; l = item_next(l))
  {
    if (l == p) return 1;
    yy -= item_height(l);
  }
  return 0;
}

// Ensure this item is displayed:
// Messy because we have no idea if it is before top or after bottom:
void Fl_Ext_TreeBrowser::display(Fl_Ext_TreeItem* p) 
{

  // First special case - want to display first item in the list?
  update_top();
  if (p == item_first()) 
  {
        position(0);
         return;
  }
  int X, Y, W, H, Yp; 
  bbox(X, Y, W, H);
  Fl_Ext_TreeItem* l = top_;
  Y = Yp = -offset_;
  int h1;

  // 2nd special case - want to display item already displayed at top of browser?
  if (l == p) {position(real_position_+Y); return;} // scroll up a bit

  // 3rd special case - want to display item just above top of browser?
  Fl_Ext_TreeItem* lp = item_prev(l);
  if (lp == p) {position(real_position_+Y-item_quick_height(lp)); return;}

#ifdef DISPLAY_SEARCH_BOTH_WAYS_AT_ONCE
  // search for item.  We search both up and down the list at the same time,
  // this evens up the execution time for the two cases - the old way was
  // much slower for going up than for going down.
  while (l || lp) 
  {
    if (l) {
      h1 = item_quick_height(l);
      if (l == p) {
	if (Y <= H) { // it is visible or right at bottom
	  Y = Y+h1-H; // find where bottom edge is
	  if (Y > 0) position(real_position_+Y); // scroll down a bit
	} else {
	  position(real_position_+Y-(H-h1)/2); // center it
	}
	return;
      }
      Y += h1;
      l = item_next(l);
    }
    if (lp) 
    {
      h1 = item_quick_height(lp);
      Yp -= h1;
      if (lp == p) 
      {
	   if ((Yp + h1) >= 0) 
          position(real_position_+Yp);
	   else 
          position(real_position_+Yp-(H-h1)/2);
	   return;
      }
      lp = item_prev(lp);
    }
  }
#else
  // Old version went forwards and then backwards:
  // search forward for it:
  l = top_;
  for (; l; l = item_next(l)) 
   {
    h1 = item_quick_height(l);
    if (l == p) 
    {
      if (Y <= H) { // it is visible or right at bottom
	Y = Y+h1-H; // find where bottom edge is
	if (Y > 0) position(real_position_+Y); // scroll down a bit
      } else {
	position(real_position_+Y-(H-h1)/2); // center it
      }
      return;
    }
    Y += h1;
  }
  // search backward for it, if found center it:
  l = lp;
  Y = -offset_;
  for (; l; l = item_prev(l)) {
    h1 = item_quick_height(l);
    Y -= h1;
    if (l == p) {
      if ((Y + h1) >= 0) position(real_position_+Y);
      else position(real_position_+Y-(H-h1)/2);
      return;
    }
  }
#endif
}

// redraw, has side effect of updating top and setting scrollbar:

void Fl_Ext_TreeBrowser::draw() 
 {
  int drawsquare = 0;
  if (damage() & FL_DAMAGE_ALL) 
   { // redraw the box if full redraw
    Fl_Boxtype b = box() ? box() : FL_DOWN_BOX;
    draw_box(b, x(), y(), w(), h(), color());
    drawsquare = 1;
   }

  update_top();
  int full_width_ = full_width();
  int full_height_ = full_height();
  int X, Y, W, H; 
  bbox(X, Y, W, H);
  int dont_repeat = 0;
J1:
  // see if scrollbar needs to be switched on/off:
  if ((has_scrollbar_ & VERTICAL) && ((has_scrollbar_ & ALWAYS_ON) || position_ || full_height_ > H)) 
   {
     if (!scrollbar.visible()) 
      {
       scrollbar.set_visible();
       drawsquare = 1;
       bbox(X, Y, W, H);
      }
    }
    else 
     {
       top_ = item_first(); real_position_ = offset_ = 0;
       if (scrollbar.visible()) 
         {
           scrollbar.clear_visible();
           clear_damage((uchar)(damage()|FL_DAMAGE_SCROLL));
         }
      }

  if ((has_scrollbar_ & HORIZONTAL) && ((has_scrollbar_ & ALWAYS_ON) || hposition_ || full_width_ > W)) 
    {
      if (!hscrollbar.visible()) 
       {
         hscrollbar.set_visible();
         drawsquare = 1;
         bbox(X, Y, W, H);
       }
     } 
     else 
      {
        real_hposition_ = 0;
        if (hscrollbar.visible()) 
         {
           hscrollbar.clear_visible();
           clear_damage((uchar)(damage()|FL_DAMAGE_SCROLL));
         }
       }

  // Check the vertical scrollbar again, just in case it needs to be drawn
  // because the horizontal one is drawn.  There should be a cleaner way
  // to do this besides copying the same code...
  if ((has_scrollbar_ & VERTICAL) && ((has_scrollbar_ & ALWAYS_ON) || position_ || full_height_ > H)) 
   {
      if (!scrollbar.visible()) 
       {
         scrollbar.set_visible();
         drawsquare = 1;
         bbox(X, Y, W, H);
       }
   } 
   else 
     {
        top_ = item_first(); real_position_ = offset_ = 0;
        if (scrollbar.visible()) 
        {
          scrollbar.clear_visible();
          clear_damage((uchar)(damage()|FL_DAMAGE_SCROLL));
        }
     }
/// Sairi ama bika 
   bbox(X, Y, W, H);
  fl_clip(X, Y, W, H);

  // for each line, draw it if full redraw or scrolled.  Erase background
  // if not a full redraw or if it is selected:
  Fl_Ext_TreeItem* l = top();
  int yy = -offset_;
  for (; l && yy < H; l = item_next(l)) 
  {
    int hh = item_height(l);
    if (hh <= 0) continue;
    if ((damage()&(FL_DAMAGE_SCROLL|FL_DAMAGE_ALL)) || l == redraw1 || l == redraw2) 
    {
    	fl_push_clip(X, yy+Y, W, hh);
	// A box for erasing the background
	// This should be available for erasing the wrong drawing on the screen
	 draw_box(box() ? box() : FL_DOWN_BOX, x(), y(), w(), h(), color()); // this will erase the background
	
	  fl_pop_clip();
      item_draw(l, X-hposition_, yy+Y, W+hposition_, hh);
     
      int ww = item_width(l);
      if (ww > max_width) {max_width = ww; max_width_item = l;}
    }
    yy += hh;
  }
  // erase the area below last line:
  if (!(damage()&FL_DAMAGE_ALL) && yy < H) 
  {
    fl_push_clip(X, yy+Y, W, H-yy);
    draw_box(box() ? box() : FL_DOWN_BOX, x(), y(), w(), h(), color());
    fl_pop_clip();
  }
  fl_pop_clip();
  redraw1 = redraw2 = 0;

  if (!dont_repeat) 
  {
    dont_repeat = 1;
    // see if changes to full_height caused by calls to slow_height
    // caused scrollbar state to change, in which case we have to redraw:
    full_height_ = full_height();
    full_width_ = full_width();
    if ((has_scrollbar_ & VERTICAL) && ((has_scrollbar_ & ALWAYS_ON) || position_ || full_height_>H)) 
    {
      if (!scrollbar.visible()) 
        goto J1;
    } 
    else 
    {
      if (scrollbar.visible()) 
        goto J1;
    }
    if ((has_scrollbar_ & HORIZONTAL) &&((has_scrollbar_ & ALWAYS_ON) || hposition_ || full_width_>W)) 
    {
      if (!hscrollbar.visible()) 
         goto J1;
    } 
    else 
    {
      if (hscrollbar.visible()) 
        goto J1;
    }
  }

  // update the scrollbars and redraw them:
  int dy = top_ ? item_quick_height(top_) : 0; if (dy < 10) dy = 10;
  if (scrollbar.visible()) 
  {
    scrollbar.damage_resize(
	scrollbar.align()&FL_ALIGN_LEFT ? X-scrollbar_width_ : X+W,
	Y, scrollbar_width_, H);
    scrollbar.value(position_, H, 0, full_height_);
    scrollbar.linesize(dy);
    if (drawsquare) draw_child(scrollbar);
    else update_child(scrollbar);
  }
  if (hscrollbar.visible()) {
    hscrollbar.damage_resize(
	X, scrollbar.align()&FL_ALIGN_TOP ? Y-scrollbar_width_ : Y+H,
	W, scrollbar_width_);
    hscrollbar.value(hposition_, W, 0, full_width_);
    hscrollbar.linesize(dy);
    if (drawsquare) draw_child(hscrollbar);
    else update_child(hscrollbar);
  }

  // draw that little square between the scrollbars:
  if (drawsquare && scrollbar.visible() && hscrollbar.visible()) {
    fl_color(parent()->color());
    fl_rectf(scrollbar.x(), hscrollbar.y(), scrollbar_width_,scrollbar_width_);
  }

  real_hposition_ = hposition_;
}


// intializing everything:
void Fl_Ext_TreeBrowser::new_list() 
{
  top_ = 0;
  position_ = real_position_ = 0;
  hposition_ = real_hposition_ = 0;
  selection_ = 0;
  offset_ = 0;
  max_width = 0;
  max_width_item = 0;
  redraw_lines();
}


// Replace an Item by another
void Fl_Ext_TreeBrowser::replacing(Fl_Ext_TreeItem* a, Fl_Ext_TreeItem* b) 
{
  redraw_line(a);
  if (a == selection_) 
     selection_ = b;
  if (a == top_) 
     top_ = b;
  if (a == max_width_item) 
  {
        max_width_item = 0;
         max_width = 0;
  }
}

// find item under mouse!
Fl_Ext_TreeItem* Fl_Ext_TreeBrowser::find_item(int my)
{
  update_top();
  int X, Y, W, H; 
  bbox(X, Y, W, H);
  Fl_Ext_TreeItem* l;
  int yy = Y-offset_;
  for (l = top_; l; l = item_next(l)) 
  {
    int hh = item_height(l); 
    if (hh <= 0) continue;
    yy += hh;
    if (my <= yy || yy>=(Y+H)) 
      return l;
  }
  return 0;
}

// Select function
int Fl_Ext_TreeBrowser::select(Fl_Ext_TreeItem* l, int i, int docallbacks) 
{
  if (type() == FL_MULTI_BROWSER) 
  {
    if (selection_ != l) 
    {
      if (selection_) 
        redraw_line(selection_);
      selection_ = l;
      redraw_line(l);
    }
    if ((!i)==(!item_selected(l))) 
       return 0;
    item_select(l, i);
    redraw_line(l);
  } else {
    if (i && selection_ == l) return 0;
    if (!i && selection_ != l) return 0;
    if (selection_) 
    {
      item_select(selection_, 0);
      redraw_line(selection_);
      selection_ = 0;
    }
    if (i) {
      item_select(l, 1);
      selection_ = l;
      redraw_line(l);
      display(l);
    }
  }	    
  if (docallbacks) {
    set_changed();
    do_callback();
  }
  return 1;
}

// Deselect 
int Fl_Ext_TreeBrowser::deselect(int docallbacks) 
{
  if (type() == FL_MULTI_BROWSER) 
  {
    int change = 0;
    
    // ama la hala dachet 
    Fl_Ext_TreeItem* p=item_first();
    while (p)
     {
         change |= select(p, 0, docallbacks);
         p=p->m_pNext;
     }
    for (Fl_Ext_TreeItem* p = item_first(); p; p = item_next(p))
             change |= select(p, 0, docallbacks);
         
    return change;
  } 
  else 
  {
    if (!selection_) 
      return 0;
    item_select(selection_, 0);
    redraw_line(selection_);
    selection_ = 0;
    return 1;
  }
}
// Select the item or change the status of the item from 1 <--> 0 Mariwan
/// Check this if it is nessesary .. Mariwan ******
int Fl_Ext_TreeBrowser::select_only(Fl_Ext_TreeItem* l, int docallbacks) 
{
  if (!l) return deselect(docallbacks);
  int change = 0;
  if (type() == FL_MULTI_BROWSER) 
  {
    for (Fl_Ext_TreeItem* p = item_first(); p; p = item_next(p))
      if (p != l) 
         change |= select(p, 0, docallbacks);
  }
  change |= select(l, 1, docallbacks);
  display(l);
  return change;
}



/////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
int Fl_Ext_TreeBrowser::handle(int event) 
{
 
  // must do shortcuts first or the scrollbar will get them...
  if (event == FL_ENTER || event == FL_LEAVE) 
    return 1;
  if (event == FL_KEYBOARD && type() >= FL_HOLD_BROWSER) 
   {
    Fl_Ext_TreeItem* l1 = selection_;
    Fl_Ext_TreeItem* l = l1; 
    if (!l) l = top_; 
    if (!l) l = item_first();
    if (l) 
       {
      if (type()==FL_HOLD_BROWSER) 
         switch (Fl::event_key()) 
         {
           case FL_Down:
	                          while ((l = item_next(l)))
	                          if (item_height(l)>0) 
                              {
                                select_only(l, 1);
                                break;
                              }
	                          return 1;
           case FL_Up:
	                          while ((l = item_prev(l))) if (item_height(l)>0) 
                              {
	                             select_only(l, 1); 
                                 break;
                               }
	                           return 1;
         } 
         else 
          switch (Fl::event_key()) 
          {
           case FL_Enter:
           case FL_KP_Enter:
	                               select_only(l, 1);
	                               return 1;
            case ' ':
	                               selection_ = l;
                                   select(l, !item_selected(l), 1);
	                               return 1;
            case FL_Down:
	                               while ((l = item_next(l))) 
                                   {
	                                 if (Fl::event_state(FL_SHIFT|FL_CTRL))
	                                   select(l, l1 ? item_selected(l1) : 1, 1);
	                                 if (item_height(l)>0) goto J1;
	                               }
	                               return 1;
            case FL_Up:
	                               while ((l = item_prev(l))) 
                                   {
	                                 if (Fl::event_state(FL_SHIFT|FL_CTRL))
	                                   select(l, l1 ? item_selected(l1) : 1, 1);
	                                 if (item_height(l)>0) 
                                       goto J1;
	                               }
	                               return 1;
                           J1:
	                               if (selection_) 
                                      redraw_line(selection_);
	                                  selection_ = l; 
                                      redraw_line(l);
	                                  display(l);
	                                  return 1;
          }
        }
     }

  if (Fl_Group::handle(event)) 
     return 1;
  int X, Y, W, H, button;
  Fl_Ext_TreeItem *pItem; // THIS IS the change of the old event .. 
  bbox(X, Y, W, H);
  int my;
  static char change;
  static char whichway;
  static int py;
  switch (event) 
    {
       case FL_PUSH:
                       if (!Fl::event_inside(X, Y, W, H))  // thi click was not in the widget
                             return 0;
                       if (Fl::visible_focus()) 
                           Fl::focus(this);
                       my = py = Fl::event_y();
                       change = 0;
                         X = Fl::event_x();
                         Y = Fl::event_y();
                       if (type() == FL_NORMAL_BROWSER || !top_)
                        { // start of change  mariwan  2005-05-07
                                  ; // do nothing 
                        // just open or close the branch
                        
                            pItem = find_item(Y);
                            if(!pItem) return 0;
                             button = Fl::event_button(); // Get the kind of the click
                            if(Fl::event_clicks()) // if it is double click 
                            {
                              HandleInvoke(pItem);
                            }
                            else // or if it is right click 
                              if(button == FL_RIGHT_MOUSE)
                            {
                              HandleMenu(pItem->m_pData);
                            }
                            else // or if it is left click 
                              if(button == FL_LEFT_MOUSE)
                               {
                                // hide/show                       // +4 added by Mariwan
                                if(pItem->IsParent() && (X > (pItem->m_nLevel*10+3+4)) && (X <= (pItem->m_nLevel*10+13+4)) )
                                 {
                                   // Change the status of the Item by inverting the IsOpen status
                                  pItem->SetBranchVisible(!pItem->IsOpen());
                                  HandleSelect(pItem,1);
                                  redraw();
                                 }
                               }
                        }
                               
                       else
                        if (type() != FL_MULTI_BROWSER) 
                          {
                              
                        //  open or close the branch
                            pItem = find_item(Y);
                            if(!pItem) 
                              return 0;
                           
                            // ama dabet chak bikret halaya.. 
                             button = Fl::event_button(); // Get the kind of the click
                            if(Fl::event_clicks()) // if it is double click 
                            {
                              HandleInvoke(pItem);  // Double click has been occured
                            }
                            else // or if it is right click 
                              if(button == FL_RIGHT_MOUSE)
                            {
                              HandleMenu(pItem->m_pData);
                            }
                            else // or if it is left click 
                              if(button == FL_LEFT_MOUSE)
                               {
                                // hide/show                       // +4 added by Mariwan
                                if(pItem->IsParent() && (X > (pItem->m_nLevel*10+3+4)) && (X <= (pItem->m_nLevel*10+13+4)) )
                                 {
                                   // Change the status of the Item by inverting the IsOpen status
                                  pItem->SetBranchVisible(!pItem->IsOpen());
                                  HandleSelect(pItem,1);
                                  redraw();
                                 }
                                 else
                                 {  
                                   change = select_only(pItem, when() & FL_WHEN_CHANGED); // take action just in case the click is not open close
                                   HandleSelect(pItem,1); // added by Mariwan 2006-06-19  Note: this should be further checked if it needs to send 1 or 0 with the HandleSelect
                                  }
                               }
                            
                          } 
                           else 
                            {
                               Fl_Ext_TreeItem* l = find_item(my);
                               whichway = 1;
                              
                              {  // first do the open close branch 
                                
                               pItem = find_item(Y);
                               if(!pItem) 
                                  return 0;

                                if(!Select(pItem)) 
                                    return 0;

                               // hide/show                       // +4 added by Mariwan
                              if(pItem->IsParent() && (X > (pItem->m_nLevel*10+3+4)) && (X <= (pItem->m_nLevel*10+13+4)) )
                               {
                                 // Change the status of the Item by inverting the IsOpen status
                                 pItem->SetBranchVisible(!pItem->IsOpen());
                                 redraw();
                               }

                               if(Fl::event_clicks())
                               {
                                 HandleInvoke(pItem);
                               }
                               else 
                                  if(button == FL_RIGHT_MOUSE)
                                   {
                                   HandleMenu(pItem->m_pData);
                                   }
                               } // end of open - close branch
                               if (Fl::event_state(FL_CTRL)) 
                                 { // toggle selection:
                       TOGGLE:
	                                if (l) 
                                      {
	                                       whichway = !item_selected(l);
	                                       change = select(l, whichway, when() & FL_WHEN_CHANGED);
	                                  }
                                 } 
                               else 
                                 if (Fl::event_state(FL_SHIFT)) 
                                   { // extend selection:
	                                 if (l == selection_) 
                                       goto TOGGLE;
	                                 // state of previous selection determines new value:
	                                 whichway = l ? !item_selected(l) : 1;
	                                 // see which of the new item or previous selection is earlier,
	                                 // by searching from the previous forward for this one:
	                                 int down;
	                                 if (!l) down = 1;
	                                 else 
                                     {
                                       for (Fl_Ext_TreeItem* m = selection_; ; m = item_next(m)) 
                                        {
	                                    if (m == l) 
                                          {
                                              down = 1;
                                              break;
                                          }
                                        if (!m) 
                                          {
                                            down = 0;
                                            break;
                                          }
	                                      }
                                     }
	                                 if (down) 
                                       {
	                                     for (Fl_Ext_TreeItem* m = selection_; m != l; m = item_next(m))
	                                      select(m, whichway, when() & FL_WHEN_CHANGED);
	                                   } 
                                       else 
                                       {
	                                     Fl_Ext_TreeItem* e = selection_;
	                                     for (Fl_Ext_TreeItem* m = item_next(l); m; m = item_next(m)) 
                                          {
	                                         select(m, whichway, when() & FL_WHEN_CHANGED);
	                                         if (m == e) 
                                               break;
	                                      }
	                                    }
	                                  // do the clicked item last so the select box is around it:
	                                  if (l) 
                                         select(l, whichway, when() & FL_WHEN_CHANGED);
	                                  change = 1;
                                      }
                                      else 
                                      { // select only this item

	                                    change = select_only(l, when() & FL_WHEN_CHANGED);
                                      }
                               }
                               return 1;
       case FL_DRAG:
                          // do the scrolling first:
                          my = Fl::event_y();
                          if (my < Y && my < py) 
                          {
                            int p = real_position_+my-Y;
                            if (p<0) 
                               p = 0;
                               position(p);
                           } 
                           else 
                             if (my > (Y+H) && my > py) 
                              {
                                int p = real_position_+my-(Y+H);
                                int hh = full_height()-H;
                                if (p > hh) 
                                   p = hh;
                                if (p<0) p = 0;
                                position(p);
                               }
                             if (type() == FL_NORMAL_BROWSER || !top_)
                                ;
                                else 
                                  if (type() == FL_MULTI_BROWSER) 
                                 {
                                   Fl_Ext_TreeItem* l = find_item(my);
                                   Fl_Ext_TreeItem* t; 
                                   Fl_Ext_TreeItem* b; // this will be the range to change
                                   if (my > py) 
                                    { // go down
	                                   t = selection_ ? item_next(selection_) : 0;
	                                   b = l ? item_next(l) : 0;
                                    } 
                                      else 
                                     {	// go up
	                                    t = l;
	                                    b = selection_;
                                     }
                                    for (; t && t != b; t = item_next(t))
	                                change |= select(t, whichway, when() & FL_WHEN_CHANGED);
                                    if (l) 
                                      selection_ = l;
                                 } 
                                 else 
                                 {
                                   Fl_Ext_TreeItem* l1 = selection_;
                                   Fl_Ext_TreeItem* l = (Fl::event_x()<x() || Fl::event_x()>x()+w()) ? selection_ :	find_item(my);
                                   select_only(l, when() & FL_WHEN_CHANGED);
                                   change = (l != l1);
                                 }
                                 py = my;
                                 return 1;
       case FL_RELEASE:
                                 if (type() == FL_SELECT_BROWSER) 
                                 {
                                    Fl_Ext_TreeItem* t = selection_; 
                                    deselect(); 
                                    selection_ = t; 
                                  }
                                  if (change) 
                                  {
                                    set_changed();
                                    if (when() & FL_WHEN_RELEASE) 
                                      do_callback();
                                   } 
                                   else 
                                    {
                                      if (when() & FL_WHEN_NOT_CHANGED) do_callback();
                                    }
                                    return 1;

       case FL_FOCUS:
       case FL_UNFOCUS:
                                    if (type() >= FL_HOLD_BROWSER && Fl::visible_focus()) 
                                     {
                                        redraw();
                                        return 1;
                                      } 
                                     else 
                                       return 0;
       }

  return 0;
}


// Default versions of some of the virtual functions:

int Fl_Ext_TreeBrowser::item_quick_height(Fl_Ext_TreeItem* l)  {
  return item_height(l);
}

int Fl_Ext_TreeBrowser::incr_height()  
{
  return item_quick_height(item_first());
}

int Fl_Ext_TreeBrowser::full_height()  
{
  int t = 0;
  for (Fl_Ext_TreeItem* p = item_first(); p; p = item_next(p))
    t += item_quick_height(p);
  return t;
}

int Fl_Ext_TreeBrowser::full_width()  
{
  return max_width;
}

// select or deselect depending on the status 1 is select 0 is deselect
void Fl_Ext_TreeBrowser::item_select(Fl_Ext_TreeItem* l, int status) 
{
l->m_bSelected=status;
return;
}

// Return itmes condition if selected 1 else 0
int Fl_Ext_TreeBrowser::item_selected(Fl_Ext_TreeItem* l) const 
{
    if (l)
    {
       return l->m_bSelected;
    }
     else 
      return 0;
}


/////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////


Fl_Ext_TreeBrowser::Fl_Ext_TreeBrowser(int X, int Y, int W, int H, const char *l /* =0 */): Fl_Group(X, Y, W, H, l), 
                     scrollbar(0, 0, 0, 0, 0), // they will be resized by draw()
                     hscrollbar(0, 0, 0, 0, 0)
{
  box(FL_NO_BOX);
  align(FL_ALIGN_BOTTOM);
  position_ = real_position_ = 0;
  hposition_ = real_hposition_ = 0;
  offset_ = 0;
  top_ = 0;
  when(FL_WHEN_RELEASE_ALWAYS);
  selection_ = 0;
  color(FL_BACKGROUND2_COLOR, FL_SELECTION_COLOR);
  scrollbar.callback(scrollbar_callback);
  scrollbar.align(FL_ALIGN_LEFT|FL_ALIGN_BOTTOM); // back compatability?
  hscrollbar.callback(hscrollbar_callback);
  hscrollbar.type(FL_HORIZONTAL);
  textfont_ = FL_HELVETICA;
  textsize_ = (uchar)FL_NORMAL_SIZE;
  textcolor_ = FL_FOREGROUND_COLOR;
  has_scrollbar_ = BOTH;
  max_width = 0;
  max_width_item = 0;
  redraw1 = redraw2 = 0;
  type(FL_SELECT_BROWSER);
  end();
  // Fl_ext_Tree origional 
  scrollbar_right() ;    // by Mariwan to let the scroolbar be in the right side (should)
  when(FL_WHEN_RELEASE);
  Fl_Widget::callback(_s_DefaultCallback);
  m_pFirst = m_pLast = NULL;

}


Fl_Ext_TreeBrowser::~Fl_Ext_TreeBrowser()
{
  _Remove(NULL, 1); // Erase everything
}

// Adding Item to the tree 
Fl_Ext_TreeItem* Fl_Ext_TreeBrowser::add_item(int nLevel, char *label, uchar x, Fl_Ext_TreeItem* pItemBase)         
{
  Fl_Ext_TreeItem *pTreeItem = new Fl_Ext_TreeItem;

  pTreeItem->m_nLevel = nLevel;
  pTreeItem->m_pData = strdup(label);
  pTreeItem->m_pPrev=0; //avoiding undefined link
  pTreeItem->m_pNext=0;  //avoiding undefined link
  pTreeItem->type(x);
  
       
    switch (pTreeItem->type())
    { // Decide wich picture will be drawn near to the text
      case FL_TREE_ITEM_NOPICTURE     :         {pTreeItem->m_PixmapPicture=0;    break;}  
      case FL_TREE_ITEM_DESKTOP       :         {pTreeItem->m_PixmapPicture=new Fl_Pixmap(desktop_xpm); break;}
      case FL_TREE_ITEM_HOME          :         {pTreeItem->m_PixmapPicture=new Fl_Pixmap(home_xpm);    break;}
      case FL_TREE_ITEM_FLOPPY        :         {pTreeItem->m_PixmapPicture=new Fl_Pixmap(floppy_unmount_xpm);    break;}
      case FL_TREE_ITEM_HARDDISK      :         {pTreeItem->m_PixmapPicture=new Fl_Pixmap(harddisk_xpm);    break;}
      case FL_TREE_ITEM_CDROM         :         {pTreeItem->m_PixmapPicture=new Fl_Pixmap(cdrom_unmount_xpm);    break;}
      case FL_TREE_ITEM_FOLDER        :         {pTreeItem->m_PixmapPicture=new Fl_Pixmap(Folder_xpm);          break; }
      case FL_TREE_ITEM_FOLDERCLOSED  :         {pTreeItem->m_PixmapPicture=new Fl_Pixmap(Folder_xpm);    break;}
      case FL_TREE_ITEM_FOLDEROPEN    :         {pTreeItem->m_PixmapPicture=new Fl_Pixmap(FolderOpened_xpm);    break;}
      case FL_TREE_ITEM_REMOTHARDDISK :         {pTreeItem->m_PixmapPicture=new Fl_Pixmap(harddisk_xpm);    break;}
      case FL_TREE_ITEM_NETWORK       :         {pTreeItem->m_PixmapPicture=new Fl_Pixmap(network_xpm);    break;}
      case FL_TREE_ITEM_CONTROLPANNEL :         {pTreeItem->m_PixmapPicture=new Fl_Pixmap(control_panel_xpm);    break;}
      case FL_TREE_ITEM_RECYCLEEMPTY  :         {pTreeItem->m_PixmapPicture=new Fl_Pixmap(trashcan_empty_xpm);    break;}
      case FL_TREE_ITEM_RECYCLEFULL   :         {pTreeItem->m_PixmapPicture=new Fl_Pixmap(trashcan_full_xpm);    break;}
      default                         :         {pTreeItem->m_PixmapPicture=new Fl_Pixmap(Folder_xpm);          break; }
    }          

return Fl_Ext_TreeBrowser::Add( pItemBase,  pTreeItem,0 ); //Add this item to the tree do not select it 
};
