#!/usr/bin/env python

import matplotlib.pyplot as plt

algorithms = ["linear_search", "binary_search", "binary_search_tree" ,"hash_table"]

for sort in algorithms:

    data_path = "benchmarks/" + sort + ".data"
    with open(data_path, "r") as f:
        lines = f.readlines()

    del lines[0]        #Ta bort Titeln ur datat
    del lines[0]        #Ta bort kolumn-titlarna ur datat

    N_arr = []
    T_arr = []
    stdDev_arr = []

    for line in lines:
        data = line.split()
        N_arr.append(int(data[0]))
        T_arr.append(float(data[1]))
        stdDev_arr.append(float(data[2]))

    plt.clf()
    plt.errorbar(N_arr, T_arr, stdDev_arr, linestyle='None', marker='x')
    plt.ylabel("T[ms]")
    plt.xlabel("N elements")

    title = sort
    plt.title(title)

    export_path = "graphs/" + sort + ".png"
    plt.savefig(export_path)

    #plt.show()



