//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Fl_ToolBar.cpp      v 0.0.1                             2006-01-02
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

#include "Fl_ToolBar.H" // class's header file

// class constructor
Fl_ToolBar::Fl_ToolBar(int x, int y, int w, int h, const char* l):Fl_Group(x,y,w,h,l)
{
  pItemFirst=0;
  pItemLast=0;
  dockable=0; // Standard toolbar is not dockable
  xCell=x+5; // Start Point;
  yCell=y+1;
  wCell=h-2;
  hCell=h-4;
}
int Fl_ToolBar::GetDockable()
{
return dockable;    
}
void Fl_ToolBar::SetDockable(int gData)
{
  dockable=gData;    
}
int Fl_ToolBar::handle(int e)
{
static int offset[2] = { 0, 0 };// This is not implimented correctly.. I leave it to other developers to do it!

    int Y_Correction=0;
    if (dockable && (Fl::event_button() == FL_LEFT_MOUSE))
    {
        switch ( e ) 
        {
            case FL_PUSH:{
                          
                          if (Fl::event_x()>=x()&& Fl::event_x()<=x()+5) 
                          {
                             offset[0] = x()-Fl::event_x() ;    // save where user clicked for dragging
                             offset[1] = y()-Fl::event_y();                               
                            return 1;
                          }
                          else 
                          return Fl_Group::handle(e);
                         }
            case FL_RELEASE:
                              return 1;
            case FL_DRAG:
                        {
                           position(offset[0]+Fl::event_x(), offset[1]+Fl::event_y());     // handle dragging
                           parent()->redraw();
                           return 1;
                        }
         
           
        }
    }
 return Fl_Group::handle(e); 
}



void Fl_ToolBar::draw()
{
     color(FL_GRAY);
     draw_box();
     align(FL_ALIGN_BOTTOM);
     draw_label();

     Fl_ToolBar_Button* pScanThem=pItemFirst;
    
        fl_color(0xff,0xff,0xff);
        fl_rectf(x(),y(),1,h());    
        fl_rectf(x(),y(),2,2);    
                
        fl_color(0xaf,0xaf,0xaf);
        fl_rectf(x()+3,y(),1,h());    
        fl_rectf(x(),y()+h()-2,2,2);
    
  
  
    
    
    while (pScanThem!=0)
    {
      pScanThem->item_draw();
       pScanThem=pScanThem->pItemNext;  
    }

}

Fl_ToolBar_Button* Fl_ToolBar::addButton(const char *l, Fl_Image *img)
{ 
    begin();
    if (l!=0 )
    {
      if (!(strcmp(l,"|"))) // this mean that we should have a standard width for the button which is the 1/2 size
      {
                wCell=(hCell)/4 -1;                   
      }
      else
      {
                wCell=hCell-1;                   
          
       }
    }
      else 
      {
                wCell=hCell-1;                   
      }
    Fl_ToolBar_Button *pAddedButton= new Fl_ToolBar_Button(xCell,yCell,wCell,hCell,l);
    if ((pItemFirst==0))
    {
       pItemFirst=pAddedButton;
       pItemLast=pAddedButton;
       pAddedButton->pItemPrev=0;
       pAddedButton->pItemNext=0;
    }
    else
    {
        pItemLast->pItemNext=pAddedButton;
        pAddedButton->pItemPrev=pItemLast;
        pItemLast=pAddedButton;
    }
         if (!l==0)
         {
           if (!(strcmp(l,"|")))
           {
              xCell=xCell+hCell/4-1; // Devider start point ;
              wCell=(hCell)/4;                   
           }
            else 
            {
              xCell=xCell+hCell-1; // Start Point;         
              wCell=hCell-1;
            if (img)
                pAddedButton->image(img);
            }
           }
          else 
          {
              xCell=xCell+hCell-1; // Start Point;         
              wCell=hCell-1;
             if (img)
                pAddedButton->image(img);
           }
        end();
    return pAddedButton;
}


// class destructor
Fl_ToolBar::~Fl_ToolBar()
{
	// insert your code here
}
