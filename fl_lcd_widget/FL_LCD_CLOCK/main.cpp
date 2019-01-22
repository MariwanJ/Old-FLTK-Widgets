#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "FL_LCD_Clock4.H"

int main (int argc, char *argv[])
{
    Fl_Window *window;
    window = new Fl_Window (0,0,300, 180, "LCD TEST");
  
    Fl_LCD_Clock4* lcd=new Fl_LCD_Clock4(5,5,175,50,"Digital 4digits 5Widgets");
    lcd->box(FL_UP_BOX);
    window->end ();
    window->resizable(window);
    window->show (argc, argv);
    return Fl::run();
}
