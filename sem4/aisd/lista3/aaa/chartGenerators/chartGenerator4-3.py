import numpy as np
import matplotlib.pyplot as plt

def load_data(path):
    try:
        data = np.genfromtxt(path, dtype=None, encoding='utf-8', names=True)
        return data
    except Exception as e:
        print(f"Unable to load data from {path}: {e}")
        return None

def process_data(data):
    results = {}
    unique_labels = np.unique(data['label'])

    for label in unique_labels:
        mask_label = data['label'] == label
        data_label = data[mask_label]

        unique_ns = np.unique(data_label['n'])

        avg_comparisons = []
        avg_times = []
        ns = []

        for n_val in unique_ns:
            mask_n = data_label['n'] == n_val
            avg_comp = np.mean(data_label[mask_n]['comps'])
            avg_time = np.mean(data_label[mask_n]['time'])
            ns.append(n_val)
            avg_comparisons.append(avg_comp)
            avg_times.append(avg_time)

        results[label] = {
            'n': np.array(ns),
            'avg_comparisons': np.array(avg_comparisons),
            'avg_time': np.array(avg_times)
        }
    
    return results

def plot_results(results):
    custom_labels = {
        'ran': 'Random value from range [1, 2n-1]',
        'beg': 'Value from the beginning of the array (index in [1, n/3])',
        'mid': 'Value from the middle of the array (index in [n/3, 2n/3])',
        'end': 'Value from the end of the array (index in [2n/3, n-1])',
        'not': 'Random value from range [1, 2n-1], not in array',
        'inA': 'Random value from array'
	}

    plt.figure(figsize=(10, 6))
    for label, stats in sorted(results.items()):
        plt.plot(stats['n'], stats['avg_comparisons'], marker='o', markersize=3, label=custom_labels.get(label, label))
    plt.title('comps')
    plt.xlabel('n')
    plt.ylabel('average comps')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig("charts/4-3_const_comps.png")
    plt.close()

    plt.figure(figsize=(10, 6))
    for label, stats in sorted(results.items()):
        plt.plot(stats['n'], stats['avg_time'], marker='o', markersize=3, label=custom_labels.get(label, label))
    plt.title('time')
    plt.xlabel('n')
    plt.ylabel('average time')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig("charts/4-3_const_time.png")
    plt.close()

def main():
    filename = 'results/binSearchConstTest.txt'

    data = load_data(filename)
    if data is None:
        return
    
    results = process_data(data)
    plot_results(results)
    print("Plots saved as '4-3_const_comps.png', '4-3_const_time.png'.")

if __name__ == '__main__':
    main()