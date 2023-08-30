#include <iostream>

using namespace std;

void calculate_knights_positions(int n) {
    for (int k = 1; k <= n; k++) {
        long long total_positions = (long long)k * k * ((k * k) - 1) / 2;
        long long attacking_positions = 4 * (k - 1) * (k - 2);
        cout << total_positions - attacking_positions << endl;
    }
}

int main() {
    int n;
    //cout << "Enter a number: ";
    cin >> n;
    calculate_knights_positions(n);
    return 0;
}