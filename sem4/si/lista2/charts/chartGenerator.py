import numpy as np
import matplotlib.pyplot as plt

def load_data(path):
	try:
		data = np.loadtxt(path)
		return data
	except Exception as e:
		print(f'Unable to load data from {path}: {e}')
		return None
	
def main():
	files3x3 = {
		'misplacedTiles': 'results/3x3-misplaced-results.txt',
		'manhattan': 'results/3x3-manhattan-results.txt'
	}

	dataMisplaced = load_data(files3x3['misplacedTiles'])
	statesMisplaced = np.mean(dataMisplaced[:, 0])
	pathMisplaced = np.mean(dataMisplaced[:, 1])

	print('Heurystyka niepoprawnych pol:')
	print(f'Srednia ilosc odwiedzonych stanow: {statesMisplaced}')
	print(f'Srednia ilosc ruchow potrzebnych do rozwiazania: {pathMisplaced}')
	
	dataManhattan = load_data(files3x3['manhattan'])
	statesManhattan = np.mean(dataManhattan[:, 0])
	pathManhattan = np.mean(dataManhattan[:, 1])

	print('\nHeurystyka manhattan:')
	print(f'Srednia ilosc odwiedzonych stanow: {statesManhattan}')
	print(f'Srednia ilosc ruchow potrzebnych do rozwiazania: {pathManhattan}')

	data4x4 = load_data('results/4x4-results.txt')

	ns = np.unique(data4x4[:, 0])
	n_vals = []
	states4x4 = []
	path4x4 = []

	for n in ns:
		mask = data4x4[:, 0] == n
		data_n = data4x4[mask]
		n_vals.append(n)
		states4x4.append(np.mean(data_n[:, 1]))
		path4x4.append(np.mean(data_n[:, 2]))
	
	n_vals = np.array(n_vals)
	states4x4 = np.array(states4x4)
	path4x4 = np.array(path4x4)

	plt.figure(figsize=(10,6))
	plt.plot(n_vals, states4x4)
	plt.title('Srednia liczba odwiedzonych stanow w zaleznosci od ilosci cofnietych ruchow')
	plt.xlabel('cofniete ruchy')
	plt.ylabel('odwiedzone stany')
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/stany.png')
	plt.close()

	plt.figure(figsize=(10,6))
	plt.plot(n_vals, path4x4)
	plt.title('Srednia liczba ruchow [ptrzebnych do ulozenia ukladanki w zaleznosci od ilosci cofnietych ruchow')
	plt.xlabel('cofniete ruchy')
	plt.ylabel('znaleziona trasa')
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/trasa.png')
	plt.close()

if __name__ == '__main__':
	main()