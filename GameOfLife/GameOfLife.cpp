#include <iostream>

using namespace std;

void print_table(char** table, int x_size, int y_size) {
	for (int i = 0; i < x_size; i++) {
		for (int j = 0; j < y_size; j++) {
			cout << table[i][j];
		}
		cout << endl;
	}
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
	const unsigned char x_size = 10, y_size = 10;
	char** table = (char**)malloc(sizeof(char*) * 100);

	// init table
	for (int i = 0; i < x_size; i++) {
		table[i] = (char*)malloc(sizeof(char) * 100);
	}

	// fill table with spaces
	for (int i = 0; i < x_size; i++)
		for (int j = 0; j < y_size; j++)
			table[i][j] = ' ';

	// set alive cells
	table[3][3] = '#';
	table[4][3] = '#';

	// process game
	while (time < max_cycles) {
		system("cls"); // clear screen
		print_table(table, x_size, y_size);
		/* change table */
		time++;
	}
	
	// free memory
	for (int i = 0; i < x_size - 1; i++) {
		free(table[i]);
	}
	free(table);
	return 0;
}
