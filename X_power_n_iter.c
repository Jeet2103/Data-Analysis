#include <stdio.h>

// Function for O(n) Time Complexity
long long compute_Xn_linear(int X, int n) {
    long long result = 1;
    int comp=0;
    for (int i = 0; i < n; ++i) {
        result *= X;
        comp++;
    }
    printf("The Number of comparision is : \t%d\n",comp);
    return result;
}

// Function for O(log n) Time Complexity
long long compute_Xn_logarithmic(int X, int n) {
    long long result = 1;
    int comp=0;
    while (n > 0) {
        if (n % 2 == 1) {
            result *= X;
        }
        X *= X;
        n /= 2;
        comp++;
    }
    printf("The Number of comparision is : \t%d\n",comp);
    return result;
}

int main() {
    // Example usage:
    int X = 2;
    int n = 10;

    // O(n) time complexity
    long long result_linear = compute_Xn_linear(X, n);
    printf("%d^%d = %lld\n", X, n, result_linear);

    // O(log n) time complexity
    long long result_logarithmic = compute_Xn_logarithmic(X, n);
    printf("%d^%d = %lld\n", X, n, result_logarithmic);

    return 0;
}
