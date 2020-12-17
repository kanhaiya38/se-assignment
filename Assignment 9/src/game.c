#include <ctype.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/game.h"
#include "../headers/menu.h"
#include "../headers/print.h"
#include "../headers/stack.h"
#include "../headers/sudokugenerator.h"
#include "../headers/sudokusolver.h"

#define UNASSIGNED 0

static inline void clr_scr() { printf("\e[1;1H\e[2J"); }

/* returns tokenised data only if is valid otherwise returns
 * false */
bool get_data(char *cmd, int strlen, values *token) {
	register int i;

	bool row = true;
	bool col = false;
	bool num = false;

	int sum = 0;

	for (i = 0; i < strlen; i++) {
		if (isspace(cmd[i])) {
			continue;
		}

		if (isalpha(cmd[i])) {
			if (row) {
				token->row = cmd[i] - 'a';
				row = false;
				col = true;
				continue;
			} else if (col) {
				token->col = cmd[i] - 'a';
				col = false;
				num = true;
				continue;
			} else {
				return false;
			}
		}

		if (isdigit(cmd[i])) {
			if (num) {
				while (isdigit(cmd[i])) {
					sum = sum * 10 + (cmd[i] - '0');
					// i++;
					if (i == strlen - 1) {
						break;
					}
					i++;
				}
				token->num = sum;
			} else {
				return false;
			}
		}
	}

	return true;
}

/* to assign value to command */
unsigned int get_command_num(char *cmd) {
	if (!strcmp(cmd, "save")) return 1;
	if (!strcmp(cmd, "undo")) return 2;
	if (!strcmp(cmd, "redo")) return 3;
	if (!strcmp(cmd, "hint")) return 4;
	if (!strcmp(cmd, "clear")) return 5;
	if (!strcmp(cmd, "solve")) return 6;
	if (!strcmp(cmd, "new")) return 7;
	if (!strcmp(cmd, "quit")) return 0;
	return 9;
}

/* saves sudoku to file */
bool save_sudoku_to_file(int **seed, int **problem, int len,
						 char *str) {
	register int i, j;
	FILE *fp_save;
	char file_name[32];
	strcpy(file_name, "./resources/");
	strcat(file_name, str);

	fp_save = fopen(file_name, "w");
	strcat(file_name, ".txt");
	/* checking if the file is opened */
	if (fp_save == NULL) {
		fprintf(stderr, "cannot open file %s\n", file_name);
		return false;
	}

	fputc((len + '0'), fp_save);
	fputc('\n', fp_save);

	for (i = 0; i < len; i++) {
		for (j = 0; j < len; j++) {
			fputc((seed[i][j] + '0'), fp_save);
			fputc(' ', fp_save);
			// fputc(' ', fp_save);
		}
	}

	fputc('\n', fp_save);

	for (i = 0; i < len; i++) {
		for (j = 0; j < len; j++) {
			fputc((problem[i][j] + '0'), fp_save);
			fputc(' ', fp_save);
		}
	}

	fclose(fp_save);
	return true;
}

/* gets saved sudoku */
bool get_saved_sudoku(int **seed, int **problem, int *len,
					  char *str) {
	register int i, j;
	FILE *fp_saved;
	char file_name[32];
	strcpy(file_name, "./resources/");
	strcat(file_name, str);

	fp_saved = fopen(file_name, "r");
	strcat(file_name, ".txt");
	/* checking if the file is opened */
	if (fp_saved == NULL) {
		fprintf(stderr, "cannot open file %s\n", file_name);
		return false;
	}

	*len = fgetc(fp_saved) - '0';

	fgetc(fp_saved);

	for (i = 0; i < *len; i++) {
		for (j = 0; j < *len; j++) {
			seed[i][j] = fgetc(fp_saved) - '0';
			fgetc(fp_saved);
		}
	}
	fgetc(fp_saved);

	for (i = 0; i < *len; i++) {
		for (j = 0; j < *len; j++) {
			problem[i][j] = fgetc(fp_saved) - '0';
			fgetc(fp_saved);
		}
	}
	fgetc(fp_saved);

	fclose(fp_saved);
	return true;
}

bool comparesudoku(int **arr1, int **arr2, int len) {
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (arr1[i][j] != arr2[i][j]) {
				return false;
			}
		}
	}
	return true;
}

