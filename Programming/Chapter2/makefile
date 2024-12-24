#Makefile

# Compiler and flags
CXX = g++
CXXFLAGS = -o

# Targets for compiling C++ files
B: B.cpp interpolation.cpp
	$(CXX) B.cpp interpolation.cpp $(CXXFLAGS) B

C: C.cpp interpolation.cpp
	$(CXX) C.cpp interpolation.cpp $(CXXFLAGS) C

D: D.cpp interpolation.cpp
	$(CXX) D.cpp interpolation.cpp $(CXXFLAGS) D

E: E.cpp interpolation.cpp
	$(CXX) E.cpp interpolation.cpp $(CXXFLAGS) E

F: F.cpp interpolation.cpp
	$(CXX) F.cpp interpolation.cpp $(CXXFLAGS) F

# Target to run the B program and generate B plot
run_B: B
	./B
	python3 B.py  # Use 'python' instead of 'python3' on Windows

# Target to run the C program and generate C plot
run_C: C
	./C
	python3 C.py  # Use 'python' instead of 'python3' on Windows

# Target to run the D program (no plot required)
run_D: D
	./D

# Target to run the E program (no plot required)
run_E: E
	./E

# Target to run the F program and generate F plot
run_F: F
	./F
	python3 F.py  # Use 'python' instead of 'python3' on Windows

# General run target to run all programs and generate plots for B, C and F
run_all: run_B run_C run_D run_E run_F

# Target to generate the report.pdf from report.tex
report: report.tex
	xelatex report.tex
	xelatex report.tex
	rm *.log *.aux

# Clean up executable files and auxiliary files generated during LaTeX compilation
clean:
	rm -f B C D E F *.txt *.log *.aux *.out *.pdf
