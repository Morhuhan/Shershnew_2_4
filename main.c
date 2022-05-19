#include <stdio.h>
#include <string.h>


// Считывает числа из файла в двумерный массив
void writing_from_file(FILE *f,  int array[][4], int rows) {

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < 4; j++) {

            fscanf(f, "%d", &array[i][j]);
        }

    }
}


void possibility_check(int array_1[][4],int array_2[][4], int rows) {

    int row_elem;

    int col_elem;

    int old_row_zero;

    int old_col_zero;

    int new_row_zero;

    int new_col_zero;

    int check = 0;


    // Находим где был ноль в массиве 1
    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < 4; j++) {

            if (array_1[i][j] == 0) {

                old_row_zero = i;
                old_col_zero = j;

            }
        }

    }
    
    // Проверяем, поменялись ли ровно 1 число и 0 местами и запоминает куда встал ноль и куда встало число
    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 4; j++) {

            // Число сдивнулось и это НЕ ноль 
            if ((array_1[i][j] != array_2[i][j]) && (array_2[i][j] != 0)) {

                check++;

                // Запоминаем КУДА сдвинулось число
                row_elem = i;
                col_elem = j;

            }

            // НОЛЬ сдвинулся
            if (array_2[i][j] == 0) {

                if (i != old_row_zero || j != old_col_zero) {

                    // Запоминаем куда сдивнулся НОЛЬ
                    new_row_zero = i;
                    new_col_zero = j;

                    check++;
                }

            }

        }
    }

    // Проверяет мог ли ноль совершить такой переход
    if ( ((new_row_zero == (old_row_zero - 1)) && (old_col_zero == new_col_zero)) || ((old_row_zero == new_row_zero) && (new_col_zero == (old_col_zero + 1))) || ((old_col_zero == new_col_zero) && (new_row_zero == (old_row_zero + 1))) || ((old_row_zero == new_row_zero) && (new_col_zero == (old_col_zero - 1)))) {

        printf("move IS possible.");

    }

    else {

        printf("move is NOT possible.");

    }

}


void check_arguments(char* argv[], int argc) {

    if ( (strcmp(argv[1], "file1.txt") != 0) || (strcmp(argv[2], "file2.txt") != 0) ) {

        printf("Wrong file's names");

        exit(0);

    }

}

void main(int argc, char* argv[]) {

    check_arguments(argv, argc);

    FILE* f;

    int array_1[4][4];

    int array_2[4][4];

    int row_elem;

    int col_elem;

    int old_row_zero;

    int old_col_zero;

    int new_row_zero;

    int new_col_zero;

    f = fopen(argv[1], "r");

    writing_from_file(f, array_1, 4);

    fclose(f);

    f = fopen(argv[2], "r");

    writing_from_file(f, array_2, 4);

    fclose(f);

    possibility_check(array_1, array_2, 4);

    
}