bool sudoku_game(int len) {
	register int i;
	int **problem_sudoku, **seed_sudoku, **sudoku;
	int sudokusize;
	char choice;
	char command[32], file_name[32];
	int row, col;
	unsigned int cmd;
	values data;
	unsigned int saved_games = 0;
	bool quit = false;
	stack undo, redo;
	init(&undo);
	init(&redo);
	DIR *dr;
	struct dirent *de;

	/* first allocating memory to store address of integer
	 * pointer then allocating each integer pointer memory
	 * to store integer
	 */
	problem_sudoku = (int **)malloc(len * sizeof(int *));
	if (problem_sudoku == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return false;
	}
	for (i = 0; i < len; i++) {
		problem_sudoku[i] =
			(int *)malloc(len * sizeof(int));
		if (problem_sudoku[i] == NULL) {
			fprintf(stderr, "Memory allocation failed\n");
			return false;
		}
	}

	seed_sudoku = (int **)malloc(len * sizeof(int *));
	if (seed_sudoku == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return false;
	}
	for (i = 0; i < len; i++) {
		seed_sudoku[i] = (int *)malloc(len * sizeof(int));
		if (seed_sudoku[i] == NULL) {
			fprintf(stderr, "Memory allocation failed\n");
			return false;
		}
	}

	sudoku = (int **)malloc(len * sizeof(int *));
	if (sudoku == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return false;
	}
	for (i = 0; i < len; i++) {
		sudoku[i] = (int *)malloc(len * sizeof(int));
		if (sudoku[i] == NULL) {
			fprintf(stderr, "Memory allocation failed\n");
			return false;
		}
	}

	puts("Do you want to resume a saved game?[y/n]");
	while (1) {
		scanf(" %c", &choice);
		if (choice == 'y') {
			dr = opendir("./resources/");
			if (dr == NULL) {
				fprintf(stderr,
						"Could not open current directory");
				return 0;
			}
			while ((de = readdir(dr)) != NULL) {
				if (strcmp(de->d_name, ".") &&
					strcmp(de->d_name, "..")) {
					printf("%s\n", de->d_name);
					saved_games++;
				}
			}

			if (saved_games == 0) {
				puts("No game is saved");
				break;
			}
			scanf("%s", file_name);
			// strcpy(file_name, "sudoku");
			get_saved_sudoku(seed_sudoku, problem_sudoku,
							 &sudokusize, file_name);
			if (sudokusize != len) {
				puts("Not a valid sudoku");
				puts("Press enter to continue");
				if (getchar() && getchar())
					;
				return false;
			}
			puts("Not a command");
			copy_sudoku(problem_sudoku, sudoku, len);
			closedir(dr);
			break;
		} else if (choice == 'n') {
			// printf("here\n");
			sudoku_generator(problem_sudoku, seed_sudoku,
							 len);
			copy_sudoku(problem_sudoku, sudoku, len);
			break;
		} else {
		}
	}

	/* to clear terminal */
	clr_scr();
	print_game_commands();
	// print_sudoku(sudoku, len);
	print_sudoku_game(seed_sudoku, sudoku, len);

	while (!quit) {
		printf(">> ");
		scanf("%s", command);
		cmd = get_command_num(command);

		switch (cmd) {
			case 1:
				puts("Save file as");
				scanf("%s", file_name);
				if (save_sudoku_to_file(seed_sudoku, sudoku,
										len, file_name)) {
					puts("File saved successfully");
					return false;
				}
				break;
			case 2:
				if (!isempty(&undo)) {
					data = pop(&undo);
					if (!isfull(&redo)) {
						push(&redo, data);
					} else {
						fprintf(stderr, "stack is full\n");
					}
					sudoku[data.row][data.col] = UNASSIGNED;
					clr_scr();
					print_game_commands();
					print_sudoku_game(seed_sudoku, sudoku,
									  len);
				} else {
					fprintf(stderr, "Cannot undo\n");
				}
				break;
			case 3:
				if (!isempty(&redo)) {
					data = pop(&redo);
					if (!isfull(&undo)) {
						push(&undo, data);
					} else {
						fprintf(stderr, "stack is full\n");
					}
					sudoku[data.row][data.col] = data.num;
					clr_scr();
					print_game_commands();
					print_sudoku_game(seed_sudoku, sudoku,
									  len);
				} else {
					fprintf(stderr, "Cannot redo\n");
				}
				break;
			case 4:
				find_empty_cell(sudoku, len, &row, &col);
				printf("%d at position %c, %c\n",
					   seed_sudoku[row][col], row + 'a',
					   col + 'a');
				break;
			case 5:
				sudoku = problem_sudoku;
				clr_scr();
				print_game_commands();
				print_sudoku_game(seed_sudoku, sudoku, len);
				break;
			case 6:
				sudoku = seed_sudoku;
				clr_scr();
				print_game_commands();
				print_sudoku_game(seed_sudoku, sudoku, len);
				puts("Sudoku solved");
				break;
			case 7:
				sudoku_generator(problem_sudoku,
								 seed_sudoku, len);
				copy_sudoku(problem_sudoku, sudoku, len);
				clr_scr();
				print_game_commands();
				print_sudoku_game(seed_sudoku, sudoku, len);
				break;
			case 8:
				break;
			case 9:
				clr_scr();
				if (get_data(command, strlen(command),
							 &data)) {
					if (data.num > len) {
						print_game_commands();
						print_sudoku_game(seed_sudoku,
										  sudoku, len);
						puts("Not a valid number");
						break;
					}
				} else {
					print_game_commands();
					print_sudoku_game(seed_sudoku, sudoku,
									  len);
					puts("Not a command");
					continue;
				}
				print_game_commands();
				if (problem_sudoku[data.row][data.col] !=
					UNASSIGNED) {
					puts(
						"You cannot change element at this "
						"position");
					puts("");
					puts("");
				} else {
					sudoku[data.row][data.col] = data.num;
					if (!isfull(&undo)) {
						push(&undo, data);
					} else {
						fprintf(stderr, "Stack is full");
					}
				}
				print_sudoku_game(seed_sudoku, sudoku, len);
				if (comparesudoku(sudoku, seed_sudoku,
								  len)) {
					puts("completed succesfully");
					clr_scr();
					return false;
				}
				break;
			case 0:
				quit = true;
				break;
		}
	}

	for (i = 0; i < len; i++) {
		free(sudoku[i]);
	}
	free(sudoku);

	for (i = 0; i < len; i++) {
		free(seed_sudoku[i]);
	}
	free(seed_sudoku);

	for (i = 0; i < len; i++) {
		free(problem_sudoku[i]);
	}
	free(problem_sudoku);

	return false;
}