import os
import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import fetch_openml
from sklearn.model_selection import train_test_split
from collections import deque, Counter
import umap

# ładowanie danych i average pooling
def load_data(n_samples=5000, random_state=42, pool_size=4):
    X, y = fetch_openml('mnist_784', version=1, return_X_y=True, as_frame=False)
    X = X.astype(np.float32) / 255.0
    y = y.astype(int)

    X, _, y, _ = train_test_split(X, y, train_size=n_samples,
                                  stratify=y, random_state=random_state)
    X_raw = X.copy()

    n = X.shape[0]
    X_img = X.reshape(n, 28, 28)
    out_dim = 28 // pool_size
    X_pooled = np.zeros((n, out_dim, out_dim), dtype=np.float32)

    for i in range(out_dim):
        for j in range(out_dim):
            block = X_img[:,
                i*pool_size:(i+1)*pool_size,
                j*pool_size:(j+1)*pool_size
            ]
            X_pooled[:, i, j] = block.mean(axis=(1,2))

    X_pooled_flat = X_pooled.reshape(n, -1)

    return X_raw, X_pooled_flat, y

import warnings
warnings.filterwarnings("ignore", category=FutureWarning)
warnings.filterwarnings("ignore", message=".*n_jobs value.*")

# umap
def reduce_dim(X, n_components=10, random_state=42):
    reducer = umap.UMAP(n_components=n_components, random_state=random_state)
    return reducer.fit_transform(X)

# główny algorytm
def dbscan(X, eps, min_pts):
    n = X.shape[0]
    labels = np.full(n, -1, dtype=int) # -1 = szum
    visited = np.zeros(n, dtype=bool)
    cluster_id = 0

    # przechodzimy po wszytskich nieodwiedzonych punktach
    for i in range(n):
        if visited[i]:
            continue

        visited[i] = True
        dist_i = np.linalg.norm(X - X[i], axis=1) # wektory odległości do wszystkich punktów
        neigh = np.where(dist_i <= eps)[0] # wybieramy te, które mieszczą się w promieniu

        # jeśli za mało sąsiadów - pozostaje szumem
        if neigh.size < min_pts:
            continue

        # inaczej nowy klaster
        labels[i] = cluster_id

        queue = deque(neigh.tolist())
        while queue:
            j = queue.popleft()

            # dla każdego nieodwiedzonego sąsiada, sprawdzamy jego sąsiadów
            # jeśli ma ich wystarczająco, dodajemy ich do kolejki 
            if not visited[j]:
                visited[j] = True
                dist_j = np.linalg.norm(X - X[j], axis=1)
                neigh_j = np.where(dist_j <= eps)[0]

                if neigh_j.size >= min_pts:
                    queue.extend(neigh_j)

            # jeśli sasiad jest szumem, to dopisujemy go do obecnego klastra
            if labels[j] == -1:
                labels[j] = cluster_id

        cluster_id += 1

    return labels, cluster_id

# liczenie statystyk
def evaluate_clusters(labels, true_labels):
    n = labels.shape[0]

    percent_noise = 100 * np.sum(labels == -1) / n

    cluster_ids = [c for c in np.unique(labels) if c != -1]
    correct = 0
    total_in_clusters = 0

    for c in cluster_ids:
        mask = labels == c
        votes = Counter(true_labels[mask])
        majority_count = votes.most_common(1)[0][1]
        correct += majority_count
        total_in_clusters += mask.sum()

    percent_correct = 100 * correct / total_in_clusters if total_in_clusters else 0.0
    percent_wrong = 100 * (total_in_clusters - correct) / total_in_clusters if total_in_clusters else 0.0

    return {
        'n_clusters': len(cluster_ids),
        'percent_noise': percent_noise,
        'percent_correct': percent_correct,
        'percent_wrong': percent_wrong
    }

# rysowanie macierzy przydziału
def plot_assignment_matrix(labels, true_labels, out_dir='results'):
    cluster_ids = [c for c in np.unique(labels) if c != -1]
    k = len(cluster_ids)
    mat = np.zeros((k, 10), dtype=int)

    for idx, c in enumerate(cluster_ids):
        mat[idx] = np.bincount(true_labels[labels==c], minlength=10)

    mat_perc = (mat.T / mat.sum(axis=1)).T * 100

    plt.figure(figsize=(8, max(4, k*0.3)))
    plt.imshow(mat_perc, interpolation='nearest', cmap='viridis')
    plt.colorbar(label='[%]')
    plt.xlabel('Cyfra prawdziwa')
    plt.ylabel('Klaster (DBSCAN)')
    plt.title(f'Przydział % cyfr do {k} klastrów (bez szumu)')
    plt.xticks(range(10))
    plt.yticks(range(k), labels=[f'C{c}' for c in cluster_ids])
    os.makedirs(out_dir, exist_ok=True)
    plt.savefig(os.path.join(out_dir, 'dbscan_assignment.png'), bbox_inches='tight')
    plt.close()

# rysowanie centroidów (średniego obrazu)
def plot_cluster_centroids(labels, X_raw, out_dir='results'):
    cluster_ids = [c for c in np.unique(labels) if c != -1]
    k = len(cluster_ids)
    n_cols = 5
    n_rows = int(np.ceil(k / n_cols))

    plt.figure(figsize=(n_cols*2, n_rows*2))

    for idx, c in enumerate(cluster_ids):
        mask = labels == c
        mean_img = X_raw[mask].mean(axis=0).reshape(28,28)
        ax = plt.subplot(n_rows, n_cols, idx+1)
        ax.imshow(mean_img, cmap='gray')
        ax.axis('off')
        ax.set_title(f'C{c}')

    plt.suptitle('Centroidy (średnie obrazy) klastrów DBSCAN')
    os.makedirs(out_dir, exist_ok=True)
    plt.savefig(os.path.join(out_dir, 'dbscan_centroids.png'), bbox_inches='tight')
    plt.close()

def main():
    print('Wczytywanie danych + average pooling...')
    X_raw, X_pool, y = load_data(n_samples=20000, pool_size=4)
    print('Dane wczytane.\n')

    print('Umap...')
    X10 = reduce_dim(X_pool, n_components=10)
    print('Umap zakończony\n')

    # parametry
    eps = 0.25
    min_pts = 5

    print('DBSCAN...')
    labels, n_clusters = dbscan(X10, eps, min_pts)
    print(f'DBSCAN zakończony. Liczba klastrów: {n_clusters}')

    plot_assignment_matrix(labels, y)
    plot_cluster_centroids(labels, X_raw)
    print('(zapisano macierz przydziału oraz obraz centroidów)')

    print('Statystyki')
    stats = evaluate_clusters(labels, y)
    print(f"\tszum: {stats['percent_noise']:.2f}%")
    print(f"\tpoprawność: {stats['percent_correct']:.2f}%")
    print(f"\tbłędne klasyfikacje w klastrach: {stats['percent_wrong']:.2f}%")

if __name__ == '__main__':
    main()
