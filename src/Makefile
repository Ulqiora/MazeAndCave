all:

cpplint:
	cp -f ../materials/linters/CPPLINT.cfg ./
	python3 ../materials/linters/cpplint.py --extensions=cpp ./Maze/Controller/*.cpp ./Maze/Controller/*.h ./Maze/Model/*.cpp ./Maze/Model/*.h ./Maze/View/*.cpp ./Maze/View/*.h
	rm -rf CPPLINT.cfg
cppcheck:
	cppcheck --enable=all --suppress=unusedFunction Maze/*/*.cpp *.h
leaks:
	CK_FORK=no leaks --atExit -- ./Maze/Tests/test