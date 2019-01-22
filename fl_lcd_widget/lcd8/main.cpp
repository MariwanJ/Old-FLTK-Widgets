#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "Fl_LCDWidget8.H"

int main (int argc, char *argv[])
{
    Fl_Window *window;
    window = new Fl_Window (0,0,300, 180,"Test LCD");
    for (int i=0;i<8;i++)
    {
     Fl_LCDWidget8 *lcd=new Fl_LCDWidget8 (5+30*i,5,30,30,"LCD8",i);
     lcd->box(FL_PLASTIC_UP_BOX);
    }

    for ( int j=0;j<8;j++)
    {
     Fl_LCDWidget8 *lcd=new Fl_LCDWidget8 (5+30*j,5+60,30,30,"LCD8",8+j);
     lcd->box(FL_PLASTIC_UP_BOX);
    }
  

    window->end ();
    window->resizable(window);
    window->show (argc, argv);
    return Fl::run();
}
