/* 
* Pietro Baggetta
* 1092160
* March 28, 2022
* CIS*3490 Assignment 4
* Question 1.2: Optimal BST using Greedy Technique
*/

#include "myHeader.h"

struct treeNode *P12 (struct inputText inputText, struct treeNode *root, int l, int r) {
    
    int index;
    float maxProb;

    index = l;
    maxProb = inputText.words[l].prob;

    /* Check if we are at the last element in the tree, if so make space */
    if ((l == 0) && (r == inputText.numDiffWords - 1)) {
        root = (struct treeNode*) malloc (sizeof (struct treeNode));
    }

    /* Find the highest probability and its index */
    for (int i = l; i <= r; i++) {
        if (inputText.words[i].prob > maxProb) {
            maxProb = inputText.words[i].prob;
            index = i;
        }
    }

    /* Make the root the word with highest probability */
    root -> word = &inputText.words[index];

    if (l == r) {
        /* All nodes analized and tree is done */
        root -> lChild = NULL;
        root -> rChild = NULL;
        return root;
    } else if (r == index) {
        /* Right branch doesnt exist but left does */
        root -> rChild = NULL;
        root -> lChild = (struct treeNode *) malloc (sizeof (struct treeNode));
        root -> lChild = P12 (inputText, root -> lChild, l + 1, r);
    } else if (l == index) {
        /* Left branch doesnt exist but right does */
        root -> lChild = NULL;
        root -> rChild = (struct treeNode *) malloc (sizeof (struct treeNode));
        root -> rChild = P12 (inputText, root -> rChild, l, r - 1);
    } else {
        /* Left and right branch exist */
        root -> lChild = (struct treeNode *) malloc (sizeof (struct treeNode));
        root -> lChild = P12 (inputText, root -> lChild, l, index - 1);
        root -> rChild = (struct treeNode *) malloc (sizeof (struct treeNode));
        root -> rChild = P12 (inputText, root -> rChild, index + 1, r);
    }

    return root;
}
