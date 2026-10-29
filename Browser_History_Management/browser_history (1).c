/*
 * Browser History Management Using Two Stacks
 *
 * backStack:
 *     Pages available when pressing Back.
 *
 * forwardStack:
 *     Pages available when pressing Forward.
 *
 * current:
 *     The page currently being viewed.
 *
 * Rules:
 *     Visit  -> push current onto backStack and clear forwardStack
 *     Back   -> push current onto forwardStack, then pop backStack
 *     Forward-> push current onto backStack, then pop forwardStack
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL 100

/* ---------- Stack implementation ---------- */

struct Node {
    char url[MAX_URL];
    struct Node *next;
};

struct Stack {
    struct Node *top;
    int size;
};

void initStack(struct Stack *stack) {
    stack->top = NULL;
    stack->size = 0;
}

int isEmpty(const struct Stack *stack) {
    return stack->top == NULL;
}

/*
 * Pushes a URL onto the stack.
 * Returns 1 on success and 0 if memory allocation fails.
 */
int push(struct Stack *stack, const char *url) {
    struct Node *newNode = malloc(sizeof(*newNode));

    if (newNode == NULL) {
        return 0;
    }

    /*
     * url is already guaranteed to fit by readUrl().
     * snprintf() also guarantees null termination when the size is nonzero.
     */
    snprintf(newNode->url, sizeof(newNode->url), "%s", url);

    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;

    return 1;
}

/*
 * Removes the top URL from the stack and stores it in output.
 * Returns 1 on success and 0 if the stack is empty.
 */
int pop(struct Stack *stack, char *output, size_t outputSize) {
    struct Node *temporary;

    if (isEmpty(stack)) {
        return 0;
    }

    temporary = stack->top;

    if (outputSize > 0) {
        snprintf(output, outputSize, "%s", temporary->url);
    }

    stack->top = temporary->next;
    stack->size--;

    free(temporary);

    return 1;
}

void clearStack(struct Stack *stack) {
    char unused[MAX_URL];

    while (pop(stack, unused, sizeof(unused))) {
        /* Continue until the stack is empty. */
    }
}

/*
 * Prints stack contents from top to bottom.
 */
void printStack(const struct Stack *stack) {
    const struct Node *currentNode;
    int position = 1;

    if (isEmpty(stack)) {
        printf("   (none)\n");
        return;
    }

    currentNode = stack->top;

    while (currentNode != NULL) {
        printf("   %d. %s\n", position, currentNode->url);
        currentNode = currentNode->next;
        position++;
    }
}

/* ---------- Browser implementation ---------- */

struct Browser {
    struct Stack backStack;
    struct Stack forwardStack;
    char current[MAX_URL];
    int hasCurrent;
};

void initBrowser(struct Browser *browser) {
    initStack(&browser->backStack);
    initStack(&browser->forwardStack);

    browser->current[0] = '\0';
    browser->hasCurrent = 0;
}

/*
 * Visits a new page.
 */
void visitPage(struct Browser *browser, const char *url) {
    if (browser->hasCurrent) {
        if (!push(&browser->backStack, browser->current)) {
            printf("Memory allocation failed. Page was not visited.\n");
            return;
        }
    }

    snprintf(browser->current, sizeof(browser->current), "%s", url);
    browser->hasCurrent = 1;

    /*
     * Visiting a new page invalidates forward history.
     */
    clearStack(&browser->forwardStack);

    printf("Visited: %s\n", browser->current);
}

/*
 * Moves one page backward.
 */
void goBack(struct Browser *browser) {
    char previousPage[MAX_URL];

    if (isEmpty(&browser->backStack)) {
        printf("No previous page to go back to.\n");
        return;
    }

    /*
     * First save the current page in the forward stack.
     */
    if (!push(&browser->forwardStack, browser->current)) {
        printf("Memory allocation failed. Cannot go back.\n");
        return;
    }

    /*
     * The back stack is known to be nonempty.
     */
    if (pop(&browser->backStack,
            previousPage,
            sizeof(previousPage))) {
        snprintf(browser->current,
                 sizeof(browser->current),
                 "%s",
                 previousPage);

        printf("Went back to: %s\n", browser->current);
    }
}

