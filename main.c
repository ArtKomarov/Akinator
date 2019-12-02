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

#define SYSTEM_STR_LEN 126

int main(int argc, char* argv[]) {
    /*tnode* tree = (tnode*)calloc(1, sizeof(tnode));
    strcpy(tree->name, "Одушевленное");
    tnode* nod = (tnode*)calloc(2, sizeof(tnode));
    tree->left = nod;
    tree->right = nod + 1;
    strcpy(tree->left->name, "Кот");
    strcpy(tree->right->name, "Ноутбук");*/
    //int i = 1;
    if(argc > 1) {
        tnode* tree = TreeConstruct(argv[1]);
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

        if(argc > 2) {
            SaveTree(tree, argv[2]);
            if(argc > 3) {
                MakeGraphFile(tree, "GrTree.dot");
                TreeDestruct(tree);
                char buff[SYSTEM_STR_LEN];
                sprintf(buff, "dot -Tpng GrTree.dot -o %s", argv[3]);
                system(buff);
            }
        }
    }
    else {
        printf("Чтобы сыграть, передайте 1 параметром дерево.\n "
                "Дополнительно: 2 параметром передайте файл, куда сохранить дерево,\n"
                " 3 параметром - имя картинки, чтобы получить дерево граффически (формата *.png)\n");
    }
    return 0;
}
