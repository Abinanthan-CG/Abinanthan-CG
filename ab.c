#include<stdio.h>
#include<stdlib.h> // For abs()

int main() {
    int RQ[100], i, n, TotalHeadMoment = 0, initial;
    printf("Enter the number of Requests\n");
    scanf("%d", &n);
    printf("Enter the Requests sequence\n");
    for (i = 0; i < n; i++)
        scanf("%d", &RQ[i]);
    printf("Enter initial head position\n");
    scanf("%d", &initial);

    // logic for FCFS disk scheduling
    for (i = 0; i < n; i++) {
        TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);
        initial = RQ[i]; // Update the head position to the current request
    }

    printf("Total head moment is %d", TotalHeadMoment);
    return 0;
}