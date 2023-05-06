import csv
import matplotlib.pyplot as plt
import seaborn as sns
import ptitprince as pt
import os
import statistics as stats
from math import ceil, floor, sqrt
from plotter_definitions import *

dirname = os.path.dirname(__file__)

min_igd_plus = 1.0
max_igd_plus = 0.0
for zdt in zdts:
    for solver in solvers:
        filename = os.path.join(dirname, "igd_plus/zdt" + zdt + "_" + solver + ".txt")
        with open(filename) as csv_file:
            data = csv.reader(csv_file)
            for row in data:
                min_igd_plus = min(min_igd_plus, float(row[0]))
                max_igd_plus = max(max_igd_plus, float(row[0]))
delta_igd_plus = max_igd_plus - min_igd_plus
min_igd_plus = max(min_igd_plus - round(0.025 * delta_igd_plus), 0.00)
max_igd_plus = min(max_igd_plus + round(0.025 * delta_igd_plus), 1.00)

for zdt in zdts:
    plt.figure(figsize = (11, 11))
    plt.title(zdt, fontsize = "xx-large")
    plt.xlabel("Modified Inverted Generational Distance", fontsize = "x-large")
    xs = []
    for solver in solvers:
        filename = os.path.join(dirname, "igd_plus/zdt" + zdt + "_" + solver + ".txt")
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
    filename = os.path.join(dirname, "igd_plus/zdt" + zdt + ".png")
    plt.savefig(filename, format = "png")
    plt.close()

igd_plus = []

for solver in solvers:
    igd_plus.append([])

for zdt in zdts:
    for i in range(len(solvers)):
        for seed in seeds:
            filename = os.path.join(dirname, "igd_plus/zdt" + zdt + "_" + solvers[i] + "_" + str(seed) + ".txt")
            if os.path.exists(filename):
                with open(filename) as csv_file:
                    data = csv.reader(csv_file, delimiter = ",")
                    for row in data:
                        igd_plus[i].append(float(row[0]))
                    csv_file.close()

plt.figure(figsize = (11, 11))
plt.title("Multi-Objective Travelling Salesman Problem", fontsize = "xx-large")
plt.xlabel("Modified Inverted Generational Distance", fontsize = "x-large")
pt.half_violinplot(data = igd_plus, palette = colors, orient = "h", width = 0.6, cut = 0.0, inner = None)
sns.stripplot(data = igd_plus, palette = colors, orient = "h", size = 2, zorder = 0)
sns.boxplot(data = igd_plus, orient = "h", width = 0.20, color = "black", zorder = 10, showcaps = True, boxprops = {'facecolor' : 'none', "zorder" : 10}, showfliers = True, whiskerprops = {'linewidth' : 2, "zorder" : 10}, flierprops = {'markersize' : 2})
plt.yticks(ticks = list(range(len(solvers))), labels = [solver_labels[solver] for solver in solvers], fontsize = "large")
filename = os.path.join(dirname, "igd_plus/igd_plus.png")
plt.savefig(filename, format = "png")
plt.close()
