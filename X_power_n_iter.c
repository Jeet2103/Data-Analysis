#include <stdio.h>

// Function for O(n) Time Complexity
long long compute_Xn_linear(int X, int n) {
    long long result = 1;
    for (int i = 0; i < n; ++i) {
        result *= X;
    }
    return result;
}

// Function for O(log n) Time Complexity
long long compute_Xn_logarithmic(int X, int n) {
    long long result = 1;
    while (n > 0) {
        if (n % 2 == 1) {
            result *= X;
        }
        X *= X;
        n /= 2;
    }
    return result;
}

int main() {
    // Example usage:
    int X = 10;
    int n = 5;

    // O(n) time complexity
    long long result_linear = compute_Xn_linear(X, n);
    printf("%d^%d = %lld\n", X, n, result_linear);

    // O(log n) time complexity
    long long result_logarithmic = compute_Xn_logarithmic(X, n);
    printf("%d^%d = %lld\n", X, n, result_logarithmic);

    return 0;
}
