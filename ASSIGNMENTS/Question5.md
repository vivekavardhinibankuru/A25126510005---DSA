#include <stdio.h>
#include <stdlib.h>

struct Node {
    int roll;
    struct Node *next;
};

struct Node *head = NULL;

struct Node* createNode(int roll) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->roll = roll;
    newNode->next = NULL;
    return newNode;
}

void insertBeginning(int roll) {
    struct Node *newNode = createNode(roll);
    newNode->next = head;
    head = newNode;
    printf("Inserted %d at the beginning\n", roll);
}

void insertEnd(int roll) {
    struct Node *newNode = createNode(roll);
    if (head == NULL) {
        head = newNode;
    } else {
        struct Node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("Inserted %d at the end\n", roll);
}

void search(int roll) {
    struct Node *temp = head;
    int pos = 1;
    while (temp != NULL) {
        if (temp->roll == roll) {
            printf("Roll number %d found at position %d\n", roll, pos);
            return;
        }
        temp = temp->next;
        pos++;
    }
    printf("Roll number %d is not available\n", roll);
}

void deleteRoll(int roll) {
    struct Node *temp = head, *prev = NULL;

    if (head == NULL) {
        printf("List is empty, cannot delete\n");
        return;
    }
    if (head->roll == roll) {
        head = head->next;
        free(temp);
        printf("Deleted %d\n", roll);
        return;
    }
    while (temp != NULL && temp->roll != roll) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Roll number %d is not available, cannot delete\n", roll);
        return;
    }
    prev->next = temp->next;
    free(temp);
    printf("Deleted %d\n", roll);
}

void display() {
    struct Node *temp = head;
    if (temp == NULL) {
        printf("List is empty\n");
        return;
    }
    printf("List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->roll);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    int choice, roll;

    while (1) {
        printf("***----- Singly Linked List Menu -----***\n");
        printf("1. Insert at beginning\t2. Insert at end\t3. Search\t");
        printf("4. Delete\t5. Display\t6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter roll number: ");
                scanf("%d", &roll);
                insertBeginning(roll);
                display();
                break;
            case 2:
                printf("Enter roll number: ");
                scanf("%d", &roll);
                insertEnd(roll);
                display();
                break;
            case 3:
                printf("Enter roll number to search: ");
                scanf("%d", &roll);
                search(roll);
                break;
            case 4:
                printf("Enter roll number to delete: ");
                scanf("%d", &roll);
                deleteRoll(roll);
                display();
                break;
            case 5:
                display();
                break;
            case 6:
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
}


<img width="1165" height="831" alt="Image" src="https://github.com/user-attachments/assets/305d0673-b797-44b6-a856-2e0b3a2979bd" />
