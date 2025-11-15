#include <iostream>
#include <cmath>
using namespace std;

long long movesCount(int n) {
    return pow(3, n) - 1;
}

void restrictedHanoi(int n, char A, char B, char C) {
    if (n == 0) return;
    restrictedHanoi(n - 1, A, B, C);
    cout << "move disk " << n << " from " << A << " to " << B << "\n";
    restrictedHanoi(n - 1, C, B, A);
    cout << "move disk " << n << " from " << B << " to " << C << "\n";
    restrictedHanoi(n - 1, A, B, C);
}

int main() {
    int n;
    cout << "Enter number of disks: ";
    cin >> n;

    cout << "Total moves = " << movesCount(n) << "\n";
    restrictedHanoi(n, 'A', 'B', 'C');
    return 0;
}
