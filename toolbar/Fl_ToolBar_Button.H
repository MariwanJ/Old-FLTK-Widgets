//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Fl_ToolBar_Button.h      v 0.0.1                          2006-01-02 
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


#ifndef FL_TOOLBAR_BUTTON_H
#define FL_TOOLBAR_BUTTON_H

#include "Fl_Button_Cell.H" // inheriting class's header file


// Toolbar button
class Fl_ToolBar_Button : public Fl_Button_Cell
{
	public:
		// class constructor
		Fl_ToolBar_Button(int x, int y, int w, int h, const char *l);
                Fl_ToolBar_Button *pItemNext;
                Fl_ToolBar_Button *pItemPrev;
		// class destructor
		~Fl_ToolBar_Button();


};

#endif // FL_TOOLBAR_BUTTON_H
