#-----------------------------------------
# Sunday May the 3rd 2020
# Asif Mammadov
# makefile for linedraw project
#-----------------------------------------

########################
# OS detection
#########################

OS = $(shell uname)

########################
# Compiler options
#########################

CC=gcc

CFLAGS = -I. -I /usr/include \
               -I /usr/local/include \
               -I /opt/local/include/GL \
               -I /opt/X11/include \
               -Wno-deprecated

ifeq (${OS},Darwin)
  CFLAGS += -I /System/Library/Frameworks/OpenGL.framework/Headers -I /System/Library/Frameworks/GLUT.framework/Versions/A//Headers
else
  CFLAGS += -I /usr/include/GL -I /usr/include
endif

CCOPTIONS = -g -O0 -Wall

#########################
# Librairies
#########################

ifeq ($(OS),Darwin)
	LIBS = -lm -framework OpenGL -framework GLUT
else
	LIBS = -lm -lGLU -lGL -lglut
endif

#########################
# Sources and objects
#########################
SDIR = src
ODIR = obj
IDIR = include

SOURCES = $(patsubst $(SDIR)/%.c, %.c, $(wildcard $(SDIR)/*.c))
OBJECTS=$(patsubst %.c, $(ODIR)/%.o,$(SOURCES))
EXECUTABLE=linedraw

#########################
# Rules
#########################

#To check whether Object directory exists


all : $(EXECUTABLE)

$(ODIR)/%.o : $(SDIR)/%.c | checkObj
	$(CC) -c -o $@ $< $(CFLAGS) $(CCOPTIONS)


$(EXECUTABLE) : $(OBJECTS)
	${CC} -o $@ $^ ${LIBS}


$(EXECUTABLE).zip :
	zip $(EXECUTABLE).zip -r $(IDIR) $(SDIR) makefile

checkObj:
ifeq (,$(wildcard $(ODIR)))
	mkdir $(ODIR)
endif

clean :
	rm -rf $(ODIR) *~

putaway :
	rm -rf $(ODIR) *~ $(EXECUTABLE)

cleanZip : 
	rm -f *.zip
