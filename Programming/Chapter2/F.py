import numpy as np
import matplotlib.pyplot as plt

# Function to plot the Bezier curve from data files
def plot_bezier_curve(m_values):
    for m in m_values:
        # Load data from file
        data = np.loadtxt(f"bezier_data_m{m}.txt")
        x, y = data[:, 0], data[:, 1]
        
        # Plot the Bezier curve
        plt.plot(x, y, label=f"m = {m}")
        plt.scatter(x, y, s=5, color='red')  # Optional: add markers for control points

    # Add labels and styling
    plt.xlabel("x")
    plt.ylabel("y")
    plt.title("Heart Shape Approximation with Bezier Curves")
    plt.axis('equal')
    plt.legend()
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    # Specify m values
    m_values = [10, 40, 160]
    plot_bezier_curve(m_values)
