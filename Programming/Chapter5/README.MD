# Makefile Guide

This Makefile manages the compilation and execution of C++ programs (A and B), a Python script (C), and report generation.

## Makefile Commands

### Compilation Targets

- **A:** Compiles `A.cpp` into an executable `A`.
- **B:** Compiles `B.cpp` into an executable `B`.

### Execution Targets

- **run_A:** Runs the `A` program and then executes `A.py`.
- **run_B:** Runs the `B` program.
- **run_C:** Executes the Python script `C.py`.


### Report Generation

- **report:** Compiles the LaTeX report file `report.tex` into `report.pdf` using `xelatex`.  Runs `xelatex` twice to resolve references. Requires LaTeX to be installed.


### Cleanup

- **clean:** Removes the compiled executables (`A`, `B`),  `coefficients.txt`, `A.png` (if they exist), and LaTeX auxiliary files.

### Default Target

- **all:** (Implicit default) Compiles `A.cpp` and `B.cpp` into their respective executables.  Does not run them.

