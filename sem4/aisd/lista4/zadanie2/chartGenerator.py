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

	# asc
	 # insert
	  # comps
	plt.figure(figsize=(10, 6))
	plt.plot(results_asc['n_vals'], results_asc['insert_comps_avg'], label='average')
	plt.plot(results_asc['n_vals'], results_asc['insert_comps_max'], label='maximum')
	plt.title('Comparisons in insert in ascending array')
	plt.xlabel('n')
	plt.ylabel('comps')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/asc_insert_comps.png')
	plt.close()
	   
	   # reads
	plt.figure(figsize=(10, 6))
	plt.plot(results_asc['n_vals'], results_asc['insert_reads_avg'], label='average')
	plt.plot(results_asc['n_vals'], results_asc['insert_reads_max'], label='maximum')
	plt.title('Reads in insert in ascending array')
	plt.xlabel('n')
	plt.ylabel('reads')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/asc_insert_reads.png')
	plt.close()
	   
	   # height
	plt.figure(figsize=(10, 6))
	plt.plot(results_asc['n_vals'], results_asc['insert_height_avg'], label='average')
	plt.plot(results_asc['n_vals'], results_asc['height_max'], label='maximum')
	plt.title('Height in insert in ascending array')
	plt.xlabel('n')
	plt.ylabel('height')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/asc_insert_height.png')
	plt.close()

	 # delete
	  # comps
	plt.figure(figsize=(10, 6))
	plt.plot(results_asc['n_vals'], results_asc['delete_comps_avg'], label='average')
	plt.plot(results_asc['n_vals'], results_asc['delete_comps_max'], label='maximum')
	plt.title('Comparisons in delete in ascending array')
	plt.xlabel('n')
	plt.ylabel('comps')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/asc_delete_comps.png')
	plt.close()
	   
	   # reads
	plt.figure(figsize=(10, 6))
	plt.plot(results_asc['n_vals'], results_asc['delete_reads_avg'], label='average')
	plt.plot(results_asc['n_vals'], results_asc['delete_reads_max'], label='maximum')
	plt.title('Reads in delete in ascending array')
	plt.xlabel('n')
	plt.ylabel('reads')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/asc_delete_reads.png')
	plt.close()
	   
	   # height
	plt.figure(figsize=(10, 6))
	plt.plot(results_asc['n_vals'], results_asc['delete_height_avg'], label='average')
	plt.plot(results_asc['n_vals'], results_asc['height_max'], label='maximum')
	plt.title('Height in delete in ascending array')
	plt.xlabel('n')
	plt.ylabel('height')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/asc_delete_height.png')
	plt.close()

	 # comps
	plt.figure(figsize=(10, 6))
	plt.plot(results_asc['n_vals'], results_asc['insert_comps_avg'], label='insert')
	plt.plot(results_asc['n_vals'], results_asc['delete_comps_avg'], label='delete')
	plt.title('Comparisons in insert vs in delete in ascending array')
	plt.xlabel('n')
	plt.ylabel('comps')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/asc_insert_delete_comps.png')
	plt.close()

	 # reads
	plt.figure(figsize=(10, 6))
	plt.plot(results_asc['n_vals'], results_asc['insert_reads_avg'], label='insert')
	plt.plot(results_asc['n_vals'], results_asc['delete_reads_avg'], label='reads')
	plt.title('Reads in insert vs in delete in ascending array')
	plt.xlabel('n')
	plt.ylabel('reads')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/asc_insert_delete_reads.png')
	plt.close()

	# ran
	 # insert
	  # comps
	plt.figure(figsize=(10, 6))
	plt.plot(results_ran['n_vals'], results_ran['insert_comps_avg'], label='average')
	plt.plot(results_ran['n_vals'], results_ran['insert_comps_max'], label='maximum')
	plt.title('Comparisons in insert in random array')
	plt.xlabel('n')
	plt.ylabel('comps')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/ran_insert_comps.png')
	plt.close()
	   
	   # reads
	plt.figure(figsize=(10, 6))
	plt.plot(results_ran['n_vals'], results_ran['insert_reads_avg'], label='average')
	plt.plot(results_ran['n_vals'], results_ran['insert_reads_max'], label='maximum')
	plt.title('Reads in insert in random array')
	plt.xlabel('n')
	plt.ylabel('reads')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/ran_insert_reads.png')
	plt.close()
	   
	   # height
	plt.figure(figsize=(10, 6))
	plt.plot(results_ran['n_vals'], results_ran['insert_height_avg'], label='average')
	plt.plot(results_ran['n_vals'], results_ran['height_max'], label='maximum')
	plt.title('Height in insert in random array')
	plt.xlabel('n')
	plt.ylabel('height')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/ran_insert_height.png')
	plt.close()

	 # delete
	  # comps
	plt.figure(figsize=(10, 6))
	plt.plot(results_ran['n_vals'], results_ran['delete_comps_avg'], label='average')
	plt.plot(results_ran['n_vals'], results_ran['delete_comps_max'], label='maximum')
	plt.title('Comparisons in delete in random array')
	plt.xlabel('n')
	plt.ylabel('comps')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/ran_delete_comps.png')
	plt.close()
	   
	   # reads
	plt.figure(figsize=(10, 6))
	plt.plot(results_ran['n_vals'], results_ran['delete_reads_avg'], label='average')
	plt.plot(results_ran['n_vals'], results_ran['delete_reads_max'], label='maximum')
	plt.title('Reads in delete in random array')
	plt.xlabel('n')
	plt.ylabel('reads')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/ran_delete_reads.png')
	plt.close()
	   
	   # height
	plt.figure(figsize=(10, 6))
	plt.plot(results_ran['n_vals'], results_ran['delete_height_avg'], label='average')
	plt.plot(results_ran['n_vals'], results_ran['height_max'], label='maximum')
	plt.title('Height in delete in random array')
	plt.xlabel('n')
	plt.ylabel('height')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/ran_delete_height.png')
	plt.close()
	
	 # comps
	plt.figure(figsize=(10, 6))
	plt.plot(results_ran['n_vals'], results_ran['insert_comps_avg'], label='insert')
	plt.plot(results_ran['n_vals'], results_ran['delete_comps_avg'], label='delete')
	plt.title('Comparisons in insert vs in delete in random array')
	plt.xlabel('n')
	plt.ylabel('comps')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/ran_insert_delete_comps.png')
	plt.close()
	
	 # reads
	plt.figure(figsize=(10, 6))
	plt.plot(results_ran['n_vals'], results_ran['insert_reads_avg'], label='insert')
	plt.plot(results_ran['n_vals'], results_ran['delete_reads_avg'], label='delete')
	plt.title('Reads in insert vs in delete in random array')
	plt.xlabel('n')
	plt.ylabel('reads')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/ran_insert_delete_reads.png')
	plt.close()

	# comps
	 # insert
	plt.figure(figsize=(10, 6))
	plt.plot(results_asc['n_vals'], results_asc['insert_comps_avg'], label='ascending')
	plt.plot(results_ran['n_vals'], results_ran['insert_comps_avg'], label='random')
	plt.title('Comps in insert in ascending vs random array')
	plt.xlabel('n')
	plt.ylabel('comps')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/asc_ran_insert_comps.png')
	plt.close()

	 # delete
	plt.figure(figsize=(10, 6))
	plt.plot(results_asc['n_vals'], results_asc['delete_comps_avg'], label='ascending')
	plt.plot(results_ran['n_vals'], results_ran['delete_comps_avg'], label='random')
	plt.title('Comps in delete in ascending vs random array')
	plt.xlabel('n')
	plt.ylabel('comps')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/asc_ran_delete_comps.png')
	plt.close()

	# reads
	 # insert
	plt.figure(figsize=(10, 6))
	plt.plot(results_asc['n_vals'], results_asc['insert_reads_avg'], label='ascending')
	plt.plot(results_ran['n_vals'], results_ran['insert_reads_avg'], label='random')
	plt.title('Reads in insert in ascending vs random array')
	plt.xlabel('n')
	plt.ylabel('reads')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/asc_ran_reads_comps.png')
	plt.close()

	 # delete
	plt.figure(figsize=(10, 6))
	plt.plot(results_asc['n_vals'], results_asc['delete_reads_avg'], label='ascending')
	plt.plot(results_ran['n_vals'], results_ran['delete_reads_avg'], label='random')
	plt.title('Reads in delete in ascending vs random array')
	plt.xlabel('n')
	plt.ylabel('reads')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.savefig('charts/asc_ran_delete_reads.png')
	plt.close()

if __name__ == '__main__':
	main()