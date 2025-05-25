#include <stdio.h>
#include <conio.h>

void main()
{
    int r[1][10], av[1][10];
    int all[10][10], max[10][10], ne[10][10], w[10], safe[10];
    int i = 0, j = 0, k = 0, l = 0, np = 0, nr = 0, count = 0, cnt = 0;
    int pass_found_process;

    clrscr();

    printf("Enter the number of processes in a system: ");
    scanf("%d", &np);
    printf("Enter the number of resources in a system: ");
    scanf("%d", &nr);

    for (i = 1; i <= nr; i++) {
        printf("\nEnter the number of instances of resource R%d: ", i);
        scanf("%d", &r[0][i]);
        av[0][i] = r[0][i];
    }

    for (i = 1; i <= np; i++) {
        w[i] = 0;
    }

    printf(" \nEnter the allocation matrix:\n");
    for (i = 1; i <= np; i++) {
        printf("P%d: ", i);
        for (j = 1; j <= nr; j++) {
            scanf("%d", &all[i][j]);
            av[0][j] = av[0][j] - all[i][j];
        }
    }

    printf("\nEnter the maximum matrix:\n");
    for (i = 1; i <= np; i++) {
        printf("P%d: ", i);
        for (j = 1; j <= nr; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    for (i = 1; i <= np; i++) {
        for (j = 1; j <= nr; j++) {
            ne[i][j] = max[i][j] - all[i][j];
            if (ne[i][j] < 0) {
                 printf("\nError: P%d has Allocation > Max for R%d. Input is inconsistent.\n", i, j);
                 printf("Max[%d][%d]=%d, Allocation[%d][%d]=%d\n", i,j,max[i][j], i,j,all[i][j]);
                 getch();
                 return;
            }
        }
    }

    printf("\n--- Process Details & Need Matrix ---\n");
    for (i = 1; i <= np; i++) {
        printf("Process P%d:\n", i);
        for (j = 1; j <= nr; j++) {
            printf("  R%d: allocated %d, maximum %d, need %d\n", j, all[i][j], max[i][j], ne[i][j]);
        }
    }

    printf("\nInitial Availability Vector:\n");
    for (i = 1; i <= nr; i++) {
        printf("R%d: %d  ", i, av[0][i]);
    }
    printf("\n");

    printf("\n--- Safe Sequence Check ---\n");
    k = 0;
    count = 0;

    for (l = 1; l <= np; l++) {
        pass_found_process = 0;
        for (i = 1; i <= np; i++) {
            if (w[i] == 0) {
                cnt = 0;
                for (j = 1; j <= nr; j++) {
                    if (ne[i][j] <= av[0][j]) {
                        cnt++;
                    }
                }
                if (cnt == nr) {
                    k++;
                    safe[k] = i;
                    printf("P%d can be allocated. Work becomes: ", i);
                    for (j = 1; j <= nr; j++) {
                        av[0][j] = av[0][j] + all[i][j];
                        printf("R%d: %d  ", j, av[0][j]);
                    }
                    printf("\n");
                    w[i] = 1;
                    count++;
                    pass_found_process = 1;
                }
            }
        }
        if (pass_found_process == 0 && count < np) {
            break;
        }
    }

    if (count == np) {
        printf("\nSystem is in a SAFE state.\nSafe sequence is: ");
        for (i = 1; i <= np; i++) {
            printf("P%d ", safe[i]);
        }
        printf("\n");
    } else {
        printf("\nSystem is in an UNSAFE state.\n");
        printf("%d out of %d processes could be allocated.\n", count, np);
        if (count > 0) {
            printf("Partial safe sequence: ");
            for (i = 1; i <= count; i++) {
                 printf("P%d ", safe[i]);
            }
            printf("\n");
        }
    }

    getch();
}
