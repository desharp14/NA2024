
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude
BUILD_DIR = build
DATA_DIR = $(BUILD_DIR)/data
FIGURES_DIR = figures
SCRIPTS_DIR = scripts
DOCS_DIR = /Users/marin/Desktop/Splinify/docs

MAIN_EXECUTABLE = $(BUILD_DIR)/splinify
CUBIC_SPLINE_TEST_EXECUTABLE = $(BUILD_DIR)/test_cubic_spline
BSPLINE_TEST_EXECUTABLE = $(BUILD_DIR)/test_bspline
INPUT_VALIDATOR_EXECUTABLE = $(BUILD_DIR)/test_input_validator
EXERCISE_A_EXECUTABLE = $(BUILD_DIR)/test_exercise_a
EXERCISE_C_EXECUTABLE = $(BUILD_DIR)/test_piecewise_polynomial
EXERCISE_E_EXECUTABLE = $(BUILD_DIR)/test_exercise_e

MAIN_SOURCES = src/main.cpp src/SplineUtils/CubicSpline.cpp
CUBIC_SPLINE_TEST_SOURCES = tests/CppTests/test_cubic_spline.cpp src/SplineUtils/CubicSpline.cpp
BSPLINE_TEST_SOURCES = tests/CppTests/test_bspline.cpp src/SplineUtils/BSpline.cpp src/SplineUtils/CubicSpline.cpp
INPUT_VALIDATOR_SOURCES = tests/CppTests/test_input_validator.cpp src/SplineUtils/InputValidator.cpp
EXERCISE_A_SOURCE = tests/CppTests/test_exercise_a.cpp
EXERCISE_C_SOURCES = tests/CppTests/test_piecewise_polynomial.cpp src/SplineUtils/PiecewisePolynomialSpline.cpp
EXERCISE_E_SOURCES = tests/CppTests/test_exercise_e.cpp src/SplineUtils/ExerciseE.cpp
HEADERS = include/SplineUtils/CubicSpline.h include/SplineUtils/BSpline.h include/SplineUtils/InputValidator.h include/SplineUtils/PiecewisePolynomialSpline.h include/SplineUtils/ExerciseE.h

PYTHON_SCRIPT = $(SCRIPTS_DIR)/visualizations.py

all: run_tests plot generate_reports

$(MAIN_EXECUTABLE): $(MAIN_SOURCES) $(HEADERS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(MAIN_EXECUTABLE) $(MAIN_SOURCES)

$(CUBIC_SPLINE_TEST_EXECUTABLE): $(CUBIC_SPLINE_TEST_SOURCES) $(HEADERS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(CUBIC_SPLINE_TEST_EXECUTABLE) $(CUBIC_SPLINE_TEST_SOURCES)

$(BSPLINE_TEST_EXECUTABLE): $(BSPLINE_TEST_SOURCES) $(HEADERS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(BSPLINE_TEST_EXECUTABLE) $(BSPLINE_TEST_SOURCES)

$(INPUT_VALIDATOR_EXECUTABLE): $(INPUT_VALIDATOR_SOURCES) $(HEADERS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(INPUT_VALIDATOR_EXECUTABLE) $(INPUT_VALIDATOR_SOURCES)

$(EXERCISE_A_EXECUTABLE): $(EXERCISE_A_SOURCE)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(EXERCISE_A_EXECUTABLE) $(EXERCISE_A_SOURCE)

$(EXERCISE_C_EXECUTABLE): $(EXERCISE_C_SOURCES) $(HEADERS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(EXERCISE_C_EXECUTABLE) $(EXERCISE_C_SOURCES)

$(EXERCISE_E_EXECUTABLE): $(EXERCISE_E_SOURCES) $(HEADERS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(EXERCISE_E_EXECUTABLE) $(EXERCISE_E_SOURCES)

run_main: $(MAIN_EXECUTABLE)
	./$(MAIN_EXECUTABLE)
run_cubic_tests: $(CUBIC_SPLINE_TEST_EXECUTABLE)
	mkdir -p $(DATA_DIR)
	./$(CUBIC_SPLINE_TEST_EXECUTABLE)

run_bspline_tests: $(BSPLINE_TEST_EXECUTABLE)
	mkdir -p $(DATA_DIR)
	./$(BSPLINE_TEST_EXECUTABLE)

run_input_validator: $(INPUT_VALIDATOR_EXECUTABLE)
	./$(INPUT_VALIDATOR_EXECUTABLE)

run_exercise_a: $(EXERCISE_A_EXECUTABLE)
	mkdir -p $(DATA_DIR)
	./$(EXERCISE_A_EXECUTABLE)

run_exercise_c: $(EXERCISE_C_EXECUTABLE)
	mkdir -p $(DATA_DIR)
	./$(EXERCISE_C_EXECUTABLE)

run_exercise_e: $(EXERCISE_E_EXECUTABLE)
	mkdir -p $(DATA_DIR)/ExerciseE
	./$(EXERCISE_E_EXECUTABLE)

run_tests: run_cubic_tests run_bspline_tests run_input_validator run_exercise_a run_exercise_c run_exercise_e

plot: run_tests
	mkdir -p $(FIGURES_DIR)
	cd $(SCRIPTS_DIR) && python $(PYTHON_SCRIPT)

generate_reports:
	cd $(DOCS_DIR) && latexmk -pdf design.tex
	cd $(DOCS_DIR) && latexmk -pdf report.tex

clean:
	rm -rf $(BUILD_DIR) $(FIGURES_DIR)
	rm -f $(DOCS_DIR)/*.pdf $(DOCS_DIR)/*.log $(DOCS_DIR)/*.aux $(DOCS_DIR)/*.out

help:
	@echo "Makefile 使用指南:"
	@echo "  make all            - 编译、生成测试数据并绘制图像"
	@echo "  make run_main       - 编译并运行主程序"
	@echo "  make run_tests      - 编译并运行所有测试程序生成数据文件"
	@echo "  make run_exercise_a - 编译并运行 练习 A 的测试程序"
	@echo "  make run_exercise_c - 编译并运行 练习 C 的测试程序"
	@echo "  make run_exercise_e - 编译并运行 练习 E 的测试程序"
	@echo "  make plot           - 使用 Python 绘制图像"
	@echo "  make clean          - 删除生成的文件和目录"
	@echo "  make generate_reports - 生成设计文档和报告文档"