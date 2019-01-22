// "$Id: Fl_LCDWidget8.cpp,v 0.0.1  2004/12/12 17:15"
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

#include "Fl_LCDWidget8.h"


int Fl_LCDWidget8 ::valuebitmap[256][8]={
                        {0,24,36,36,36,36,36,24},   //0
                        {0,8,24,8,8,8,8,28},       //1
                        {0,24,36,4,8,16,32,60},     //2
                        {0,24,36,4,8,4,36,24},      //3
                        {0,0,64,72,72,124,8,8},    //4
                        {0,60,32,56,4,4,36,24},     //5
                        {0,12,16,32,60,36,36,24},    //6
                        {0,60,4,4,8,16,16,16},    //7
                        {0,24,36,36,24,36,36,24},    //8
                        {0,24,36,36,28,4,8,48},     //9
                        {0,0,0,24,24,0,24,24},      //10
                        {60,66,165,129,165,153,66,60},
                        {2,5,0,7,133,135,129,255},
                        {1,1,25,17,57,129,129,255},
                        {0,24,36,36,60,36,36,36},
                        {0,24,36,36,56,36,36,56}
                        };






// Addition of a number -- many times
int Fl_LCDWidget8::Addition(int base, int timesAdd)
{
int result=0;
for (int i=0;i<timesAdd;i++)
{
result=base+result;
}
return result;

}
// Power calculation
int Fl_LCDWidget8::power(int base, int topower)
{
int result=1;
for (int i=0;i<topower;i++)
{
result=base*result;
}
return result;

}


Fl_LCDWidget8::~Fl_LCDWidget8()
{
//Destructor
}
//Constructor
Fl_LCDWidget8::Fl_LCDWidget8(int x, int y, int w, int h, char* l,int v):Fl_Widget(x,y,h,w,l)
{
value=v;
// Default color
    Fl_LCDWidget8::ONCOLOR=FL_BLUE;
    Fl_LCDWidget8::OFFCOLOR=FL_FOREGROUND_COLOR;
}

// Set ON OFF Color 
void Fl_LCDWidget8::SetONOFFCOLOR( Fl_Color ONcolor, Fl_Color OFFcolor)
{
this->OFFCOLOR=OFFcolor;
this->ONCOLOR=ONcolor;
this->draw();
}

//Draw function .. Here all drawing is done 
void Fl_LCDWidget8::draw()
{
 draw_box();
 align(FL_ALIGN_BOTTOM);
 draw_label();

int widthofpixel = 7;

 // All the rows
for (int i=0;i<8;i++)
{
  // One line 
  
  for (int j=0;j<8;j++)
   {
   if (valuebitmap[this->value][i]&(power(2,7-j)))  
     {
       ONOFFCOLOR = ONCOLOR;
       fl_color(ONOFFCOLOR);
       fl_rectf(x()-2+((Addition(2,(j+1))-1)*w())/17, -2+y()+((Addition(2,(i+1))-1)*h())/17, w()/widthofpixel,h()/widthofpixel);
      }
  // else
//   if (!1==1){
//             ONOFFCOLOR = OFFCOLOR;
//             fl_color(ONOFFCOLOR);
//             fl_rectf(x()-2+((Addition(2,(j+1))-1)*w())/17, -2+y()+((Addition(2,(i+1))-1)*h())/17, w()/widthofpixel,h()/widthofpixel);
//            }

   }

}


}
// Get widgets value
int Fl_LCDWidget8::LCD_Value()
{
return value;
}
//Set widgets value
void Fl_LCDWidget8::LCD_Value(int& v)
{
value=v;
redraw();
}



