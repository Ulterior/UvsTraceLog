# main compiler
CC := gcc

TARGET1 := screenlog
TARGET2 := filelog
TARGET3 := tcplog
TARGET4 := tcplistener

INCLUDES:= -I$(SRC_DIR). -I$(SRC_DIR)TraceLogger/includes
CFLAGS:=$(INCLUDES) -std=c++11 -lstdc++
LIBS:= -lpthread -lstdc++
LDFLAGS := -L$(SRC_DIR) -Wl

LIB_SOURCES := $(shell find $(SRC_DIR)TraceLogger/src -name '*.cpp')
trace_log_objs := $(LIB_SOURCES:%.cpp=%.o)

#$(info VAR is $(trace_log_objs))

all: ${trace_log_objs} $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4)

# The rule to compile object files and produce dependencies.
%.o : %.cpp
	${CC} $(CFLAGS) -c $< -o $@

$(TARGET1):
	$(CC) $(CFLAGS) -c $(TARGET1).cpp -o $(TARGET1).o
	$(CC) ${trace_log_objs} $(TARGET1).o -o $(TARGET1) $(LDFLAGS) $(LIBS)

$(TARGET2):
	$(CC) $(CFLAGS) -c $(TARGET2).cpp -o $(TARGET2).o
	$(CC) ${trace_log_objs} $(TARGET2).o -o $(TARGET2) $(LDFLAGS) $(LIBS)

$(TARGET3):
	$(CC) $(CFLAGS) -c $(TARGET3).cpp -o $(TARGET3).o
	$(CC) ${trace_log_objs} $(TARGET3).o -o $(TARGET3) $(LDFLAGS) $(LIBS)

$(TARGET4):
	$(CC) $(CFLAGS) -c $(TARGET4).cpp -o $(TARGET4).o
	$(CC) ${trace_log_objs} $(TARGET4).o -o $(TARGET4) $(LDFLAGS) $(LIBS)

clean:
	@rm -rf $(trace_log_objs) $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) *.o
