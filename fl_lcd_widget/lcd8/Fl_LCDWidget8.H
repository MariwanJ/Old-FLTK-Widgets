// "$Id: Fl_LCDWidget8.H,v 0.0.1  2004/12/12 17:15"
//
// LCD Widget for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2003 by Bill Spitzak, Mariwan Jalal & others.
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
// Please report all bugs and problems to "mariwan.jalal@gmail.com".
//

#ifndef _FL_LCDWIDGET8_H_
#define _FL_LCDWIDGET8_H_

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Widget.H>

class Fl_LCDWidget8 : public Fl_Widget {

public :
    
    Fl_LCDWidget8(int, int, int, int, char*,int); // Constructor
    ~Fl_LCDWidget8();           // Destructor
    int LCD_Value();          // Get Value
    void LCD_Value(int &v);  // Set Value
    void draw();          // Draw Function 
    static int valuebitmap[256][8];
    Fl_Color ONOFFCOLOR;  // Color variable (used)
    Fl_Color OFFCOLOR;   // OFF color
    Fl_Color ONCOLOR;  // On color
    int value;        // Widgets value
    int widthofpixel; // Width between pixels
    void SetONOFFCOLOR( Fl_Color, Fl_Color);
private:

    int Addition(int ,int);  // Power calculation
    int power(int ,int);      // 
    

};



#endif 
