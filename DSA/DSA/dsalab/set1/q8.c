#include <stdio.h>

typedef struct {
    int row;
    int col;
    int value;
} Element;

void countNonZeroElements(Element matrix[], int size, int rows) {
    for (int i = 0; i < rows; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (matrix[j].row == i && matrix[j].value != 0) {
                count++;
            }
        }
        printf("Row %d has %d non-zero elements.\n", i, count);
    }
}

int main() {
    Element matrix[] = {{0, 0, 3}, {1, 2, 5}, {2, 1, 0}, {2, 2, 4}};
    int rows = 3; // Example with 3 rows
    countNonZeroElements(matrix, 4, rows);

    return 0;
}
