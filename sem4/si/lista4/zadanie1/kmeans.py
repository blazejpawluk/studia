import os
import numpy as np
import matplotlib.pyplot as plt

# tylko do pobrania datasetu
from sklearn.datasets import fetch_openml
from sklearn.model_selection import train_test_split

# ładowanie danych i normalizacja
def load_data(n_samples=5000, random_state=42):
    X, y = fetch_openml('mnist_784', version=1, return_X_y=True, as_frame=False)
    X = X.astype(np.float32) / 255.0
    y = y.astype(int)
    return train_test_split(X, y, train_size=n_samples, stratify=y, random_state=random_state)

# inicjalizacja centroidów (wybor losowych)
def initialize_centroids(X, c, random_state):
    rng = np.random.RandomState(random_state)
    n_samples = X.shape[0]
    indices = rng.choice(n_samples, size=c, replace=False)
    centroids = X[indices].copy()
    return centroids

# główny algorytm
def kmeans(X, c, max_iter=100, tol=1e-4, random_state=None):
    centroids = initialize_centroids(X, c, random_state)

    for it in range(max_iter):
        # odległość każdego punktu od każdego centroidu (wymiar: |X|*c)
        distances = np.linalg.norm(X[:, None] - centroids[None, :], axis=2)

        # przypisanie każdemu punktowi etykiety najbliższego centroidu
        labels = np.argmin(distances, axis=1)

        # aktualizacja centroidów - średnia punktów przypisanych do klastra (lub bez zmian jeśli pusty)
        new_centroids = np.array([
            X[labels==i].mean(axis=0) 
            if np.any(labels==i) 
            else centroids[i]

            for i in range(c)
        ])

        shift = np.linalg.norm(new_centroids - centroids, axis=1).sum()
        centroids = new_centroids

        if shift < tol:
            break

    inertia = np.sum((X - centroids[labels])**2)

    return centroids, labels, inertia

# wyświetlenie macierzy przydziału
def plot_assignment_matrix(labels, true_labels, c, out_dir):
    mat = np.zeros((c, 10), dtype=int)

    for i in range(c):
        counts = np.bincount(true_labels[labels==i], minlength=10)
        mat[i] = counts

    mat_perc = (mat.T / mat.sum(axis=1)).T * 100

    plt.figure(figsize=(8,6))
    plt.imshow(mat_perc, interpolation='nearest', cmap='viridis')
    plt.colorbar(label='[%]')
    plt.xlabel('Etykieta')
    plt.ylabel('Klaster')
    plt.title(f'Przydział % cyfr do {c} klastrów')
    plt.xticks(range(10))
    plt.yticks(range(c))
    plt.tight_layout()
    plt.savefig(os.path.join(out_dir, f'assignment_{c}.png'))
    plt.close()

# wyświetlanie centroidów
def plot_centroids(centroids, c, out_dir):
    n_cols = 5
    n_rows = int(np.ceil(c / n_cols))

    plt.figure(figsize=(n_cols*2, n_rows*2))

    for i, centroid in enumerate(centroids):
        ax = plt.subplot(n_rows, n_cols, i+1)
        ax.imshow(centroid.reshape(28,28), cmap='gray')
        ax.axis('off')
        ax.set_title(f'Cluster {i}')

    plt.suptitle(f'Centroidy dla {c} klastrów')
    plt.tight_layout()
    plt.savefig(os.path.join(out_dir, f'centroids_{c}.png'))
    plt.close()

# główna pętla programu
def run_experiments(X, y, clusters=[10,15,20,30], reps=5, out_dir='results'):
    os.makedirs(out_dir, exist_ok=True) # folder na wyniki

    for c in clusters:
        best = None

        # wykonujemy reps powtórzeń, wybieramy z nich najmniejszą inercję
        for init in range(reps):
            # algorytm z różnymi ziarnami
            centroids, labels, inertia = kmeans(X, c, max_iter=100, random_state=init)
            if best is None or inertia < best['inertia']:
                best = {'centroids': centroids, 'labels': labels, 'inertia': inertia, 'init': init}

        print(f'-> ilość klastrów = {c}: najlepsza inercja = {best["inertia"]:.2f} (init = {best["init"]})')

        # macierz przydziału
        plot_assignment_matrix(best['labels'], y, c, out_dir)
        print('(Zapisano macierz przydziału)')

        # wyświetlanie centroidow
        plot_centroids(best['centroids'], c, out_dir)
        print('(Zapisano grafikę z centroidami)')

if __name__ == '__main__':
    print('Ładowanie danych...')
    X_train, X_test, y_train, y_test = load_data()
    print('Dane załadowane.\n')

    print('Uruchomienie algorytmu.')
    run_experiments(X_train, y_train)
    print('Algorytm zakończony, wyniki w results.')