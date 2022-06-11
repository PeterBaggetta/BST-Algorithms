/* 
* Pietro Baggetta
* 1092160
* March 28, 2022
* CIS*3490 Assignment 4
* Question 2: Gale-Shapely Stable Marriage Algorithm
*/

#include "myHeader.h"

bool wPrefer (int info[200][200], int w, int m, int m2, int n) {

    for (int i = 0; i < n; i++) {
        if (info[w + n - 1][i] == m2 + 1) {
            /* Old engagement is prefereble to woman, no swap */
            return true;
        }

        if (info[w + n - 1][i] == m + 1) {
            /* Old engagement is not prefereble to woman, swap */
            return false;
        }
    }
    return false;
}

void P2 (char *fileName) {

    FILE *file = fopen (fileName, "r");
    if (file == NULL) {
        printf ("Invalid file name.\n");
        return;
    }

    int info[200][200];
    int number[100], n;

    /* Read the n value from the file */
    fscanf (file, "%d", number);
    n = *number;
    int i = 0;

    /* Read in the file to an array */
    for (i = 0; i < n * 2; i++) {
        for (int j = 0; j < n; j++) {
            fscanf (file, "%d", number);
            info[i][j] = *number;
        }
    }

    /* Initialize all free men and women parter arrays */
    int wPartner[n], freeCounter = n;
    bool freeMale[n];

    for (int i = 0; i < n; i++) {
        wPartner[i] = -1;
        freeMale[i] = false;
    }

    /* Continue to run while there are still free men */
    while (freeCounter > 0) {
        int m;
        /* Find the first free male */
        for (m = 0; m < n; m++) {
            if (freeMale[m] == false) {
                break;
            }
        }

        /* Go through the mens preference of women and pick one at a time */
        for (int i = 0; i < n && freeMale[m] == false; i++) {
            int w = info[m][i];
            if (wPartner[w - 1] == -1) {
                /* Woman is free so male is engaged (not married) */
                wPartner[w - 1] = m;
                freeMale[m] = true;
                freeCounter--;
            } else {
                /* Woman is not free, so check who the woman prefers */
                int m2 = wPartner[w - 1];
                if (wPrefer (info, w, m, m2, n) == false) { 
                    /* Swap men with woman is she prefers one over another */
                    wPartner[w - 1] = m;
                    freeMale[m] = true;
                    freeMale[m2] = false;
                }
            }
        }
    }

    /* Print the output of marriage */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (wPartner[i] == j) {
                printf ("1 ");
            } else {
                printf ("0 ");
            }
        }
        printf ("\n");
    }

    fclose (file);
}
