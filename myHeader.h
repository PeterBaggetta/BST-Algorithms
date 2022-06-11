#ifndef _MYHEADER_H
#define _MYHEADER_H

/* Header files used */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Structs used */
typedef struct word {
    char *p;
    int repetitions;
    float prob;
    float avgNumComp;
} word;

typedef struct inputText {
    struct word *words;
    int numDiffWords;
    int totalWords;
} inputText;

typedef struct treeNode {
    struct word *word;
    struct treeNode *rChild;
    struct treeNode *lChild;
} treeNode;

/* Main functions */
struct inputText getInputText();
struct inputText sortArray (struct inputText array);
void bstSearch (struct treeNode *node, char *userKey, int type);

/* P11 functions */
struct treeNode *P11 (struct inputText inputText);
struct treeNode *optimizeBST (struct treeNode *node, struct inputText inputText, int i, int j, float **avgRootTable, int **rootTable);

/* P12 functions */
struct treeNode *P12 (struct inputText inputText, struct treeNode *root, int l, int r);

/* P2 functions */
bool wPrefer (int info[200][200], int w, int m, int m2, int n);
void P2 (char *fileName);


#endif
