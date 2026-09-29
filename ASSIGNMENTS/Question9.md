#include <stdio.h>

#define MAX 20

int adj[MAX][MAX];
int visited[MAX];
int n;

void bfs(int start) {
    int queue[MAX], front = 0, rear = 0;
    int i;

    printf("BFS traversal starting from vertex %d: ", start);

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);

        for (i = 0; i < n; i++) {
            if (adj[current][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
    printf("\n");
}

int main() {
    int edges, u, v, start, i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
        visited[i] = 0;
    }

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (vertex pairs, 0-indexed):\n");
    for (i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1;   // undirected graph
    }

    printf("Enter starting vertex: ");
    scanf("%d", &start);

    bfs(start);

    // Check if all vertices were visited (fully connected check)
    int allVisited = 1;
    printf("\nUnvisited vertices: ");
    int noneFound = 1;
    for (i = 0; i < n; i++) {
        if (!visited[i]) {
            printf("%d ", i);
            allVisited = 0;
            noneFound = 0;
        }
    }
    if (noneFound) printf("None");
    printf("\n");

    if (allVisited) {
        printf("The graph is fully connected.\n");
    } else {
        printf("The graph is NOT fully connected from vertex %d.\n", start);
    }

    return 0;
}


<img width="537" height="317" alt="Image" src="https://github.com/user-attachments/assets/1dd25220-e357-482c-b6ae-52ce36c6f07f" />
