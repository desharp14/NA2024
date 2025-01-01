# Splinify: A Comprehensive Spline Implementation and Curve Fitting Library

## Project Structure

```
Splinify/
├── src/                      # C++ source code
│   ├── main.cpp              # Main program entry
│   ├── SplineUtils/          # Spline function implementations
│   │   ├── LinearSpline.cpp  # Linear spline implementation
│   │   ├── CubicSpline.cpp   # Cubic spline implementation
│   │   └── BSpline.cpp       # B-spline implementation
│   └── CurveFitting/         # Curve fitting algorithms
│       ├── PlaneFitting.cpp  # 2D curve fitting
│       └── SphereFitting.cpp # 3D curve fitting
├── include/                  # C++ header files
│   ├── SplineUtils/          # Spline function headers
│   └── CurveFitting/         # Curve fitting headers
├── lib/                      # External libraries, e.g., Eigen
├── scripts/                  # Python scripts for visualization
│   ├── plot_utils.py         # Utility functions for plotting
│   └── visualizations.py     # Main plotting script using Matplotlib
├── data/                     # Raw and processed data
│   ├── raw/
│   └── processed/
├── tests/                    # Test scripts
│   ├── CppTests/             # C++ tests
│   │   └── spline_tests.cpp
│   └── PythonTests/          # Python visualization tests
│       └── test_plots.py
├── docs/                     # Project documentation
│   ├── design.tex            # Design documentation
│   └── report.tex            # Project report
├── figures/                  # Generated figures
├── CMakeLists.txt            # CMake build file
├── requirements.txt          # Python dependencies
└── README.md                 # Project overview
```

---

## Features

### 1. Spline Implementation
- **Piecewise-polynomial splines (pp-Form)**
- **B-splines (B-Form)**

### 2. Linear and Cubic Splines
- Implement linear splines in both **pp-Form** and **B-spline** formats.
- Implement three types of cubic splines (\( S_3^2 \)) in both **pp-Form** and **B-spline** formats:
  - Periodic boundary conditions.
  - Natural splines.
  - Complete cubic splines.

### 3. Spline Validation
- Ensure **pp-Form** and **B-spline** formats produce identical curves for the same interpolation points and boundary conditions.

### 4. Support for Arbitrary Orders and Nodes
- Enable splines of arbitrary orders and custom nodes in the **B-spline** format.

### 5. Curve Fitting
- **2D Curve Fitting:** Spline curve fitting on planes.
- **3D Curve Fitting:** Spline curve fitting on spherical surfaces.

### 6. Programming Exercises
- Complete all programming exercises from **Chapter 3**, including:
  - Fitting specific curves.
  - Applying spline functions.
- Exercises include tasks **A, C, D, E,** and **F**.

### 7. Additional Features and Testing
- Use `jsoncpp` for controlling interpolation parameters, including boundary conditions, order, nodes, and intervals.
- Implement spline curve fitting in arbitrary dimensions.
- Perform convergence analysis for various splines.
- Develop and test algorithms for detecting self-intersections in curves.
- Design robust test functions for comprehensive evaluation.

### 8. Documentation and Report
- **Design and Mathematical Documentation:**
  - Program structure explanation.
  - Design rationale.
  - Class functions and interfaces.
  - Relationships between classes.
  - Mathematical equations and theories.
- **Project Report:**
  - Results and analysis of all tasks.
  - Error analysis, particularly for additional tasks.
