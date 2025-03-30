import os
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.lines import Line2D

output_dir = "charts"
if not os.path.exists(output_dir):
    os.makedirs(output_dir)

files = ["insertSortTest.txt", "quickSortTest.txt", "hybridSortTest.txt"]
labels = ["InsertSort", "QuickSort", "HybridSort"]
colors = ['blue', 'orange', 'green']  # Kolory dla poszczególnych serii

k_values = [1, 10, 100]

results = {k: [] for k in k_values}

for file in files:
    data = np.loadtxt(file)
    for k in k_values:
        data_k = data[data[:, 1] == k]
        n_unique = np.unique(data_k[:, 0])
        avg_c = []
        avg_s = []
        for n_val in n_unique:
            mask = data_k[:, 0] == n_val
            avg_c.append(np.mean(data_k[mask, 2]))
            avg_s.append(np.mean(data_k[mask, 3]))
        results[k].append({
            'n': np.array(n_unique),
            'c': np.array(avg_c),
            's': np.array(avg_s)
        })

def create_chart(k, metric, ylabel, filename, filter_n=False):
    plt.figure(figsize=(8, 6))
    legend_handles = []
    for idx, res in enumerate(results[k]):
        if filter_n:
            mask = res['n'] <= 50
            n_values = res['n'][mask]
            metric_values = res[metric][mask]
        else:
            n_values = res['n']
            metric_values = res[metric]
        plt.scatter(n_values, metric_values, color=colors[idx])
        handle = Line2D([0], [0], marker='o', color='w',
                        markerfacecolor=colors[idx], markersize=8, label=labels[idx])
        legend_handles.append(handle)
    plt.title(f"Średnia liczba {ylabel} (k = {k})" + (" [n<=50]" if filter_n else ""))
    plt.xlabel("Długość tablicy (n)")
    plt.ylabel(f"Średnia liczba {ylabel}")
    plt.legend(handles=legend_handles)
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, filename))
    plt.close()

for k in k_values:
    create_chart(k, 'c', "porównań", f"porownania_k{k}_all.png", filter_n=False)
    create_chart(k, 'c', "porównań", f"porownania_k{k}_filtered.png", filter_n=True)
    create_chart(k, 's', "zamian", f"zamiany_k{k}_all.png", filter_n=False)
    create_chart(k, 's', "zamian", f"zamiany_k{k}_filtered.png", filter_n=True)
