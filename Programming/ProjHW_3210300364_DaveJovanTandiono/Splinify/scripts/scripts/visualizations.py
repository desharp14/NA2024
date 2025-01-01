import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import os
import numpy as np

def save_results_to_file(x, y, z=None, file_name="Exercise_E_Spline_Results.txt"):
    """
    将计算的结果保存到文件中。

    :param x: X 数据
    :param y: Y 数据
    :param z: Z 数据（可选）
    :param file_name: 保存的文件名
    """
    with open(file_name, 'w') as f:
        f.write("X,Y,Z\n")  
        for i in range(len(x)):
            if z is not None:
                f.write(f"{x[i]},{y[i]},{z[i]}\n")  
            else:
                f.write(f"{x[i]},{y[i]}\n")  # 
    print(f"结果已保存到 {file_name}")


def plot_spline(file_name, title, output_image, delimiter=None):
    """
    读取插值数据文件并绘制样条插值曲线。

    :param file_name: 输入的插值数据文件路径
    :param title: 图像标题
    :param output_image: 输出图像文件路径
    :param delimiter: 数据分隔符，默认使用空白分隔，可设置为 ',' 等。
    """
    x, y = [], []
    try:
        with open(file_name, 'r') as f:
            first_line = f.readline().strip()
            if "x" in first_line.lower() and "y" in first_line.lower():
                pass  
            else:
                f.seek(0)

            for line in f:
                if line.strip():  
                    if delimiter:
                        xi, yi = map(float, line.strip().split(delimiter))
                    else:
                        xi, yi = map(float, line.strip().split())
                    x.append(xi)
                    y.append(yi)
    except FileNotFoundError:
        print(f"文件 {file_name} 未找到，请确认路径是否正确。")
        return
    except Exception as e:
        print(f"读取文件 {file_name} 时发生错误：{e}")
        return

    plt.figure(figsize=(8, 6))
    plt.plot(x, y, label="Spline Interpolation", color="blue", linewidth=2)
    plt.scatter(x, y, color="red", label="Control Points")  # 控制点
    plt.title(title)
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.grid(True)
    plt.legend()

    os.makedirs(os.path.dirname(output_image), exist_ok=True)
    plt.savefig(output_image)
    print(f"图像已保存为 {output_image}")


def plot_heart_shape(output_image):
    """
    绘制心形曲线。
    """
    t = np.linspace(0, 2 * np.pi, 1000)

    x = 16 * np.sin(t)**3
    y = 13 * np.cos(t) - 5 * np.cos(2*t) - 2 * np.cos(3*t) - np.cos(4*t)

    save_results_to_file(x, y, file_name="Heart_Shape_Results.txt")  # 保存心形曲线数据

    plt.figure(figsize=(8, 6))
    plt.plot(x, y, label="Heart Shape", color="red")
    plt.title("Heart Shape Curve")
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.grid(True)
    plt.legend()

    os.makedirs(os.path.dirname(output_image), exist_ok=True)
    plt.savefig(output_image)
    print(f"图像已保存为 {output_image}")




if __name__ == "__main__":
    data_dir = "../build/data"  
    figures_dir = "../figures"  

    plot_spline(
        file_name=os.path.join(data_dir, "Natural_Boundary_Test_CubicSpline.txt"),
        title="Natural Boundary Spline (CubicSpline)",
        output_image=os.path.join(figures_dir, "natural_boundary_cubic_spline.png")
    )
    plot_spline(
        file_name=os.path.join(data_dir, "Periodic_Boundary_Test_CubicSpline.txt"),
        title="Periodic Boundary Spline (CubicSpline)",
        output_image=os.path.join(figures_dir, "periodic_boundary_cubic_spline.png")
    )
    plot_spline(
        file_name=os.path.join(data_dir, "Clamped_Boundary_Test_CubicSpline.txt"),
        title="Clamped Boundary Spline (CubicSpline)",
        output_image=os.path.join(figures_dir, "clamped_boundary_cubic_spline.png")
    )
    plot_spline(
        file_name=os.path.join(data_dir, "Natural_Boundary_Test_BSpline.txt"),
        title="Natural Boundary Spline (BSpline)",
        output_image=os.path.join(figures_dir, "natural_boundary_bspline.png")
    )
    plot_spline(
        file_name=os.path.join(data_dir, "Periodic_Boundary_Test_BSpline.txt"),
        title="Periodic Boundary Spline (BSpline)",
        output_image=os.path.join(figures_dir, "periodic_boundary_bspline.png")
    )
    plot_spline(
        file_name=os.path.join(data_dir, "Clamped_Boundary_Test_BSpline.txt"),
        title="Clamped Boundary Spline (BSpline)",
        output_image=os.path.join(figures_dir, "clamped_boundary_bspline.png")
    )
    plot_spline(
        file_name=os.path.join(data_dir, "Exercise_A_Test.txt"),
        title="Exercise A Spline",
        output_image=os.path.join(figures_dir, "exercise_a_spline.png"),
        delimiter=','
    )
    plot_spline(
        file_name=os.path.join(data_dir, "Piecewise_Polynomial_Spline.txt"),
        title="Piecewise Polynomial Spline",
        output_image=os.path.join(figures_dir, "piecewise_polynomial_spline.png")
    )

    plot_heart_shape(output_image=os.path.join(figures_dir, "heart_shape_curve.png"))
