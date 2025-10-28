import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("../data/wyniki5.txt")
if data.ndim == 1:
	data = data[np.newaxis, :]

i = data[:, 0]
pi1 = data[:, 1]
pi2 = data[:, 2]
pi32 = data[:, 3]
pi64 = data[:, 4]

fig, ax = plt.subplots(figsize=(10,6))
ax.plot(i, pi1, marker='none', label=r"$p_n$ (Float64, bez zaokrąglania)")
ax.plot(i, pi2, marker='none', label=r"$p_n$ (Float64, zaokrąglenie dla $n=10$)")

ax.set_xlabel(r"$n$")
ax.set_ylabel(r"$p_n$")
ax.legend()

plt.savefig("images/zadanie5-1.png")

fig, ax = plt.subplots(figsize=(10,6))
ax.plot(i, pi32, marker='none', label=r"$p_n$ (Float32)")
ax.plot(i, pi64, marker='none', label=r"$p_n$ (Float64)")

ax.set_xlabel(r"$n$")
ax.set_ylabel(r"$p_n$")
ax.legend()

plt.savefig("images/zadanie5-2.png")