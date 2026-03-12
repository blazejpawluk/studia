import os
import matplotlib.pyplot as plt

os.makedirs("zad3/results", exist_ok=True)

data_dir = "zad3/data"
out_dir = "zad3/results"

if not os.path.isdir(data_dir):
    raise SystemExit(f"Directory '{data_dir}' does not exist")

for fname in os.listdir(data_dir):
    if not fname.lower().endswith(".txt"):
        continue
    path = os.path.join(data_dir, fname)
    edges = []
    nodes = set()
    with open(path, "r") as f:
        for line in f:
            parts = line.strip().split()
            if len(parts) < 4:
                continue
            try:
                x1, y1, x2, y2 = map(float, parts[:4])
            except ValueError:
                continue
            p1 = (x1, y1)
            p2 = (x2, y2)
            edges.append((p1, p2))
            nodes.add(p1)
            nodes.add(p2)
    if not edges:
        continue
    xs = [p[0] for p in nodes]
    ys = [p[1] for p in nodes]

    plt.figure(figsize=(6, 6))
    for (x1, y1), (x2, y2) in edges:
        plt.plot([x1, x2], [y1, y2], linewidth=1)
    plt.scatter(xs, ys, s=20, zorder=3)
    plt.gca().set_aspect("equal", adjustable="box")
    plt.axis("off")

    out_path = os.path.join(out_dir, os.path.splitext(fname)[0] + ".png")
    plt.savefig(out_path, bbox_inches="tight", dpi=150)
    plt.close()