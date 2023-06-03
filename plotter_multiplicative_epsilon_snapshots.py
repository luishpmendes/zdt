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
max_time = 0.0
for zdt in zdts:
    for solver in solvers:
        for seed in seeds:
            filename = os.path.join(dirname, "multiplicative_epsilon_snapshots/zdt" + zdt + "_" + solver + "_" + str(seed) + ".txt")
            if os.path.exists(filename):
                with open(filename) as csv_file:
                    data = csv.reader(csv_file, delimiter = ",")
                    for row in data:
                        min_multiplicative_epsilon = min(min_multiplicative_epsilon, float(row[2]))
                        max_multiplicative_epsilon = max(max_multiplicative_epsilon, float(row[2]))
                        max_time = max(max_time, float(row[1]))
delta_multiplicative_epsilon = max_multiplicative_epsilon - min_multiplicative_epsilon
min_multiplicative_epsilon = max(min_multiplicative_epsilon - round(0.025 * delta_multiplicative_epsilon), 0.00)
max_multiplicative_epsilon = min(max_multiplicative_epsilon + round(0.025 * delta_multiplicative_epsilon), 1.00)

multiplicative_epsilon_per_solver = {}
time_per_solver = {}

for solver in solvers:
    multiplicative_epsilon_per_solver[solver] = []
    time_per_solver[solver] = []
    for i in range(num_snapshots + 1):
        multiplicative_epsilon_per_solver[solver].append([])
        time_per_solver[solver].append([])

multiplicative_epsilon_per_snapshot = []

for i in range(num_snapshots + 1):
    multiplicative_epsilon_per_snapshot.append([])
    for solver in solvers:
        multiplicative_epsilon_per_snapshot[i].append([])

for zdt in zdts:
    for i in range(len(solvers)):
        for seed in seeds:
            filename = os.path.join(dirname, "multiplicative_epsilon_snapshots/zdt" + zdt + "_" + solvers[i] + "_" + str(seed) + ".txt")
            if os.path.exists(filename):
                with open(filename) as csv_file:
                    data = csv.reader(csv_file, delimiter = ",")
                    j = 0
                    for row in data:
                        time_per_solver[solvers[i]][j].append(float(row[1]))
                        multiplicative_epsilon_per_solver[solvers[i]][j].append(float(row[2]))
                        multiplicative_epsilon_per_snapshot[j][i].append(float(row[2]))
                        j += 1
                    csv_file.close()

plt.figure()
plt.title("ZDT", fontsize = "xx-large")
plt.xlabel("Time (s)", fontsize = "x-large")
plt.ylabel("Multiplicative Epsilon", fontsize = "x-large")
for i in range(len(solvers)):
    x = []
    y = []
    for j in range(num_snapshots + 1):
        x.append(stats.mean(time_per_solver[solvers[i]][j]))
        y.append(stats.mean(multiplicative_epsilon_per_solver[solvers[i]][j]))
    plt.plot(x, y, label = solver_labels[solvers[i]], marker = (i + 3, 2, 0), color = colors[i], alpha = 0.80)
plt.xlim(left = 0.0, right = max_time)
plt.ylim(bottom = min_multiplicative_epsilon, top = max_multiplicative_epsilon)
plt.legend(loc = "best", fontsize = "large")
filename = os.path.join(dirname, "multiplicative_epsilon_snapshots/multiplicative_epsilon_mean_snapshots.png")
plt.savefig(filename, format = "png")
plt.close()

plt.figure()
plt.title("ZDT", fontsize = "xx-large")
plt.xlabel("Time (s)", fontsize = "x-large")
plt.ylabel("Multiplicative Epsilon", fontsize = "x-large")
for i in range(len(solvers)):
    x = []
    y0 = []
    y2 = []
    for j in range(num_snapshots + 1):
        x.append(stats.mean(time_per_solver[solvers[i]][j]))
        quantiles = stats.quantiles(multiplicative_epsilon_per_solver[solvers[i]][j])
        y0.append(quantiles[0])
        y2.append(quantiles[2])
    plt.fill_between(x, y0, y2, color = colors[i], alpha = 0.25)
for i in range(len(solvers)):
    x = []
    y1 = []
    for j in range(num_snapshots + 1):
        x.append(stats.mean(time_per_solver[solvers[i]][j]))
        quantiles = stats.quantiles(multiplicative_epsilon_per_solver[solvers[i]][j])
        y1.append(quantiles[1])
    plt.plot(x, y1, label = solver_labels[solvers[i]], marker = (i + 3, 2, 0), color = colors[i], alpha = 0.75)
plt.xlim(left = 0.0, right = max_time)
plt.ylim(bottom = min_multiplicative_epsilon, top = max_multiplicative_epsilon)
plt.legend(loc = "best", fontsize = "large")
filename = os.path.join(dirname, "multiplicative_epsilon_snapshots/multiplicative_epsilon_quartiles_snapshots.png")
plt.savefig(filename, format = "png")
plt.close()

for snapshot in range(num_snapshots + 1):
    plt.figure(figsize = (11, 11))
    plt.title("ZDT", fontsize = "xx-large")
    plt.xlabel("Multiplicative Epsilon", fontsize = "x-large")
    pt.half_violinplot(data = multiplicative_epsilon_per_snapshot[snapshot], palette = colors, orient = "h", width = 0.6, cut = 0.0, inner = None)
    sns.stripplot(data = multiplicative_epsilon_per_snapshot[snapshot], palette = colors, orient = "h", size = 2, zorder = 0)
    sns.boxplot(data = multiplicative_epsilon_per_snapshot[snapshot], orient = "h", width = 0.20, color = "black", zorder = 10, showcaps = True, boxprops = {'facecolor' : 'none', "zorder" : 10}, showfliers = True, whiskerprops = {'linewidth' : 2, "zorder" : 10}, flierprops = {'markersize' : 2})
    plt.xlim(left = 0.0, right = 1.0)
    plt.xticks(ticks = [0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0], fontsize = "large")
    plt.yticks(ticks = list(range(len(solvers))), labels = [solver_labels[solver] for solver in solvers], fontsize = "large")
    filename = os.path.join(dirname, "multiplicative_epsilon_snapshots/snapshot_" + str(snapshot) + ".png")
    plt.savefig(filename, format = "png")
    plt.close()
