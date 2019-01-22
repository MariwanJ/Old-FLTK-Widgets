// "$Id: Fl_LCD_Clock4.H,v 0.0.1  2004/12/12 17:15"
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


#ifndef FL_LCD_CLOCK_H
#define FL_LCD_CLOCK_H

#include <FL/Fl_Widget.h> // inheriting class's header file
#include "Fl_LCDWidget4.h"

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <math.h>
#include <time.h>
#ifndef WIN32
#  include <sys/time.h>
#endif /* !WIN32 */


/*
 * Digital Clock
 */
 
class FL_EXPORT Fl_LCD_Clock4 : public Fl_Widget
{
	public:
//	friend class  Fl_LCDWidget;
	int HH;
	int MM;
	int SS;
	
	int Hours();
	int Mins();
	int Secs();
	
	Fl_LCDWidget4*w1;
    Fl_LCDWidget4*w2;
	Fl_LCDWidget4*w3;
	Fl_LCDWidget4*w4;
	Fl_LCDWidget4*w5;
	
	void value(int , int, int );
	void value(ulong v);
    int value();
		// class constructor
		Fl_LCD_Clock4(int, int, int ,int, char*);
		// class destructor
		~Fl_LCD_Clock4();
    int handle(int );
    protected:
     void  draw();
};

#endif // FL_LCD_CLOCK_H

