//////////////////////////////////////////////////////////////////////
// main.cpp      v 0.0.1                             2006-01-02 
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

/*

A simple test file showing the 3 widget. Fl_Button_Cell and Fl_Button is almost the same 


*/
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Window.H>
#include "Fl_ToolBar.H"
#include "Fl_Button_Cell.H"
#include "Fl_ToolBar_Button.H"
#include <FL/Fl_Pixmap.H>


static char * button_find_xpm[] = {
"21 21 3 1",
" 	c None",
".	c #FFFFFF",
"+	c #000000",
"      +++   +++      ",
"      +++   +++      ",
"      +++   +++      ",
"      +++   +++      ",
"      +++   +++      ",
"      +.+   +.+      ",
"      +++   +++      ",
"     +++++ +++++     ",
"     +.+++ +.+++     ",
"    +++++++++++++    ",
"   ++.+++ ++.+++++   ",
"   ++.+++ ++.+++++   ",
"   ++.++++++.+++++   ",
"   +++++++ +++++++   ",
"   +.+++     +.+++   ",
"   +.+++     +.+++   ",
"   +++++     +++++   ",
"   +++++     +++++   ",
"   +++++     +++++   ",
"   +++++     +++++   ",
"   +++++     +++++   "};
void cb_btn(Fl_Widget*, void* data)
{
 Fl_Double_Window *n= new Fl_Double_Window(300,100,(const char*)data);
 n->show();

}
int main (int argc, char ** argv)
{

  Fl_Double_Window *window= new Fl_Double_Window(1000, 480);
  window->begin();
 
   Fl_Pixmap* dd= new Fl_Pixmap(button_find_xpm);
  
   Fl_ToolBar *tb1= new Fl_ToolBar (20,5, 450,70,"Pic Over Text -- this one is dockabel .. you can move the toolbar");


   tb1->SetDockable(1); // Please note that this function is not completed 
   tb1->begin();
    // Adding button
    {
      Fl_ToolBar_Button*o= tb1->addButton("text 1",dd);
      o->callback((Fl_Callback*)cb_btn, (void*) ("Do this"));
      o->cellStyle(FL_Pic_Over_Text_CENTER);
    }

    {
      Fl_ToolBar_Button*o= tb1->addButton("text  2",dd);
      o->cellStyle(FL_Pic_Over_Text_LEFT);
    }
    {
      Fl_ToolBar_Button*o= tb1->addButton("Deactivated",dd);
      o->cellStyle(FL_Pic_Over_Text_RIGHT);
      o->deactivate();
   }

    
  {
      Fl_ToolBar_Button*o= tb1->addButton("text 4",dd);
      o->cellStyle(FL_Pic_Over_Text_RIGHT);
   }
   tb1->end();
   tb1->box(FL_UP_BOX);
   Fl_ToolBar *tb2= new Fl_ToolBar (20,90, 450,70,"Pic Under Text");
   tb2->begin();
      
  {
      Fl_ToolBar_Button*o= tb2->addButton("text 4",dd);
      o->cellStyle( FL_Pic_Under_Text_CENTER);
    }
    
    {// This will draw a divider
      Fl_ToolBar_Button*o= tb2->addButton("|",0);
      o->cellStyle(FL_Pic_Under_Text_LEFT);
    }

  {
      Fl_ToolBar_Button*o= tb2->addButton("text 5",dd);
      o->cellStyle(FL_Pic_Under_Text_LEFT);
    }

  {
      Fl_ToolBar_Button*o= tb2->addButton("text 6",dd);
      o->cellStyle(FL_Pic_Under_Text_RIGHT);
    }
  tb2->end();
  tb2->box(FL_UP_BOX);
  Fl_ToolBar *tb3= new Fl_ToolBar (20,175, 450,70,"Pic Left To Text");
  tb3->begin();
  {
      Fl_ToolBar_Button*o= tb3->addButton("text 7",dd);
      o->cellStyle(FL_Pic_LeftTo_Text_CENTER);
    }

  {
      Fl_ToolBar_Button*o= tb3->addButton("text 8",dd);
      o->cellStyle(FL_Pic_LeftTo_Text_LEFT);
    }

  {
      Fl_ToolBar_Button*o= tb3->addButton("text 9",dd);
      o->cellStyle(FL_Pic_LeftTo_Text_RIGHT);
    }
   tb3->end();
   tb3->box(FL_UP_BOX);
   Fl_ToolBar *tb4= new Fl_ToolBar (20,265, 450,70,"Pic Right To Text");
   tb4->begin();

  {
      Fl_ToolBar_Button*o= tb4->addButton("text 10",dd);
      o->cellStyle(FL_Pic_RightTo_Text_CENTER);
    }

  {
      Fl_ToolBar_Button*o= tb4->addButton("text 11",dd);
      o->cellStyle(FL_Pic_RightTo_Text_LEFT);
    }

  {
      Fl_ToolBar_Button*o= tb4->addButton("text 12",dd);
      o->cellStyle(FL_Pic_RightTo_Text_RIGHT);
  }
   tb4->box(FL_UP_BOX);
   tb4->end();
 

   Fl_ToolBar_Button *box = new Fl_ToolBar_Button (20, 355, 300, 50, "FL TOOLBAR BUTTON!");
   box->labelfont (FL_BOLD+FL_ITALIC);
   box->labeltype (FL_SHADOW_LABEL);


   Fl_Button_Cell *cel = new Fl_Button_Cell (20, 415, 200, 35, "FL_CELL");
   cel->image(dd);
   cel->labelfont (FL_BOLD+FL_ITALIC);
   cel->labeltype (FL_SHADOW_LABEL);

  
  window->end ();

  window->resizable(window);
  window->show (argc, argv);
  return(Fl::run());
}
