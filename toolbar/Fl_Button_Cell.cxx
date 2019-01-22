//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Fl_Button_Cell.cpp      v 0.0.1                             2006-01-02
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


#include "Fl_Button_Cell.H" // class's header file

// class constructor
Fl_Button_Cell::Fl_Button_Cell(int x, int y, int w, int h,const char *l):Fl_Widget(x, y, w, h, l)
{
 value=0;
 cellImage=0;
 cellStyle_=FL_Pic_LeftTo_Text_CENTER; // Defatult Style is to have the picture over the text.
 pictWidth=pictHeight=nX=nW=nH=nY=nXX=nYY=0; // Just in case !!
 labelsize(10);
 labelfont(FL_HELVETICA);
  if (l)
   fl_measure(l, labelWidth, labelHeight, 1);
 lab=l;
}

void Fl_Button_Cell::cellStyle(int StyleType)
{
 cellStyle_=StyleType;
 redraw();
}
int Fl_Button_Cell::cellStyle()
{
  return cellStyle_;
}

void Fl_Button_Cell::draw()
{


  item_draw();
}

void Fl_Button_Cell::item_draw()
{
     if (!(active()))
        if (lab)
        {
          if (!(strcmp(lab,"|")))
            value =4;
           else 
            value =3;
        }
        else
        {
          value =3;
        }
int xd=0;
int colorUsed;
if (image())
{
  cellImage=image();
  image(0);
}  
if (cellImage) // if any image 
{
 pictWidth=cellImage->w();
 pictHeight=cellImage->h();
}
// Here we should calculate how to draw the txt and the image... for the new style I made it
//Start -- Style
// I should calculate the start point for the txt and the image 


switch (cellStyle_)
{
// picture Over Text and (Center, Top, Bottom, Left & Right)
case FL_Pic_Over_Text_CENTER:
                             {

                                align(FL_ALIGN_CENTER|FL_ALIGN_WRAP|FL_ALIGN_INSIDE);
                                 nH=this->h();
                                 nW=this->w();
                                if (((lab==0)|(cellImage==0))) // We don't need to apply any style if there isn't both (label and picture)
                                {
                                  // One of them is zero ..  i.e There is only Label or Only picture
                                  //We need just to calculate the center 

                                  // picture calculation
                                  nXX=this->x()+this->w()/2-pictWidth/2 ;        
                                  nYY=this->y()+this->h()/2 -pictHeight/2;       
    
                                  // Label calculation
                                  nX=this->x();                     
                                  nY=this->y();                                   
                                 }
                                else 
                                {
                                  // BOTH will be drawn
                                  nXX=this->x()+this->w()/2-pictWidth/2;
                                  nYY=this->y()+pictHeight/4;

                                  nX=this->x();
                                  nY=this->y()+pictHeight/2;
     
                                }



                              }
                              break;
case FL_Pic_Over_Text_LEFT:
                             {
                                align(FL_ALIGN_LEFT|FL_ALIGN_WRAP|FL_ALIGN_INSIDE);
                                 nH=this->h();
                                 nW=this->w();

                                if (((lab==0)|(cellImage==0))) // We don't need to apply any style if there isn't both (label and picture)
                                {
                                  // One of them is zero ..  i.e There is only Label or Only picture
                                  //We need just to calculate the center 

                                  // picture calculation
                                  nXX=this->x() ;        
                                  nYY=this->y()+this->h()/2 -pictHeight/2;       
    
                                  // Label calculation
                                  nX=this->x()+3;                     
                                  nY=this->y();                                   
                                 }
                                else 
                                {
                                  // BOTH will be drawn
                                  nXX=this->x();
                                  nYY=this->y()+pictHeight/4;

                                  nX=this->x()+3;
                                  nY=this->y()+pictHeight/2;
     
                                }
                             }
                             break;
                             
case FL_Pic_Over_Text_RIGHT:
                             {
                                align(FL_ALIGN_RIGHT|FL_ALIGN_WRAP|FL_ALIGN_INSIDE);
                                 nH=this->h();
                                 nW=this->w();

                                if (((lab==0)|(cellImage==0))) // We don't need to apply any style if there isn't both (label and picture)
                                {
                                  // One of them is zero ..  i.e There is only Label or Only picture
                                  //We need just to calculate the center 

                                  // picture calculation
                                  nXX=this->x()+w()-pictWidth ;        
                                  nYY=this->y()+this->h()/2 -pictHeight/2;       
    
                                  // Label calculation
                                  nX=this->x();                     
                                  nY=this->y();                                   
                                 }
                                else 
                                {
                                  // BOTH will be drawn
                                  nXX=this->x()+w()-pictWidth;
                                  nYY=this->y()+pictHeight/4;

                                  nX=this->x();
                                  nY=this->y()+pictHeight/2;
     
                                }

                                
                            
                             }
                             break;

                             
                             

// pictuer Under Text and (Center, Top, Bottom, Left & Right)
case FL_Pic_Under_Text_CENTER:
                             {

                                 align(FL_ALIGN_CENTER|FL_ALIGN_WRAP|FL_ALIGN_INSIDE);
                                 nW=this->w();

                                if (((lab==0)|(cellImage==0))) // We don't need to apply any style if there isn't both (label and picture)
                                {
                                  // One of them is zero ..  i.e There is only Label or Only picture
                                  //We need just to calculate the center 
                                  nH=this->h();
                                  // picture calculation
                                  nXX=this->x()+this->w()/2-pictWidth/2 ;        
                                  nYY=this->y()+this->h()/2 -pictHeight/2;       
    
                                  // Label calculation
                                  nX=this->x();                     
                                  nY=this->y();                                   
                                 }
                                else 
                                {
                                  nH=this->h()/2;
                                  // BOTH will be drawn
                                  nXX=this->x()+this->w()/2-pictWidth/2;
                                  nYY=this->y()+h()-pictHeight-pictHeight/2;

                                  nX=this->x();
                                  nY=this->y();
     
                                }



                              }
                              break;

 
case FL_Pic_Under_Text_LEFT:
                             {
                            
                                 align(FL_ALIGN_LEFT|FL_ALIGN_WRAP|FL_ALIGN_INSIDE);
                                 nW=this->w();

                                if (((lab==0)|(cellImage==0))) // We don't need to apply any style if there isn't both (label and picture)
                                {
                                  // One of them is zero ..  i.e There is only Label or Only picture
                                  //We need just to calculate the center 
                                  nH=this->h();
                                  
                                  // picture calculation
                                  nXX=this->x() ;        
                                  nYY=this->y()+this->h()/2 -pictHeight/2;       
    
                                  // Label calculation
                                  nX=this->x();                     
                                  nY=this->y();                                   
                                 }
                                else 
                                {
                                  nH=this->h()/2;
                                  // BOTH will be drawn
                                  nXX=this->x();
                                  nYY=this->y()+h()-pictHeight-pictHeight/2;

                                  nX=this->x();
                                  nY=this->y();
     
                                }



                              }
                              break;

case FL_Pic_Under_Text_RIGHT:
                             {
                                 align(FL_ALIGN_RIGHT|FL_ALIGN_WRAP|FL_ALIGN_INSIDE);
                                 nW=this->w();

                                if (((lab==0)|(cellImage==0))) // We don't need to apply any style if there isn't both (label and picture)
                                {
                                  // One of them is zero ..  i.e There is only Label or Only picture
                                  //We need just to calculate the center 
                                  nH=this->h();
                                  
                                  // picture calculation
                                  nXX=this->x()+w()-pictWidth;        
                                  nYY=this->y()+this->h()/2 -pictHeight/2;       
    
                                  // Label calculation
                                  nX=this->x();                     
                                  nY=this->y();                                   
                                 }
                                else 
                                {
                                  nH=this->h()/2;
                                  // BOTH will be drawn
                                  nXX=this->x()+w()-pictWidth;
                                  nYY=this->y()+h()-pictHeight-pictHeight/2;

                                  nX=this->x();
                                  nY=this->y();
     
                                }

                              }
                              break;

// pictuer Left To Text and (Center, Top, Bottom, Left & Right)
case FL_Pic_LeftTo_Text_CENTER:
                             {
                                 align(FL_ALIGN_CENTER|FL_ALIGN_WRAP|FL_ALIGN_INSIDE);

                                 nH=this->h();
                                if (((lab==0)|(cellImage==0))) // We don't need to apply any style if there isn't both (label and picture)
                                {
                                  // One of them is zero ..  i.e There is only Label or Only picture
                                  //We need just to calculate the center 
                                 
                                  nW=this->w();                                  
                                  // picture calculation
                                  nXX=this->x()+this->w()/2 -pictWidth/2;;        
                                  nYY=this->y()+this->h()/2 -pictHeight/2;       
    
                                  // Label calculation
                                  nX=this->x();                     
                                  nY=this->y();                                   
                                 }
                                else 
                                {
                                  nW=int (this->w()/1.5);
                                  // BOTH will be drawn
                                  nXX=this->x()+this->w()/3-pictWidth;        
                                  if(nXX<this->x())
                                     nXX=this->x();
                                  nYY=this->y()+this->h()/2 -pictHeight/2;       
                                  
                                  nX=this->x()+this->w()/2-pictWidth/2;                     
                                  nY=this->y();
     
                                }

                              }
                              break;
                             
                             
case FL_Pic_LeftTo_Text_LEFT:
                             {
                                 align(FL_ALIGN_LEFT|FL_ALIGN_WRAP|FL_ALIGN_INSIDE);
                                 nW=this->w()-2-pictWidth;
                                 nH=this->h();
                                if (((lab==0)|(cellImage==0))) // We don't need to apply any style if there isn't both (label and picture)
                                {
                                  // One of them is zero ..  i.e There is only Label or Only picture
                                  //We need just to calculate the center 
                                 
                                  
                                  // picture calculation
                                  nXX=this->x();        
                                  nYY=this->y()+this->h()/2 -pictHeight/2;       
    
                                  // Label calculation
                                  nX=this->x();                     
                                  nY=this->y();                                   
                                 }
                                else 
                                {
                                  // BOTH will be drawn
                                  nXX=this->x();
                                  nYY=this->y()+this->h()/2 -pictHeight/2;       

                                  nX=this->x()+pictWidth;                     
                                  nY=this->y();
     
                                }

                              }
                              break;
                             
case FL_Pic_LeftTo_Text_RIGHT:
                              {
                                 align(FL_ALIGN_RIGHT|FL_ALIGN_WRAP|FL_ALIGN_INSIDE);
                                 nW=this->w()-pictWidth;
                                 nH=this->h();
                                if (((lab==0)|(cellImage==0))) // We don't need to apply any style if there isn't both (label and picture)
                                {
                                  // One of them is zero ..  i.e There is only Label or Only picture
                                  //We need just to calculate the center 
                                 
                                  
                                  // picture calculation
                                  nXX=this->x()+this->w()-pictWidth;        
                                  nYY=this->y()+this->h()/2 -pictHeight/2;       
    
                                  // Label calculation
                                  nX=this->x();                     
                                  nY=this->y();                                   
                                 }
                                else 
                                {
                                  // BOTH will be drawn
                                  nXX=this->x()+this->w()-labelWidth-pictWidth;
                                  if (nXX<this->x())
                                       nXX=this->x();
                                  nYY=this->y()+this->h()/2 -pictHeight/2;       

                                  nX=this->x()+pictWidth;                     
                                  nY=this->y();
     
                                }

                              }
                              break;
                             
  
// pictuer Right To Text and (Center, Top, Bottom, Left & Right)
case FL_Pic_RightTo_Text_CENTER:
                             {
                                 align(FL_ALIGN_CENTER|FL_ALIGN_WRAP|FL_ALIGN_INSIDE);

                                 nH=this->h();
                                if (((lab==0)|(cellImage==0))) // We don't need to apply any style if there isn't both (label and picture)
                                {
                                  // One of them is zero ..  i.e There is only Label or Only picture
                                  //We need just to calculate the center 
                                 
                                  nW=this->w();                                  
                                  // picture calculation
                                  nXX=this->x()+this->w()/2 -pictWidth/2;;        
                                  nYY=this->y()+this->h()/2 -pictHeight/2;       
    
                                  // Label calculation
                                  nX=this->x();                     
                                  nY=this->y();                                   
                                 }
                                else 
                                {
                                  nW=this->w()-pictWidth;
                                  // BOTH will be drawn
                                  nXX=this->x()+this->w()/2+pictWidth/2;
                                  if (nXX+pictWidth> (this->x()+this->w()))
                                     nXX=this->x()+this->w()-pictWidth;        
                                  nYY=this->y()+this->h()/2 -pictHeight/2;       
                                  
                                  nX=this->x();                     
                                  nY=this->y();
     
                                }

                              }
                              break;
                             
                             
case FL_Pic_RightTo_Text_LEFT:
                             {
                                 align(FL_ALIGN_LEFT|FL_ALIGN_WRAP|FL_ALIGN_INSIDE);

                                 nH=this->h();
                                if (((lab==0)|(cellImage==0))) // We don't need to apply any style if there isn't both (label and picture)
                                {
                                  // One of them is zero ..  i.e There is only Label or Only picture
                                  //We need just to calculate the center 
                                 
                                  nW=this->w();                                  
                                  // picture calculation
                                  nXX=this->x();        
                                  nYY=this->y()+this->h()/2 -pictHeight/2;       
    
                                  // Label calculation
                                  nX=this->x();                     
                                  nY=this->y();                                   
                                 }
                                else 
                                {
                                  nW=this->w()-pictWidth;
                                  // BOTH will be drawn
                                  nXX=this->x()+labelWidth+pictWidth/2;
                                  if (nXX+pictWidth> (this->x()+this->w()))
                                     nXX=this->x()+this->w()-pictWidth;        
                                  nYY=this->y()+this->h()/2 -pictHeight/2;       
                                  
                                  nX=this->x();                     
                                  nY=this->y();
     
                                }

                              }
                              break;
                             

                            
case FL_Pic_RightTo_Text_RIGHT:
                             {
                                 align(FL_ALIGN_RIGHT|FL_ALIGN_WRAP|FL_ALIGN_INSIDE);

                                 nH=this->h();
                                if (((lab==0)|(cellImage==0))) // We don't need to apply any style if there isn't both (label and picture)
                                {
                                  // One of them is zero ..  i.e There is only Label or Only picture
                                  //We need just to calculate the center 
                                 
                                  nW=this->w();                                  
                                  // picture calculation
                                  nXX=this->x()+this->w()-pictWidth;        
                                  nYY=this->y()+this->h()/2 -pictHeight/2;       
    
                                  // Label calculation
                                  nX=this->x();                     
                                  nY=this->y();                                   
                                 }
                                else 
                                {
                                  nW=this->w()-pictWidth;
                                  // BOTH will be drawn
                                  nXX=this->x()+this->w()-pictWidth;
                                  nYY=this->y()+this->h()/2 -pictHeight/2;       
                                  
                                  nX=this->x();                     
                                  nY=this->y();
     
                                }

                              }
                              break;

 default:                     { // the same as FL_Pic_LeftTo_Text_CENTER
                                          align(FL_ALIGN_CENTER|FL_ALIGN_WRAP|FL_ALIGN_INSIDE);

                                 nH=this->h();
                                if (((lab==0)|(cellImage==0))) // We don't need to apply any style if there isn't both (label and picture)
                                {
                                  // One of them is zero ..  i.e There is only Label or Only picture
                                  //We need just to calculate the center 
                                 
                                  nW=this->w();                                  
                                  // picture calculation
                                  nXX=this->x()+this->w()/2 -pictWidth/2;;        
                                  nYY=this->y()+this->h()/2 -pictHeight/2;       
    
                                  // Label calculation
                                  nX=this->x();                     
                                  nY=this->y();                                   
                                 }
                                else 
                                {
                                  nW=int (this->w()/1.5);
                                  // BOTH will be drawn
                                  nXX=this->x()+this->w()/3-pictWidth;        
                                  if(nXX<this->x())
                                     nXX=this->x();
                                  nYY=this->y()+this->h()/2 -pictHeight/2;       
                                  
                                  nX=this->x()+this->w()/2-pictWidth/2;                     
                                  nY=this->y();
     
                                }

                              }
                            

                                     
}
//Start -- End Style



switch (value)
{
case 0: // Not clicked and active 
       {
      
         for (int i=0;i<h();i++)
          {// drawing curve square ... not working 2005-10-28
              xd=0x10*i/h();
                 colorUsed=0xff-xd;
                    fl_color(colorUsed,colorUsed,colorUsed);
                    fl_line(x(),y()+i,w()+x(),y()+i);
          }
		 if (lab)
		 {
          fl_color(this->labelcolor()); 
          draw_label( nX, nY, nW,nH, align());
		 }

         if (cellImage)
         {
           cellImage->draw(nXX,nYY);
         }
          break;
          }
        
case 1:    // clicked and active
{
          
          for (int i=0;i<h();i++)
          {
             xd=0x10*i/h();
             colorUsed=0xef+xd;

             fl_color(colorUsed,colorUsed,colorUsed);
             fl_line(x(),y()+i,x()+w(),y()+i);
           }
           // Black line 
           fl_color(0x00,0x00,0x00);
           fl_rectf(x(),y(),2,h()+1);
           fl_rectf(x(),y(),w()+1,2);
           // white line 
           fl_color(0xff,0xff,0xff);
           fl_rectf(x(),y()+h()-1,w()+1,2);
           fl_rectf(x()+w(),y(),2,h()+1);
 		   if (lab)
		   {
            fl_color(this->labelcolor()); 
            draw_label( nX, nY, nW,nH, align());

		   }

           if (cellImage)
           {
             cellImage->draw(nXX,nYY);
           }

           break;
}
case 2:{ // active and mouse over
         for (int i=0;i<h();i++)
          {
            xd=0x10*i/h();
                 colorUsed=0xff-xd;
                    fl_color(colorUsed,colorUsed,colorUsed);
                    fl_line(x(),y()+i,x()+w(),y()+i);
          
          }
            // Black line 
          fl_color(0x00,0x00,0x00);
          fl_rectf(x(),y()+h()-2,w()+1,2);
          fl_rectf(x()+w(),y(),2,h());
          // white line 
          fl_color(0xff,0xff,0xff);
          fl_rectf(x(),y(),2,h()+1);
          fl_rectf(x(),y(),w()+1,2);
          fl_color(0xff,0xdb,0x00);
          fl_rect(x(),y(),w(),h());
          if (lab)
		  {
            fl_color(this->labelcolor()); 
            draw_label( nX, nY, nW,nH, align());
		  } 

            
          if (cellImage)
           {
             cellImage->draw(nXX,nYY);
           }

          break;
       }
       
case 3:{ // Not active 
     
         for (int i=0;i<h();i++)
          {// drawing curve square ... not working 2005-10-28
              xd=0x10*i/h();
                 colorUsed=0xff-xd;
                    fl_color(colorUsed,colorUsed,colorUsed);
                    fl_line(x(),y()+i,w()+x(),y()+i);
          }
		  if (lab)
		  {
           fl_color(this->labelcolor()); 
           draw_label( nX, nY, nW, nH, align());
		  }
            
         if (cellImage)
         {
          Fl_Image *inactiveImage=cellImage->copy();
          inactiveImage->inactive();
          inactiveImage->draw(nXX,nYY);
          delete(inactiveImage);
         }
          break;
       }



case 4:  // deactivated  and it is seperator "|"
         {
          if(lab) // If the label=0 do somthing else 
          if (!(strcmp(lab,"|")))
           {
             for (int i=0;i<h();i++)
             {
                xd=0x10*i/h();
                colorUsed=0xff-xd;
                fl_color(colorUsed,colorUsed,colorUsed);
                fl_line(x(),y()+i,w()+x(),y()+i);
              }
           }
                fl_color(0xcf,0xcf,0xcf);
                fl_rectf(x()+(w()/2)-1,y()+3,1,h()-5);
                fl_color(0xfe,0xfe,0xfd);                           
                fl_rectf(x()+(w()/2),y()+3,1,h()-5);                            
                deactivate();
         break;
         } 
     
default:
        break;     
}    

}
int  Fl_Button_Cell::handle(int e)
{
     if (active()) // if the widget is not active , neglect everything
     switch (e)
     {
       case FL_PUSH:
       case FL_DRAG:
            {
              if (Fl::event_button() == FL_LEFT_MOUSE)       
              {
                value=1;
                redraw();
                if (when() & FL_WHEN_CHANGED) do_callback();
                return 1;
              }
              break;    
              }
       case FL_RELEASE:
             {
              if (Fl::event_button() == FL_LEFT_MOUSE)                            
               {
               value=0;
               redraw();
               if (when() & FL_WHEN_RELEASE) do_callback();
               return 1;
              }
              break;
              }

       case FL_ENTER:
       case FL_MOVE:
            {
                if (Fl::belowmouse()==this ) 
                {
                  if ((value!=2))
                  {
                     value=2;
                     redraw();
                     return 1;
                 }
                }
                break;
            }
        default:
               {
               if (Fl::belowmouse()!=this ) 
                {
                  value=0;
                  redraw();
                  return 1;
                }
                return 0;

               }
     }
return 0;
}

// class destructor
Fl_Button_Cell::~Fl_Button_Cell()
{
	// insert your code here
}
