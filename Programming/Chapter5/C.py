import numpy as np

def hilbert_matrix(n):
    """
    Create a Hilbert matrix of size n x n.
    Each element H[i, j] = 1 / (i + j + 1).
    """
    return np.array([[1.0 / (i + j + 1) for j in range(n)] for i in range(n)])

def compute_rhs_vectors(n):
    """
    Compute the right-hand side vectors b1 and b2 for the normal equations.
    b1 corresponds to (-1)^j, and b2 accumulates the alternating harmonic series.
    """
    b1 = np.array([(-1) ** j for j in range(n)])
    b2 = np.zeros(n)
    for i in range(1, n + 1):
        b2[i - 1] = sum((-1) ** (j + i) / j for j in range(1, i + 1))
    return b1, b2

def tikhonov_regularization(H, b, alpha=1e-10):
    """
    Solve the system Hx = b using Tikhonov regularization with parameter alpha.
    """
    reg_matrix = alpha * np.eye(H.shape[0]) + H.T @ H
    reg_rhs = H.T @ b
    return np.linalg.solve(reg_matrix, reg_rhs)

def solve_and_analyze(n):
    """
    Solve the system for given n using rational and floating-point arithmetic.
    Compute beta, gamma, and alpha vectors, and analyze convergence properties.
    """
    H = hilbert_matrix(n)
    b1, b2 = compute_rhs_vectors(n)

    # Solve for beta and gamma
    beta = np.linalg.solve(H, b1)
    gamma = np.linalg.solve(H, b2)
    print(f"n = {n}, beta =", beta)
    print(f"n = {n}, gamma =", gamma)

    # Solve for alpha with ln(2) approximated to machine precision
    b_ln2 = b1 * np.log(2) + b2
    alpha_ln2 = np.linalg.solve(H, b_ln2)
    print(f"n = {n}, alpha (ln(2) to machine precision) =", alpha_ln2)

    # Solve for alpha with ln(2) ≈ 0.69315
    b_float = b1 * 0.69315 + b2
    alpha_float = np.linalg.solve(H, b_float)
    print(f"n = {n}, alpha (ln(2) ≈ 0.69315) =", alpha_float)

    # Analyze condition number
    cond_number = np.linalg.cond(H, 2)
    print(f"Condition number of Hilbert matrix (n={n}) =", cond_number)

    # Tikhonov regularization
    alpha_tikh = tikhonov_regularization(H, b_float)
    print(f"n = {n}, alpha (Tikhonov regularization) =", alpha_tikh)

def main():
    """
    Main function to solve and analyze for n = 1, 2, ..., 6.
    """
    for n in range(1, 7):
        solve_and_analyze(n)

if __name__ == "__main__":
    main()
