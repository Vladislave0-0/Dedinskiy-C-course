CFLAGS = -g -c -Winit-self -Wredundant-decls -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations 			\
		 -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -pipe -fexceptions 				\
		 -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers 			\
		 -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo 		\
		 -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG			\

CC = g++

DIR_ASM = ./Assembler/
DIR_CPU = ./CPU/

TARGET = PROCESSOR

all: make_assembler make_CPU

make_assembler:
	@cd $(DIR_ASM) && make

make_CPU:
	@cd $(DIR_CPU) && make

clean:
	@cd $(DIR_ASM) && make clean
	@cd $(DIR_CPU) && make clean