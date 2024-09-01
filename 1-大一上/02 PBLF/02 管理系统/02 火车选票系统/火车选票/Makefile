# Define the compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Specify the executable target name
TARGET = booking_system

# Specify source files and object files
SRCS = main.c prepare.c operation.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Include dependency info for *existing* .o files
-include $(OBJS:.o=.d)

# Compile source files and generate dependency info
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	$(CC) $(CFLAGS) -MM $< > $*.d

# Clean target to remove build artifacts
clean:
	rm -f $(TARGET) $(OBJS) $(OBJS:.o=.d)

# Phony targets
.PHONY: all clean