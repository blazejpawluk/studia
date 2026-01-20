import os
import pandas as pd
import matplotlib.pyplot as plt

DATA_PATH = os.path.join("../output", "raw-data.txt")

cols = ["k", "alg", "time_ms", "flow"]

df = pd.read_csv(DATA_PATH, sep=r"\s+", names=cols, header=None)

summary = df.groupby(["k", "alg"]).mean().reset_index()

def plot_two_series(x, y, title, ylabel, filename):
	plt.figure()
	for alg in ["EK", "DINIC"]:
		sub = summary[summary["alg"] == alg]
		plt.plot(sub[x], sub[y], marker="o", label=alg)
	plt.title(title)
	plt.xlabel(x)
	plt.ylabel(ylabel)
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig(os.path.join("../output", filename))
	plt.close()

plot_two_series(
	x="k",
	y="time_ms",
	title="Średni czas wykonania (k)",
	ylabel="czas [ms]",
	filename="avg_time_vs_k.png"
)

plot_two_series(
	x="k",
	y="flow",
	title="Średni przepływ (k)",
	ylabel="średni przepływ",
	filename="avg_flow_vs_k.png"
)

plt.figure()
dinic = summary[summary["alg"] == "DINIC"]
plt.plot(dinic["k"], dinic["time_ms"], marker="o")
plt.title("Średni czas wykonania algorytmu Dinica (k)")
plt.xlabel("k")
plt.ylabel("czas [ms]")
plt.grid(True)
plt.tight_layout()
plt.savefig(os.path.join("../output", "avg_time_dinic_vs_k.png"))
plt.close()

print("Wykresy zapisane w katalogu output:")
print("- avg_time_vs_k.png")
print("- avg_flow_vs_k.png")
print("- avg_time_dinic_vs_k.png")