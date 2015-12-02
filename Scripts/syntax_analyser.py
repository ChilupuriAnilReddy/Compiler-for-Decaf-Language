import sys
import os
file_name = sys.argv[1]
if __name__ == "__main__":
	#os.system("clear")
	#os.system("clear")
	os.system("bison -d module2_bison.y")
	os.system("flex module2_flex.l")
	os.system("g++ module2_bison.tab.c module2_class_defination.cpp lex.yy.c -lfl -o executable `llvm-config --libs core jit native --cxxflags` `llvm-config --ldflags` ")
	os.system("./executable"+" " + str(file_name))
