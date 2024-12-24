# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Targets
TARGET_A = A
CPP_SRC_A = A.cpp
PYTHON_SCRIPT_A = A.py
OUTPUT_FILE_A = coefficients.txt
PLOT_FILE_A = A.png

TARGET_B = B
CPP_SRC_B = B.cpp

TARGET_C = C  # New target for C.py
PYTHON_SCRIPT_C = C.py # Python script for C

.PHONY: all clean run_A run_B run_C # Add run_C to phony targets


# Default target
all: $(TARGET_A) $(TARGET_B)


# Compile the C++ source for A
$(TARGET_A): $(CPP_SRC_A)
	$(CXX) $(CXXFLAGS) -o $(TARGET_A) $(CPP_SRC_A)

# Compile the C++ source for B
$(TARGET_B): $(CPP_SRC_B)
	$(CXX) $(CXXFLAGS) -o $(TARGET_B) $(CPP_SRC_B)

# Run the entire workflow for A
run_A: $(TARGET_A)
	./$(TARGET_A)
	python $(PYTHON_SCRIPT_A)

# Run the entire workflow for B
run_B: $(TARGET_B)
	./$(TARGET_B)

# Run C.py  (New rule)
run_C:
	python $(PYTHON_SCRIPT_C)

#Generate the report.pdf from report.tex
report: report.tex

	xelatex report.tex
	xelatex report.tex
	rm *.log *.aux

# Clean up generated files (Improved)
clean:
	rm -f $(TARGET_A) $(OUTPUT_FILE_A) $(PLOT_FILE_A)
	rm -f $(TARGET_B)  # Removed nonexistent OUTPUT/PLOT_FILE_B