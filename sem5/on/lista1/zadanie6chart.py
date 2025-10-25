import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("wyniki6.txt")
if data.ndim == 1:
	data = data[np.newaxis, :]

n = data[:, 0]
f = data[:, 1]
g = data[:, 2]

fig, ax = plt.subplots(figsize=(10,6))
ax.semilogy(n, np.abs(g), marker='o', linestyle='-', markersize=3, label=r"$g(x)=\dfrac{x^2}{\sqrt{x^2+1}+1}$")
ax.semilogy(n, np.abs(f), marker='o', linestyle='-', markersize=3, label=r"$f(x)=\sqrt{x^2+1}+1$")

ax.set_xlabel(r"$n$ (dla $x=8^{-n}$)")
ax.set_ylabel("wartość funkcji")
ax.set_title(r"Porównanie $f(x)$ i $g(x)$ dla $x=8^{-n}$")
ax.legend(loc='best')

plt.tight_layout()
plt.savefig("zadanie6chart.png")