Expression.o: Expression.cpp Value.o Errors.o Answer.o
	c++ -c -o  Expression.o Expression.cpp Value.o Errors.o Answer.o >debug 2>&1
