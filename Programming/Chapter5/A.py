import numpy as np
import matplotlib.pyplot as plt

# Load coefficients from the file
with open("coefficients.txt", "r") as file:
    coefficients = [float(line.strip()) for line in file.readlines()]

# Define the polynomial function
def quadratic(a, x):
    return a[0] + a[1] * x + a[2] * x**2

# Data points
x = [i * 0.5 for i in range(21)]
y = [2.9, 2.7, 4.8, 5.3, 7.1, 7.6, 7.7, 7.6, 9.4, 9.0,
     9.6, 10.0, 10.2, 9.7, 8.3, 8.4, 9.0, 8.3, 6.6, 6.7, 4.1]

# Generate points for the polynomial
xx = np.linspace(0, 10, 200)
yy = quadratic(coefficients, xx)

# Plot the polynomial and data points
plt.title('Least Square Fit via Normal Equations')
plt.xlabel('x')
plt.ylabel('y')
plt.plot(xx, yy, label="Fitted Polynomial", color="blue")
plt.scatter(x, y, color="red", label="Data Points")
plt.legend()
plt.grid()

# Save and show the plot
plt.savefig("A.png")
plt.show()
