import numpy as np
import matplotlib.pyplot as plt

def load_data(path):
	try:
		data = np.loadtxt(path)
		return data
	except Exception as e:
		print(f"Unable to load data from {path}: {e}")
		return None
	
def convert_data(data):
	ns = np.unique(data[:, 0])
	n_vals = []
	times = []

	for n in ns:
		mask = data[:, 0] == n
		data_n = data[mask]
		n_vals.append(n)
		times.append(np.mean(data_n[:, 1]))
	
	n_vals = np.array(n_vals)
	idx = np.argsort(n_vals)
	
	results = {}
	results['ns'] = n_vals[idx]
	results['times'] = np.array(times)[idx]

	return results

def main():
	files = {
		'algorytm Kruskala': 'resultsKruskal.txt',
		'algorytm Prima': 'resultsPrim.txt'
	}

	dataK = load_data(files['algorytm Kruskala'])
	dataP = load_data(files['algorytm Prima'])

	if dataK is None or dataP is None:
		print("Unable to load data. Ending program.")
		return
	
	resultsK = convert_data(dataK)
	resultsP = convert_data(dataP)

	plt.figure(figsize=(10,6))
	plt.plot(resultsK['ns'], resultsK['times'], label='algorytm Kruskala')
	plt.plot(resultsP['ns'], resultsP['times'], label='algorytm Prima')
	plt.title('Porównanie czasów działania algorytmów Kruskala i Prima')
	plt.xlabel('n')
	plt.ylabel('średni czas wykonywania algorytmu')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('plot.png')
	plt.close()

if __name__ == '__main__':
	main()