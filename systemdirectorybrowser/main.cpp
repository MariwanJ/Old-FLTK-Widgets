//////////////////////////////////////////////////////////////////////
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
//#include "fl_ext_tree_browser.H"
#include "Fl_SystemDirectory_Browser.h"
#include <FL/Fl_File_Browser.H>


class testSystemDir : public Fl_SystemDirectory_Browser
{
public :
       testSystemDir(int,int,int,int,char *l);
  int HandleSelect(Fl_Ext_TreeItem *pItemClicked, int bState);
       ~testSystemDir();
};
testSystemDir::~testSystemDir()
{
;                               
}
testSystemDir::testSystemDir(int x,int y,int w,int h,char *l):Fl_SystemDirectory_Browser(x,y,w,h,l)
{
                                 
;// Do nothing
                           
}
int testSystemDir::HandleSelect(Fl_Ext_TreeItem *pItemClicked, int bState)
{
// You should run the original HandleSelect to get the tree be up-to-date  
int kll=Fl_SystemDirectory_Browser::HandleSelect(pItemClicked, bState);        
// Write you code here  Mariwan

char* PathNameString=0;


  if (!pItemClicked==0&& !bState==0)
  {
      PathNameString=  GetItemToDirectory(pItemClicked);
    if (!(PathNameString)==0)
    {
    this->copy_label(PathNameString);
     if (this->visible())
          this->redraw();
    }
 
  }
 if (PathNameString)   delete [] PathNameString;  
 
return kll;
}

int main(int argc, char *argv[])
{
  { Fl_Double_Window* o =  new Fl_Double_Window(600, 300, "FLTK System Directory Browser Widget");
    testSystemDir* w= new testSystemDir(2, 2, 300, 250,"Directory Browser");
    o->resizable(o); 
    o->end(); 
    o->show(argc, argv);
    return Fl::run();
}

}

