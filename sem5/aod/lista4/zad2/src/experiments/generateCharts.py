from pathlib import Path
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

ROOT = Path(__file__).resolve().parents[2]
OUTPUT = ROOT / "output"
CHARTS = OUTPUT / "charts"

CHARTS.mkdir(parents=True, exist_ok=True)
DATA_FILE = OUTPUT / "results.csv"

df = pd.read_csv(DATA_FILE)

agg = (
	df.groupby(["k", "i"])
		.agg(
			mean_time=("time_us", "mean"),
			mean_mm=("mm", "mean")
		)
		.reset_index()
)

for k in sorted(agg["k"].unique()):
    sub = agg[agg["k"] == k].sort_values("i")

    plt.figure()
    plt.plot(
        sub["i"],
        sub["mean_mm"],
        marker="o",
        linestyle="-"
    )

    plt.title(f"Średni wynik (mm) w zależności od i dla k = {k}")
    plt.xlabel("i")
    plt.ylabel("średni wynik (mm)")
    plt.grid(True)

    plt.savefig(CHARTS / f"mm_k_{k}.png", dpi=200, bbox_inches="tight")
    plt.close()

diag = agg[agg["i"] == agg["k"]].sort_values("k")

fig, ax1 = plt.subplots()

color_time = "tab:blue"
color_mm = "tab:orange"

ax1.set_xlabel("k")
ax1.set_ylabel("średni czas [µs]", color=color_time)
ax1.plot(
    diag["k"],
    diag["mean_time"],
    marker="o",
    linestyle="-",
    color=color_time,
    label="czas"
)
ax1.tick_params(axis="y", labelcolor=color_time)
ax1.grid(True)

ax2 = ax1.twinx()
ax2.set_ylabel("średni wynik (mm)", color=color_mm)
ax2.plot(
    diag["k"],
    diag["mean_mm"],
    marker="s",
    linestyle="--",
    color=color_mm,
    label="wynik (mm)"
)
ax2.tick_params(axis="y", labelcolor=color_mm)

plt.title("Czas i wynik w zależności od k (i = k)")

fig.tight_layout()
plt.savefig(CHARTS / "time_and_mm_vs_k_i_eq_k.png", dpi=200, bbox_inches="tight")
plt.close()

time_pivot = agg.pivot(index="k", columns="i", values="mean_time")
mm_pivot = agg.pivot(index="k", columns="i", values="mean_mm")

plt.figure(figsize=(8, 6))
sns.heatmap(
	time_pivot,
	annot=True,
	fmt=".0f",
	cmap="viridis",
	annot_kws={"size": 8, "ha": "center", "va": "center"},
	cbar_kws={"label": "średni czas [µs]"}
)
plt.title("Heatmapa średniego czasu")
plt.xlabel("i")
plt.ylabel("k")
plt.tight_layout()
plt.savefig(CHARTS / "heatmap_time.png", dpi=200)
plt.close()

plt.figure(figsize=(8, 6))
sns.heatmap(
	mm_pivot,
	annot=True,
	fmt=".2f",
	cmap="viridis",
	annot_kws={"size": 8, "ha": "center", "va": "center"},
	cbar_kws={"label": "średni wynik (mm)"}
)
plt.title("Heatmapa średniego wyniku (mm)")
plt.xlabel("i")
plt.ylabel("k")
plt.tight_layout()
plt.savefig(CHARTS / "heatmap_mm.png", dpi=200)
plt.close()

print("Wykresy zapisane w output/charts/")