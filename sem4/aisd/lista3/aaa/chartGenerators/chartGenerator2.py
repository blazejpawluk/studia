import numpy as np
import matplotlib.pyplot as plt

def load_data(path):
    try:
        data = np.loadtxt(path)
        return data
    except Exception as e:
        print(f"Unable to load data from {path}: {e}")
        return None

def set_label(n, k):
    if k == 1:
        return "k=1"
    elif 4 * k == n:
        return "k=n/4"
    elif 2 * k == n:
        return "k=n/2"
    elif 4 * k == 3 * n:
        return "k=3n/4"
    elif k == n:
        return "k=n"
    else:
        return "Inne"

def convert_data_k(data):
    labels = ["k=1", "k=n/4", "k=n/2", "k=3n/4", "k=n"]
    results = {e: {} for e in labels}
    
    ns = np.unique(data[:, 0])
    for n in ns:
        mask = data[:, 0] == n
        data_n = data[mask]
        temp = {}
        for record in data_n:
            n_val = int(record[0])
            k_val = int(record[1])
            label = set_label(n_val, k_val)
            if label not in temp:
                temp[label] = {"comparisons": [], "swaps": []}
            temp[label]["comparisons"].append(record[2])
            temp[label]["swaps"].append(record[3])
        for label, stat in temp.items():
            if label not in results:
                results[label] = {}
            if 'n' not in results[label]:
                results[label]['n'] = []
                results[label]['comparisons'] = []
                results[label]['swaps'] = []
            results[label]['n'].append(n)
            results[label]['comparisons'].append(np.mean(stat["comparisons"]))
            results[label]['swaps'].append(np.mean(stat["swaps"]))
    
    for label in results:
        if 'n' in results[label]:
            idx = np.argsort(results[label]['n'])
            results[label]['n'] = np.array(results[label]['n'])[idx]
            results[label]['comparisons'] = np.array(results[label]['comparisons'])[idx]
            results[label]['swaps'] = np.array(results[label]['swaps'])[idx]
    return results

def convert_data_no_k(data):
    ns = np.unique(data[:, 0])
    n_vals = []
    comparisons = []
    swaps = []
    for n in ns:
        mask = data[:, 0] == n
        data_n = data[mask]
        n_vals.append(n)
        comparisons.append(np.mean(data_n[:, 2]))
        swaps.append(np.mean(data_n[:, 3]))
    n_vals = np.array(n_vals)
    comparisons = np.array(comparisons)
    swaps = np.array(swaps)
    idx = np.argsort(n_vals)
    return n_vals[idx], comparisons[idx], swaps[idx]

def draw_plots(results_random, results_select):
    labels = ["k=1", "k=n/4", "k=n/2", "k=3n/4", "k=n"]
    
    for label in labels:
        if label not in results_random or label not in results_select:
            print(f"No data for {label} for at least one algorithm.")
            continue

        plt.figure(figsize=(10, 6))
        plt.plot(results_random[label]['n'], results_random[label]['comparisons'],
                 marker='o', linestyle='', markersize=3, label='randomSelect')
        plt.plot(results_select[label]['n'], results_select[label]['comparisons'],
                 marker='o', linestyle='', markersize=3, label='select')
        plt.title(f'comps - {label}')
        plt.xlabel('n')
        plt.ylabel('average comps')
        plt.legend()
        plt.grid(True)
        plt.tight_layout()
        plt.savefig(f"charts/2_comps_{label.replace('=', '').replace('/', '_')}.png")
        plt.close()

        plt.figure(figsize=(10, 6))
        plt.plot(results_random[label]['n'], results_random[label]['swaps'],
                 marker='o', linestyle='', markersize=3, label='randomSelect')
        plt.plot(results_select[label]['n'], results_select[label]['swaps'],
                 marker='o', linestyle='', markersize=3, label='select')
        plt.title(f'swaps - {label}')
        plt.xlabel('n')
        plt.ylabel('average swaps')
        plt.legend()
        plt.grid(True)
        plt.tight_layout()
        plt.savefig(f"charts/2_swaps_{label.replace('=', '').replace('/', '_')}.png")
        plt.close()

def draw_plots_no_k(n_random, comp_random, swaps_random, n_select, comp_select, swaps_select):
    plt.figure(figsize=(10, 6))
    plt.plot(n_random, comp_random, marker='o', linestyle='', markersize=3, label='randomSelect')
    plt.plot(n_select, comp_select, marker='o', linestyle='', markersize=3, label='select')
    plt.title('comps')
    plt.xlabel('n')
    plt.ylabel('average comps')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig("charts/2_comps.png")
    plt.close()
    
    plt.figure(figsize=(10, 6))
    plt.plot(n_random, swaps_random, marker='o', linestyle='', markersize=3, label='randomSelect')
    plt.plot(n_select, swaps_select, marker='o', linestyle='', markersize=3, label='select')
    plt.title('swaps')
    plt.xlabel('n')
    plt.ylabel('average swaps')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig("charts/2_swaps.png")
    plt.close()

def main():
    files = {
        'randomSelect': 'results/randomSelectTest.txt',
        'select': 'results/selectTest.txt'
    }
    
    data_random = load_data(files['randomSelect'])
    data_select = load_data(files['select'])
    
    if data_random is None or data_select is None:
        print("Unable to load data. Ending program.")
        return
    
    results_random = convert_data_k(data_random)
    results_select = convert_data_k(data_select)
    
    draw_plots(results_random, results_select)
    
    n_random, comp_random, swaps_random = convert_data_no_k(data_random)
    n_select, comp_select, swaps_select = convert_data_no_k(data_select)
    draw_plots_no_k(n_random, comp_random, swaps_random, n_select, comp_select, swaps_select)

if __name__ == '__main__':
    main()