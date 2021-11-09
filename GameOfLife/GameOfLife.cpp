#include <iostream>
#include <chrono>
#include <thread>

#define ALIVE_CHAR 35
#define DEAD_CHAR 32

using namespace std;


void print_table(char** table, int x_size, int y_size) {
	for (int i = 0; i < x_size; i++) {
		for (int j = 0; j < y_size; j++) {
			cout << table[i][j];
		}
		cout << endl;
	}
}


bool is_in_cell(char** table, int x, int y, int x_size, int y_size) {
	int actual_x = x, actual_y = y;

	if (x == -1)
		actual_x = x_size - 1;
	if (x == x_size)
		actual_x = 0;
	if (y == -1)
		actual_y = y_size - 1;
	if (y == y_size)
		actual_y = 0;

	return table[actual_x][actual_y] == ALIVE_CHAR;
}


void set_cell(char** table, char** old_table, int x, int y, int x_size, int y_size) {
	unsigned char alive_neighbors =
		is_in_cell(old_table, x - 1, y - 1, x_size, y_size) +
		is_in_cell(old_table, x, y - 1, x_size, y_size) +
		is_in_cell(old_table, x + 1, y - 1, x_size, y_size) +
		is_in_cell(old_table, x - 1, y, x_size, y_size) +
		is_in_cell(old_table, x + 1, y, x_size, y_size) +
		is_in_cell(old_table, x - 1, y + 1, x_size, y_size) +
		is_in_cell(old_table, x, y + 1, x_size, y_size) +
		is_in_cell(old_table, x + 1, y + 1, x_size, y_size);

	if (table[x][y] == ALIVE_CHAR) {
		if (alive_neighbors == 2 || alive_neighbors == 3) // cell survives
			return;
		else // cell dies
			table[x][y] = DEAD_CHAR;
	}
	else if (alive_neighbors == 3) {
		table[x][y] = ALIVE_CHAR;
	}
}


void copy_array(char** matrix, char** duplicate, int x_size, int y_size) {
	for (int i = 0; i < x_size; i++)
		for (int j = 0; j < y_size; j++)
			duplicate[i][j] = matrix[i][j];
}

// table:
// - x (row)
// - y (column)
//
// time:
// - +1 per cycle
int main()
{
	unsigned int time = 0;
	unsigned const int max_cycles = 100;
	const unsigned char x_size = 30, y_size = 30;
	char** table = (char**)malloc(sizeof(char*) * 100);
	char** temp_table = (char**)malloc(sizeof(char*) * 100);

	// init table
	for (int i = 0; i < x_size; i++) {
		table[i] = (char*)malloc(sizeof(char) * 100);
		temp_table[i] = (char*)malloc(sizeof(char) * 100);

	}

	// fill table with spaces
	for (int i = 0; i < x_size; i++)
		for (int j = 0; j < y_size; j++) {
			table[i][j] = ' ';
			temp_table[i][j] = ' ';
		}


	// set alive cells
	// Blinker
	table[3][3] = ALIVE_CHAR;
	table[4][3] = ALIVE_CHAR;
	table[5][3] = ALIVE_CHAR;

	// Toad
	table[6][6] = ALIVE_CHAR;
	table[6][7] = ALIVE_CHAR;
	table[6][8] = ALIVE_CHAR;
	table[7][7] = ALIVE_CHAR;
	table[7][8] = ALIVE_CHAR;
	table[7][9] = ALIVE_CHAR;


	// Penta-decathlon
	table[10][15] = ALIVE_CHAR;

	table[9][16] = ALIVE_CHAR;
	table[11][16] = ALIVE_CHAR;

	table[12][17] = ALIVE_CHAR;
	table[12][18] = ALIVE_CHAR;
	table[12][19] = ALIVE_CHAR;
	table[12][20] = ALIVE_CHAR;
	table[12][21] = ALIVE_CHAR;
	table[12][22] = ALIVE_CHAR;

	table[8][17] = ALIVE_CHAR;
	table[8][18] = ALIVE_CHAR;
	table[8][19] = ALIVE_CHAR;
	table[7][20] = ALIVE_CHAR;
	table[8][21] = ALIVE_CHAR;
	table[9][22] = ALIVE_CHAR;

	table[9][23] = ALIVE_CHAR;
	table[11][23] = ALIVE_CHAR;

	table[10][24] = ALIVE_CHAR;

	// ship
	table[20][5] = ALIVE_CHAR;
	table[21][6] = ALIVE_CHAR;
	table[22][6] = ALIVE_CHAR;
	table[20][7] = ALIVE_CHAR;
	table[21][7] = ALIVE_CHAR;

	// copy to temp array
	copy_array(table, temp_table, x_size, y_size);

	// process game
	while (time < max_cycles) {
		system("cls"); // clear screen
		print_table(table, x_size, y_size);
		for (int i = 0; i < x_size; i++)
			for (int j = 0; j < y_size; j++) {
				// check neighbours
				set_cell(table, temp_table, i, j, x_size, y_size);
			}
		copy_array(table, temp_table, x_size, y_size);
		time++;
		this_thread::sleep_for(0.1s);
	}

	// free memory
	for (int i = 0; i < x_size - 1; i++) {
		free(table[i]);
	}
	free(table);
	return 0;
}
