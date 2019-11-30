/*
 * Akinator.h
 *
 *  Created on: Nov 30, 2019
 *      Author: artem
 */

#ifndef AKINATOR_H_
#define AKINATOR_H_

#include <stdio.h>

#define MAX_NAME_LEN 256
#define MAX_NUM_OF_NODES 512

typedef struct _tnode {
    char name[MAX_NAME_LEN];
    struct _tnode* left;
    struct _tnode* right;
} tnode;

enum {
    LEFT = -1,
    RIGHT = 1
};

int Ask(const tnode nod);
int Guess(tnode* nod);
int GetNewNode(tnode* nod);
void FPrintNode(const tnode tree, FILE* fd);

#endif /* AKINATOR_H_ */
