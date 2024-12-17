################################################################################
#
# https://github.com/lostella/SimpleMakefile
#
### CUSTOMIZE BELOW HERE #######################################################

CC=g++  # define the compiler to use
INCLUDES=-I../..
TARGET=si5351_pipe # define the name of the executable
SOURCES=si5351_pipe.cpp ../../si5351_linux.cpp ../../Si5351Arduino/src/si5351_base.cpp ../../userspace-i2c/src/i2c.cpp
##CFLAGS=-Wall  #-O3  # for gcc
CXXFLAGS=-Wall $(INCLUDES) #-O3 for g++
LFLAGS=-lm -lc

################################################################################
### DO NOT EDIT THE FOLLOWING LINES ############################################

# define list of objects
OBJSC=$(SOURCES:.c=.o)
OBJS=$(OBJSC:.cpp=.o)

# the target is obtained linking all .o files
all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)

purge: clean
	rm -f $(TARGET)

clean:
	rm -f $(OBJS)

################################################################################
################################################################################
