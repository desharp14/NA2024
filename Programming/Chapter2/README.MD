# Makefile Guide

This Makefile manages the compilation and execution of various C++ programs for interpolation tasks, as well as report generation and cleanup.

## Makefile Commands

### Compilation Targets
- **B**: Compiles `B.cpp` with `interpolation.cpp` into an executable `B`.
- **C**: Compiles `C.cpp` with `interpolation.cpp` into an executable `C`.
- **D**: Compiles `D.cpp` with `interpolation.cpp` into an executable `D`.
- **E**: Compiles `E.cpp` with `interpolation.cpp` into an executable `E`.
- **F**: Compiles `F.cpp` with `interpolation.cpp` into an executable `F`.

### Run and Plot Targets
- **run_B**: Runs the `B` program and generates the plot using `B.py`.
- **run_C**: Runs the `C` program and generates the plot using `C.py`.
- **run_D**: Runs the `D` program (no plot required).
- **run_E**: Runs the `E` program (no plot required).
- **run_F**: Runs the `F` program and generates the plot using `F.py`.

### Combined Execution
- **run_all**: Executes all run targets (B, C, D, E, and F) and generates plots for B, C, and F.

### Report Generation
- **report**: Compiles the LaTeX report file `report.tex` into `report.pdf` using `xelatex`. Ensure all required LaTeX packages are installed.

### Cleanup
- **clean**: Removes all compiled executables (`B`, `C`, `D`, `E`, `F`) and any temporary `.txt` files.
