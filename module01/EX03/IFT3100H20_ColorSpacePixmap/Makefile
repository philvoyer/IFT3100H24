TARGET = generate_pixmap

CC = g++               # gcc c++ compiler
CV = -std=c++11        # c++ version
CD = -g                # generate debug information
CW = -Wall -Wextra     # compiler extra warnings
CP = -pedantic         # ISO C/C++ compliance
CN = -Wc++11-narrowing # warnings about narrowing
CO = -O0               # level of optimization
RF = rm -f             # force remove
RR = rm -rf            # force remove recursive

SOURCE = main.cpp

default: release

release:
	$(CC) $(CV) $(CO) -o $(TARGET) $(SOURCE)

debug:
	$(CC) $(CV) $(CD) $(CN) $(CW) $(CP) -o $(TARGET) $(SOURCE)

clean:
	$(RF) $(TARGET)
	$(RR) $(TARGET).dSYM
