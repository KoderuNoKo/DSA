#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

int Dijkstra(int** graph, int src, int dst) {
	// TODO: return the length of shortest path from src to dst.
    int n = 0;
    while (graph[n] != nullptr && graph[n][0] != -1) {
        ++n ;
    }

    vector<int> dist(n, INT_MAX);
    vector<bool> visited(n, false);

    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push(make_pair(dist[src], src));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;

        visited[u] = true;
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] > 0) {
                int weight = graph[u][v];
                if (!visited[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
    }

    return dist[dst];
}