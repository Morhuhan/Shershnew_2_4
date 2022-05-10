#include <stdio.h>

// Считывает числа из файла в двумерный массив
void writing_from_file(FILE *f,  int array[][4], int rows) {

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < 4; j++) {

            fscanf(f, "%d", &array[i][j]);
        }

    }
}

// Находит НОЛЬ в исходном массиве и записывает его индексы в old_row_zero и old_col_zero
void find_zero(int array[][4], int rows, int* old_row_zero, int* old_col_zero) {

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < 4; j++) {

            if (array[i][j] == 0) {

                *old_row_zero = i;
                *old_col_zero = j;

            }
        }

    }
}

// Проверяет, поменялись ли ровно 1 число и 0 местами и запоминает куда встал ноль и куда встало число
int swap_check(int array_1[][4], int array_2[][4], int rows, int* row_elem, int* col_elem, int* new_row_zero, int* new_col_zero, int old_row_zero, int old_col_zero) {

    int check = 0;
    
    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 4; j++) {

            // Число сдивнулось и это НЕ ноль 
            if ((array_1[i][j] != array_2[i][j]) && (array_2[i][j] != 0)) {

                check++;

                // Запоминаем КУДА сдвинулось число
                *row_elem = i;
                *col_elem = j;

            }

            // НОЛЬ сдвинулся
            if (array_2[i][j] == 0) {

                if (i != old_row_zero || j != old_col_zero) {

                    // Запоминаем куда сдивнулся НОЛЬ
                    *new_row_zero = i;
                    *new_col_zero = j;

                    check++;
                }

            }

        }

    }

    if (check == 2) {
        return 1;
    }

    else {
        return 0;
    }
}

// Проверяет мог ли ноль совершить такой переход
void possibility_check (int old_row_zero, int old_col_zero, int new_row_zero, int new_col_zero) {

    if ( ((new_row_zero == (old_row_zero - 1)) && (old_col_zero == new_col_zero)) || ((old_row_zero == new_row_zero) && (new_col_zero == (old_col_zero + 1))) || ((old_col_zero == new_col_zero) && (new_row_zero == (old_row_zero + 1))) || ((old_row_zero == new_row_zero) && (new_col_zero == (old_col_zero - 1)))) {

        printf("Such a move is possible.");

    }

    else {

        printf("Such a move is not possible.");

    }

}


void main(void) {

    FILE* f;

    int array_1[4][4];

    int array_2[4][4];

    int row_elem;

    int col_elem;

    int old_row_zero;

    int old_col_zero;

    int new_row_zero;

    int new_col_zero;

    f = fopen("file1.txt", "r");

    writing_from_file(f, array_1, 4);

    fclose(f);

    f = fopen("file2.txt", "r");

    writing_from_file(f, array_2, 4);

    fclose(f);

    find_zero(array_1, 4, &old_row_zero, &old_col_zero);

    if (swap_check(array_1, array_2, 4, &row_elem, &col_elem, &new_row_zero, &new_col_zero, old_row_zero, old_col_zero)  == 1) {

        possibility_check(old_row_zero, old_col_zero, new_row_zero, new_col_zero);

    }

    else {

        printf("Such a move is not possible.");

    }

    
}
