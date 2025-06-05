import numpy as np
import matplotlib.pyplot as plt

def load_data(path):
	try:
		data = np.loadtxt(path)
		return data
	except Exception as e:
		print(f"Unable to load data from {path}: {e}")
		return None

def convert_data1(data):
	results = {}
	for row in data:
		idx = int(row[0])
		ops = row[1:]
		results[idx] = ops
	return results

def convert_data2(data):
	ns = np.unique(data[:, 0])
	n_vals = []
	comps = []

	for n in ns:
		mask = data[:, 0] == n
		data_n = data[mask]
		n_vals.append(n)
		comps.append(np.mean(data_n[:, 1]))

	n_vals = np.array(n_vals)
	idx = np.argsort(n_vals)

	results = {}
	results['ns'] = n_vals[idx]
	results['comps'] = np.array(comps)[idx]
	return results

def main():
	file = '500-results.txt'
	data = load_data(file)
	results = convert_data1(data)
	
	x = np.arange(1, 5)
	plt.figure(figsize=(10,6))
	for i in sorted(results.keys()):
		y = results[i]
		plt.plot(x, y, marker='o', linestyle='-', label=f'Symulacja {i}')
	plt.xticks(x, ['Make-Heap', 'Insert', 'Union', 'Delete'])
	plt.xlabel('Operacje')
	plt.ylabel('Porównania')
	plt.title('Porównania w dla danych operacji.')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig("plot500.png")

	file = 'resultsN.txt'
	data = load_data(file)
	results = convert_data2(data)

	plt.figure()
	plt.plot(results['ns'], results['comps'], linestyle='-', marker='o', label='średnia liczba porównań')
	plt.title('Średnia łączna liczba porównań dzielona przez n')
	plt.xlabel('n')
	plt.ylabel('porównania / n')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('plotN.png')
	plt.close()

if __name__ == '__main__':
	main()