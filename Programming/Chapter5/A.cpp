#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>

// Function to perform Gaussian Elimination
std::vector<double> gaussianElimination(std::vector<std::vector<double>> A, std::vector<double> b, int n) {
    std::vector<double> x(n, 0);
    for (int i = 0; i < n; ++i) {
        // Find the pivot
        int pivot = i;
        for (int j = i + 1; j < n; ++j) {
            if (std::fabs(A[j][i]) > std::fabs(A[pivot][i]))
                pivot = j;
        }
        // Swap rows
        std::swap(A[i], A[pivot]);
        std::swap(b[i], b[pivot]);

        // Eliminate column
        for (int j = i + 1; j < n; ++j) {
            double ratio = A[j][i] / A[i][i];
            for (int k = i; k < n; ++k) {
                A[j][k] -= ratio * A[i][k];
            }
            b[j] -= ratio * b[i];
        }
    }

    // Back substitution
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0;
        for (int j = i + 1; j < n; ++j) {
            sum += A[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / A[i][i];
    }

    return x;
}

// Function to calculate the least squares coefficients
std::vector<double> leastSquares(const std::vector<double>& x, const std::vector<double>& y, int degree) {
    int n = degree + 1;
    int N = x.size();

    // Build the normal equations matrix and vector
    std::vector<std::vector<double>> G(n, std::vector<double>(n, 0));
    std::vector<double> c(n, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double sum = 0;
            for (int k = 0; k < N; ++k) {
                sum += std::pow(x[k], i + j);
            }
            G[i][j] = sum;
        }
        double sum = 0;
        for (int k = 0; k < N; ++k) {
            sum += y[k] * std::pow(x[k], i);
        }
        c[i] = sum;
    }

    // Solve the normal equations
    return gaussianElimination(G, c, n);
}

int main() {
    // Input data
    std::vector<double> x = {0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 
                             5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0};
    std::vector<double> y = {2.9, 2.7, 4.8, 5.3, 7.1, 7.6, 7.7, 7.6, 9.4, 9.0, 
                             9.6, 10.0, 10.2, 9.7, 8.3, 8.4, 9.0, 8.3, 6.6, 6.7, 4.1};

    // Degree of the polynomial
    int degree = 2;

    // Calculate the coefficients
    std::vector<double> coefficients = leastSquares(x, y, degree);

    // Print the polynomial equation
    std::cout << "The best-fit quadratic polynomial is:\n";
    std::cout << "$\\hat{\\varphi}(x) = ";
    std::cout << std::fixed << std::setprecision(8);
    std::cout << coefficients[2] << "x^2 + " 
              << coefficients[1] << "x + " 
              << coefficients[0] << "$" << std::endl;

    // Save coefficients to a file
    std::ofstream outFile("coefficients.txt");
    for (double coeff : coefficients) {
        outFile << coeff << "\n";
    }
    outFile.close();

    return 0;
}
