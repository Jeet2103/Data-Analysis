#include <stdio.h>
#include<time.h>
void tower_of_hanoi(int num_disks, char source_rod, char destination_rod, char auxiliary_rod) {
    if (num_disks == 1) {
        printf("Move disk from rod %c to rod %c\n", source_rod, destination_rod);
        
    }
    else{

    tower_of_hanoi(num_disks - 1, source_rod, auxiliary_rod, destination_rod);
    tower_of_hanoi(1,source_rod,destination_rod,auxiliary_rod);
    tower_of_hanoi(num_disks - 1, auxiliary_rod, destination_rod, source_rod);
}
}

int main() {
    int number_of_disks;

    printf("Enter the number of disks: ");
    scanf("%d", &number_of_disks);

    if (number_of_disks <= 0) {
        printf("Invalid number of disks. Please enter a positive integer.\n");
        return 1;
    }
    clock_t end,start;
    start=clock();

    tower_of_hanoi(number_of_disks, 'A', 'C', 'B'); // Assuming A is the source, C is the destination, and B is the auxiliary rod
    end= clock();
    double t = 1.0*((end-start)/CLOCKS_PER_SEC);
    printf("%lf",t);
    return 0;
}
