// statki.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Header.h"

int display_map(char map[11][11])
{
    system("cls");
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            if (j == 10) printf("     ");
            else printf("     |");
        }
        printf("\n");
        for (int j = 0; j < 11; j++)
        {
            if (i == 10 && j == 0) printf(" 10  |");
            else if (j == 10) printf("  %c  ", map[i][j]);
            else printf("  %c  |", map[i][j]);
        }
        printf("\n");
        if (i != 10)
        {
            for (int j = 0; j < 11; j++)
            {
                if (j == 10) printf("_____");
                else printf("_____|");
            }
        }
        else
        {
            for (int j = 0; j < 11; j++)
            {
                if (j == 10) printf("     ");
                else printf("     |");
            }
        }
        printf("\n");
    }

    return 0;
}

//sprawdza i zamienia kordy na pozycje X i Y
int read_input(int* a, int* b)
{ 
    char inp[4];
    int i;
    do
    {
        printf("Podaj pole: ");
        i = scanf_s("%s", inp, 4);
        if (strlen(inp) == 2)
        {
            if (inp[0] >= '1' && inp[0] <= '9')
            {
                if (inp[1] >= 'A' && inp[1] <= 'J')
                {
                    *a = inp[1] - 'A' + 1;
                    *b = inp[0] - '1' + 1;
                }
                else if (inp[1] >= 'a' && inp[1] <= 'j')
                {
                    *a = inp[1] - 'a' + 1;
                    *b = inp[0] - '1' + 1;
                }
                else i = 0;
            }
            else if (inp[0] >= 'A' && inp[0] <= 'J')
            {
                if (inp[1] >= '1' && inp[1] <= '9')
                {
                    *a = inp[0] - 'A' + 1;
                    *b = inp[1] - '1' + 1;
                }
                else i = 0;
            }
            else if (inp[0] >= 'a' && inp[0] <= 'j')
            {
                if (inp[1] >= '1' && inp[1] <= '9')
                {
                    *a = inp[0] - 'a' + 1;
                    *b = inp[1] - '1' + 1;
                }
                else i = 0;
            }
            else i = 0;
        }
        else if (strlen(inp) == 3)
        {
            if (inp[0] >= 'A' && inp[0] <= 'J')
            {
                if (inp[1] >= '1' && inp[2] <= '0')
                {
                    *a = inp[0] - 'A' + 1;
                    *b = 10;
                }
                else i = 0;
            }
            else if (inp[0] >= 'a' && inp[0] <= 'j')
            {
                if (inp[1] == '1' && inp[2] == '0')
                {
                    *a = inp[0] - 'a' + 1;
                    *b = 10;
                }
                else i = 0;
            }
            else if (inp[0] == '1' && inp[1] == '0')
            {
                if (inp[2] >= 'A' && inp[2] <= 'J')
                {
                    *a = inp[2] - 'A' + 1;
                    *b = 10;
                }
                else if (inp[2] >= 'a' && inp[2] <= 'j')
                {
                    *a = inp[2] - 'a' + 1;
                    *b = 10;
                }
                else i = 0;
            }
            else i = 0;
        }

    } while (!i || strlen(inp) <= 1);
    return  0;
}

void game(char map_hid[11][11], char map_vis[11][11], int hp[10], int* hp_a)
{
    int x_axis = 0;
    int y_axis = 0;
    read_input(&x_axis, &y_axis);
    if (check_if_hit(x_axis, y_axis, map_hid))
    {
        
        if (hit(map_hid, map_vis, x_axis, y_axis, hp, hp_a))
        {
            display_map(map_vis);
            printf("Trafiony zatopiony!!!\n");
        }
        else
        {
            display_map(map_vis);
            printf("Trafiony!\n");
        }
    }
    else
    {
        map_hid[y_axis][x_axis] = '*';
        map_vis[y_axis][x_axis] = '*';
        display_map(map_vis);
        printf("Pudlo\n");
    }
}

bool check_if_hit(int x, int y, char map[11][11])
{
    if (map[y][x] >= 'K' && map[y][x] <= 'T') return true;
    return false;
}
int hit(char map_hid[11][11], char map_vis[11][11], int x, int y, int hp[10], int* hp_a)
{
    int unit = map_hid[y][x];
    hp[unit - 75] = hp[unit - 75] - 1;
    map_hid[y][x] = 'X';
    map_vis[y][x] = 'X';
    unit -= 75;
    if (hp[unit] == 0)
    {
        *hp_a = *hp_a - 1;
        return 1;
    }
    return 0;
}

