#include <stdio.h>
#include <conio.h> // For clrscr() and getch()

// Manual uses main() which defaults to int in modern C,
// but void main() was common in old Turbo C.
// For better compatibility, let's use int main()
int main() {
    int s[10], p[10], n, i, j, w1 = 0, w[10], t[10], st[10], tq, tst = 0;
    int tt = 0, tw = 0; // Total turnaround, total waiting
    float aw, at;     // Average waiting, average turnaround

    clrscr(); // Clear screen

    printf("Enter no. of processes: "); // Manual says "processes \n"
    scanf("%d", &n);

    // The manual code asks for time quantum after process details,
    // but it's usually asked before. Let's stick to manual order.

    printf("\nEnter the process & service time of each process separated by a space\n");
    // Manual asks for p[i] but doesn't seem to use it beyond potential display.
    // We'll read it but mostly use index i for process identification.
    for (i = 0; i < n; i++) {
        // printf("Process P%d (ID BurstTime): ", i); // More user-friendly prompt
        scanf("%d%d", &p[i], &s[i]); // p[i] is process ID, s[i] is service time
    }

    printf("\nEnter the time quantum: "); // Manual says "\n Enter the time quantum \n"
    scanf("%d", &tq);


    for (i = 0; i < n; i++) {
        st[i] = s[i]; // Store original service time
        tst = tst + s[i]; // Calculate total service time needed by all processes
    }

    // The manual's outer loop for(j=0; j<tst; j++) is a bit misleading.
    // The simulation runs until all processes are complete, driven by quanta.
    // A better loop condition is until remaining service time for all s[i] is 0.
    // Or, more simply, iterate enough times based on tst and tq.
    // The manual's double loop for(j=0;j<tst;j++) for(i=0;i<n;i++) will execute
    // the inner process loop tst times, which is not correct for RR logic based on quanta.
    // Let's try to replicate the *intended* behavior of processing in quanta.

    w1 = 0; // current time
    int all_done;
    do {
        all_done = 1; // Assume all processes are done
        for (i = 0; i < n; i++) {
            if (s[i] > 0) { // If process still has burst time remaining
                all_done = 0; // At least one process is not done
                if (s[i] > tq) {
                    w1 = w1 + tq;
                    s[i] = s[i] - tq;
                    // For RR, turnaround/waiting is calculated at completion.
                    // The manual's intermediate t[i]=w1 is more like completion time of a slice.
                    // We'll calculate final t[i] and w[i] when s[i] becomes 0.
                } else { // s[i] <= tq and s[i] > 0
                    w1 = w1 + s[i];
                    t[i] = w1;          // Final Turnaround Time for process i
                    w[i] = t[i] - st[i]; // Final Waiting Time for process i
                    s[i] = 0;           // Process i is finished
                }
            }
        }
    } while (all_done == 0);


    printf("\nProcess\tService Time(st)\tWaiting Time(wt)\tTurnaround Time(tt)\n");
    // The manual uses p[i] for process ID display.
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t\t%d\t\t\t%d\n", p[i], st[i], w[i], t[i]);
        tw = tw + w[i];
        tt = tt + t[i];
    }

    aw = (float)tw / n;
    at = (float)tt / n;

    printf("\nAverage Waiting Time (awt) = %.2f\n", aw); // Manual: awt=%f\n
    printf("Average Turnaround Time (att) = %.2f\n", at); // Manual: att=%f\n

    getch(); // Wait for key press
    return 0;
}