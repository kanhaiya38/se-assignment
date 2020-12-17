#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 32

static inline void clr_scr() { printf("\e[1;1H\e[2J"); }

// void fastscan(int *number)
// {
//     register int c;

//     *number = 0;

//     // extract current character from buffer
//     c = getchar();
//     if(!(c > 47 && c < 58)) {
//         *number = 100;
//     }
//     // if (c=='-')
//     // {
//     //     // number is negative
//     //     negative = true;

//     //     // extract the next character from the buffer
//     //     c = getchar();
//     // }

//     // Keep on extracting characters if they are integers
//     // i.e ASCII Value lies from '0'(48) to '9' (57)
//     // for (; (c>47 && c<58); c=getchar())
//     while(c > 47 && c < 58) {
//         *number = *number * 10 + c - 48;
//         c = getchar();
//     }
//     // if scanned input has a negative sign, negate the
//     // value of the input number
//         // number *= -1;
// }

void scan_opt(int *num) {
	char str[10];
	scanf("%s", str);
	int sum = 0;
	register int i;
	for (i = 0; i < strlen(str); i++) {
		if (isspace(str[i])) {
			continue;
		}
		if (isalpha(str[i])) {
			*num = 100;
			return;
		}
		if (isdigit(str[i])) {
			while (isdigit(str[i])) {
				sum = sum * 10 + (str[i] - '0');
				// i++;
				if (i == strlen(str) - 1) {
					break;
				}
				i++;
			}
			*num = sum;
			return;
		}
	}
}

int print_menu() {
	int choice;
	clr_scr();
	puts("1. Solve a Sudoku");
	puts("2. Generate a Sudoku");
	puts("0. Quit");
	scan_opt(&choice);
	while (choice > 2) {
		clr_scr();
		puts("Select one of the options: ");
		puts("1. Solve a Sudoku");
		puts("2. Generate a Sudoku");
		puts("0. Quit");
		scan_opt(&choice);
	}
	return choice;
}

int print_solver_menu() {
	int choice;
	clr_scr();
	puts("1. Get sudoku from a file");
	puts("2. Enter a sudoku");
	puts("0. To go back");
	scan_opt(&choice);
	while (choice > 2) {
		clr_scr();
		puts("Select one of the options: ");
		puts("1. Get sudoku from a file");
		puts("2. Enter a sudoku");
		puts("0. To go back");
		scan_opt(&choice);
	}
	return choice;
}

int get_sudoku_size() {
	int size;
	puts("Enter the size of the sudoku");
	scan_opt(&size);
	while (size != 4 && size != 9 && size != 16 &&
		   size != 25 && size != 0) {
		puts(
			"Please enter a valid size or enter 0 to go "
			"back one stage");
		// fastscan(&size);
		scan_opt(&size);
	}
	return size;
}

bool get_sudoku_from_file(int **arr, int len) {
	char file_name[128];
	FILE *fp_problem;
	char ch;
	int sum = 0;
	register int i, j;
	puts("Enter file name");
	scanf("%s", file_name);

	/*opening the file.
	 */
	fp_problem = fopen(file_name, "r");

	/* checking if the file is opened
	 */
	while (fp_problem == NULL) {
		fprintf(stderr, "cannot open file %s\n", file_name);
		puts(
			"Please enter a valid file or quit to go back");
		scanf("%s", file_name);
		if (!strcmp(file_name, "quit")) {
			return false;
		}
		fp_problem = fopen(file_name, "r");
	}
	/* getting input from a file in the sudoku
	 */
	for (i = 0; i < len; i++) {
		for (j = 0; j < len; j++) {
			sum = 0;
			while (!feof(fp_problem)) {
				ch = fgetc(fp_problem);
				if (isspace(ch)) {
					continue;
				}
				if (isalpha(ch)) {
					fprintf(stderr,
							"%s is not a valid sudoku\n",
							file_name);
					return false;
				}
				if (isdigit(ch)) {
					while (isdigit(ch)) {
						sum = sum * 10 + (ch - '0');
						if (!feof(fp_problem)) {
							ch = fgetc(fp_problem);
						} else {
							break;
						}
					}

					break;
				}
			}
			arr[i][j] = sum;
		}
	}
	fclose(fp_problem);

	return true;
}

bool get_input_sudoku(int **arr, int len) {
	register int i, j;
	for (i = 0; i < len; i++) {
		for (j = 0; j < len; j++) {
			// fastscan(&arr[i][j]);
			scan_opt(&arr[i][j]);
		}
	}

	return true;
}

int print_generator_menu() {
	int choice;
	puts("Choose difficulty level");
	puts("1. Easy");
	puts("2. Medium");
	puts("3. Hard");
	puts("4. Expert");
	puts("0. Quit");
	scan_opt(&choice);
	while (choice > 4) {
		puts("Select one of the options: ");
		puts("1. Easy");
		puts("2. Medium");
		puts("3. Hard");
		puts("4. Expert");
		puts("0. Quit");
		scan_opt(&choice);
	}
	return choice;
}

void print_game_commands() {
	puts("Commands:");
	puts("");
	puts("  save");
	puts("  undo");
	puts("  redo");
	puts("  hint");
	puts("  clear");
	puts("  solve");
	puts("  new");
	puts("  quit");
	puts("");
}