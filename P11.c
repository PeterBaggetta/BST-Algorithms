/* 
* Pietro Baggetta
* 1092160
* March 28, 2022
* CIS*3490 Assignment 4
* Question 1.1: Optimal BST using Dynamic Programming
*/

#include "myHeader.h"

struct treeNode *P11 (struct inputText inputText) {

    int i, j, k, d, s, n;
    float minValue, sum;
    float **C;
    int **R;
    int kMin;

    struct treeNode *root;

    n = inputText.numDiffWords;
    root = (struct treeNode *) malloc (sizeof (struct treeNode));

    /* Allocate space for tables and root */
    C = (float **) malloc ((n + 1) * sizeof (float *));
    R = (int **) malloc ((n + 1) * sizeof (int *));

    for (i = 0; i <= n; i++) {
        C[i] = (float *) malloc ((n + 1) * sizeof (float));
        R[i] = (int *) malloc ((n + 1) * sizeof (int));
    }
    /* Initialize tables with zeros */
    for (i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            C[i][j] = 0;
            R[i][j] = 0;
        }
    }

    /* Initial diagonal */
    for (i = 0; i <= n; i++) {
        C[i][i + 1] = inputText.words[i].prob;
        R[i][i + 1] = i + 1;
    }

    /* All other diagonals of the tables */
    for (d = 2; d <= n; d++) {
        for (i = 0; i <= n - d; i++) {
            j = i + d;
            minValue = 9999999999;

            /* Search for smallest sum */
            for (k = i; k < j; k++) {
                if ((C[i][k] + C[k + 1][j]) < minValue) {
                    minValue = C[i][k] + C[k + 1][j];
                    kMin = k;
                }
            }

            R[i][j] = kMin + 1;

            sum = inputText.words[i].prob;
            for (s = i + 1; s < j; s++) {
                sum += inputText.words[s].prob;
            }
            C[i][j] = minValue + sum;
        }
    }

    /* Shift R so it is easier to index through for program */
    for (i = n; i > 0; i--) { 
        for (j = 0; j <= n; j++) {
            R[i][j] = R[i - 1][j];
        }
    }

    root = optimizeBST (root, inputText, 1, n, C, R);

    return root;
}

struct treeNode *optimizeBST (struct treeNode *node, struct inputText inputText, int i, int j, float **C, int **R) {

    /* Represents root of the optimied subtree */
    int k;
    k = R[i][j];

    node -> word = &inputText.words[k - 1];
    node -> word -> avgNumComp = C[i][j];

    if (i < k && k < j) {
        /* Left and right subtrees have nodes left to assign */
        node -> lChild = (struct treeNode *) malloc (sizeof (struct treeNode));
        node -> lChild = optimizeBST (node -> lChild, inputText, i, k - 1, C, R);
        node -> rChild = (struct treeNode *) malloc (sizeof (struct treeNode));
        node -> rChild = optimizeBST (node -> rChild, inputText, k + 1, j, C, R);
    } else if (i == j && i == k) {
        /* No more nodes to be assigned */
        node -> lChild = NULL;
        node -> rChild = NULL;
    } else if (k == i) {
        /* Left has no more to be assigned but right does */
        node -> lChild = NULL;
        node -> rChild = (struct treeNode *) malloc (sizeof (struct treeNode));
        node -> rChild = optimizeBST (node -> rChild, inputText, i + 1, j, C, R);
    } else if (k == j) {
        /* Right has no more to be assigned but left does */
        node -> rChild = NULL;
        node -> lChild = (struct treeNode *) malloc (sizeof (struct treeNode));
        node -> lChild = optimizeBST (node -> lChild, inputText, i, j - 1, C, R);
    }

    return node;
}
