//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

// Fl_Ext_TreeItem.cpp     v 0.0.1                              2006-06-19 
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




#include "fl_ext_tree_item.h"

#include <string.h>
#include <stdio.h>
//////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

void Fl_Ext_TreeItem::HandleFree(void )
{
     
return;     
     
}



// Set Item type (this affect the pixmap drawn)
void Fl_Ext_TreeItem::type(uchar typestype)
{
  type_= typestype;
}
// Return the type
uchar Fl_Ext_TreeItem::type()
{
  return type_;
}
//Constructor of Item class
Fl_Ext_TreeItem::Fl_Ext_TreeItem()
{
  m_nLevel = 0;   // Level at the begining
  m_bVisible = 1;  // Visible  0 not 1 visible
  m_bSelected = 0;  // Selected or not 0 not 1 selected
  type_=FL_TREE_ITEM_FOLDER; // Use folder picture as standard

  m_pPrev = NULL;  // No previous
  m_pNext = NULL;  // No next
  m_pData = NULL;  // No data or name
  m_bGrey=  0;  // Not Grey
  }

int Fl_Ext_TreeItem::GetGrey(void)
{
 return m_bGrey;
}

int Fl_Ext_TreeItem::SetGrey(int bSet)
{
//Avoid error
if (this)
{
      if (bSet <0) bSet =0;
      if (bSet >1) bSet =1;
      m_bGrey=bSet; //Set Grey
      cb_GetGrey();
      return 1;
}

     return 0; //error
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

//Item class Destructor
Fl_Ext_TreeItem::~Fl_Ext_TreeItem()
{
#ifdef DEBUG
  if(cb_GetName && m_pData) printf("deleting tree item %s\n", (*cb_GetName)(m_pData));
#endif
  if (!(this->m_PixmapPicture==0))  // make sure the pixmap has been deleted
    delete this->m_PixmapPicture;
    HandleFree(); // do the callback 
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// the funnction is not implimented .. to be done in the future
int   Fl_Ext_TreeItem::cb_GetGrey()    // A Callback function pointer left for the user : 
{
     return 0;  
}


char *Fl_Ext_TreeItem::GetName()
{
     // this return the item name 
     // the function could be re-writen it is vertual 
     if(this)
       if (!((m_pData==0)||(strlen((char*)(m_pData))==0)||(this==0)))
           return ((char*)(m_pData)); 
    return ""; // return nothing when error occure
}

int Fl_Ext_TreeItem::IsParent()
{
  if(!(m_pNext)) return 0; // no other item in the tree so get out with Zero result
  
  return (m_pNext->m_nLevel > m_nLevel);  // return if the next item is a higher level (i.e child)
  
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


int Fl_Ext_TreeItem::IsOpen()
{
  if(!IsParent()) 
    return 0;
   return m_pNext->m_bVisible; //  return if it is visible  - this is for the childs only
  }

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


Fl_Ext_TreeItem *Fl_Ext_TreeItem::GetParent(void) // Return the parent to the child if available
{
  if(!(m_nLevel)) 
    return NULL;  // error

  Fl_Ext_TreeItem *pPrev = m_pPrev; // Get previous
  while(pPrev) // Search for the parrent
  {
    if(pPrev->m_nLevel < m_nLevel)   // if the parrent found go out and return it
       break;
    if(pPrev->m_nLevel == 0 )  //whe have reached the first item
    {
      return 0; // the item dose not has any parent
      break;   //
      
    }
    
    pPrev = pPrev->m_pPrev;  // Get previous item
  }
  
  return pPrev; // Return the result (the parrent)
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// This determine the last child
Fl_Ext_TreeItem *Fl_Ext_TreeItem::GetLastChild(void)
{
  Fl_Ext_TreeItem *pNext = m_pNext;
  if(!pNext) return NULL;
  if(pNext->m_nLevel != m_nLevel + 1) return NULL;

  // find last in this branch
  Fl_Ext_TreeItem *pTemp = NULL;

  while(pNext)
  {
    if(pNext->m_nLevel <= m_nLevel) break;
    pTemp = pNext;
    pNext = pNext->m_pNext;
  }

  return pTemp;
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

// is it the last?
int Fl_Ext_TreeItem::IsLastSibling()
{
  Fl_Ext_TreeItem *pNnext = m_pNext;
  while(pNnext)
  {
    if(pNnext->m_nLevel <= m_nLevel) break;

    pNnext = pNnext->m_pNext;
  }

  if(!pNnext) return 1;
  
  return (pNnext->m_nLevel < m_nLevel);
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

// is it the first?
int Fl_Ext_TreeItem::IsFirstSibling()
{
  Fl_Ext_TreeItem *pPrev = m_pPrev;
  while(pPrev)
  {
    if(pPrev->m_nLevel <= m_nLevel) break;

    pPrev = pPrev->m_pPrev;
  }

  if(!pPrev) return 1;
  
  return (pPrev->m_nLevel < m_nLevel);
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


// changed to stop at lower level when expanding
// Show the branch 
int Fl_Ext_TreeItem::SetBranchVisible(int bVisible)
{
  if(!IsParent()) return 0;

  if(m_pNext->m_bVisible == bVisible) return 0;

  Fl_Ext_TreeItem *pNnext = m_pNext;
    
  while(pNnext)
  {
    if(pNnext->m_nLevel <= m_nLevel) break;

    if(!bVisible || (bVisible && pNnext->m_nLevel == (m_nLevel+1))) // only expand immediate children
    {
      pNnext->m_bVisible = bVisible;
    }

    if(!bVisible) // not visible so hide them.
       pNnext->m_bSelected = 0; // de-select all sub-items when hiding
    pNnext = pNnext->m_pNext;
  }
  
  return 1;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
