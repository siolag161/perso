NAME :=  timer

OBJDIR  := obj/
BINDIR  := bin/
EXE     := $(BINDIR)$(NAME)
SOURCEDIR := src/
INCLUDEDIR := include/

SFILES  := cc
OFILES  := o
CC      := g++
CFLAGS  := -c -O3 -Wall

SOURCES := $(wildcard $(SOURCEDIR)*.$(SFILES))
OBJECTS := $(patsubst $(SOURCEDIR)%$(SFILES), $(OBJDIR)%$(OFILES), $(SOURCES))

INCLUDES := -I$(INCLUDEDIR) 


ALLFILES := $(SOURCES)

.PHONY: all clean test

all:	$(EXE) 

$(EXE):	$(OBJECTS)	
	@mkdir -p $(BINDIR)
	@$(CC) -O3 $(INCLUDES) $^ -o$@ -lrt


$(OBJDIR)%$(OFILES): $(SOURCEDIR)%$(SFILES) 
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(INCLUDES) $< -o $@ -lrt

$(OBJDIR):	
	mkdir -p $(OBJDIR)


clean: 
	rm -f $(OBJDIR)*.$(OFILES) $(SOURCEDIR)*~ $(INCLUDEDIR)*~ $(BINDIR)$(NAME) 
