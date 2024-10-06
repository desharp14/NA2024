# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Source files
SOURCES = B.cpp C.cpp D.cpp E.cpp F.cpp
HEADERS = Function.h EquationSolver.h
OBJECTS = $(SOURCES:.cpp=.o)

# LaTeX report
TEX_SRC = report.tex
TEX_PDF = report.pdf

# Default target
all: run report

# Compile and run all the problem files
run: $(OBJECTS)
	@echo "Running all problem files..."
	$(CXX) $(CXXFLAGS) -o program $(OBJECTS)
	./program

# Compile LaTeX report to PDF
report: $(TEX_SRC)
	@echo "Compiling report..."
	pdflatex $(TEX_SRC)
	bibtex $(basename $(TEX_SRC)).aux
	pdflatex $(TEX_SRC)
	pdflatex $(TEX_SRC)

# Clean up intermediate files
clean:
	@echo "Cleaning up..."
	rm -f *.o program *.aux *.log *.out *.synctex.gz *.toc *.bbl *.blg *.run.xml $(TEX_PDF)

# Phony targets
.PHONY: all run report clean
