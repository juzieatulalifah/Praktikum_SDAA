#include <iostream>
using namespace std;

int pascal(int n, int k) {
    if (k == 0 or k == n) {
        return 1;
    }
    return pascal(n - 1, k - 1) + pascal(n - 1, k);
}

void segitiga(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            cout << pascal(i, j);
        }
        cout << endl;
    }
}

int main() {
    int tinggi = 3; 
    segitiga(tinggi);
    return 0;
}
