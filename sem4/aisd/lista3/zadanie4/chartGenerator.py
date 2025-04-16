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
        const_comparisons = []
        const_times = []
        ns = []

        for n_val in unique_ns:
            mask_n = data_label['n'] == n_val
            avg_comp = np.mean(data_label[mask_n]['comparisons'])
            avg_time = np.mean(data_label[mask_n]['time'])
            const_comp = np.mean(data_label[mask_n]['compsConst'])
            const_time = np.mean(data_label[mask_n]['timeConst'])
            ns.append(n_val)
            avg_comparisons.append(avg_comp)
            avg_times.append(avg_time)
            const_comparisons.append(const_comp)
            const_times.append(const_time)

        results[label] = {
            'n': np.array(ns),
            'avg_comparisons': np.array(avg_comparisons),
            'avg_time': np.array(avg_times),
            'const_comparisons': np.array(const_comparisons),
            'const_time': np.array(const_times)
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
    plt.title('Comparisons')
    plt.xlabel('n - array size')
    plt.ylabel('Average Comparisons')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig("comparisons.png")
    plt.close()

    plt.figure(figsize=(10, 6))
    for label, stats in sorted(results.items()):
        plt.plot(stats['n'], stats['avg_time'], marker='o', markersize=3, label=custom_labels.get(label, label))
    plt.title('Time')
    plt.xlabel('n - array size')
    plt.ylabel('Average Time')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig("time.png")
    plt.close()

    plt.figure(figsize=(10, 6))
    for label, stats in sorted(results.items()):
        plt.plot(stats['n'], stats['const_comparisons'], marker='o', markersize=3, label=custom_labels.get(label, label))
    plt.title('Comparisons - constant')
    plt.xlabel('n - array size')
    plt.ylabel('Average Comparisons / log(n)')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig("comparisons_constant.png")
    plt.close()

    plt.figure(figsize=(10, 6))
    for label, stats in sorted(results.items()):
        plt.plot(stats['n'], stats['const_time'], marker='o', markersize=3, label=custom_labels.get(label, label))
    plt.title('Time - constant')
    plt.xlabel('n - array size')
    plt.ylabel('Average Time / log(n)')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig("time_constant.png")
    plt.close()

def main():
    filename = 'binSearchTest.txt'

    data = load_data(filename)
    if data is None:
        return
    
    results = process_data(data)
    plot_results(results)
    print("Plots saved as 'comparisons.png', 'comparisons_constant.png', 'time.png' and 'time_constant.png'.")

if __name__ == '__main__':
    main()