#include <stdio.h>

int fibonacci_iterative(int n) {
    if (n <= 1) {
        return n;
    }

    int a = 0, b = 1, c, comparisons = 0;
    for (int i = 2; i <= n; i++) {
        comparisons += 2; // Increment for loop condition and update
        c = a + b;
        a = b;
        b = c;
        printf("%d\n",c);
    }

    printf("Iterative approach comparisons: %d\n", comparisons);
    return c;
}

int fibonacci_recursive(int n, int depth, int *comparisons) {
    if (n <= 1) {
        return n;
    } else {
        (*comparisons)++; // Increment for base case comparison
        int a = fibonacci_recursive(n - 1, depth + 1, comparisons);
        (*comparisons)++; // Increment for another comparison
        int b = fibonacci_recursive(n - 2, depth + 1, comparisons);
        *comparisons += 2; // Two more comparisons in this function
        return a + b;
    }
}

int main() {
    int n, choice;

    do {
        printf("\nMenu:\n");
        printf("1. Iterative approach\n");
        printf("2. Recursive approach\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value of n: ");
                scanf("%d", &n);
                printf("The nth Fibonacci number (iterative) is: %d\n", fibonacci_iterative(n));
                break;
            case 2:
                printf("Enter the value of n: ");
                scanf("%d", &n);
                int comparisons = 0;
                printf("The nth Fibonacci number (recursive) is: %d\n", fibonacci_recursive(n, 0, &comparisons));
                printf("Recursive approach comparisons: %d\n", comparisons);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);

    return 0;
}
