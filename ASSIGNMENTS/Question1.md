#include <stdio.h>

int main() {
    int n, i, key;
    int low, high, mid;
    int comparisons = 0, found = 0;

    printf("Enter number of employees: ");
    scanf("%d", &n);

    int ids[n];
    printf("Enter %d employee IDs in ascending order:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &ids[i]);
    }

    printf("Enter the employee ID to search: ");
    scanf("%d", &key);

    low = 0;
    high = n - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        comparisons++;

        if (ids[mid] == key) {
            printf("Employee ID %d found at position %d (index %d)\n",
                   key, mid + 1, mid);
            found = 1;
            break;
        } else if (key < ids[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    if (!found) {
        printf("Employee ID %d not found in the list.\n", key);
    }

    printf("Number of comparisons: %d\n", comparisons);

    return 0;
}



<img width="497" height="240" alt="Image" src="https://github.com/user-attachments/assets/ea048ec8-fe09-42c7-a250-e5ce00fbac5c" />
<img width="441" height="231" alt="Image" src="https://github.com/user-attachments/assets/62087f9e-9cd6-4e0d-bcb0-565f6434c17f" />