int generate_map(char map[11][11])
{
    char symbol = 'K';
    bool check = false;
    for (int i = 0; i < UNITS_4; i++)
    {
        while (generate_unit(&symbol, 4, map)) {/**/ }
    }

    for (int i = 0; i < UNITS_3; i++)
    {
        while (generate_unit(&symbol, 3, map)) {/**/}
    }

    for (int i = 0; i < UNITS_2; i++)
    {
        while (generate_unit(&symbol, 2, map)) {/**/}
    }

    for (int i = 0; i < UNITS_1; i++)
    {
        while (generate_unit(&symbol, 1, map)) {/**/}
    }

    return 0;
}

int generate_unit(char* symbol, int length, char map[11][11])
{
    bool check = false;
    int x = rand() % 10 + 1;
    int y = rand() % 10 + 1;
    //---------------*
    //direction
    //0 - right
    //1 - down
    //2 - left
    //3 - right
    //---------------*
    int dir = rand() % 4;
    for (int i = dir; i < dir + 4; i++)
    {
        check = ship(x, y, -1 * abs(i - 3) + 3, length, *symbol, map);
        if (!check)
        {
            *symbol = *symbol + 1;
            break;
        }
    }
    return check;
}

bool check_if_field_empty(char map[11][11], int x_start, int y_start, int x_end, int y_end)
{
    for (int i = y_start; i <= y_end; i++)
    {
        for (int j = x_start; j <= x_end; j++)
        {
            if (map[i][j] != ' ') return true;
        }
    }
    return false;
}

int ship(int x, int y, int dir, int length, char symbol, char map[11][11])
{
    int x_s;
    int y_s;
    int x_e;
    int y_e;
    switch (dir)
    {
        case 0:
            if (x + length - 1 > 10) return 1; //check if out of index
            if (check_if_field_empty(map, x, y, x + length - 1, y)) return 1; //check if field is taken
            x_s = x - 1;
            y_s = y - 1;
            x_e = x + length;
            y_e = y + 1;
            break;
        case 1:
            if (y + length - 1 > 10) return 1;
            if (check_if_field_empty(map, x, y, x, y + length - 1)) return 1;
            x_s = x - 1;
            y_s = y - 1;
            x_e = x + 1;
            y_e = y + length;
            break;
        case 2:
            if (x - length + 1 > 10) return 1;
            if (check_if_field_empty(map, x - length + 1, y, x, y)) return 1;
            x_s = x - length;
            y_s = y - 1;
            x_e = x + 1;
            y_e = y + 1;
            break;
        case 3:
            if (y - length + 1 > 10) return 1;
            if (check_if_field_empty(map, x, y - length + 1, x, y)) return 1;
            x_s = x - 1;
            y_s = y - length;
            x_e = x + 1;
            y_e = y + 1;
            break;
        default:
            return 1;
    }
    write_fields(map, symbol, x_s, y_s, x_e, y_e);
    return 0;
}

void write_fields(char map[11][11], char symbol, int x_start, int y_start, int x_end, int y_end)
{
    for (int i = y_start; i <= y_end; i++)
    {
        for (int j = x_start; j <= x_end; j++)
        {
            if (i < 1 || i > 10 || j < 1 || j > 10) continue; //when out of index
            if (i > y_start && i < y_end && j > x_start && j < x_end) map[i][j] = symbol;
            else map[i][j] = 'z';
        }
    }
}

int main()
{
    srand(time(NULL));
    //srand(2);
    int hp[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
    int hp_all = All_UNITS;
    char map_ai[11][11] =
    {
    {' ', 'A', 'B', 'B', 'D', 'E', 'F', 'G', 'H', 'I', 'J'},
    {'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'2', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'3', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'4', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'5', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'6', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'7', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'8', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'9', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    };
    char map_user[11][11] =
    {
    {' ', 'A', 'B', 'B', 'D', 'E', 'F', 'G', 'H', 'I', 'J'},
    {'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'2', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'3', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'4', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'5', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'6', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'7', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'8', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'9', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    };
    generate_map(map_ai);
    display_map(map_user);
    while (hp_all != 0)
    {
        game(map_ai, map_user, hp, &hp_all);
    }
    system("cls");
    printf("KONIEC GRY!!!");
}

