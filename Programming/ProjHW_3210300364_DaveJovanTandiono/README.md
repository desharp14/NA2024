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
│   ├── design.tex
│   └── report.tex
├── figures/                  # Generated figures
├── CMakeLists.txt            # CMake build file
├── requirements.txt          # Python dependencies
└── README.md                 # Project overview

1.	Spline Implementation
	•	Implement piecewise-polynomial splines (pp-Form).
	•	Implement B-splines (B-Form).
	2.	Linear and Cubic Splines
	•	Implement linear splines in both pp-Form and B-spline formats.
	•	Implement three types of cubic splines (S_3^2) in both pp-Form and B-spline formats:
	•	Periodic boundary conditions.
	•	Natural splines.
	•	Complete cubic splines.
	3.	Spline Validation
	•	Validate that pp-Form and B-spline formats produce identical curves given the same interpolation points and boundary conditions.
	4.	Support for Arbitrary Orders and Nodes
	•	Enable support for splines of arbitrary orders and custom nodes in the B-spline format.
	5.	Curve Fitting
	•	Implement spline curve fitting on planes (2D curve fitting).
	•	Implement spline curve fitting on spherical surfaces (3D curve fitting).
	6.	Programming Exercises
	•	Complete all programming exercises from Chapter 3, including fitting specific curves and applying spline functions.
	•	Exercises include tasks A, C, D, E, and F.
	7.	Additional Features and Testing
	•	Use \texttt{jsoncpp} to control interpolation parameters, such as boundary conditions, order, nodes, and intervals.
	•	Implement spline curve fitting in arbitrary dimensions.
	•	Perform convergence analysis for various splines.
	•	Design additional test functions for more robust evaluation.
	•	Implement and test algorithms for detecting self-intersections in curves.
	8.	Documentation and Report
	•	Prepare design and mathematical documentation, including:
	•	Program structure explanation.
	•	Design rationale.
	•	Class functions and interfaces.
	•	Relationships between classes.
	•	Mathematical equations and theories used.
	•	Prepare a project report that includes:
	•	Results and analysis of all tasks.
	•	Error analysis, particularly for additional tasks.