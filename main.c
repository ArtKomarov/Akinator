/*
 * main.c
 *
 *  Created on: Nov 30, 2019
 *      Author: artem
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Akinator.h"

int main() {
    /*tnode* tree = (tnode*)calloc(1, sizeof(tnode));
    strcpy(tree->name, "Одушевленное");
    tnode* nod = (tnode*)calloc(2, sizeof(tnode));
    tree->left = nod;
    tree->right = nod + 1;
    strcpy(tree->left->name, "Кот");
    strcpy(tree->right->name, "Ноутбук");*/
    //int i = 1;
    tnode* tree = TreeConstruct("Tr2.txt");
    while(1) {
        Guess(tree);
        puts("Are you wont to continue? (y = yes)");
        char con[126];
        fgets(con, 126, stdin);
        if(strcmp(con, "y\n") == 0)
            continue;
        else {
            if(strcmp(con, "n\n") == 0)
                break;
            puts("To continue you must enter \"y\" and press enter, but you did't do this, so you left from game!");
            break;
        }
    }
    MakeGraphFile(tree, "GrTree.dot");
    SaveTree(tree, "Tr2.txt");
    TreeDestruct(tree);
    return 0;
}
