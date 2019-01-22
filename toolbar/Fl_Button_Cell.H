//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Fl_Button_Cell.h     v 0.0.1                             2006-01-02 
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



#ifndef FL_CELL_H
#define FL_CELL_H
#include <Fl/Fl.H> // inheriting class's header file
#include <Fl/Fl_Widget.H> // inheriting class's header file
#include <Fl/Fl_Shared_Image.H> // inheriting class's header file
#include <Fl/fl_draw.H> // inheriting class's header file
#include <iostream>


enum Fl_PicTex_Style
{	// align() values
// picture Over Text and (Center, Left & Right)
  FL_Pic_Over_Text_CENTER	                  	= 0,
  FL_Pic_Over_Text_LEFT		                    = 3,
  FL_Pic_Over_Text_RIGHT		                = 4,

// pictuer Under Text and (Center,  Left & Right)
  FL_Pic_Under_Text_CENTER	                  	= 5,
  FL_Pic_Under_Text_LEFT		                = 8,
  FL_Pic_Under_Text_RIGHT		                = 9,

// pictuer Left To Text and (Center,Left & Right)
  FL_Pic_LeftTo_Text_CENTER	                  	= 10,
  FL_Pic_LeftTo_Text_LEFT		                = 13,
  FL_Pic_LeftTo_Text_RIGHT		                = 14,
  
// pictuer Right To Text and (Center, Left & Right)
  FL_Pic_RightTo_Text_CENTER	               	= 15,
  FL_Pic_RightTo_Text_LEFT		                = 18,
  FL_Pic_RightTo_Text_RIGHT		                = 19,
  
};




// No description
class Fl_Button_Cell : public Fl_Widget
{
   private:
           int                value;
           const char         * lab;
           Fl_Image           *cellImage;
           //nX, nY is label start point .. nXX and nYY is Picture start point
           int nX, nY, nXX, nYY,nH,nW,labelWidth, labelHeight, pictWidth, pictHeight;

           int                cellStyle_;
   protected:
           virtual   void      draw();
           virtual int         handle(int e);

	public:

           int cellStyle();
           void cellStyle(int);
           void                item_draw();
           
                       
		// class constructor
		Fl_Button_Cell(int x, int y, int w, int h, const char* l);
		// class destructor
		~Fl_Button_Cell();
};

#endif // FL_CELL_H
