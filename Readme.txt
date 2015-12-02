LLVM used - 3.4
Scanner - flex
Parser - bison
Install all the above along with llvm-runtime
Makesure llvm folder is present in /usr/include

How to run:
	python syntax_analyser.py path_to_test_program
	save out put of the out command in file say output.txt
	run lli output.txt
	we can see the output of test_program


codegen for loops(for,if) are not implemented

