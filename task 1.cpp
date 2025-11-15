#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <string>
using namespace std;

// bubble sort
int bubble_sort_count(int arr[], int n) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            count++;
            if (arr[j] > arr[j + 1]) {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    return count;
}

// selection sort
int selection_sort_count(int arr[], int n) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            count++;
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            int t = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = t;
        }
    }
    return count;
}

// insertion sort
int insertion_sort_count(int arr[], int n) {
    int count = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            count++;
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    return count;
}

enum Pattern { RANDOM, SORTED, REVERSED };

string pattern_name(Pattern p) {
    if (p == RANDOM) return "random";
    if (p == SORTED) return "sorted";
    return "reversed";
}

vector<int> make_array(int n, Pattern p, mt19937 &rng) {
    vector<int> a(n);
    if (p == RANDOM) {
        uniform_int_distribution<int> d(0, 1000000);
        for (int i = 0; i < n; i++) a[i] = d(rng);
    } else if (p == SORTED) {
        for (int i = 0; i < n; i++) a[i] = i;
    } else { // REVERSED
        for (int i = 0; i < n; i++) a[i] = n - 1 - i;
    }
    return a;
}

//  sorter and measure comparisons & time
pair<int,double> run_and_time(int (*fn)(int[], int), const vector<int>& base) {
    vector<int> b = base;
    int *arr = &b[0];
    int n = (int)b.size();

    chrono::high_resolution_clock::time_point t0 = chrono::high_resolution_clock::now();
    int comps = fn(arr, n);
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

    chrono::duration<double> dt = t1 - t0;

    pair<int,double> res;
    res.first = comps;
    res.second = dt.count();
    return res;
}

void test_comparisons() {
    const int TRIALS = 30;
    const int MIN_N = 1;
    const int MAX_N = 30;

    ofstream compsCSV("comparisons.csv");
    ofstream timeCSV("times.csv");
    compsCSV << "Pattern,n,Algorithm,AvgComparisons\n";
    timeCSV  << "Pattern,n,Algorithm,AvgSeconds\n";

    mt19937 rng(1234567);

    vector<Pattern> pats;
    pats.push_back(RANDOM);
    pats.push_back(SORTED);
    pats.push_back(REVERSED);

    cout << "Task 1 (C++)\n";
    cout << "bubble / selection / insertion\n";
    cout << "patterns: random, sorted, reversed | sizes 1..30 | 30 trials\n\n";

    for (size_t pi = 0; pi < pats.size(); ++pi) {
        Pattern p = pats[pi];
        cout << "Pattern: " << pattern_name(p) << "\n";

        for (int n = MIN_N; n <= MAX_N; n++) {
            double sumCB = 0, sumTB = 0;
            double sumCS = 0, sumTS = 0;
            double sumCI = 0, sumTI = 0;

            for (int t = 0; t < TRIALS; t++) {
                vector<int> base = make_array(n, p, rng);

                pair<int,double> r1 = run_and_time(bubble_sort_count, base);
                sumCB += r1.first; sumTB += r1.second;

                pair<int,double> r2 = run_and_time(selection_sort_count, base);
                sumCS += r2.first; sumTS += r2.second;

                pair<int,double> r3 = run_and_time(insertion_sort_count, base);
                sumCI += r3.first; sumTI += r3.second;
            }

            double aCB = sumCB / TRIALS, aTB = sumTB / TRIALS;
            double aCS = sumCS / TRIALS, aTS = sumTS / TRIALS;
            double aCI = sumCI / TRIALS, aTI = sumTI / TRIALS;

            cout << "n=" << n
                 << "  bubble comps=" << (int)aCB << " time=" << aTB
                 << "  selection comps=" << (int)aCS << " time=" << aTS
                 << "  insertion comps=" << (int)aCI << " time=" << aTI << "\n";

            string pat = pattern_name(p);
            compsCSV << pat << "," << n << ",bubble,"    << aCB << "\n";
            compsCSV << pat << "," << n << ",selection," << aCS << "\n";
            compsCSV << pat << "," << n << ",insertion," << aCI << "\n";

            timeCSV  << pat << "," << n << ",bubble,"    << aTB << "\n";
            timeCSV  << pat << "," << n << ",selection," << aTS << "\n";
            timeCSV  << pat << "," << n << ",insertion," << aTI << "\n";
        }
        cout << "\n";
    }

    compsCSV.close();
    timeCSV.close();
    cout << "wrote: comparisons.csv and times.csv\n";
}

int main() {
    test_comparisons();
    return 0;
}
