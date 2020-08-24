#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include "Fl_Font_Browser.H"
  void cb_btn(Fl_Widget *, void *){
  Fl_Font_Browser *fn=new Fl_Font_Browser();
  fn->show();
 }
int main (int argc, char ** argv)
{
  Fl_Window *window;
  Fl_Button *box;

  window = new Fl_Window (0,0,300, 180,"demo");
  Fl_Button *btn = new Fl_Button (20, 40, 260, 100, "FontBrowser");
  btn->callback(cb_btn,btn);
  window->end ();
  window->show (argc, argv);

  return(Fl::run());
}
