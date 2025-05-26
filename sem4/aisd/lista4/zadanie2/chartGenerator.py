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
	insert_comps_avg = []
	insert_comps_max = []
	insert_reads_avg = []
	insert_reads_max = []
	insert_height_avg = []
	height_max = []
	delete_comps_avg = []
	delete_comps_max = []
	delete_reads_avg = []
	delete_reads_max = []
	delete_height_avg = []

	for n in ns:
		mask = data[:, 0] == n
		data_n = data[mask]
		n_vals.append(n)
		insert_comps_avg.append(np.mean(data_n[:, 1]))
		insert_comps_max.append(np.mean(data_n[:, 2]))
		insert_reads_avg.append(np.mean(data_n[:, 3]))
		insert_reads_max.append(np.mean(data_n[:, 4]))
		insert_height_avg.append(np.mean(data_n[:, 5]))
		height_max.append(np.mean(data_n[:, 6]))
		delete_comps_avg.append(np.mean(data_n[:, 7]))
		delete_comps_max.append(np.mean(data_n[:, 8]))
		delete_reads_avg.append(np.mean(data_n[:, 9]))
		delete_reads_max.append(np.mean(data_n[:, 10]))
		delete_height_avg.append(np.mean(data_n[:, 11]))

	results = {}
	n_vals = np.array(n_vals)
	idx = np.argsort(n_vals)
	results['n_vals'] = n_vals[idx]
	results['insert_comps_avg'] = np.array(insert_comps_avg)[idx]
	results['insert_comps_max'] = np.array(insert_comps_max)[idx]
	results['insert_reads_avg'] = np.array(insert_reads_avg)[idx]
	results['insert_reads_max'] = np.array(insert_reads_max)[idx]
	results['insert_height_avg'] = np.array(insert_height_avg)[idx]
	results['height_max'] = np.array(height_max)[idx]
	results['delete_comps_avg'] = np.array(delete_comps_avg)[idx]
	results['delete_comps_max'] = np.array(delete_comps_max)[idx]
	results['delete_reads_avg'] = np.array(delete_reads_avg)[idx]
	results['delete_reads_max'] = np.array(delete_reads_max)[idx]
	results['delete_height_avg'] = np.array(delete_height_avg)[idx]

	return results

