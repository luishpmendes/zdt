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
        plt.ylabel("Number of elites", fontsize = "x-large")
        for solver in solvers:
            if solver.startswith("nsbrkga"):
                filename = os.path.join(dirname, "num_elites_snapshots/zdt" + str(zdt) + "_" + solver + "_" + version + ".txt")
                if os.path.exists(filename):
                    x = []
                    y = []
                    with open(filename) as csv_file:
                        data = csv.reader(csv_file, delimiter = " ")
                        for row in data:
                            x.append(float(row[1]))
                            y.append(float(row[2]))
                    plt.plot(x, y, label = solver_labels[solver])
        plt.xlim(left = 0)
        plt.ylim(bottom = 0)
        plt.legend(loc = "best", fontsize = "large")
        filename = os.path.join(dirname, "num_elites_snapshots/zdt" + str(zdt) + "_" + version + ".png")
        plt.savefig(filename, format = "png")
        plt.close()
