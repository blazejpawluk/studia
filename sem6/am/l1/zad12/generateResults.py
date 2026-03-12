import os
import matplotlib.pyplot as plt

os.makedirs("zad12/results", exist_ok=True)

for file in os.listdir("zad12/data"):
    if not file.endswith(".txt"):
        continue

    x = []
    y = []

    with open("zad12/data/" + file) as f:
        for line in f:
            a, b = map(float, line.split())
            x.append(a)
            y.append(b)

    if len(x) == 0:
        continue

    x.append(x[0])
    y.append(y[0])

    plt.figure()
    plt.plot(x, y, marker='o')

    out = "zad12/results/" + file.replace(".txt", ".png")
    plt.savefig(out)
    plt.close()