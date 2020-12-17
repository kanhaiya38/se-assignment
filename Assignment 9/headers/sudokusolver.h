bool issafe(int **arr, int len, int row, int col, int num);

bool find_empty_cell(int **arr, int len, int *row,
					 int *col);

bool find_safe_num(int **arr, int len, int row, int col,
				   int *i);

bool valid_sudoku_size(int len);

bool valid_sudoku(int **arr, int len);

bool sudoku_solver(int **arr, int len);