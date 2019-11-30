/*
 * main.c
 *
 *  Created on: Nov 30, 2019
 *      Author: artem
 */

#include <stdio.h>
#include <string.h>

#include "Akinator.h"

int main() {
    tnode tree;
    strcpy(tree.name, "Одушевленное");
    Guess(&tree);
    return 0;
}
