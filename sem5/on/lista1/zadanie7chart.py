import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("wyniki7.txt")
if data.ndim == 1:
	data = data[np.newaxis, :]

n = data[:, 0]
appr = data[:, 2]
real = data[:, 3]
diff = data[:, 4]

fig, ax = plt.subplots(figsize=(10,6))
ax.plot(n, appr, marker='o', linestyle='-', markersize=3, label=r"$\tilde{f}'(x_0)$")
ax.plot(n, real, marker='none', linestyle='-', label=r"$f'(x_0)$")

ax.set_xlabel(r"$n$ (dla $h=2^{-n}$)")
ax.set_ylabel("wartości funkcji")
ax.set_title(r"Porównanie $f'(x_0)$ i $\tilde{f}'(x_0)$ dla $h=2^{-n}$")
ax.legend(loc='best')

plt.savefig("zadanie7chart-full.png")

fig, ax = plt.subplots(figsize=(10,6))
ax.plot(n, appr, marker='o', linestyle='-', markersize=3, label=r"$\tilde{f}'(x_0)$")
ax.plot(n, real, marker='none', linestyle='-', label=r"$f'(x_0)$")

ax.set_ylim(-1.988, -1.98)
ax.set_xlabel(r"$n$ (dla $h=2^{-n}$)")
ax.set_ylabel("wartości funkcji")
ax.set_title(r"Porównanie $f'(x_0)$ i $\tilde{f}'(x_0)$ dla $h=2^{-n}$")
ax.legend(loc='best')

plt.savefig("zadanie7chart.png")

fig, ax = plt.subplots(figsize=(10,6))
ax.plot(n, diff, marker='o', linestyle='-', markersize=3, label=r"$|f'(x_0)-\tilde{f}'(x_0)|$")

ax.set_ylim(0, 2)
ax.set_xlabel(r"$n$ (dla $h=2^{-n}$)")
ax.set_ylabel("błąd")
ax.set_title(r"Różnica między wyliczonym przybliżeniem, a realną wartością $f'(x_0)$")
ax.legend(loc='best')

plt.savefig("zadanie7chart-diff.png")