def main():
	files = {
		'ascending array': 'results/ascResults.txt',
		'random array': 'results/ranResults.txt'
	}
	
	data_asc = load_data(files['ascending array'])
	data_ran = load_data(files['random array'])

	if data_asc is None or data_ran is None:
		print("Unable to load data. Ending program.")
		return
	
	results_asc = convert_data(data_asc)
	results_ran = convert_data(data_ran)

	plt.figure(figsize=(10, 6))
	plt.plot(results_asc['n_vals'], results_asc['insert_comps_avg'], label='average (insert)', linestyle='-')
	plt.plot(results_asc['n_vals'], results_asc['insert_comps_max'], label='maximum (insert)', marker='o', linestyle='')
	plt.plot(results_asc['n_vals'], results_asc['delete_comps_avg'], label='average (delete)', linestyle='-')
	plt.plot(results_asc['n_vals'], results_asc['delete_comps_max'], label='maximum (delete)', marker='o', linestyle='')
	plt.title('Comparisons in insert and delete in ascending array')
	plt.xlabel('n')
	plt.ylabel('comps')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/bst-ascending-comparisons.png')
	plt.close()

	plt.figure(figsize=(10, 6))
	plt.plot(results_ran['n_vals'], results_ran['insert_comps_avg'], label='average (insert)', linestyle='-')
	plt.plot(results_ran['n_vals'], results_ran['insert_comps_max'], label='maximum (insert)', marker='o', linestyle='')
	plt.plot(results_ran['n_vals'], results_ran['delete_comps_avg'], label='average (delete)', linestyle='-')
	plt.plot(results_ran['n_vals'], results_ran['delete_comps_max'], label='maximum (delete)', marker='o', linestyle='')
	plt.title('Comparisons in insert and delete in random array')
	plt.xlabel('n')
	plt.ylabel('comps')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/bst-random-comparisons.png')
	plt.close()

	plt.figure(figsize=(10, 6))
	plt.plot(results_asc['n_vals'], results_asc['insert_reads_avg'], label='average (insert)', linestyle='-')
	plt.plot(results_asc['n_vals'], results_asc['insert_reads_max'], label='maximum (insert)', marker='o', linestyle='')
	plt.plot(results_asc['n_vals'], results_asc['delete_reads_avg'], label='average (delete)', linestyle='-')
	plt.plot(results_asc['n_vals'], results_asc['delete_reads_max'], label='maximum (delete)', marker='o', linestyle='')
	plt.title('Reads in insert and delete in ascending array')
	plt.xlabel('n')
	plt.ylabel('reads')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/bst-ascending-reads.png')
	plt.close()

	plt.figure(figsize=(10, 6))
	plt.plot(results_ran['n_vals'], results_ran['insert_reads_avg'], label='average (insert)', linestyle='-')
	plt.plot(results_ran['n_vals'], results_ran['insert_reads_max'], label='maximum (insert)', marker='o', linestyle='')
	plt.plot(results_ran['n_vals'], results_ran['delete_reads_avg'], label='average (delete)', linestyle='-')
	plt.plot(results_ran['n_vals'], results_ran['delete_reads_max'], label='maximum (delete)', marker='o', linestyle='')
	plt.title('Reads in insert and delete in random array')
	plt.xlabel('n')
	plt.ylabel('reads')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/bst-random-reads.png')
	plt.close()

	plt.figure(figsize=(10, 6))
	plt.plot(results_asc['n_vals'], results_asc['insert_height_avg'], label='average (insert)', linestyle='-')
	plt.plot(results_asc['n_vals'], results_asc['height_max'], label='maximum', marker='o', linestyle='')
	plt.plot(results_asc['n_vals'], results_asc['delete_height_avg'], label='average (delete)', linestyle='-')
	plt.title('Height in insert and delete in ascending array')
	plt.xlabel('n')
	plt.ylabel('height')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/bst-ascending-height.png')
	plt.close()

	plt.figure(figsize=(10, 6))
	plt.plot(results_ran['n_vals'], results_ran['insert_height_avg'], label='average (insert)', linestyle='-')
	plt.plot(results_ran['n_vals'], results_ran['height_max'], label='maximum', marker='o', linestyle='')
	plt.plot(results_ran['n_vals'], results_ran['delete_height_avg'], label='average (delete)', linestyle='-')
	plt.title('Height in insert and delete in random array')
	plt.xlabel('n')
	plt.ylabel('height')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/bst-random-height.png')
	plt.close()

	plt.figure(figsize=(10, 6))
	plt.plot(results_ran['n_vals'], results_asc['insert_comps_avg'], label='average (ascending)', linestyle='-')
	plt.plot(results_ran['n_vals'], results_asc['insert_comps_max'], label='max (ascending)', marker='o', linestyle='')
	plt.plot(results_ran['n_vals'], results_ran['insert_comps_avg'], label='average (random)', linestyle='-')
	plt.plot(results_ran['n_vals'], results_ran['insert_comps_max'], label='max (random)', marker='o', linestyle='')
	plt.title('Comparisons in insert in ascending and random array')
	plt.xlabel('n')
	plt.ylabel('comps')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/bst-insert-comps.png')
	plt.close()

	plt.figure(figsize=(10, 6))
	plt.plot(results_ran['n_vals'], results_asc['delete_comps_avg'], label='average (ascending)', linestyle='-')
	plt.plot(results_ran['n_vals'], results_asc['delete_comps_max'], label='max (ascending)', marker='o', linestyle='')
	plt.plot(results_ran['n_vals'], results_ran['delete_comps_avg'], label='average (random)', linestyle='-')
	plt.plot(results_ran['n_vals'], results_ran['delete_comps_max'], label='max (random)', marker='o', linestyle='')
	plt.title('Comparisons in delete in ascending and random array')
	plt.xlabel('n')
	plt.ylabel('comps')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/bst-delete-comps.png')
	plt.close()

	plt.figure(figsize=(10, 6))
	plt.plot(results_ran['n_vals'], results_asc['insert_reads_avg'], label='average (ascending)', linestyle='-')
	plt.plot(results_ran['n_vals'], results_asc['insert_reads_max'], label='max (ascending)', marker='o', linestyle='')
	plt.plot(results_ran['n_vals'], results_ran['insert_reads_avg'], label='average (random)', linestyle='-')
	plt.plot(results_ran['n_vals'], results_ran['insert_reads_max'], label='max (random)', marker='o', linestyle='')
	plt.title('Reads in insert in ascending and random array')
	plt.xlabel('n')
	plt.ylabel('reads')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/bst-insert-reads.png')
	plt.close()

	plt.figure(figsize=(10, 6))
	plt.plot(results_ran['n_vals'], results_asc['delete_reads_avg'], label='average (ascending)', linestyle='-')
	plt.plot(results_ran['n_vals'], results_asc['delete_reads_max'], label='max (ascending)', marker='o', linestyle='')
	plt.plot(results_ran['n_vals'], results_ran['delete_reads_avg'], label='average (random)', linestyle='-')
	plt.plot(results_ran['n_vals'], results_ran['delete_reads_max'], label='max (random)', marker='o', linestyle='')
	plt.title('Reads in delete in ascending and random array')
	plt.xlabel('n')
	plt.ylabel('reads')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/bst-delete-reads.png')
	plt.close()

	plt.figure(figsize=(10, 6))
	plt.plot(results_ran['n_vals'], results_asc['insert_height_avg'], label='average (ascending)', linestyle='-')
	plt.plot(results_ran['n_vals'], results_asc['height_max'], label='max', marker='o', linestyle='')
	plt.plot(results_ran['n_vals'], results_ran['insert_height_avg'], label='average (random)', linestyle='-')
	plt.title('Height in insert in ascending and random array')
	plt.xlabel('n')
	plt.ylabel('height')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/bst-insert-height.png')
	plt.close()

	plt.figure(figsize=(10, 6))
	plt.plot(results_ran['n_vals'], results_asc['delete_height_avg'], label='average (ascending)', linestyle='-')
	plt.plot(results_ran['n_vals'], results_asc['height_max'], label='max', marker='o', linestyle='')
	plt.plot(results_ran['n_vals'], results_ran['delete_height_avg'], label='average (random)', linestyle='-')
	plt.title('Height in delete in ascending and random array')
	plt.xlabel('n')
	plt.ylabel('height')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/bst-delete-height.png')
	plt.close()

if __name__ == '__main__':
	main()