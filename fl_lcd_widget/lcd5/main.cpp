#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "Fl_LCDWidget5.H"


int main (int argc, char *argv[])
{
    Fl_Window *window;
    window = new Fl_Window (0,0,300, 180,"Test LCD");
    Fl_LCDWidget5 *lcd[10];
    for (int st =0; st< 10;st++)
    {    
    lcd[st]=new Fl_LCDWidget5 ((5+16*st),60,15,50,"Digit2",st);
    lcd[st]->box(FL_PLASTIC_DOWN_BOX);
    lcd[st]->box(FL_PLASTIC_DOWN_BOX);
    }
    window->end ();
    window->resizable(window);
    window->show (argc, argv);
    
    return Fl::run();
}

