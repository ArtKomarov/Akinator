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

typedef struct _tqueue {
    tnode *tree[MAX_NUM_OF_NODES];
    int cur;
    int size;
} tqueue;

enum {
    LEFT = -1,
    RIGHT = 1
};

int Ask(const tnode nod);
int Guess(tnode* nod);
int GetNewNode(tnode* nod);
int FPrintNode(tqueue *queue, FILE* fd);
int QueuePush(tqueue* queue, tnode* nod1);

tnode* TreeConstruct(char* filename);
int FScanNode(tnode* nod, char* CurStr, FILE* fd);

int SaveTree(tnode* tree, char* filename);
tnode* MakeBinTree(tqueue* queue);
int TreeDestruct(tnode* node);
int TreeDestructChilds(tnode* node);

int MakeGraphFile(tnode* tree, char* FileName);
int FPrintGraphNode(tnode* node, FILE* fd);

int FPrintLeftNode(tnode *node, FILE* fd);
int FPrintRightNode(tnode *node, FILE* fd);

#endif /* AKINATOR_H_ */
