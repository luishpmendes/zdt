import csv
import matplotlib.pyplot as plt
import seaborn as sns
import ptitprince as pt
import os
import statistics as stats
from math import ceil, floor, sqrt
from plotter_definitions import *

dirname = os.path.dirname(__file__)

min_multiplicative_epsilon = 1.0
max_multiplicative_epsilon = 0.0
for zdt in zdts:
    for solver in solvers:
        filename = os.path.join(dirname, "multiplicative_epsilon/zdt" + zdt + "_" + solver + ".txt")
        with open(filename) as csv_file:
            data = csv.reader(csv_file)
            for row in data:
                min_multiplicative_epsilon = min(min_multiplicative_epsilon, float(row[0]))
                max_multiplicative_epsilon = max(max_multiplicative_epsilon, float(row[0]))
delta_multiplicative_epsilon = max_multiplicative_epsilon - min_multiplicative_epsilon
min_multiplicative_epsilon = max(min_multiplicative_epsilon - round(0.025 * delta_multiplicative_epsilon), 0.00)
max_multiplicative_epsilon = min(max_multiplicative_epsilon + round(0.025 * delta_multiplicative_epsilon), 1.00)

for zdt in zdts:
    plt.figure(figsize = (11, 11))
    plt.title("zdt" + zdt, fontsize = "xx-large")
    plt.xlabel("Multiplicative Epsilon Indicator", fontsize = "x-large")
    xs = []
    for solver in solvers:
        filename = os.path.join(dirname, "multiplicative_epsilon/zdt" + zdt + "_" + solver + ".txt")
        x = []
        with open(filename) as csv_file:
            data = csv.reader(csv_file)
            for row in data:
                x.append(float(row[0]))
        xs.append(x)
    pt.half_violinplot(data = xs, palette = colors, orient = "h", width = 0.6, cut = 0.0, inner = None)
    sns.stripplot(data = xs, palette = colors, orient = "h", size = 2, zorder = 0)
    sns.boxplot(data = xs, orient = "h", width = 0.20, color = "black", zorder = 10, showcaps = True, boxprops = {'facecolor' : 'none', "zorder" : 10}, showfliers = True, whiskerprops = {'linewidth' : 2, "zorder" : 10}, flierprops = {'markersize' : 2})
    plt.yticks(ticks = list(range(len(solvers))), labels = [solver_labels[solver] for solver in solvers], fontsize = "large")
    filename = os.path.join(dirname, "multiplicative_epsilon/zdt" + zdt + ".png")
    plt.savefig(filename, format = "png")
    plt.close()

multiplicative_epsilon = []

for solver in solvers:
    multiplicative_epsilon.append([])

for zdt in zdts:
    for i in range(len(solvers)):
        for seed in seeds:
            filename = os.path.join(dirname, "multiplicative_epsilon/zdt" + zdt + "_" + solvers[i] + "_" + str(seed) + ".txt")
            if os.path.exists(filename):
                with open(filename) as csv_file:
                    data = csv.reader(csv_file, delimiter = ",")
                    for row in data:
                        multiplicative_epsilon[i].append(float(row[0]))
                    csv_file.close()

plt.figure(figsize = (11, 11))
plt.title("ZDT", fontsize = "xx-large")
plt.xlabel("Multiplicative Epsilon Indicator", fontsize = "x-large")
pt.half_violinplot(data = multiplicative_epsilon, palette = colors, orient = "h", width = 0.6, cut = 0.0, inner = None)
sns.stripplot(data = multiplicative_epsilon, palette = colors, orient = "h", size = 2, zorder = 0)
sns.boxplot(data = multiplicative_epsilon, orient = "h", width = 0.20, color = "black", zorder = 10, showcaps = True, boxprops = {'facecolor' : 'none', "zorder" : 10}, showfliers = True, whiskerprops = {'linewidth' : 2, "zorder" : 10}, flierprops = {'markersize' : 2})
plt.yticks(ticks = list(range(len(solvers))), labels = [solver_labels[solver] for solver in solvers], fontsize = "large")
filename = os.path.join(dirname, "multiplicative_epsilon/multiplicative_epsilon.png")
plt.savefig(filename, format = "png")
plt.close()
