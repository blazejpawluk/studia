from pathlib import Path
import argparse
import math
import statistics
import numpy as np
import matplotlib.pyplot as plt
import csv
import re
import sys


def parse_values_from_file(path: Path):
    with path.open('r', encoding='utf-8', errors='replace') as f:
        lines = [ln.strip() for ln in f.readlines()]

    country = None
    values = []
    for i, ln in enumerate(lines):
        if ln != '':
            country = ln
            rest = lines[i+1:]
            break
    else:
        return (path.stem, [])

    for ln in rest:
        if ln == '':
            continue
        ln2 = ln.replace(',', '.')
        ln2 = ln2.replace(' ', '')
        try:
            val = float(ln2)
            if math.isfinite(val):
                values.append(val)
        except Exception:
            continue

    return country, values


def group_minima(values, group_size: int):
    minima = []
    n = len(values)
    full_groups = n // group_size
    for g in range(full_groups):
        start = g * group_size
        group = values[start:start + group_size]
        minima.append(min(group))
    return minima


def compute_metrics(values):
    res = {
        'avg_min_10': None,
        'avg_min_50': None,
        'overall_min': None,
        'minima_10': [],
        'minima_50': [],
    }
    if not values:
        return res

    res['overall_min'] = min(values)
    minima_10 = group_minima(values, 10)
    minima_50 = group_minima(values, 50)
    res['minima_10'] = minima_10
    res['minima_50'] = minima_50
    if minima_10:
        res['avg_min_10'] = statistics.mean(minima_10)
    if minima_50:
        res['avg_min_50'] = statistics.mean(minima_50)
    return res


def sanitize_filename(name: str):
    s = re.sub(r'[^0-9A-Za-z_.-]', '_', name)
    return s[:200]


def plot_for_country(country, values, minima_10, minima_50, outpath: Path):
    if not values:
        print(f"{country}: no data to create plots")
        return

    x = list(range(1, len(values)+1))

    fig, axes = plt.subplots(3, 1, figsize=(12, 10), constrained_layout=True)

    axes[0].plot(x, values)
    axes[0].set_title(f"{country} — all values (n={len(values)})")
    axes[0].set_xlabel('index')
    axes[0].set_ylabel('path length')

    if minima_10:
        x10 = list(range(1, len(minima_10)+1))
        axes[1].bar(x10, minima_10)
        axes[1].set_title('Minimum values for each of 10 random permuatations (100 groups of 10)')
        axes[1].set_xlabel('group (of 10)')
        axes[1].set_ylabel('min (of 10)')
    else:
        axes[1].text(0.5, 0.5, 'no full groups of 10', ha='center', va='center')
        axes[1].set_axis_off()

    if minima_50:
        x50 = list(range(1, len(minima_50)+1))
        axes[2].bar(x50, minima_50)
        axes[2].set_title('Minimum values for each of 50 random permuatations (20 groups of 50)')
        axes[2].set_xlabel('group (of 50)')
        axes[2].set_ylabel('min (of 50)')
    else:
        axes[2].text(0.5, 0.5, 'no full groups of 50', ha='center', va='center')
        axes[2].set_axis_off()

    fig.suptitle(f'{country}', fontsize=14)

    outpath.parent.mkdir(parents=True, exist_ok=True)
    fig.savefig(outpath)
    plt.close(fig)


def main():
    parser = argparse.ArgumentParser(description='Calculate average from minimum (100 groups of 10, 20 groups of 50), calculate minimum value, graphical reprezentation of results')
    parser.add_argument('--folder', '-f', default='zad12/data', help='Path to folder with files (default: \'zad12/data\')')
    parser.add_argument('--output', '-o', default='zad12/results', help='Output folder (default: \'zad12/results\')')
    args = parser.parse_args()

    folder = Path(args.folder)
    if not folder.exists() or not folder.is_dir():
        print('Błędna ścieżka do folderu:', folder)
        sys.exit(1)

    outdir = Path(args.output)
    outdir.mkdir(parents=True, exist_ok=True)

    summary_rows = []

    files = folder.iterdir()
    for file in files:
        if not file.is_file():
            continue
        country, values = parse_values_from_file(file)
        metrics = compute_metrics(values)

        sanitized = sanitize_filename(country or file.stem)
        png_path = outdir / f"{sanitized}.png"

        plot_for_country(country or file.stem, values, metrics['minima_10'], metrics['minima_50'], png_path)

        summary_rows.append({
            'file': str(file),
            'country': country,
            'n_values': len(values),
            'avg_min_10': metrics['avg_min_10'],
            'avg_min_50': metrics['avg_min_50'],
            'overall_min': metrics['overall_min'],
            'png': str(png_path),
        })

        print(f"Przetworzono {file.name} -> {png_path.name} | avg_min_10={metrics['avg_min_10']} | avg_min_50={metrics['avg_min_50']} | overall_min={metrics['overall_min']}")

    csv_path = outdir / 'summary.csv'
    with csv_path.open('w', newline='', encoding='utf-8') as csvfile:
        fieldnames = ['file', 'country', 'n_values', 'avg_min_10', 'avg_min_50', 'overall_min', 'png']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        writer.writeheader()
        for row in summary_rows:
            writer.writerow(row)

    print('\nZapisano podsumowanie do:', csv_path)
    print('Gotowe.')


if __name__ == '__main__':
    main()
