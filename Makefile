################################################################################
#
# https://github.com/lostella/SimpleMakefile
#
### CUSTOMIZE BELOW HERE #######################################################

CC=g++ # define the compiler to use
TARGET=linux_example # define the name of the executable
SOURCES=linux_example.cpp userspace-i2c/src/i2c.cpp Si5351Arduino/src/si5351.cpp
CFLAGS=-Wall #-O3
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
	rm -f *.o

################################################################################
################################################################################
