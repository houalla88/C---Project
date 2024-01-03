import time

def matrix_multiplication(n):
    # Generating two n x n matrices with arbitrary values
    matrix1 = [[i + j for j in range(n)] for i in range(n)]
    matrix2 = [[i - j for j in range(n)] for i in range(n)]
    result_matrix = [[0 for _ in range(n)] for _ in range(n)]

    print("started...")

    start_time = time.time()
    # Matrix multiplication
    for i in range(n):
        for j in range(n):
            for k in range(n):
                result_matrix[i][j] += matrix1[i][k] * matrix2[k][j]

    end_time = time.time()

    return result_matrix, end_time - start_time

# Define the size of the matrix (n x n)
n = 2032  # Modify this value as needed

# Performing matrix multiplication
_, execution_time = matrix_multiplication(n)

# Writing the execution time to a text file
with open('C:/Users/houba/C - Project/matrix_multiplication_time.txt', 'w') as file:
    file.write(f"Execution Time for {n}x{n} Matrix Multiplication: {execution_time} seconds")

execution_time