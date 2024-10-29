import numpy as np
import matplotlib.pyplot as plt

# Define the original function to compare with interpolations
def f(x):
    return 1 / (1 + x**2)

# Generate x values and plot the original function
x = np.linspace(-5, 5, 1000)
y = f(x)
plt.plot(x, y, 'k--', label="y = 1 / (1 + x^2)")

# Load and plot interpolated data for each n value
for n in [2, 4, 6, 8]:
    data = np.loadtxt(f"interpolation_n{n}.txt")
    x_data, y_data = data[:, 0], data[:, 1]
    plt.plot(x_data, y_data, label=f"n={n}")

# Label the plot and display
plt.xlabel("x")
plt.ylabel("y")
plt.legend()
plt.title("Runge's Function and Polynomial Interpolations")
plt.grid(True)
plt.show()
