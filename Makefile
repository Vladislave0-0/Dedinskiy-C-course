CFLAGS = -g -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations  \
         -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -pipe -fexceptions -Wcast-qual	              \
         -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op                     \
         -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192             \
         -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG                                                  \

TARGET = list
CC = g++

PREF_VIZ = ./Graphviz/
PREF_OBJ = ./obj/
PREF_SRC = ./src/
PREF_IMG = ./Images/

LIST_SRC = $(wildcard $(PREF_SRC)*.cpp)
VIZ_SRC = $(wildcard $(PREF_VIZ)*.cpp)

LIST_OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(LIST_SRC))
VIZ_OBJ = $(patsubst $(PREF_VIZ)%.cpp, $(PREF_OBJ)%.o, $(VIZ_SRC))

OBJ = $(LIST_OBJ) $(VIZ_OBJ)

all : $(TARGET)

$(TARGET) : $(OBJ) 	
	@$(CC) $(OBJ) -o $(TARGET)

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

$(PREF_OBJ)%.o : $(PREF_VIZ)%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(TARGET) $(PREF_OBJ)*.o $(PREF_IMG)*.png graph_log.html graphviz.txt
    