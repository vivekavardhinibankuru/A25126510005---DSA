#include <stdio.h>
#include <limits.h>

#define MAX 20
#define INF INT_MAX

int adj[MAX][MAX];
int n;

int minDistance(int dist[], int visited[]) {
    int min = INF, minIndex = -1;

    for (int v = 0; v < n; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void dijkstra(int src) {
    int dist[MAX];
    int visited[MAX];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, visited);
        if (u == -1) break;  // remaining vertices are unreachable

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && adj[u][v] != 0 && dist[u] != INF &&
                dist[u] + adj[u][v] < dist[v]) {
                dist[v] = dist[u] + adj[u][v];
            }
        }
    }

    printf("\nVertex\tDistance from source %d\n", src);
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) {
            printf("%d\tUnreachable\n", i);
        } else {
            printf("%d\t%d\n", i, dist[i]);
        }
    }
}

int main() {
    int edges, u, v, w, src;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
    }

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges as: u v weight (0-indexed, space-separated)\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d %d", &u, &v, &w);
        adj[u][v] = w;
        adj[v][u] = w;   // undirected graph
    }

    printf("Enter source vertex: ");
    scanf("%d", &src);

    dijkstra(src);

    return 0;
}


<img width="617" height="465" alt="Image" src="https://github.com/user-attachments/assets/a9cbf89f-c70e-460b-835b-4d5b2171b1fd" />
