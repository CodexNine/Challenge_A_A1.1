#ifndef PRINT_H_INCLUDED   /* Include guard */
#define PRINT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int unchanged_field[13][13] =
     {
        {-1, -1, -1, -1, 0, -1, 0, -1, 0, -1, -1, -1, -1},
        {-1, -1, -1, -1,-1, -1,-1, -1,-1, -1, -1, -1, -1},
        {-1, -1,  0,  0, 0,  0, 0,  0, 0,  0,  0, -1, -1},
        {-1, -1,  0, -1, 0, -1, 0, -1, 0, -1,  0, -1, -1},
        { 0, -1,  0,  0, 0,  0, 0,  0, 0,  0,  0, -1,  0},
        {-1, -1,  0, -1, 0, -1, 0, -1, 0, -1,  0, -1, -1},
        { 0, -1,  0,  0, 0,  0, 0,  0, 0,  0,  0, -1,  0},
        {-1, -1,  0, -1, 0, -1, 0, -1, 0, -1,  0, -1, -1},
        { 0, -1,  0,  0, 0,  0, 0,  0, 0,  0,  0, -1,  0},
        {-1, -1,  0, -1, 0, -1, 0, -1, 0, -1,  0, -1, -1},
        {-1, -1,  0,  0, 0,  0, 0, 0,  0,  0,  0, -1, -1},
        {-1, -1, -1, -1,-1, -1,-1, -1,-1, -1, -1, -1, -1},
        {-1, -1, -1, -1, 0, -1, 0, -1, 0, -1, -1, -1, -1}
    };

char instruct_output[]="";
char f = 'f';
char r = 'r';
char l = 'l';
char t = 't';
char s = 's';

int kruising[27][2];

int clear_kruising[27][2] = {{0}};
int integer = 1;
int checkpoints[3];





#endif
