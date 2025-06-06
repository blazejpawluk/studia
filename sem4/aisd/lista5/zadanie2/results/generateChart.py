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
	path_avg = []
	path_min = []
	path_max = []

	for n in ns:
		mask = data[:, 0] == n
		data_n = data[mask]
		n_vals.append(n)
		path_avg.append(np.mean(data_n[:, 1]))
		path_min.append(np.min(data_n[:, 1]))
		path_max.append(np.max(data_n[:, 1]))
	
	n_vals = np.array(n_vals)
	idx = np.argsort(n_vals)
	
	results = {}
	results['ns'] = n_vals[idx]
	results['path_avg'] = np.array(path_avg)[idx]
	results['path_min'] = np.array(path_min)[idx]
	results['path_max'] = np.array(path_max)[idx]

	return results

def main():
	file = 'results.txt'

	data = load_data(file)

	if data is None:
		print("Unable to load data. Ending program.")
		return
	
	results = convert_data(data)

	plt.figure(figsize=(10,6))
	plt.plot(results['ns'], results['path_avg'], linestyle='-', label='średnia')
	plt.plot(results['ns'], results['path_min'], marker='o', linestyle='', label='minimum')
	plt.plot(results['ns'], results['path_max'], marker='o', linestyle='', label='maksimum')
	plt.title('Średnia liczba rund potrzebnych do wysłania wiadomości po całym grafie')
	plt.xlabel('n')
	plt.ylabel('rundy')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('plot.png')
	plt.close()

if __name__ == '__main__':
	main()