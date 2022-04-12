#pragma once
int display_map(char map[11][11]);
int read_input(int* a, int* b);
int generate_map(char map[11][11]);
int generate_unit(char* symbol, int length, char map[11][11]);

int num_in_range(int num, int min, int max);
bool check_if_field_empty(char map[11][11], int x_start, int y_start, int x_end, int y_end);
void write_fields(char map[11][11], char symbol, int x_start, int y_start, int x_end, int y_end);

int ship_1(int x, int y, char map[11][11]);
int ship(int x, int y, int dir, int length, char symbol, char map[11][11]);
