#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/baseseed.h"
#include "../headers/check.h"
#include "../headers/game.h"
#include "../headers/menu.h"
#include "../headers/print.h"
#include "../headers/stack.h"
#include "../headers/sudokugenerator.h"
#include "../headers/sudokusolver.h"

#define UNASSIGNED 0
#define MAX 25

int main() {
	int **sudoku = NULL;
	unsigned int sudokusize;
	register int i;
	int ch_menu;
	bool quit = false;
	int temp;
	char choice;

	/* first allocating memory to store address of integer
	 * pointer then allocating each integer pointer memory
	 * to store integer
	 */
	sudoku = (int **)malloc(MAX * sizeof(int *));
	if (sudoku == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return false;
	}
	for (i = 0; i < MAX; i++) {
		sudoku[i] = (int *)malloc(MAX * sizeof(int));
		if (sudoku[i] == NULL) {
			fprintf(stderr, "Memory allocation failed\n");
			return false;
		}
	}
	/* while quit is false */
	while (!quit) {
		ch_menu = print_menu();
		switch (ch_menu) {
			/* Solve a sudoku */
			case 1:
				while (!quit) {
					ch_menu = print_solver_menu();
					switch (ch_menu) {
						/* get sudoku from file */
						case 1:
							sudokusize = get_sudoku_size();
							if (sudokusize == 0) {
								// quit = true;
								break;
							}

							if (!get_sudoku_from_file(
									sudoku, sudokusize)) {
								// quit = true;
								break;
							}

							if (!valid_sudoku(sudoku,
											  sudokusize)) {
								fprintf(stderr,
										"It is not a valid "
										"sudoku\n");
								// quit = true;
								break;
							}

							if (!sudoku_solver(
									sudoku, sudokusize)) {
								fprintf(
									stderr,
									"No solutions found\n");
								// quit = true;
								break;
							}

							print_sudoku(sudoku,
										 sudokusize);

							puts("Enter enter to continue");

							if (getchar() && getchar())
								;

							break;
						/* enter sudoku */
						case 2:
							sudokusize = get_sudoku_size();
							if (sudokusize == 0) {
								break;
							}

							puts(
								"Enter sudoku[Warning: "
								"seperate numbers by "
								"spaces]");

							if (!get_input_sudoku(
									sudoku, sudokusize)) {
								break;
							}

							puts("Input Sudoku:");
							print_sudoku(sudoku,
										 sudokusize);

							if (!valid_sudoku(sudoku,
											  sudokusize)) {
								fprintf(stderr,
										"It is not a valid "
										"sudoku\n");
								break;
							}

							if (!sudoku_solver(
									sudoku, sudokusize)) {
								fprintf(
									stderr,
									"No solutions found\n");
								break;
							}

							puts("Solution");

							print_sudoku(sudoku,
										 sudokusize);

							puts("Enter enter to continue");

							if (getchar() && getchar())
								;

							break;

						/* to go back */
						case 0:
							quit = true;
							break;
						/* NOTA */
						default:
							puts(
								"Please choose one of the "
								"above");
							break;
					}
				}
				quit = false;
				break;
			/* Generate a sudoku */
			case 2:
				while (!quit) {
					temp = print_generator_menu();
					switch (temp) {
						/* easy */
						case 1:
							sudokusize = 4;
							quit = true;
							break;
						case 2:
							sudokusize = 9;
							quit = true;
							break;
						case 3:
							sudokusize = 16;
							quit = true;
							break;
						case 4:
							sudokusize = 25;
							quit = true;
							break;
						case 0:
							quit = true;
							break;
						default:
							puts(
								"Please choose one of the "
								"above or 0 to go back");
							break;
					}
					quit = false;
					if (sudokusize == 0) {
						quit = true;
						break;
					}
					if (!sudoku_game(sudokusize)) {
						quit = true;
						break;
					} else {
						print_sudoku(sudoku, sudokusize);
					}
				}
				quit = false;
				break;
			/* Quit */
			case 0:
				quit = true;
				break;
			/* NOTA */
			default:
				break;
		}
	}
	for (i = 0; i < MAX; i++) {
		free(sudoku[i]);
	}
	free(sudoku);
	return EXIT_SUCCESS;
}