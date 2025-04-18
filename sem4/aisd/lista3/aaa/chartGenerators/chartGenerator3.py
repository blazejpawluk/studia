import numpy as np
import matplotlib.pyplot as plt

def load_data(path):
    try:
        data = np.loadtxt(path)
        return data
    except Exception as e:
        print(f"Unable to load data from {path}: {e}")
        return None

def process_data(data):
    results = {}
    unique_ks = np.unique(data[:, 1])
    
    for k_val in unique_ks:
        mask_k = data[:, 1] == k_val
        data_k = data[mask_k]
        
        unique_ns = np.unique(data_k[:, 0])
        
        avg_comparisons = []
        avg_swaps = []
        ns = []
        
        for n_val in unique_ns:
            mask_n = data_k[:, 0] == n_val
            avg_comp = np.mean(data_k[mask_n, 2])
            avg_swap = np.mean(data_k[mask_n, 3])
            ns.append(n_val)
            avg_comparisons.append(avg_comp)
            avg_swaps.append(avg_swap)
        
        results[k_val] = {
            'n': np.array(ns),
            'avg_comparisons': np.array(avg_comparisons),
            'avg_swaps': np.array(avg_swaps)
        }
    
    return results

def plot_results(results):
    plt.figure(figsize=(10, 6))
    for k_val, stats in sorted(results.items()):
        plt.scatter(stats['n'], stats['avg_comparisons'], label=f'k = {int(k_val)}', s=10)
    plt.title('comps')
    plt.xlabel('n')
    plt.ylabel('average comparisons')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig('charts/3_comps.png')
    plt.close()
    
    plt.figure(figsize=(10, 6))
    for k_val, stats in sorted(results.items()):
        plt.scatter(stats['n'], stats['avg_swaps'], label=f'k = {int(k_val)}', s=10)
    plt.title('swaps')
    plt.xlabel('n')
    plt.ylabel('average swaps')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig('charts/3_swaps.png')
    plt.close()

def main():
    filename = 'results/selectTresholdTest.txt'
    
    data = load_data(filename)
    if data is None:
        return
    
    results = process_data(data)
    plot_results(results)
    print("Plots saved as 'comparisons.png' and 'swaps.png'.")

if __name__ == '__main__':
    main()
