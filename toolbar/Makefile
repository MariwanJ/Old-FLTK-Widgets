CC   = $(shell fltk-config --cc)
CXX  =$(shell fltk-config --cxx)
LD   =g++

TARGET   =toolbar
FLUID    =fluid
PREFIX   =
CFLAGS   = -Wall -Os -I. $(shell fltk-config --use-images --cflags)
CXXFLAGS =-Wall -Os -I. $(shell fltk-config --use-images --cflags)
LIBS=$(shell fltk-config --use-images --ldstaticflags)

CPP_SRC=main.cxx Fl_ToolBar.cxx Fl_ToolBar_Button.cxx Fl_Button_Cell.cxx
OBJS = $(CPP_SRC:.cpp=.o) $(C_SRC:.c=.o)

all : $(TARGET)

.SUFFIXES:	.cpp .cxx .c .h .o .fld

.fld.cxx:
	$(FLUID) -c $<
.cxx.o :
	$(CXX) -c $< -o $(<:.cxx=.o) $(CXXFLAGS)
.c.o :
	$(CC) -c $< -o $(<:.c=.o) $(CFLAGS)

$(TARGET) : $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LIBS)
# strip $(TARGET)

clean:
	-rm *.o
	-rm $(TARGET)

backup:
	tar cvf $(TARGET).tar $(PREFIX)*.cpp  $(PREFIX)*.h  $(PREFIX)*.JPG =
	gzip $(TARGET).tar
