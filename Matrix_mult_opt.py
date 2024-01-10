import numpy as np
import time

def matrix_multiplication(n):
    # Generating two n x n matrices with arbitrary values
    matrix1 = np.array([[i + j for j in range(n)] for i in range(n)])
    matrix2 = np.array([[i - j for j in range(n)] for i in range(n)])

    print("started...")

    start_time = time.time()

    # Using NumPy's dot function for matrix multiplication
    result_matrix = np.dot(matrix1, matrix2)

    end_time = time.time()

    return result_matrix, end_time - start_time

n = 2032

_, execution_time = matrix_multiplication(n)

with open('C:/Users/houba/C - Project/execution_time_p_opt.txt', 'w') as file:
    file.write(f"Execution Time for {n}x{n} Matrix Multiplication: {execution_time} seconds")

print(f"Execution Time: {execution_time} seconds")
