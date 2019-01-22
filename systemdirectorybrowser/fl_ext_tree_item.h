//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Fl_Ext_TreeItem.h     v 0.0.1                              2006-06-19 
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


#ifndef FL_EXT_TREE_ITEM_H
#define FL_EXT_TREE_ITEM_H
#include <Fl/Fl_Pixmap.h>

// defenition of Item type
#define       FL_TREE_ITEM_NOPICTURE              0
#define       FL_TREE_ITEM_DESKTOP                1   
#define       FL_TREE_ITEM_HOME                   2
#define       FL_TREE_ITEM_FLOPPY                 3
#define       FL_TREE_ITEM_HARDDISK               4
#define       FL_TREE_ITEM_CDROM                  5
#define       FL_TREE_ITEM_FOLDER                 6
#define       FL_TREE_ITEM_FOLDERCLOSED           7
#define       FL_TREE_ITEM_FOLDEROPEN             8
#define       FL_TREE_ITEM_REMOTHARDDISK          9
#define       FL_TREE_ITEM_NETWORK                10
#define       FL_TREE_ITEM_CONTROLPANNEL          11
#define       FL_TREE_ITEM_RECYCLEEMPTY           12
#define       FL_TREE_ITEM_RECYCLEFULL            13
                               

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


class Fl_Ext_TreeItem   // Item class which used by the tree browser
{
friend class Fl_Ext_TreeBrowser;
public:
  Fl_Ext_TreeItem();
  virtual ~Fl_Ext_TreeItem();

  // user setable callbacks etc.
  
// Get Item name to the root . 
   virtual char *GetName(); // return a pointer to a string
   virtual int SetGrey(int bSet); // set Grey.
   int GetGrey(void);
   virtual int cb_GetGrey();
   void* m_pData;    // Item name 

  int IsOpen(void);    
  int IsParent(void);

  Fl_Ext_TreeItem *GetParent(void);                      //  Get  Parent item
  Fl_Ext_TreeItem *GetLastChild(void);                   //  Get Last child in the tree

  int IsLastSibling();
  int IsFirstSibling();

  int SetBranchVisible(int bVisible);
  uchar type_;
  void type( uchar );
public:
  int m_nLevel;                        // Level of the item 
  int m_bVisible;                      //  
  int m_bSelected;                     // selected
  int m_bGrey;                         // grey or not 1 grey 0 not 
uchar type();

  Fl_Pixmap *m_PixmapPicture;          // item's picture 
  
  Fl_Ext_TreeItem *m_pPrev;            // Previous item
  Fl_Ext_TreeItem *m_pNext;            // Next Item
  
  // USER callbacks 
  
   virtual void  HandleFree(void );   // When Item deleted and Mem cleaned 
 
};


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


#endif // FL_EXT_TREE_ITEM_H


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
