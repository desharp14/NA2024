import numpy as np
import matplotlib.pyplot as plt

# Define the original Runge function for comparison
def f(x):
    return 1 / (1 + 25 * x**2)

# Generate x values and plot the original function
x = np.linspace(-1, 1, 400)
y = f(x)
plt.plot(x, y, 'k--', label=r'$f(x) = \frac{1}{1 + 25x^2}$')

# Load and plot Chebyshev-interpolated data for different n values
for n in [5, 10, 15, 20]:
    data = np.loadtxt(f"C_data_n{n}.txt")
    x_data, y_data = data[:, 0], data[:, 1]
    plt.plot(x_data, y_data, label=f"Chebyshev Interpolation (n={n})")

# Configure plot aesthetics and display
plt.xlabel("x")
plt.ylabel("f(x) and Interpolated Values")
plt.legend()
plt.title("Chebyshev Interpolation of Runge Function")
plt.grid(True)
plt.show()
