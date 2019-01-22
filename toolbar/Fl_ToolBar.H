//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Fl_ToolBar.h     v 0.0.1                             2006-01-02 
//
//         for the Fast Light Tool Kit (FLTK) 1.1.x .
//
//    by Mariwan Jalal
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



#ifndef FL_TOOLBAR_H
#define FL_TOOLBAR_H

#include <FL/Fl_Window.H> // inheriting class's header file
#include <FL/Fl_Group.H> // inheriting class's header file
#include "Fl_ToolBar_Button.H" // inheriting class's header file

// A toolbar widget using Fl_Cell
class Fl_ToolBar : public Fl_Group
{
	public:
		// class constructor
    	Fl_ToolBar(int x, int y, int h, int w , const char* l);
void    SetDockable(int gData); 
int     GetDockable(); 
        Fl_ToolBar_Button* addButton(const char *l, Fl_Image *img);
		~Fl_ToolBar();
protected:
virtual  int handle(int e);
virtual  void draw();
         Fl_ToolBar_Button *pItemFirst;
         Fl_ToolBar_Button *pItemLast;

  private: 
         static int offset[2];
         int dockable; //  1 docable , 0 not 
         int xCell;
         int yCell;
         int wCell;
         int hCell;
         
        
	

};

#endif // FL_TOOLBAR_H
