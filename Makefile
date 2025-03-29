CFLAGS = -g -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations  \
         -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -pipe -fexceptions -Wcast-qual	              \
         -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op                     \
         -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192             \
         -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG                                                  \

TARGET = diff
CC = g++

PREF_GRPH = ./Graphics/
PREF_OBJ = ./obj/
PREF_SRC = ./src/
PREF_OUT = ./Output/

DIFF_SRC = $(wildcard $(PREF_SRC)*.cpp)
GRPH_SRC = $(wildcard $(PREF_GRPH)*.cpp)

DIFF_OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(DIFF_SRC))
GRPH_OBJ = $(patsubst $(PREF_GRPH)%.cpp, $(PREF_OBJ)%.o, $(GRPH_SRC))

OBJ = $(DIFF_OBJ) $(GRPH_OBJ)

all : $(TARGET)

$(TARGET) : $(OBJ) 	
	@$(CC) $(OBJ) -o $(TARGET)

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

$(PREF_OBJ)%.o : $(PREF_GRPH)%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(TARGET) $(PREF_OBJ)*.o $(PREF_OUT)*.txt $(PREF_OUT)*.png $(PREF_OUT)*.tex TexExpression.pdf
    