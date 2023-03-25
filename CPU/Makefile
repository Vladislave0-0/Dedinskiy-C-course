CFLAGS = -g -c -Winit-self -Wredundant-decls -Wundef -Wcast-align -Wfloat-equal -Winline                                \
		 -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default                \
 		 -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy               \
		 -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers    \
		 -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing      \
		 -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG

TARGET = CPU
CC = g++

PREF_STK = ../Stack/src/
PREF_OBJ = ./obj/
PREF_SRC = ./src/

CPU_SRC = $(wildcard $(PREF_SRC)*.cpp)
STK_SRC = $(wildcard $(PREF_STK)*.cpp)

CPU_OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(CPU_SRC))
STK_OBJ = $(patsubst $(PREF_STK)%.cpp, $(PREF_OBJ)%.o, $(STK_SRC))

OBJ = $(CPU_OBJ) $(STK_OBJ)

all : $(TARGET)

$(TARGET) : $(OBJ) 	
	$(CC) $(OBJ) -o $(TARGET)

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(PREF_OBJ)%.o : $(PREF_STK)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(TARGET) $(PREF_OBJ)*.o
