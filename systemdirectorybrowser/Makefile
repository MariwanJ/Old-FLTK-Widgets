CC      = gcc
CXX		= g++
LD		= g++
CPP		= g++
TARGET = explorer
FLUID = fluid
PREFIX  = 

IFLAGS = -I/usr/X11/include
LFLAGS = -L/usr/X11R6/lib -L/usr/local/lib
LFLAGS = $(shell fltk-config --ldflags)
CPPFLAGS  = -O2 -g $(IFLAGS) $(DFLAGS) -Wall 
CXXFLAGS  = -O2 $(IFLAGS) $(DFLAGS) -Wall 
CFLAGS  = -O2 $(IFLAGS) $(DFLAGS) -Wall 
LLIBS =
LIBS = -lfltk -lX11 -lm

CPP_SRC= main.cpp fl_ext_tree_browser.cpp fl_ext_tree_item.cpp fl_systemdirectory_browser.cpp flstring.c vsnprintf.c
OBJS = $(CPP_SRC:.cpp=.o) $(C_SRC:.c=.o)

all : $(TARGET)

.SUFFIXES:	.cpp .c .h .o .fld

.fld.cxx:
	$(FLUID) -c $<
.cxx.o :
	$(CXX) -c $< -o $(<:.cxx=.o) $(CXXFLAGS)
.c.o :
	$(CC)  -c $< -o $(<:.c=.o) $(CPPFLAGS)

$(TARGET) : $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LFLAGS) $(LLIBS) $(LIBS)
#	strip $(TARGET)

clean:
	-rm *.o
	-rm $(TARGET)

backup:
	tar cvf $(TARGET).tar $(PREFIX)*.*  Makefile
	gzip $(TARGET).tar

protos:
	cproto -e -q -E 0 -O /dev/null -o protos.h $(IFLAGS) $(PREFIX)*.cc  $(PREFIX)*.c
