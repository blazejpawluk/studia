import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("../data/wyniki3.txt")
if data.ndim == 1:
	data = data[np.newaxis, :]

hilbertFilter = data[:, 0] == 0
hilbertData = data[hilbertFilter]
n = hilbertData[:, 1]
e1 = hilbertData[:, 2]
e2 = hilbertData[:, 3]

fig, ax = plt.subplots(figsize=(10,6))
ax.plot(n, e1, marker='o', markersize='3', label=r"$A\backslash  b$")
ax.plot(n, e2, marker='o', markersize='3', label=r"$A^{-1}b$")

ax.set_xlabel(r"$n$")
ax.set_ylabel(r"$x$")
ax.legend()

plt.savefig("images/zadanie3H.png")

randomFilter = data[:, 0] == 1
randomData = data[randomFilter]
n = randomData[:, 1]
e1 = randomData[:, 2]
e2 = randomData[:, 3]

fig, ax = plt.subplots(figsize=(10,6))
ax.plot(n[randomData[:, 4] == 0], e1[randomData[:, 4] == 0], marker='o', markersize='3', label=r"$A\backslash  b$")
ax.plot(n[randomData[:, 4] == 0], e2[randomData[:, 4] == 0], marker='o', markersize='3', label=r"$A^{-1}b$")

ax.set_xlabel(r"$n$")
ax.set_ylabel(r"$x$")
ax.legend()

plt.savefig("images/zadanie3R0.png")

fig, ax = plt.subplots(figsize=(10,6))
ax.plot(n[randomData[:, 4] == 1], e1[randomData[:, 4] == 1], marker='o', markersize='3', label=r"$A\backslash  b$")
ax.plot(n[randomData[:, 4] == 1], e2[randomData[:, 4] == 1], marker='o', markersize='3', label=r"$A^{-1}b$")

ax.set_xlabel(r"$n$")
ax.set_ylabel(r"$x$")
ax.legend()

plt.savefig("images/zadanie3R1.png")

fig, ax = plt.subplots(figsize=(10,6))
ax.plot(n[randomData[:, 4] == 3], e1[randomData[:, 4] == 3], marker='o', markersize='3', label=r"$A\backslash  b$")
ax.plot(n[randomData[:, 4] == 3], e2[randomData[:, 4] == 3], marker='o', markersize='3', label=r"$A^{-1}b$")

ax.set_xlabel(r"$n$")
ax.set_ylabel(r"$x$")
ax.legend()

plt.savefig("images/zadanie3R3.png")

fig, ax = plt.subplots(figsize=(10,6))
ax.plot(n[randomData[:, 4] == 7], e1[randomData[:, 4] == 7], marker='o', markersize='3', label=r"$A\backslash  b$")
ax.plot(n[randomData[:, 4] == 7], e2[randomData[:, 4] == 7], marker='o', markersize='3', label=r"$A^{-1}b$")

ax.set_xlabel(r"$n$")
ax.set_ylabel(r"$x$")
ax.legend()

plt.savefig("images/zadanie3R7.png")

fig, ax = plt.subplots(figsize=(10,6))
ax.plot(n[randomData[:, 4] == 12], e1[randomData[:, 4] == 12], marker='o', markersize='3', label=r"$A\backslash  b$")
ax.plot(n[randomData[:, 4] == 12], e2[randomData[:, 4] == 12], marker='o', markersize='3', label=r"$A^{-1}b$")

ax.set_xlabel(r"$n$")
ax.set_ylabel(r"$x$")
ax.legend()

plt.savefig("images/zadanie3R12.png")

fig, ax = plt.subplots(figsize=(10,6))
ax.plot(n[randomData[:, 4] == 16], e1[randomData[:, 4] == 16], marker='o', markersize='3', label=r"$A\backslash  b$")
ax.plot(n[randomData[:, 4] == 16], e2[randomData[:, 4] == 16], marker='o', markersize='3', label=r"$A^{-1}b$")

ax.set_xlabel(r"$n$")
ax.set_ylabel(r"$x$")
ax.legend()

plt.savefig("images/zadanie3R16.png")

fig, ax = plt.subplots(figsize=(10,6))
ax.semilogy(n[randomData[:, 4] == 0], e1[randomData[:, 4] == 0], marker='o', markersize='3', label=r"$c=0$")
ax.semilogy(n[randomData[:, 4] == 1], e1[randomData[:, 4] == 1], marker='o', markersize='3', label=r"$c=1$")
ax.semilogy(n[randomData[:, 4] == 3], e1[randomData[:, 4] == 3], marker='o', markersize='3', label=r"$c=3$")
ax.semilogy(n[randomData[:, 4] == 7], e1[randomData[:, 4] == 7], marker='o', markersize='3', label=r"$c=7$")
ax.semilogy(n[randomData[:, 4] == 12], e1[randomData[:, 4] == 12], marker='o', markersize='3', label=r"$c=12$")
ax.semilogy(n[randomData[:, 4] == 16], e1[randomData[:, 4] == 16], marker='o', markersize='3', label=r"$c=16$")

ax.set_xlabel(r"$n$")
ax.set_ylabel(r"$x$")
ax.legend()

plt.savefig("images/zadanie3Rall.png")