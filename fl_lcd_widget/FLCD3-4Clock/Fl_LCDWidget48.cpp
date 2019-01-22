// "$Id: Fl_LCDWidget48.cpp,v 0.0.1  2004/12/12 17:15"
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




#include "Fl_LCDWidget48.h"


int Fl_LCDWidget48::valuebitmap[256][8]={
                        {0,6,9,9,9,9,9,6},   //0
                        {0,2,6,2,2,2,2,7},       //1
                        {0,6,9,1,2,4,8,15},     //2
                        {0,6,9,1,2,1,9,6},      //3
                        {0,2,6,10,10,15,2,2},   //4
                        {0,15,8,15,1,1,9,6},     //5
                        {0,1,2,4,15,9,9,6},    //6
                        {0,15,1,2,4,8,8,8},    //7
                        {0,6,9,9,6,9,9,6},    //8
                        {0,6,9,9,7,2,4,8},     //9
                        {0,0,6,6,0,6,6,0}      //10 ::
                        };


// Addition of a number -- many times
int Fl_LCDWidget48::Addition(int base, int timesAdd)
{
int result=0;
for (int i=0;i<timesAdd;i++)
{
result=base+result;
}
return result;

}
// Power calculation
int Fl_LCDWidget48::power(int base, int topower)
{
int result=1;
for (int i=0;i<topower;i++)
{
result=base*result;
}
return result;

}

void Fl_LCDWidget48::setDefaultSeperator(int v)
{
DefaultSeperator=v;
}

Fl_LCDWidget48::~Fl_LCDWidget48()
{
//Destructor
}
//Constructor
Fl_LCDWidget48::Fl_LCDWidget48(int x, int y, int w, int h, char* l):Fl_Widget(x,y,w,h,l)
{

DefaultSeperator=10; // this is just the ':' symbol
// Default color
  
    Fl_LCDWidget48::ONCOLOR= (Fl_Color)(84); 
    Fl_LCDWidget48::OFFCOLOR=FL_FOREGROUND_COLOR ;
}


// Set ON OFF Color 
void Fl_LCDWidget48::SetONOFFCOLOR( Fl_Color ONcolor, Fl_Color OFFcolor)
{
this->OFFCOLOR=OFFcolor;
this->ONCOLOR=ONcolor;
this->draw();
}

//Draw function .. Here all drawing is done 
void Fl_LCDWidget48::draw()
{

 draw_box();
 draw_label();    // Should be fixed

widthofpixel = 6;
int sizegive =18;

int maxwid=w()/5;
int maxhi=h();

//All Digits
for( int nex=0; nex<8;nex++) // Digits
 // All the rows
for (int i=0;i<8;i++)
{
  // One line 
int savex=x();
int savey=y();


  
  for (int j=0;j<=4;j++)
   {
   if (valuebitmap[this->value[nex]][i]&(power(2,4-j)))  // Era bigora
     {
       ONOFFCOLOR= ONCOLOR;
       fl_color(ONOFFCOLOR);
       fl_rectf((int)(0.60*nex*maxwid)+savex+((Addition(2,(j+1)))*maxwid)/sizegive, (int)(-1*0.035* maxhi)+savey+((Addition(2,(i+1))-1)*h())/sizegive, maxwid/widthofpixel,maxhi/widthofpixel);
      }
   else  if (!OFFCOLOR==FL_FOREGROUND_COLOR)
           {
             ONOFFCOLOR = OFFCOLOR;
             fl_color(ONOFFCOLOR);
             fl_rectf((int)(0.60*nex*maxwid)+savex+((Addition(2,(j+1)))*maxwid)/sizegive,(int)(-1*0.035* maxhi)+savey+((Addition(2,(i+1))-1)*h())/sizegive, maxwid/widthofpixel,maxhi/widthofpixel);
            }

   }

}

}
