include ../common.mk

INCLUDES = -I $(crave_INCLUDES) -I $(metaSMT_INCLUDES)
LIBS = $(metaSMT_LIBRARIES) $(crave_LIBRARIES)

SRC = main.cpp
TARGET = test

all: $(SRC)
	g++ $(SRC) $(INCLUDES) $(LIBS) -o $(TARGET) -O2
	
clean:
	rm -f $(TARGET)

