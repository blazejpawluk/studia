#include "bst.cpp"
#include <algorithm>
#include <random>
#include <fstream>

int main() {
	ofstream fileAsc("results/ascResults.txt");
	ofstream fileRan("results/ranResults.txt");

	random_device rd;
	mt19937 gen(rd());
	
	for (int n = 1000; n <= 10000; n += 1000) {
		cout << n << endl;
		uniform_int_distribution<> dis(0, 2 * n - 1);

		for (int k = 0; k < 20; k++) {
			int ascArr[n], ranArr[n], del[n];
			for (int i = 0; i < n; i++) {
				ranArr[i] = dis(gen);
				ascArr[i] = ranArr[i];
				del[i] = i;
			}
			sort(ascArr, ascArr + n);
			random_shuffle(del, del + n);

			// ascending array
			root = nullptr;
			double avgComps = 0, avgReads = 0, avgHeight = 0;
			int maxComps = 0, maxReads = 0;
			for (int i = 0; i < n; i++) {
				comps = 0; reads = 0;
				root = Insert(root, ascArr[i]);
				avgComps += comps * 1.0 / n;
				avgReads += reads * 1.0 / n;
				avgHeight += Height(root) * 1.0 / n;
				maxComps = max(maxComps, comps);
				maxReads = max(maxReads, comps);
			}
			fileAsc << n << " ";
			fileAsc << avgComps << " " << maxComps << " ";
			fileAsc << avgReads << " " << maxReads << " ";
			fileAsc << avgHeight << " " << Height(root) << " ";

			avgComps = 0, avgReads = 0, avgHeight = 0;
			maxComps = 0, maxReads = 0;
			for (int i = 0; i < n; i++) {
				comps = 0; reads = 0;
				root = Delete(root, ascArr[del[i]]);
				avgComps += comps * 1.0 / n;
				avgReads += reads * 1.0 / n;
				avgHeight += Height(root) * 1.0 / n;
				maxComps = max(maxComps, comps);
				maxReads = max(maxReads, comps);
			}
			fileAsc << avgComps << " " << maxComps << " ";
			fileAsc << avgReads << " " << maxReads << " ";
			fileAsc << avgHeight << endl;

			// random array
			root = nullptr;
			avgComps = 0, avgReads = 0, avgHeight = 0;
			maxComps = 0, maxReads = 0;
			for (int i = 0; i < n; i++) {
				comps = 0; reads = 0;
				root = Insert(root, ranArr[i]);
				avgComps += comps * 1.0 / n;
				avgReads += reads * 1.0 / n;
				avgHeight += Height(root) * 1.0 / n;
				maxComps = max(maxComps, comps);
				maxReads = max(maxReads, comps);
			}
			fileRan << n << " ";
			fileRan << avgComps << " " << maxComps << " ";
			fileRan << avgReads << " " << maxReads << " ";
			fileRan << avgHeight << " " << Height(root) << " ";

			avgComps = 0, avgReads = 0, avgHeight = 0;
			maxComps = 0, maxReads = 0;
			for (int i = 0; i < n; i++) {
				comps = 0; reads = 0;
				root = Delete(root, ranArr[del[i]]);
				avgComps += comps * 1.0 / n;
				avgReads += reads * 1.0 / n;
				avgHeight += Height(root) * 1.0 / n;
				maxComps = max(maxComps, comps);
				maxReads = max(maxReads, comps);
			}
			fileRan << avgComps << " " << maxComps << " ";
			fileRan << avgReads << " " << maxReads << " ";
			fileRan << avgHeight << endl;
		}
	}

	fileAsc.close();
	fileRan.close();

	return 0;
}