/**
 * @file life.c
 * @author Michael Hodges
 * @date 12/7/14
 * @brief functions for game of life
 * @todo model implementation, dox
 * @bug structure declares here and in header instead of just header
*/

#include "life.h"

/** 
 * creates a 2D matrix
 * @param rows the number of rows
 * @param cols the number of collumns
 * @return a the completed 2D matrix
 */
unsigned char **init_matrix(int rows, int cols)
{
	int i, j;
	unsigned char **a;

	a = malloc(rows * sizeof(char *));
	if(!a)
		return NULL;

	for(i = 0; i < rows; i++) {
		a[i] = malloc(cols * sizeof(char));
		if(!a[i]) {
			for (j = 0; j < i; j++)
				free(a[j]);
			free(a);
			return NULL;
		}
	}

	return a;
}

/** 
 * sets the entire array to 0
 * @param a the array being affected
 * @param rows the number of rows
 * @param cols the number of collumns
 * @return void
 */
void grid_set(unsigned char **a, int rows, int cols)
{
	int i, j;

	for(i = 0; i < rows; i++) {
		for(j = 0; j < cols; j++) {
			a[i][j] = 0;
		}
	}
}

/** 
 * counts the number of alive points around a given point
 * @param a the array the point is from
 * @param i the x coordinate of the point
 * @param j the y value of the point
 * @return n the number of points around the point
 */
int around_point(unsigned char **a, int i, int j)
{
	int n = 0;
	int x, y;

	for(x = -1; x < 2; x++) {
		for(y = -1; y < 2; y++) {
			if(x != 0 || y != 0) {
				if(a[i + x][j + y] == 1)
					n++;
			}
		}
	}

	return n;
}

/** 
 * prints out help
 * @param void
 * @return void
 */
void help()
{
	printf("-w width of the screen argument 640, 800, 1024, etc.\n");
	printf("-h height of the screen argument 480, 600, 768, etc.\n");
	printf("-e type of edge. Values are hedge, torus or klein (strings)\n");
	printf("-r the red color value, an integer between [0, 255]\n");
	printf("-g the green color value, an integer between [0, 255]\n");
	printf("-b the blue color value, an integer between [0, 255]\n");
	printf("-s size of the sprite. Valid values are 2, 4, 8, or 16 only. An integer.\n");
	printf("-f filename, a life pattern in file format 1.06.\n");
	printf("-o x,y the initial x,y coordinate of the pattern found in the file. No space between the x and y.\n");
	printf("-H help, print out usage information and a brief description of each option.\n");
}
