/*
 * Akinator.c
 *
 *  Created on: Nov 30, 2019
 *      Author: artem
 */

#include "Akinator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

int Guess(tnode* nod) {
    assert(nod != NULL);
    if(Ask(*nod) == LEFT) {
        if(nod->left != NULL) Guess(nod->left);
        else {
            printf("ИИ рулит!\n");
            return 0;
        }
    }
    else {
        if(nod->right != NULL) Guess(nod->right);
        else {
            GetNewNode(nod);
        }
    }
    return 0;
}

int Ask(const tnode nod) {
    //puts("Дайте-ка подумаю...\n");
    //sleep(3);
    printf("Тот, кого вы загадали %s?(y = yes, y = no)\n", nod.name);
    char answer[3];
    while(1) {
        fgets(answer, 3, stdin);
        if(strcmp("y", answer) == 0)
            return LEFT;
        else if(strcmp("n", answer) == 0)
            return RIGHT;
        else
            printf("Введите y в случае положителього ответа, или n в противном!\n");
    }
    //return 0;
}

int GetNewNode(tnode* nod) {
    printf("Чем Ваше слово отличается от %s? (введите 1-2 слова, не используя частицу \"нет\")", nod->name);
    char difference[MAX_NAME_LEN];
    char answer[MAX_NAME_LEN];
    if(fgets(difference, MAX_NAME_LEN, stdin) != NULL) {
        if(fgets(answer, MAX_NAME_LEN, stdin) != NULL) {
            tnode *node = (tnode*) calloc(2, sizeof(tnode));

            strcpy(node[0].name, answer);
            node[0].left = NULL;
            node[0].right = NULL;

            strcpy(node[1].name, nod->name);
            node[1].left = NULL;
            node[1].right = NULL;

            strcpy(nod->name, difference);
            nod->left = node;
            nod->right = node+1;
            return 0;
        }
        fputs("Загаданное слово не было получено!:(\n", stderr);
        return -1;
    }
    fputs("Взаимодействие с ИИ и человеком нарушено!(\n", stderr);
    return -2;
}

int SaveTree(const tnode tree, char* filename) {
    assert(filename != NULL);
    FILE* fd;
    if((fd = fopen(filename, "w")) == NULL) {
        perror("fopen");
        return -1;
    }
    tnode queue[MAX_NUM_OF_NODES];
    queue[0] = tree;
    FPrintNode(tree, fd);
    return 0;
}

void FPrintNode(const tnode tree, FILE* fd) {
    assert(fd != NULL);
    fprintf(fd, "%s\n", tree.name);
    if(tree.left != NULL)
        FPrintNode(*tree.left, fd);
    if(tree.right != NULL)
        FPrintNode(*tree.right, fd);
    return;
}

tnode* TreeConstruct(char* filename) {
    assert(filename != NULL);
    FILE* fd;
    if((fd = fopen(filename, "r")) == NULL) {
        perror("fopen");
        return -1;
    }
    tnode* nod;
    FScanNode(nod, fd);

}

int FScanNode(tnode* nod, FILE* fd) {
    assert(fd != NULL);
    assert(nod != NULL);
    fgets(nod->name, MAX_NAME_LEN, fd);

}
