from __future__ import annotations
import argparse
import os
import sys
from collections import defaultdict
from typing import Dict, List, Tuple

import numpy as np
import matplotlib.pyplot as plt


def parse_line(line: str) -> Tuple[str, int, List[float]]:
    s = line.strip()
    if not s or s.startswith('#'):
        raise ValueError("pominięty wiersz (komentarz/pusty)")

    parts = s.split()
    if len(parts) < 7:
        raise ValueError(f"nieprawidłowa liczba pól: {len(parts)} wiersz: {s!r}")

    name_i = parts[0]
    try:
        name, i_str = name_i.rsplit('.', 1)
    except ValueError:
        raise ValueError(f"pierwsze pole musi zawierać nazwę i indeks oddzielone kropką, np. 'Family.0'. Otrzymano: {name_i!r}")

    try:
        i = int(i_str)
    except ValueError:
        try:
            i = int(float(i_str))
        except Exception:
            raise ValueError(f"nie można sparsować indeksu i jako liczby całkowitej: {i_str!r}")

    vals = []
    for j in range(1, 7):
        try:
            vals.append(float(parts[j]))
        except Exception as e:
            raise ValueError(f"nie można sparsować wartości float w polu {j+1}: {parts[j]!r} ({e})")

    return name, i, vals


def read_data(filename: str) -> Dict[str, Dict[str, List[float]]]:
    data: Dict[str, Dict[str, List[float]]] = {}
    def get_rec(name: str):
        if name not in data:
            data[name] = {
                'i': [],
                'minDij': [],
                'minDia': [],
                'minRad': [],
                'avgDij': [],
                'avgDia': [],
                'avgRad': [],
            }
        return data[name]

    with open(filename, 'r', encoding='utf-8') as f:
        for lineno, line in enumerate(f, start=1):
            line = line.strip()
            if not line or line.startswith('#'):
                continue
            try:
                name, i, vals = parse_line(line)
            except ValueError as e:
                print(f"Ostrzeżenie: linia {lineno} pominięta: {e}", file=sys.stderr)
                continue

            rec = get_rec(name)
            rec['i'].append(i)
            rec['minDij'].append(vals[0])
            rec['minDia'].append(vals[1])
            rec['minRad'].append(vals[2])
            rec['avgDij'].append(vals[3])
            rec['avgDia'].append(vals[4])
            rec['avgRad'].append(vals[5])

    return data


def ensure_sorted(rec: Dict[str, List[float]]) -> Dict[str, np.ndarray]:
    i_arr = np.array(rec['i'], dtype=int)
    order = np.argsort(i_arr)
    sorted_rec = {
        'i': i_arr[order],
        'minDij': np.array(rec['minDij'], dtype=float)[order],
        'minDia': np.array(rec['minDia'], dtype=float)[order],
        'minRad': np.array(rec['minRad'], dtype=float)[order],
        'avgDij': np.array(rec['avgDij'], dtype=float)[order],
        'avgDia': np.array(rec['avgDia'], dtype=float)[order],
        'avgRad': np.array(rec['avgRad'], dtype=float)[order],
    }
    return sorted_rec


def make_plot(x, series: List[Tuple[np.ndarray, str, str]], title: str, xlabel: str, ylabel: str, outpath: str):
    plt.figure(figsize=(10, 6))

    for y, label, style in series:
        if style:
            plt.plot(x, y, style, label=label, linewidth=1.5, markersize=6)
        else:
            plt.plot(x, y, label=label, linewidth=1.5, markersize=6)

    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.legend()
    plt.grid(True, linestyle='--', alpha=0.6)
    plt.tight_layout()
    plt.savefig(outpath, dpi=150)
    plt.close()
    print(f"Zapisano: {outpath}")


def generate_plots_for_name(name: str, rec: Dict[str, List[float]], outdir: str):
    recs = ensure_sorted(rec)
    x = recs['i']

    title = f"Rodzina grafów name: {name}"

    # 1) 3 serie: minDij, minDia, minRad
    series1 = [
        (recs['minDij'], 'minDij', 'o-'),
        (recs['minDia'], 'minDia', 's-'),
        (recs['minRad'], 'minRad', '^-'),
    ]
    out1 = os.path.join(outdir, f"{name}_min_three_series.png")
    make_plot(x, series1, title + ' — min (3 serie)', 'i', 'wartość', out1)

    # 2) 3 serie: avgDij, avgDia, avgRad
    series2 = [
        (recs['avgDij'], 'avgDij', 'o-'),
        (recs['avgDia'], 'avgDia', 's-'),
        (recs['avgRad'], 'avgRad', '^-'),
    ]
    out2 = os.path.join(outdir, f"{name}_avg_three_series.png")
    make_plot(x, series2, title + ' — avg (3 serie)', 'i', 'wartość', out2)

    # 3) 2 serie: minDij, avgDij
    series3 = [
        (recs['minDij'], 'minDij', 'o-'),
        (recs['avgDij'], 'avgDij', 's--'),
    ]
    out3 = os.path.join(outdir, f"{name}_dij_min_vs_avg.png")
    make_plot(x, series3, title + ' — minDij vs avgDij', 'i', 'wartość', out3)

    # 4) 2 serie: minDia, avgDia
    series4 = [
        (recs['minDia'], 'minDia', 'o-'),
        (recs['avgDia'], 'avgDia', 's--'),
    ]
    out4 = os.path.join(outdir, f"{name}_dia_min_vs_avg.png")
    make_plot(x, series4, title + ' — minDia vs avgDia', 'i', 'wartość', out4)

    # 5) 2 serie: minRad, avgRad
    series5 = [
        (recs['minRad'], 'minRad', 'o-'),
        (recs['avgRad'], 'avgRad', 's--'),
    ]
    out5 = os.path.join(outdir, f"{name}_rad_min_vs_avg.png")
    make_plot(x, series5, title + ' — minRad vs avgRad', 'i', 'wartość', out5)


def main(argv=None):
    parser = argparse.ArgumentParser(description='Generowanie wykresów z pliku danych')
    parser.add_argument('--input', '-i', default='data.txt', help='Plik wejściowy (domyślnie data.txt)')
    parser.add_argument('--outdir', '-o', default='plots', help='Katalog na wykresy (domyślnie ./plots)')
    args = parser.parse_args(argv)

    if not os.path.isfile(args.input):
        print(f"Błąd: plik wejściowy nie istnieje: {args.input}", file=sys.stderr)
        sys.exit(2)

    os.makedirs(args.outdir, exist_ok=True)

    data = read_data(args.input)
    if not data:
        print("Brak danych do przetworzenia.", file=sys.stderr)
        sys.exit(1)

    for name, rec in data.items():
        try:
            generate_plots_for_name(name, rec, args.outdir)
        except Exception as e:
            print(f"Błąd podczas tworzenia wykresów dla {name}: {e}", file=sys.stderr)


if __name__ == '__main__':
    main()