/*
 * Moves one page forward.
 */
void goForward(struct Browser *browser) {
    char nextPage[MAX_URL];

    if (isEmpty(&browser->forwardStack)) {
        printf("No forward page available.\n");
        return;
    }

    /*
     * First save the current page in the back stack.
     */
    if (!push(&browser->backStack, browser->current)) {
        printf("Memory allocation failed. Cannot go forward.\n");
        return;
    }

    /*
     * The forward stack is known to be nonempty.
     */
    if (pop(&browser->forwardStack,
            nextPage,
            sizeof(nextPage))) {
        snprintf(browser->current,
                 sizeof(browser->current),
                 "%s",
                 nextPage);

        printf("Went forward to: %s\n", browser->current);
    }
}

void showCurrent(const struct Browser *browser) {
    if (!browser->hasCurrent) {
        printf("No page is open yet.\n");
    } else {
        printf("Current page: %s\n", browser->current);
    }
}

void showHistory(const struct Browser *browser) {
    printf("\n---------- Browsing History ----------\n");

    printf("Back pages, most recent first [%d]:\n",
           browser->backStack.size);
    printStack(&browser->backStack);

    printf("Current page:\n");
    if (browser->hasCurrent) {
        printf("   %s\n", browser->current);
    } else {
        printf("   (none)\n");
    }

    printf("Forward pages, next page first [%d]:\n",
           browser->forwardStack.size);
    printStack(&browser->forwardStack);

    printf("--------------------------------------\n");
}

void clearHistory(struct Browser *browser) {
    clearStack(&browser->backStack);
    clearStack(&browser->forwardStack);

    browser->current[0] = '\0';
    browser->hasCurrent = 0;

    printf("History cleared.\n");
}

/* ---------- Input helper functions ---------- */

void clearInputBuffer(void) {
    int character;

    while ((character = getchar()) != '\n' &&
           character != EOF) {
        /* Discard remaining input. */
    }
}

int readInteger(const char *prompt) {
    int value;

    while (1) {
        printf("%s", prompt);

        if (scanf("%d", &value) == 1) {
            clearInputBuffer();
            return value;
        }

        printf("Invalid input. Please enter a number.\n");
        clearInputBuffer();
    }
}

/*
 * Reads a URL without silently truncating it.
 *
 * Returns 1 when a valid URL is read.
 * Returns 0 on end-of-file.
 */
int readUrl(char *destination, size_t destinationSize) {
    size_t length;

    while (1) {
        printf("Enter URL: ");

        if (fgets(destination, destinationSize, stdin) == NULL) {
            destination[0] = '\0';
            return 0;
        }

        length = strlen(destination);

        /*
         * If there is no newline, the input was longer than the buffer.
         */
        if (length == 0 || destination[length - 1] != '\n') {
            clearInputBuffer();
            printf("URL is too long. Maximum length is %zu characters.\n",
                   destinationSize - 1);
            continue;
        }

        /*
         * Remove the trailing newline.
         */
        destination[length - 1] = '\0';

        if (destination[0] == '\0') {
            printf("URL cannot be empty.\n");
            continue;
        }

        return 1;
    }
}

/* ---------- Main program ---------- */

int main(void) {
    struct Browser browser;
    char url[MAX_URL];
    int choice;

    initBrowser(&browser);

    do {
        printf("\n===== Browser History Manager =====\n");
        printf("1. Visit new page\n");
        printf("2. Back\n");
        printf("3. Forward\n");
        printf("4. Show current page\n");
        printf("5. Show full history\n");
        printf("6. Clear history\n");
        printf("0. Exit\n");

        choice = readInteger("Enter your choice: ");

        switch (choice) {
            case 1:
                if (readUrl(url, sizeof(url))) {
                    visitPage(&browser, url);
                }
                break;

            case 2:
                goBack(&browser);
                break;

            case 3:
                goForward(&browser);
                break;

            case 4:
                showCurrent(&browser);
                break;

            case 5:
                showHistory(&browser);
                break;

            case 6:
                clearHistory(&browser);
                break;

            case 0:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);

    /*
     * Release all remaining dynamically allocated nodes.
     */
    clearStack(&browser.backStack);
    clearStack(&browser.forwardStack);

    return 0;
}
