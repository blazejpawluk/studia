import os
import numpy as np
import matplotlib.pyplot as plt

# tylko do pobrania datasetu
from sklearn.datasets import fetch_openml
from sklearn.model_selection import train_test_split

def load_mnist(n_samples=5000, random_state=42):
    X, y = fetch_openml('mnist_784', version=1, return_X_y=True, as_frame=False)
    X = X.astype(np.float32) / 255.0
    y = y.astype(int)
    return train_test_split(X, y, train_size=n_samples, stratify=y, random_state=random_state)

def initialize_centroids(X, k, random_state):
    rng = np.random.RandomState(random_state)
    n_samples, _ = X.shape
    centroids = np.empty((k, X.shape[1]), dtype=X.dtype)
    centroids[0] = X[rng.randint(n_samples)]
    dist = np.full(n_samples, np.inf)
    for i in range(1, k):
        dist = np.minimum(dist, np.sum((X - centroids[i-1])**2, axis=1))
        probs = dist / dist.sum()
        cumprobs = np.cumsum(probs)
        r = rng.rand()
        idx = np.searchsorted(cumprobs, r)
        centroids[i] = X[idx]
    return centroids

def kmeans(X, k, max_iter=100, tol=1e-4, random_state=None):
    centroids = initialize_centroids(X, k, random_state)
    for it in range(max_iter):
        dists = np.linalg.norm(X[:, None] - centroids[None, :], axis=2)
        labels = np.argmin(dists, axis=1)
        new_centroids = np.array([X[labels==i].mean(axis=0) if np.any(labels==i) else centroids[i]
                                  for i in range(k)])
        shift = np.linalg.norm(new_centroids - centroids, axis=1).sum()
        centroids = new_centroids
        if shift < tol:
            break
    inertia = np.sum((X - centroids[labels])**2)
    return centroids, labels, inertia

def plot_assignment_matrix(labels, true_labels, k, out_dir):
    mat = np.zeros((k, 10), dtype=int)
    for i in range(k):
        counts = np.bincount(true_labels[labels==i], minlength=10)
        mat[i] = counts
    mat_perc = (mat.T / mat.sum(axis=1)).T * 100
    plt.figure(figsize=(8,6))
    plt.imshow(mat_perc, interpolation='nearest', cmap='viridis')
    plt.colorbar(label='[%]')
    plt.xlabel('Cyfra prawdziwa')
    plt.ylabel('Klaster')
    plt.title(f'Przydział % cyfr do {k} klastrów')
    plt.xticks(range(10))
    plt.yticks(range(k))
    fname = os.path.join(out_dir, f'assignment_{k}.png')
    plt.savefig(fname)
    plt.close()
    print(f'[OK] Macierz przydziału zapisana: {fname}')

def plot_centroids(centroids, k, out_dir):
    n_cols = 5
    n_rows = int(np.ceil(k / n_cols))
    plt.figure(figsize=(n_cols*2, n_rows*2))
    for i, c in enumerate(centroids):
        ax = plt.subplot(n_rows, n_cols, i+1)
        ax.imshow(c.reshape(28,28), cmap='gray')
        ax.axis('off')
        ax.set_title(f'Clust {i}')
    plt.suptitle(f'Centroidy dla k={k}')
    fname = os.path.join(out_dir, f'centroids_{k}.png')
    plt.savefig(fname)
    plt.close()
    print(f'[OK] Centroidy zapisane: {fname}')

def run_experiments(X, y, ks=[10,15,20,30], n_init=5, out_dir='results'):
    os.makedirs(out_dir, exist_ok=True)
    for k in ks:
        best = None
        for init in range(n_init):
            cent, lab, inertia = kmeans(X, k, max_iter=1000, random_state=init)
            if best is None or inertia < best['inertia']:
                best = {'cent': cent, 'lab': lab, 'inertia': inertia, 'init': init}
        print(f'>>> k={k}: najlepsza inercja={best["inertia"]:.2f} (init={best["init"]})')
        plot_assignment_matrix(best['lab'], y, k, out_dir)
        plot_centroids(best['cent'], k, out_dir)

if __name__ == '__main__':
    print('1) Ładowanie danych…')
    X_train, X_test, y_train, y_test = load_mnist(20000)
    print('2) Uruchamiam k-means dla różnych k…')
    run_experiments(X_train, y_train)
    print('Gotowe! Wyniki w katalogu "results".')