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
    printf("Тот, кого вы загадали %s?(y = yes, n = no)\n", nod.name);
    char answer[3];
    while(1) {
        fgets(answer, 3, stdin);
        if(strcmp("y\n", answer) == 0)
            return LEFT;
        else if(strcmp("n\n", answer) == 0)
            return RIGHT;
        else
            printf("Введите y в случае положителього ответа, или n в противном!\n");
    }
    //return 0;
}

int GetNewNode(tnode* nod) {
    printf("Чем Ваше слово отличается от %s? (введите 1-2 слова, не используя частицу \"нет\")\n", nod->name);
    char difference[MAX_NAME_LEN];
    char answer[MAX_NAME_LEN];
    if(fgets(difference, MAX_NAME_LEN, stdin) != NULL) {
        puts("А что Вы загадали?");
        if(fgets(answer, MAX_NAME_LEN, stdin) != NULL) {
            tnode *node = (tnode*) calloc(2, sizeof(tnode));

            int answlen = strlen(answer);
            if(answer[answlen - 1] == '\n')
                answer[answlen - 1] = '\0';
            strcpy(node[0].name, answer);
            node[0].left = NULL;
            node[0].right = NULL;

            strcpy(node[1].name, nod->name);
            node[1].left = NULL;
            node[1].right = NULL;

            int diflen = strlen(difference);
            if(difference[diflen - 1] == '\n')
                difference[diflen - 1] = '\0';
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

int SaveTree(tnode* tree, char* filename) {
    assert(filename != NULL);
    FILE* fd;
    if((fd = fopen(filename, "w")) == NULL) {
        perror("fopen");
        return -1;
    }
    //tqueue queue;
    //queue.tree[0] = tree;
    //queue.size = 1;
    //queue.cur = 0;
    //printf("%s\n", queue->tree[queue->cur]->name);
    fprintf(fd, "%s\n", tree->name);
    FPrintLeftNode(tree->left, fd);
    FPrintRightNode(tree->right, fd);
    fclose(fd);
    return 0;
}

int FPrintNode2(tqueue *queue, FILE* fd) {
    assert(fd != NULL);
    assert(queue != NULL);
    if(queue->cur >= queue->size) return 0;
    printf("%s\n", queue->tree[queue->cur]->name);
    fprintf(fd, "%s\n", queue->tree[queue->cur]->name);
    if(queue->tree[queue->cur]->left != NULL)
        if(QueuePush(queue, queue->tree[queue->cur]->left) != 0)
            return -1;
    if(queue->tree[queue->cur]->right != NULL)
        if(QueuePush(queue, queue->tree[queue->cur]->right) != 0)
            return -1;
    queue->cur++;
    FPrintNode2(queue, fd);
    return 0;
}

int FPrintLeftNode(tnode *node, FILE* fd) {
    assert(fd != NULL);
    assert(node != NULL);
    printf("(%s\n", node->name);
    fprintf(fd, "(%s\n", node->name);
    if(node->left != NULL)
        FPrintLeftNode(node->left, fd);
    if(node->right != NULL)
        FPrintRightNode(node->right, fd);
    return 0;
}

int FPrintRightNode(tnode *node, FILE* fd) {
    assert(fd != NULL);
    assert(node != NULL);
    printf(",%s\n", node->name);
    fprintf(fd, ",%s\n", node->name);
    if(node->left != NULL)
        FPrintLeftNode(node->left, fd);
    if(node->right != NULL)
        FPrintRightNode(node->right, fd);
    printf(")\n");
    fprintf(fd, ")\n");
    return 0;
}

tnode* TreeConstruct(char* filename) {
    assert(filename != NULL);
    FILE* fd;
    if((fd = fopen(filename, "r")) == NULL) {
        perror("fopen");
        return NULL;
    }
    //tqueue queue;
    tnode* nod = (tnode*)calloc(1, sizeof(tnode));
    //if(fgets(nod->name, MAX_NAME_LEN, fd) == NULL)
    //    return -1;
    nod->left = NULL;
    nod->right = NULL;
    if(fgets(nod->name, MAX_NAME_LEN, fd) == NULL) {
        fclose(fd);
        return NULL;
    }
    int Len = strlen(nod->name);
    if(Len > 0 && nod->name[Len - 1] == '\n')
        nod->name[Len - 1] = '\0';
    char buff[MAX_NAME_LEN+1];
    FScanNode(nod, buff, fd);
    //queue.cur = 0;
    fclose(fd);
    return nod;
}

int FScanNode(tnode* nod, char* CurStr, FILE* fd) {
    assert(fd  != NULL);
    assert(nod != NULL);
    //char buff[MAX_NAME_LEN+1];
    if(fgets(CurStr, MAX_NAME_LEN + 1, fd) == NULL || CurStr[0] == '\n') {
        nod = NULL;
    }
    else {
        int BuffLen = strlen(CurStr);
        if(BuffLen > 0 && CurStr[BuffLen - 1] == '\n')
            CurStr[BuffLen - 1] = '\0';
        if(CurStr[0] != '(')
            return 0;
        else {
            tnode* nod2 = (tnode*)calloc(2, sizeof(tnode));
            nod->left = nod2;
            nod->right = nod2 + 1;
            strcpy(nod->left->name, CurStr + 1);
            if(FScanNode(nod->left, CurStr, fd) == -1) return -1;
            if(CurStr[0] != ',') {
                fprintf(stderr, "Invalid format of input file!!!\n");
                return -1;
            }
            strcpy(nod->right->name, CurStr + 1);
            if(FScanNode(nod->right, CurStr, fd) == -1) return -1;
            if(CurStr[0] != ')') {
                fprintf(stderr, "Invalid format of input file!!!\n");
                return -1;
            }
            else if(fgets(CurStr, MAX_NAME_LEN + 1, fd) != NULL) {
                int Len = strlen(CurStr);
                if(Len > 0 && CurStr[Len - 1] == '\n')
                    CurStr[Len - 1] = '\0';
            }
        }
    }
    return 0;
}

int QueuePush(tqueue* queue, tnode* nod) {
    assert(queue != NULL);
    assert(nod   != NULL);
    if(queue->size + 1 >= MAX_NUM_OF_NODES)
        return -1;
    queue->tree[queue->size++] = nod;
    return 0;
}

tnode* MakeBinTree(tqueue* queue) {
    assert(queue != NULL);
    if(queue->tree[queue->cur] == NULL)
        return NULL;
    queue->tree[queue->cur]->left  = queue->tree[2 * queue->cur + 1];
    queue->tree[queue->cur]->right = queue->tree[2 * queue->cur + 2];
    queue->cur++;
    MakeBinTree(queue);
    return queue->tree[0];
}

int MakeGraphFile(tnode* tree, char* FileName) {
    assert(tree     != NULL);
    assert(FileName != NULL);
    FILE* fd;
    if((fd = fopen(FileName, "w")) == NULL) {
        perror("fopen");
        return -1;
    }
    fprintf(fd, "digraph G{\n");
    FPrintGraphNode(tree, fd);
    fprintf(fd, "}\n");
    fclose(fd);
    return 0;
}

int FPrintGraphNode(tnode* node, FILE* fd) {
    if(node->left != NULL) {
        fprintf(fd, "\"%s\"->\"%s\" [label = \"Да\"]\n", node->name, node->left->name);
    }
    if(node->right != NULL) {
        fprintf(fd, "\"%s\"->\"%s\" [label = \"Нет\"]\n", node->name, node->right->name);
    }
    if(node->left != NULL)
        FPrintGraphNode(node->left, fd);
    if(node->right != NULL)
        FPrintGraphNode(node->right, fd);
    return 0;
}

int TreeDestruct(tnode* node) {
    TreeDestructChilds(node);
    free(node);
    node = NULL;
    return 0;
}

int TreeDestructChilds(tnode* node) {
    if(node->left == NULL)
        return 0;
    TreeDestructChilds(node->left);
    TreeDestructChilds(node->right);
    free(node->left);
    return 0;
}
