import os
import pandas as pd
import matplotlib.pyplot as plt

DATA_PATH = os.path.join("../output", "raw-data.txt")

cols = ["k", "time_s", "a", "flow"]

df = pd.read_csv(DATA_PATH, sep=r"\s+", names=cols, header=None)

summary = df.groupby("k").mean().reset_index()

plt.figure()
plt.plot(summary["k"], summary["time_s"], marker="o")
plt.title("Średni czas wykonania (k)")
plt.xlabel("k")
plt.ylabel("czas [ms]")
plt.grid(True)
plt.tight_layout()
plt.savefig(os.path.join("../output", "avg_time_vs_k.png"))
plt.close()

plt.figure()
plt.plot(summary["k"], summary["a"], marker="o")
plt.title("Średnia liczba ścieżek powiększających (k)")
plt.xlabel("k")
plt.ylabel("średnia liczba ścieżek")
plt.grid(True)
plt.tight_layout()
plt.savefig(os.path.join("../output", "avg_paths_vs_k.png"))
plt.close()

plt.figure()
plt.plot(summary["k"], summary["flow"], marker="o")
plt.title("Średni przepływ (k)")
plt.xlabel("k")
plt.ylabel("średni przepływ")
plt.grid(True)
plt.tight_layout()
plt.savefig(os.path.join("../output", "avg_flow_vs_k.png"))
plt.close()

print("Wykresy zapisane w katalogu output:")
print("- avg_time_vs_k.png")
print("- avg_paths_vs_k.png")
print("- avg_flow_vs_k.png")