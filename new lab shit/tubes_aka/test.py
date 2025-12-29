import time
import matplotlib.pyplot as plt
from prettytable import PrettyTable

# Rekursif
def factorial_recursive(n):
    if n == 0 or n == 1:
        return 1
    return n * factorial_recursive(n - 1)

# Iteratif
def factorial_iterative(n):
    result = 1
    for i in range(1, n + 1):
        result *= i
    return result

# Data
n_values = []
recursive_times = []
iterative_times = []

# Tabel
def print_table():
    table = PrettyTable()
    table.field_names = ["n", "Recursive Time (s)", "Iterative Time (s)"]
    for i in range(len(n_values)):
        table.add_row([n_values[i], recursive_times[i], iterative_times[i]])
    print(table)

# Grafik
def show_graph():
    plt.figure()
    plt.plot(n_values, recursive_times, marker='o', label='Recursive')
    plt.plot(n_values, iterative_times, marker='o', label='Iterative')
    plt.xlabel("n")
    plt.ylabel("Execution Time (seconds)")
    plt.title("Recursive vs Iterative Factorial")
    plt.legend()
    plt.grid(True)
    plt.show()

# Main
while True:
    n = int(input("Masukkan n (-1 untuk keluar): "))
    if n == -1:
        break
    if n < 0:
        print("n harus >= 0")
        continue

    n_values.append(n)

    start = time.time()
    factorial_recursive(n)
    recursive_times.append(time.time() - start)

    start = time.time()
    factorial_iterative(n)
    iterative_times.append(time.time() - start)

    print_table()
    show_graph()
