/* 
 * Pietro Baggetta
 * 1092160
 * March 28, 2022
 * CIS*3490 Assignment 4
 * Main File
*/

#include "myHeader.h"

struct inputText getInputText() {

    FILE *file;
    struct inputText inputText;
    char word[100];
    bool insert;

    /* Read in file */
    file = fopen ("data_A4_Q1.txt", "rb");
    fseek (file, 0, SEEK_SET);

    inputText.words = (struct word*) malloc (0);
    inputText.numDiffWords = 0;
    inputText.totalWords = 0;

    while (!feof (file)) {
        /* Scanf current word */
        fscanf (file, "%s", word);
        insert = true;
        int i = 0;
        inputText.totalWords++;

        /* Compare to make sure the word is not already in the array */
        while ((i < inputText.numDiffWords) && (insert == true)) {
            /* If the array has the word, increase the number of repetitions */
            if (strcmp (inputText.words[i].p, word) == 0) {
                insert = false;
                inputText.words[i].repetitions++;
            }
            i++;
        }

        /* If the word is not in the array, add it to the array */
        if (insert == true) {
            inputText.words = (struct word*) realloc (inputText.words, (inputText.numDiffWords + 1) * sizeof (struct word));
            inputText.words[inputText.numDiffWords].p = (char *) malloc ((strlen (word)) * sizeof (char));
            strcpy (inputText.words[inputText.numDiffWords].p, word);
            inputText.words[inputText.numDiffWords].repetitions = 1;
            inputText.numDiffWords++;
        }
    }

    /* Find the probability of each word in the array */
    for (int i = 0; i < inputText.numDiffWords; i++) {
        inputText.words[i].prob = (float) inputText.words[i].repetitions / inputText.totalWords;
    }

    fclose (file);

    /* Sort the tree so the highest probability is at the root */
    inputText = sortArray (inputText);

    return inputText;
}

struct inputText sortArray (struct inputText array) {
    
    int min;
    struct word temp;

    /* Go through the tree and sort it */
    for (int i = 0; i < array.numDiffWords - 1; i++) {
        min = i;
        for (int j = i + 1; j < array.numDiffWords; j++) {
            if (strcmp (array.words[min].p, array.words[j].p) > 0) {
                min = j;
            }
        }
        /* Swap */
        temp = array.words[i];
        array.words[i] = array.words[min];
        array.words[min] = temp;
    }
    return array;
}

void bstSearch (struct treeNode *node, char *userKey, int type) {

    if (node == NULL) {
        /* No word to be found */
        printf ("Not found.\n");
        return;
    }

    if (type == 1) {
        /* Print comparison for Q1.1 */
        printf ("Compared with %s (%.3f), ", node -> word -> p, node -> word -> avgNumComp);
    } else if (type == 2) {
        /* Print comparison for Q1.2 */
        printf ("Compared with %s (%.3f), ", node -> word -> p, node -> word -> prob);
    }

    if (strcmp (node -> word -> p, userKey) == 0) {
        /* Word is found */
        printf ("found.\n");
    } else if (strcmp (node -> word -> p, userKey) > 0) {
        /* Need to go left in the subtree */
        printf ("go left subtree.\n");
        bstSearch (node -> lChild, userKey, type);
    } else {
        /* Need to go right in the subtree */
        printf ("go right subtree.\n");
        bstSearch (node -> rChild, userKey, type);
    }
}

int main (int argc, char *argv[]) {
    
    double time1 = 0.0, time2 = 0.0, time3 = 0.0, time4 = 0.0;
    char userKey[100], fileName[100];
    int userSelection;
    struct inputText inputText;
    struct treeNode *rootNode;

    printf ("--------------------------------------------------\n");
    printf ("| Option 1: BST using dynamic programming (Q1.1) |\n");
    printf ("| Option 2: BST using greedy technique    (Q1.2) |\n");
    printf ("| Option 3: Gale-Shapely stable marriage  (Q2)   |\n");
    printf ("--------------------------------------------------\n");

    /* Ask user to choice of option */
    printf ("Choose an option.\n");
    scanf ("%d", &userSelection);

    if (userSelection < 1 || userSelection > 3) {
        printf ("Invalid option\n");
        return 0;
    }

    if (userSelection == 1 || userSelection == 2) {
        printf ("Enter a key: ");
        scanf ("%s", userKey);
        printf ("\n");

        /* Read in the text file */
        inputText = getInputText();
    }

    if (userSelection == 1) {
        rootNode = P11 (inputText);
    } else if (userSelection == 2) {
        rootNode = NULL;
        rootNode = P12 (inputText, rootNode, 0, inputText.numDiffWords - 1);
    }

    /* Search for the key in Q1.1 and Q1.2 */
    if (userSelection == 1 || userSelection == 2) {
        bstSearch (rootNode, userKey, userSelection);
    }

    /* Stable Marriage */
    if (userSelection == 3) {
        printf ("Enter the name of the file: ");
        scanf ("%s", fileName);

        P2 (fileName);
    }

    return 0;
}
