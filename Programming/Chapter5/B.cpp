#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

double matrix2Norm(const std::vector<std::vector<double>>& A) {
    int rows = A.size();
    int cols = A[0].size();
    double maxSingularValue = 0.0;
    for (int j = 0; j < cols; ++j) {
        double colNormSq = 0.0;
        for (int i = 0; i < rows; ++i) {
            colNormSq += A[i][j] * A[i][j];
        }
        maxSingularValue = std::max(maxSingularValue, std::sqrt(colNormSq));
    }
    return maxSingularValue;
}

std::vector<std::vector<double>> matrixMultiply(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int rowsB = B.size();
    int colsB = B[0].size();
    if (colsA != rowsB) {
        throw std::invalid_argument("Matrix dimensions are not compatible for multiplication.");
    }
    std::vector<std::vector<double>> result(rowsA, std::vector<double>(colsB, 0.0));
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

std::vector<std::vector<double>> transpose(const std::vector<std::vector<double>>& A) {
    int rows = A.size();
    int cols = A[0].size();
    std::vector<std::vector<double>> result(cols, std::vector<double>(rows));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[j][i] = A[i][j];
        }
    }
    return result;
}


std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> householderQR(std::vector<std::vector<double>> A) {
    int m = A.size();
    int n = A[0].size();
    std::vector<std::vector<double>> Q(m, std::vector<double>(m, 0.0));
    for (int i = 0; i < m; ++i) Q[i][i] = 1.0;
    std::vector<std::vector<double>> R = A;

    for (int k = 0; k < std::min(m - 1, n); ++k) {
        std::vector<double> x(m - k);
        for (int i = k; i < m; ++i) x[i - k] = R[i][k];
        double alpha = -std::copysign(std::sqrt(std::inner_product(x.begin(), x.end(), x.begin(), 0.0)), x[0]);
        std::vector<double> v = x;
        v[0] -= alpha;
        double vNorm = std::sqrt(std::inner_product(v.begin(), v.end(), v.begin(), 0.0));
         if (vNorm < 1e-10) continue; // Skip if v is close to zero
        for (double& vi : v) vi /= vNorm;

        for (int j = 0; j < n; ++j) {
            double beta = -2.0 * std::inner_product(v.begin(), v.end(), R.begin() + k, 0.0, std::plus<double>(),
                [&](double vi, const std::vector<double>& Rrow) { return vi * Rrow[j]; });
            for (int i = k; i < m; ++i) R[i][j] += beta * v[i - k];
        }
        for (int j = 0; j < m; ++j) {
            double beta = -2.0 * std::inner_product(v.begin(), v.end(), Q.begin() + k, 0.0, std::plus<double>(),
                [&](double vi, const std::vector<double>& Qrow) { return vi * Qrow[j]; });
            for (int i = k; i < m; ++i) Q[i][j] += beta * v[i - k];
        }

    }
    return {transpose(Q),R};
}



double computeConditionNumber(const std::vector<std::vector<double>>& A) {
    int n = A.size();
    auto [Q, R] = householderQR(A);
    std::vector<std::vector<double>> Ainv(n, std::vector<double>(n, 0.0));

    for(int i=0; i<n; ++i){
        std::vector<double> b(n,0.0);
        b[i] = 1.0;
        std::vector<double> x(n, 0.0);
        for (int j = n - 1; j >= 0; --j) {
            x[j] = b[j];
            for (int k = j + 1; k < n; ++k) {
                x[j] -= R[j][k] * x[k];
            }
            x[j] /= R[j][j];
        }

        for(int j=0; j<n; ++j){
            double sum = 0.0;
            for(int k=0; k<n; ++k) sum += Q[j][k]*x[k];
            Ainv[j][i] = sum;
        }
    }



    return matrix2Norm(A) * matrix2Norm(Ainv);
}


int main() {
    std::vector<double> x = {0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0};
    std::vector<double> y = {2.9, 2.7, 4.8, 5.3, 7.1, 7.6, 7.7, 7.6, 9.4, 9.0, 9.6, 10.0, 10.2, 9.7, 8.3, 8.4, 9.0, 8.3, 6.6, 6.7, 4.1};
    int n = 2;
    int N = 21;


    std::vector<std::vector<double>> G(n + 1, std::vector<double>(n + 1, 0));
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            for (int k = 0; k < N; ++k) {
                G[i][j] += std::pow(x[k], i + j);
            }
        }
    }

    double condG = computeConditionNumber(G);

    std::vector<std::vector<double>> A(N, std::vector<double>(n + 1));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= n; ++j) {
            A[i][j] = std::pow(x[i], j);
        }
    }
    auto [Q, R] = householderQR(A);

    std::vector<std::vector<double>> R1(n + 1, std::vector<double>(n + 1));
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            R1[i][j] = R[i][j];
        }
    }
    double condR = computeConditionNumber(R1);

    std::cout << std::fixed;
    std::cout.precision(10);
    std::cout << "cond(G) = " << condG << std::endl;
    std::cout << "cond(R) = " << condR << std::endl;

    return 0;
}