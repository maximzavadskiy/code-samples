VariableTest: VariableTest.cpp  Variable.cpp  Value.cpp my_fractionlib.cpp my_regexlib.cpp
	c++  -o VariableTest VariableTest.cpp  Variable.cpp  Value.cpp my_fractionlib.cpp my_regexlib.cpp >debug 2>&1 
#VariableTest.o: VariableTest.cpp
#	c++ -c -o VariableTest.o VariableTest.cpp
#Value.o: Value.cpp my_fractionlib.o
#	c++ -c -o Value.o Value.cpp my_fractionlib.o

