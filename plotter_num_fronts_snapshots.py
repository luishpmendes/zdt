import csv
import matplotlib.pyplot as plt
import os
from plotter_definitions import *

dirname = os.path.dirname(__file__)

for zdt in zdts:
    for version in versions:
        plt.figure()
        plt.title("zdt" + str(zdt), fontsize = "xx-large")
        plt.xlabel("Time (s)", fontsize = "x-large")
        plt.ylabel("Non-dominated Fronts", fontsize = "x-large")
        for i in range(len(solvers)):
            filename = os.path.join(dirname, "num_fronts_snapshots/zdt" + str(zdt) + "_" + solvers[i] + "_" + version + ".txt")
            if os.path.exists(filename):
                x = []
                y = []
                with open(filename) as csv_file:
                    data = csv.reader(csv_file, delimiter = " ")
                    for row in data:
                        x.append(float(row[1]))
                        y.append(float(row[2]))
                plt.plot(x, y, label = solver_labels[solvers[i]], color = colors[i], marker = (i + 3, 2, 0), alpha = 0.80)
        plt.xlim(left = 0)
        plt.ylim(bottom = 0)
        plt.legend(loc = "best", fontsize = "large")
        filename = os.path.join(dirname, "num_fronts_snapshots/zdt" + str(zdt) + "_" + version + ".png")
        plt.savefig(filename, format = "png")
        plt.close()
