#pragma once

#define			UNITS_4 1
#define			UNITS_3 2
#define			UNITS_2 3
#define			UNITS_1 4
#define			All_UNITS UNITS_1  +UNITS_2 + UNITS_3 + UNITS_4


int display_map(char map[11][11]);
int read_input(int* a, int* b);
int generate_map(char map[11][11]);
int generate_unit(char* symbol, int length, char map[11][11]);

bool check_if_field_empty(char map[11][11], int x_start, int y_start, int x_end, int y_end);
void write_fields(char map[11][11], char symbol, int x_start, int y_start, int x_end, int y_end);

int ship(int x, int y, int dir, int length, char symbol, char map[11][11]);

void game(char map_hid[11][11], char map_vis[11][11], int hp[10], int* hp_a);
bool check_if_hit(int x, int y, char map[11][11]);
int hit(char map_hid[11][11], char map_vis[11][11], int x, int y, int hp[10], int* hp_a);
