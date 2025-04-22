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
    comparisons = []
    times = []
    for n in ns:
        mask = data[:, 0] == n
        data_n = data[mask]
        n_vals.append(n)
        comparisons.append(np.mean(data_n[:, 1]))
        times.append(np.mean(data_n[:, 2]))
    n_vals = np.array(n_vals)
    comparisons = np.array(comparisons)
    times = np.array(times)
    idx = np.argsort(n_vals)
    return n_vals[idx], comparisons[idx], times[idx]

def main():
	files = {
		'quickSort': 'results/quickSortTestW.txt',
		'quickSelectSort': 'results/quickSelectSortTestW.txt',
		'DPQuickSort': 'results/DPQuickSortTestW.txt',
		'DPQuickSelectSort': 'results/DPQuickSelectSortTestW.txt'
	}

	dataQS = load_data(files['quickSort'])
	dataQSS = load_data(files['quickSelectSort'])
	dataDPQS = load_data(files['DPQuickSort'])
	dataDPQSS = load_data(files['DPQuickSelectSort'])

	nQS, compQS, timeQS = convert_data(dataQS)
	nQSS, compQSS, timeQSS = convert_data(dataQSS)
	nDPQS, compDPQS, timeDPQS = convert_data(dataDPQS)
	nDPQSS, compDPQSS, timeDPQSS = convert_data(dataDPQSS)
     
	plt.figure(figsize=(10, 6))
	plt.plot(nQS, compQS, marker='o', linestyle='', markersize=3, label='quickSort')
	plt.plot(nQSS, compQSS, marker='o', linestyle='', markersize=3, label='quickSelectSort')
	plt.plot(nDPQS, compDPQS, marker='o', linestyle='', markersize=3, label='DPQuickSort')
	plt.plot(nDPQSS, compDPQSS, marker='o', linestyle='', markersize=3, label='DPQuickSelectSort')
	plt.title('comps')
	plt.xlabel('n')
	plt.ylabel('average comps')
	plt.ticklabel_format(style='plain', axis='y')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig("charts/5-3_comps.png")
	plt.close()
     
	plt.figure(figsize=(10, 6))
	plt.plot(nQS, timeQS, marker='o', linestyle='', markersize=3, label='quickSort')
	plt.plot(nQSS, timeQSS, marker='o', linestyle='', markersize=3, label='quickSelectSort')
	plt.plot(nDPQS, timeDPQS, marker='o', linestyle='', markersize=3, label='DPQuickSort')
	plt.plot(nDPQSS, timeDPQSS, marker='o', linestyle='', markersize=3, label='DPQuickSelectSort')
	plt.title('time')
	plt.xlabel('n')
	plt.ylabel('average time')
	plt.ticklabel_format(style='plain', axis='y')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig("charts/5-3_time.png")
	plt.close()
     
if __name__ == '__main__':
    main()