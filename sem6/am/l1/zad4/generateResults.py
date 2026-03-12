import os
import matplotlib.pyplot as plt

os.makedirs("zad4/results", exist_ok=True)

data_dir = "zad4/data"
out_dir = "zad4/results"

for fname in os.listdir(data_dir):
    if not fname.lower().endswith(".txt"):
        continue
    path = os.path.join(data_dir, fname)
    x_coords = []
    y_coords = []
    with open(path, "r") as f:
        for line in f:
            parts = line.strip().split()
            if len(parts) < 2:
                continue
            try:
                x, y = map(float, parts[:2])
            except ValueError:
                continue
            x_coords.append(x)
            y_coords.append(y)
    if not x_coords:
        continue
    x_coords.append(x_coords[0])
    y_coords.append(y_coords[0])

    plt.figure(figsize=(6, 6))
    plt.plot(x_coords, y_coords, marker='o')
    plt.scatter(x_coords, y_coords, s=20, zorder=3)
    plt.gca().set_aspect("equal", adjustable="box")
    plt.axis("off")

    out_path = os.path.join(out_dir, os.path.splitext(fname)[0] + ".png")
    plt.savefig(out_path, bbox_inches="tight", dpi=150)
    plt.close()