#include <Fl/Fl_Window.h>
#include <Fl/Fl.h>
#include "Fl_LCD_Clock.h"
int main (int argc, char *argv[])
{
    Fl_Window *window;
    window = new Fl_Window (0,0,300, 180,"Test LCD");
    //Fl_LCDWidget48 *d= new Fl_LCDWidget48(15,15,60,30,"ER");
    Fl_LCD_Clock *lcd=new Fl_LCD_Clock (15,15,60,30,"Digital FLTK Clock");
    window->end ();
    window->resizable(window);
    window->show (argc, argv);
    
    return Fl::run();
}

