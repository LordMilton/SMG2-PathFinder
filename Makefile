CC   = g++

SRCDIR=./src
TESTDIR=./test
INCDIR=./inc
BINDIR=./bin
OBJDIR=$(BINDIR)

SRCS=$(SRCDIR)/Galaxy.cpp \
     $(SRCDIR)/Star.cpp \
     $(SRCDIR)/GalaxyMap.cpp

#TESTS=

TARGET = $(BINDIR)/pathFinder

INCLUDE = $(addprefix -I,$(INCDIR))
OBJS=${SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o}
CPPFLAGS   = $(INCLUDE)

all: $(TARGET)

$(TARGET): 
	$(CC) $(CPPFLAGS) -o $@ $(SRCS)
   
test: $(TARGET)
	$(CC) $(CPPFLAGS) $<  