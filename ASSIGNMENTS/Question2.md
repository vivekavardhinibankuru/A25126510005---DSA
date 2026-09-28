#include <stdio.h>

int main() {
    int n, i, j, key;
    int shifts = 0;

    printf("Enter number of students: ");
    scanf("%d", &n);

    int marks[n];
    printf("Enter %d marks:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &marks[i]);
    }

    for (i = 1; i < n; i++) {
        key = marks[i];
        j = i - 1;

        while (j >= 0 && marks[j] > key) {
            marks[j + 1] = marks[j];
            shifts++;
            j--;
        }
        marks[j + 1] = key;

        printf("After pass %d: ", i);
        for (int k = 0; k < n; k++) {
            printf("%d ", marks[k]);
        }
        printf("\n");
    }

    printf("\nFinal sorted marks: ");
    for (i = 0; i < n; i++) {
        printf("%d ", marks[i]);
    }
    printf("\nTotal number of shifts: %d\n", shifts);

    return 0;
}





<img width="607" height="368" alt="Image" src="https://github.com/user-attachments/assets/aebe65c6-de27-4068-ac44-bb0762bccb84" />
