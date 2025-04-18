import matplotlib.pyplot as plt
from collections import defaultdict

# Mapping of data files to algorithm names
data_files = {
    'qsTest.txt': 'QuickSort',
    'dpqsTest.txt': 'DPQuickSort',
    'qssTest.txt': 'QuickSelectSort',
    'dpqssTest.txt': 'DPQuickSelectSort',
}

def load_and_average(filename):
    """
    Wczytuje dane z pliku i oblicza średnie wartości dla każdej długości tablicy n:
    - comps_avg: średnia liczba porównań
    - times_avg: średni czas wykonania (ns)
    Plik ma format: n k comps time (bez nagłówka)
    """
    comps_dict = defaultdict(list)
    times_dict = defaultdict(list)

    with open(filename) as f:
        for line in f:
            parts = line.split()
            if len(parts) != 4:
                continue
            n, _, comps, time_ns = map(int, parts)
            comps_dict[n].append(comps)
            times_dict[n].append(time_ns)

    ns = sorted(comps_dict.keys())
    comps_avg = [sum(comps_dict[n]) / len(comps_dict[n]) for n in ns]
    times_avg = [sum(times_dict[n]) / len(times_dict[n]) for n in ns]

    return ns, comps_avg, times_avg

# Przygotowanie danych do wykresów
data_comps = {}
data_times = {}
for filename, algo in data_files.items():
    ns, comps_avg, times_avg = load_and_average(filename)
    data_comps[algo] = (ns, comps_avg)
    data_times[algo] = (ns, times_avg)

# Wykres średniej liczby porównań vs długość tablicy
plt.figure()
for algo, (ns, avgs) in data_comps.items():
    plt.plot(ns, avgs, marker='o', label=algo)
plt.title('Średnia liczba porównań vs długość tablicy')
plt.xlabel('Długość tablicy (n)')
plt.ylabel('Średnia liczba porównań')
plt.legend()
plt.grid(True)
plt.savefig('comparisons.png')
plt.close()

# Wykres średniego czasu wykonania vs długość tablicy
plt.figure()
for algo, (ns, avgs) in data_times.items():
    plt.plot(ns, avgs, marker='o', label=algo)
plt.title('Średni czas wykonania vs długość tablicy')
plt.xlabel('Długość tablicy (n)')
plt.ylabel('Średni czas wykonania (ns)')
plt.legend()
plt.grid(True)
plt.savefig('execution_time.png')
plt.close()
