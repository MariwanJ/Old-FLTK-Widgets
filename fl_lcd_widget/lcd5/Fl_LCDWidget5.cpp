// "$Id: Fl_LCDWidget5.cpp,v 0.0.1  2004/12/12 17:15"
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

#include "Fl_LCDWidget5.h"

// Change the data hear to get what you wish to show!!
// Any 8x8 Bitmap charachter .. 

int Fl_LCDWidget5::valuebitmap[256][8]={
                        {0,6,9,9,9,9,9,6},   //0
                        {0,2,6,2,2,2,2,7},       //1
                        {0,6,9,1,2,4,8,15},     //2
                        {0,6,9,1,2,1,9,6},      //3
                        {0,2,10,10,15,2,2,2},    //4
                        {0,15,8,15,1,1,9,6},     //5
                        {0,2,4,6,9,9,9,6},    //6
                        {0,15,1,2,4,8,8,8},    //7
                        {0,6,9,9,6,9,9,6},    //8
                        {0,6,9,9,7,2,4,8},     //9
                        {0,0,6,6,0,6,6,0}      //10 ::
                        };


// Addition of a number -- many times
int Fl_LCDWidget5::Addition(int base, int timesAdd)
{
int result=0;
for (int i=0;i<timesAdd;i++)
{
result=base+result;
}
return result;

}
// Power calculation
int Fl_LCDWidget5::power(int base, int topower)
{
int result=1;
for (int i=0;i<topower;i++)
{
result=base*result;
}
return result;

}


Fl_LCDWidget5::~Fl_LCDWidget5()
{
//Destructor
}
//Constructor
Fl_LCDWidget5::Fl_LCDWidget5(int x, int y, int w, int h, char* l,int v):Fl_Widget(x,y,w,h,l)
{
box(FL_NO_BOX);
value=v;
// Default color
    Fl_LCDWidget5::ONCOLOR=FL_DARK_CYAN;
    Fl_LCDWidget5::OFFCOLOR=FL_FOREGROUND_COLOR;
}

//Constructor
Fl_LCDWidget5::Fl_LCDWidget5(int w, int h, char *l, int v):Fl_Widget(0,0,w,h,l)
{
value=v;
    Fl_LCDWidget5::ONCOLOR=FL_RED;
    Fl_LCDWidget5::OFFCOLOR=FL_FOREGROUND_COLOR;
}

// Set ON OFF Color 
void Fl_LCDWidget5::SetONOFFCOLOR( Fl_Color ONcolor, Fl_Color OFFcolor)
{
this->OFFCOLOR=OFFcolor;
this->ONCOLOR=ONcolor;
}

//Draw function .. Here all drawing is done 
void Fl_LCDWidget5::draw()
{
 draw_box();
 align(FL_ALIGN_BOTTOM);
 draw_label();
//draw_label();     Should be fixed
widthofpixel = 6;
int sizegive =19;
 // All the rows
for (int i=0;i<8;i++)
{
  // One line 
  
  for (int j=0;j<=5;j++)
   {
   if (valuebitmap[this->value][i]&(power(2,5-j)))  
     {
       ONOFFCOLOR = ONCOLOR;
       fl_color(ONOFFCOLOR);
       fl_rectf(x()+((Addition(2,(j+1)))*w())/sizegive, -2+y()+((Addition(2,(i+1))-1)*h())/sizegive, w()/widthofpixel,h()/widthofpixel);
      }
   else
   if (!1==1){
             ONOFFCOLOR = OFFCOLOR;
             fl_color(ONOFFCOLOR);
             fl_rectf(x()+((Addition(2,(j+1)))*w())/sizegive, -2+y()+((Addition(2,(i+1))-1)*h())/sizegive, w()/widthofpixel,h()/widthofpixel);
            }

   }

}


}
// Get widgets value
int Fl_LCDWidget5::LCD_Value()
{
return value;
}
//Set widgets value
void Fl_LCDWidget5::LCD_Value(int& v)
{
value=v;
damage(FL_DAMAGE_CHILD);
}
