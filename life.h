/**
 * @file life.h
 * @author Michael Hodges
 * @date 12/7/14
 * @brief handles life.c
*/

#ifndef LIFE_H_
#define LIFE_H_

#include "SDL2/SDL.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

unsigned char **init_matrix(int rows, int cols);
void grid_set(unsigned char **a, int rows, int cols);
int around_point(unsigned char **a, int i, int j);

#endif
