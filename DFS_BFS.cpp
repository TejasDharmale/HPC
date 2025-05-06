#include <iostream>
#include <string.h>
#include <omp.h>

using namespace std;

const int MAXN = 100;

int adj_matrix[MAXN][MAXN];
int adj_list[MAXN][MAXN];
int dist[MAXN];
bool visited[MAXN];
omp_lock_t locks[MAXN];

void dfs(int node)
{
    visited[node] = true;
    cout << node << " ";

#pragma omp parallel for
    for (int i = 0; i < MAXN; i++)
    {
        if (adj_matrix[node][i])
        {
            omp_set_lock(&locks[i]);
            if (!visited[i])
            {
                visited[i] = true;
                omp_unset_lock(&locks[i]);
                dfs(i);
            }
            else
            {
                omp_unset_lock(&locks[i]);
            }
        }
    }
}

void bfs(int node)
{
    memset(dist, -1, sizeof(dist));
    dist[node] = 0;

    int q[MAXN];
    int front = 0, rear = 0;
    q[rear++] = node;

    while (front != rear)
    {
        int u = q[front++];
        cout << u << " ";

#pragma omp parallel for
        for (int i = 0; i < MAXN; i++)
        {
            if (adj_list[u][i])
            {
                omp_set_lock(&locks[i]);
                if (dist[i] == -1)
                {
                    dist[i] = dist[u] + 1;
                    q[rear++] = i;
                }
                omp_unset_lock(&locks[i]);
            }
        }
    }
}

int main()
{
    int n, m;
    cout << "Enter the number of nodes: ";
    cin >> n;
    cout << "Enter the number of edges: ";
    cin >> m;

    for (int i = 0; i < MAXN; i++)
    {
        for (int j = 0; j < MAXN; j++)
        {
            adj_matrix[i][j] = 0;
            adj_list[i][j] = 0;
        }
        visited[i] = false;
        omp_init_lock(&locks[i]);
    }

    cout << "Enter the edges: " << endl;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cout << "Enter edge " << i + 1 << " (u v): ";
        cin >> u >> v;
        adj_matrix[u][v] = adj_matrix[v][u] = 1;
        adj_list[u][v] = adj_list[v][u] = 1;
    }

    int start_node;
    cout << "Enter the starting node for DFS and BFS: ";
    cin >> start_node;

    cout << "DFS: ";
    dfs(start_node);
    cout << endl;

    cout << "BFS: ";
    bfs(start_node);
    cout << endl;

    for (int i = 0; i < MAXN; i++)
    {
        omp_destroy_lock(&locks[i]);
    }

    return 0;
}
