// "$Id: Fl_LCD_Clock.cpp,v 0.0.1  2004/12/12 17:15"
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


#include "Fl_LCD_Clock.h" // class's header file

// class constructor



Fl_LCD_Clock::Fl_LCD_Clock(int x, int y, int w ,int h, char*l): Fl_LCDWidget48(x,y,w,h,l)
{
ShowFlasSec=false;   
HH = 0; 
MM = 0; 
SS= 0;
this->box(FL_PLASTIC_UP_BOX);
align(FL_ALIGN_BOTTOM);

Fl_LCDWidget48::value[2]=DefaultSeperator;
Fl_LCDWidget48::value[5]=DefaultSeperator;


}

static void tick(void *v) 
{
#ifdef WIN32
  ((Fl_LCD_Clock*)v)->value(time(0));
   Fl::add_timeout(1.0, tick, v);
#else
  struct timeval t;
  gettimeofday(&t, 0);
  ((Fl_LCD_Clock*)v)->value(t.tv_sec);
  double delay = 1.0-t.tv_usec*.000001;
  if (delay < .1 || delay > .9) delay = 1.0;
  Fl::add_timeout(delay, tick, v);
#endif
}

// Halayak lerada haya sairi bika bizana chia masala
void Fl_LCD_Clock::value(int h, int m, int s) {
 if (h!=HH)
  {
  HH=h;
    
      Fl_LCDWidget48::value[0]=(HH/10);
      Fl_LCDWidget48::value[1]=(HH%10);
      
  }

  if (m!=MM)
  {
  MM=m;
      Fl_LCDWidget48::value[3]=(MM/10);
      Fl_LCDWidget48::value[4]=(MM%10);
      
  }
  if ( s!=SS) 
  {
  SS=s;

     Fl_LCDWidget48::value[6]=(SS/10);
     Fl_LCDWidget48::value[7]=(SS%10);

     if (ShowFlasSec )
     {
       if (Fl_LCDWidget48::value[5]==10)         Fl_LCDWidget48::value[5]=20;
        else 
       if (Fl_LCDWidget48::value[5]==20)        Fl_LCDWidget48::value[5]=10;
      }
     else 
        Fl_LCDWidget48::value[5]==10;
     
  }
  
   this->damage(FL_DAMAGE_CHILD);
}
int Fl_LCD_Clock::value()
{
return this->HH;
}
void Fl_LCD_Clock::value(ulong v) 
{
   struct tm *timeofday;
   timeofday = localtime((const time_t *)&v);
   this->value(timeofday->tm_hour, timeofday->tm_min, timeofday->tm_sec);
}


// class destructor
Fl_LCD_Clock::~Fl_LCD_Clock()
{
 Fl::remove_timeout(tick, this);
}

int Fl_LCD_Clock::Hours()
{
return this->HH;
}

int Fl_LCD_Clock::Secs()
{
return this->SS;
}
int Fl_LCD_Clock::Mins()
{
return this->MM;
}


void Fl_LCD_Clock::draw()
{
Fl_LCDWidget48::draw();
}

int Fl_LCD_Clock::handle(int event)
 {
  switch (event) 
  {
    case FL_SHOW:
                 tick(this);
                 break;
    case FL_HIDE:
                 Fl::remove_timeout(tick, this);
                 break; 
  }
 return 0;//Fl_Clock_Output::handle(event);
}
