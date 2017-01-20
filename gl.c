/**
 * @file gl.c
 * @author Michael Hodges
 * @date 12/7/14
 * @brief main function for game of life
 * @todo command line arguments, doxygen, models
 * @bug struct keeps declaring itself in varius places
*/

#include <stdlib.h>
#include "SDL2/SDL.h"
#include "sdl.h"
#include "life.h"

int main(int argc, char *argv[])
{
	int i, j;
	int turn = 0;
	int n = 0;
	char edge[6];
	char file[50];
	char hlp;
	int width = 800;
	int height = 800;
	int sprite_size = 8; /* either 2, 4, 8, or 16 */
	int m = 10;
	int nn = 10;
        /* colors are RGB model valid values [0, 255] */
	unsigned char red = 0;
	unsigned char green = 255;
	unsigned char blue = 255;
        struct sdl_info_t sdl_info; /* this is needed to graphically display the game */
	unsigned char **a;
	unsigned char **b;

	char com;
	char buf[50];
	char *buf2;

	while((com = getopt(argc, argv, "abc:")) != -1) {
		switch (com) {
			case 'w':
				sdl_info.width = optarg;
				break;
			case 'h':
				sdl_info.height = optarg;
				break;
			case 'e':
				//edge[] = optarg;
				break;
			case 'r':
				sdl_info.color.red = optarg;
				break;
			case 'g':
				sdl_info.color.green = optarg;
				break;
			case 'b':
				sdl_info.color.blue = optarg;
				break;
			case 's':
				sdl_info.sprite_size = optarg;
				break;
			case 'f':
				//file[] = optarg;
				break;
			case 'o':
				do {
					fgets(buf, 49, stdin);
				} while(buf[0] == '\n');
				buf2 = strtok (buf, ",");
				m = buf2;
				buf2 = strtok (NULL, ",");
				nn = buf2;
				break;
			case 'H':
				hlp = 1;
				break;
			default:
				hlp = 1;
		}
	}

	if(hlp == 1) {
		help();
		return 0;
	}

        /* set up SDL -- works with SDL2, also gives harmless(?) video errors */
	init_sdl_info(&sdl_info, width, height, sprite_size, red, green, blue);

	/* life initialization code here */
/*
	a = init_matrix((height/sprite_size), (width/sprite_size)); //(height, width);
	grid_set(a, (height/sprite_size), (width/sprite_size)); //(a, height, width);
	b = init_matrix((height/sprite_size), (width/sprite_size)); //(height, width);
	grid_set(b, (height/sprite_size), (width/sprite_size)); //(b, height, width);
*/
	a = init_matrix(height, width);
	grid_set(a, height, width);
	b = init_matrix(height, width);
	grid_set(b, height, width); 

a[5][5] = 1;
a[4][5] = 1;
a[3][5] = 1; //creates floater for test
a[5][4] = 1;
a[4][3] = 1;

        /* Main loop: loop forever. */
	while (1)
	{
	if (SDL_GetTicks() % 50 == 0){

		/* array switch  */
		if(turn == 0) {
			sdl_render_life(&sdl_info, a);
			turn++;
		}
		else {
			sdl_render_life(&sdl_info, b);
			turn = 0;
		}

		/* live logic */
		if(turn == 0) {
			for(i = 1; i < height - 1; i++) {
				for(j = 1; j < width - 1; j++) {
					n = around_point(b, i, j);
					if(n < 2)
						a[i][j] = 0;
					if(n > 3)
						a[i][j] = 0;
					if(n == 3)
						a[i][j] = 1;
					if(n == 2)
						a[i][j] = b[i][j];
				}
			}
		}
		else {
			for(i = 1; i < height - 1; i++) {
				for(j = 1; j < width - 1; j++) {
					n = around_point(a, i, j);
					if(n < 2)
						b[i][j] = 0;
					if(n > 3)
						b[i][j] = 0;
					if(n == 3)
						b[i][j] = 1;
					if(n == 2)
						b[i][j] = a[i][j];
				}
			}
		}

                 /* Poll for events, and handle the ones we care about. 
                  * click the X button to close the window
                  */
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			switch (event.type) 
			{
			case SDL_KEYDOWN:
				break;
			case SDL_KEYUP:
                        /* If escape is pressed, return (and quit) */
				if (event.key.keysym.sym == SDLK_ESCAPE)
					return 0;
				break;
			case SDL_QUIT:
				return(0);
			}
		}
	}
	}
	return 0;
}
