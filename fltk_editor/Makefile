C	= gcc
CXX	= g++
LD	= g++
CPP	= g++

TARGET	= Editor
FLUID	= fluid
PREFIX=*
IFLAGS	= -I/usr/X11/include 
LFLAGS	= -L/usr/X11R6/lib -L/usr/local/lib
CPPFLAGS= -O2 $(IFLAGS) $(DFLAGS) -Wall
CXXFLAGS= -O2 $(IFLAGS) $(DFLAGS) -Wall
CFLAGS	= -O2 $(IFLAGS) $(DFLAGS) -Wall
LIBS	= -lX11 -lfltk -lfltk_images -lm -lXpm -lpng -lz -ljpeg

SUB_FONT=  ../FontBrowser/
SUB_COLOR= ../colorbrowser/
SUB_SYSDIR= ../systemdirectorybrowser/

CPP_SRC_ED =  Editor.cpp Fl_Split.cpp
CPP_SRC_COL=  fl_color_direct_selector.cpp
CPP_SRC_DIR1=  fl_systemdirectory_browser.cpp
CPP_SRC_DIR2=  fl_ext_tree_browser.cpp 
CPP_SRC_DIR3=  fl_ext_tree_item.cpp 
CPP_SRC_FON=  fl_font_browser.cpp
 
OBJS_EDITOR=  $(CPP_SRC_ED:.cpp=.o) 
OBJS_COLOR=   $(SUB_COLOR)$(CPP_SRC_COL:.cpp=.o)
OBJS_SYSDIR1= $(SUB_SYSDIR)$(CPP_SRC_DIR1:.cpp=.o)  
OBJS_SYSDIR2= $(SUB_SYSDIR)$(CPP_SRC_DIR2:.cpp=.o)
OBJS_SYSDIR3= $(SUB_SYSDIR)$(CPP_SRC_DIR3:.cpp=.o) 
OBJS_FONT=    $(SUB_FONT)$(CPP_SRC_FON:.cpp=.o) 

all	: $(TARGET)

.SUFFIXES:	.cpp .cxx .c .h .o .fld

.fld.cxx:
	$(FLUID) -c $<
.cxx.o :
	$(CXX) -c $< -o $(<:.cxx=.o) $(CXXFLAGS)

.cpp.o :
	$(CPP) -c $< -o $(<:.cpp=.o) $(CPPFLAGS)

.c.o :
	$(CC) -c $< -o $(<:.c=.o) $(CPPFLAGS)

$(TARGET) : $(OBJS_EDITOR) $(OBJS_COLOR) $(OBJS_SYSDIR1) $(OBJS_SYSDIR2) $(OBJS_SYSDIR3) $(OBJS_FONT)
	    $(LD) -o $(TARGET) $(OBJS_EDITOR) $(OBJS_COLOR) $(OBJS_SYSDIR1) $(OBJS_SYSDIR2) $(OBJS_SYSDIR3)  $(OBJS_FONT) $(LFLAGS) $(LLIBS) $(LIBS)

clean:
	-rm *.o
	-rm $(TARGET)

backup:
	tar cvf $(TARGET).tar $(PREFIX).* Makefile 
	gzip $(TARGET).tar