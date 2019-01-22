//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//  Fl_SystemDirectory_Browser.h      v 0.0.1                              2006-06-19 
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

#ifndef FL_SYSTEMDIRECTORY_BROWSER_H
#define FL_SYSTEMDIRECTORY_BROWSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "fl_systemdirectory_icons.h"
#include "Fl_Ext_Tree_Browser.h" // inheriting class's header file
#include "fl_ext_tree_item.h"


#include <Fl/filename.H>
#include <Fl/Fl_File_Icon.h>
#include <Fl/x.h>
#include <FL/fl_draw.H>
#include "flstring.h"

// See if this required ... Start---+
#ifdef __CYGWIN__
#  include <mntent.h>
#elif defined(WIN32)
#  include <windows.h>
#  include <direct.h>
// Apparently Borland C++ defines DIRECTORY in <direct.h>, which
// interfers with the Fl_File_Icon enumeration of the same name.
#  ifdef DIRECTORY
#    undef DIRECTORY
#  endif // DIRECTORY
#endif // __CYGWIN__

#ifdef __EMX__
#  define  INCL_DOS
#  define  INCL_DOSMISC
#  include <os2.h>
#endif // __EMX__
// See if this required ... END---+

// System File Directory Widget .. by Mariwan Jalal
class Fl_SystemDirectory_Browser : public Fl_Ext_TreeBrowser
{
	public:
		// class constructor
       Fl_SystemDirectory_Browser(int, int, int, int, const char *);
		// class destructor
      ~Fl_SystemDirectory_Browser();
    virtual int DriverLoad(const char*);	// I - Sort function to use
    Fl_Ext_TreeItem* DirectoryLoad( char  *PathOrDriver, Fl_Ext_TreeItem * pItemBase);	// I - Sort function to use
    int UpdateDirList(Fl_Ext_TreeItem *StartItem)    ;
    int CheckIfTheTreeHasThisItem(char *pItemToCheck, Fl_Ext_TreeItem * pItemBaseToCheckedItem);   // check if you can find this item under the mentioned base item (return non zero if it find it)
    Fl_Ext_TreeItem * ItemToDirectoryUpdate( char  *PathOrDriver, Fl_Ext_TreeItem * pItemBase);
    virtual int   (HandleSelect)( Fl_Ext_TreeItem* pData, int bState);  // A Callback function pointer left for the user : 
    virtual int   (HandleInvoke)(Fl_Ext_TreeItem *ItemSquareClicked );              // A Callback function pointer left for the user :  double click 
    virtual int   (HandleMenu)(void *pData);                                      /// left for the user
    virtual char*   GetItemToDirectory(Fl_Ext_TreeItem *pItem); // Converting the Item name to a directory path

};

#endif // FL_SYSTEMDIRECTORY_BROWSER_H

