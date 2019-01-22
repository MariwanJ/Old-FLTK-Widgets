// "$Id: Fl_LCD_Clock4.cpp,v 0.0.1  2004/12/12 17:15"
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


#include "Fl_LCD_Clock4.h" // class's header file

// class constructor

Fl_LCD_Clock4::Fl_LCD_Clock4(int x, int y, int w ,int h, char*l):Fl_Widget(x,y,w,h,l)
{
   
    HH = 0; 
    MM = 0; 
    SS= 0;


int widgetsize=this->w()/5;
w1=new Fl_LCDWidget4 (this->x(),this->y(),widgetsize,this->h(),"",HH/10);
w2=new Fl_LCDWidget4 (this->x()+widgetsize,this->y(),widgetsize,this->h(),"",HH%10);
w3=new Fl_LCDWidget4 (this->x()+2*widgetsize,this->y(),widgetsize,this->h(),"",10);
w4=new Fl_LCDWidget4(this->x()+3*widgetsize,this->y(),widgetsize,this->h(),"",MM/10);
w5=new Fl_LCDWidget4 (this->x()+4*widgetsize,this->y(),widgetsize,this->h(),"",MM%10);
}

static void tick(void *v) 
{
#ifdef WIN32
  ((Fl_LCD_Clock4*)v)->value(time(0));
   Fl::add_timeout(1.0, tick, v);
#else
  struct timeval t;
  gettimeofday(&t, 0);
  ((Fl_LCD_Clock4*)v)->value(t.tv_sec);
  double delay = 1.0-t.tv_usec*.000001;
  if (delay < .1 || delay > .9) delay = 1.0;
  Fl::add_timeout(delay, tick, v);
#endif
}

// Halayak lerada haya sairi bika bizana chia masala
void Fl_LCD_Clock4::value(int h, int m, int s) {
 if (h!=HH)
  {
  HH=h;
      this->w1->Value(HH/10);
      this->w2->Value(HH%10);
      
  }

  if (m!=MM)
  {
  MM=m;
      this->w4->Value(MM/10);
      this->w5->Value(MM%10);
  }

  if ( s!=SS) 
  {
  SS=s;
      if (this->w3->Value()==10)         this->w3->Value(20);
       else 
        if (this->w3->Value()==20)        this->w3->Value(10);
  }
 
}
int Fl_LCD_Clock4::value()
{
return this->HH;
}
void Fl_LCD_Clock4::value(ulong v) 
{
   struct tm *timeofday;
   timeofday = localtime((const time_t *)&v);
   this->value(timeofday->tm_hour, timeofday->tm_min, timeofday->tm_sec);
}


// class destructor
Fl_LCD_Clock4::~Fl_LCD_Clock4()
{
 Fl::remove_timeout(tick, this);
}

int Fl_LCD_Clock4::Hours()
{
return this->HH;
}

int Fl_LCD_Clock4::Secs()
{
return this->SS;
}
int Fl_LCD_Clock4::Mins()
{
return this->MM;
}


void Fl_LCD_Clock4::draw()
{
align(FL_ALIGN_BOTTOM);
draw_label();  

}

int Fl_LCD_Clock4::handle(int event)
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
