#include <vector>
#include <iostream>
#include <limits.h>
#include <tuple>
#include <cassert>

using namespace std;

const int INF = 1e9;

/**
 * @brief Implements the Bellman-Ford algorithm to find shortest paths from a source vertex to all other vertices in a weighted directed graph, and detects negative cycles.
 *
 * @note Time Complexity: O(V*E), where V is the number of vertices and E is the number of edges.
 * @note Space Complexity: O(V) for storing distances.
 *
 * @param V The number of vertices in the graph.
 * @param edges A vector of tuples, where each tuple represents an edge (u, v, w) from vertex u to vertex v with weight w.
 * @param source The source vertex to start the shortest path calculation from.
 * @param dist A vector to store the shortest distances from the source vertex to all other vertices. Initialized to infinity. Vertices not reachable from the source will remain at infinity.
 *
 * @return True if a negative cycle is detected in the graph, false otherwise.
 *         If no negative cycle is detected, the 'dist' vector will contain the shortest distances from the source. Vertices not reachable from the source will have a distance of INF.
 *         If a negative cycle is detected, the 'dist' vector may contain incorrect shortest path distances due to the cycle.
 */
bool bellmanFord(int V, const vector<tuple<int, int, int>>& edges, int source, vector<int>& dist) {
    dist.assign(V, INF);
    dist[source] = 0;

    for (int i = 1; i <= V - 1; ++i) {
        for (const auto& edge : edges) {
            int u, v, w;
            tie(u, v, w) = edge;
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    for (const auto& edge : edges) {
        int u, v, w;
        tie(u, v, w) = edge;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            return true; // Negative cycle detected
        }
    }

    return false; // No negative cycle
}

void testBellmanFord() {
    {
        // Test case 1: Basic test with no negative cycle.
        int V = 5;
        vector<tuple<int, int, int>> edges = {
            {0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2}, {1, 4, 2},
            {3, 2, 5}, {3, 1, 1}, {4, 3, -3}
        };
        int source = 0;
        vector<int> dist;
        bool negative_cycle = bellmanFord(V, edges, source, dist);
        assert(!negative_cycle);
        vector<int> expected_dist = {0, -1, 2, -2, 1};
        assert(dist == expected_dist);
    }

    {
        // Test case 2: Test with a negative cycle.
        int V = 3;
        vector<tuple<int, int, int>> edges = {
            {0, 1, -1}, {1, 2, -2}, {2, 0, -3}
        };
        int source = 0;
        vector<int> dist;
        bool negative_cycle = bellmanFord(V, edges, source, dist);
        assert(negative_cycle);
    }

    {
        // Test case 3: Test with disconnected components.
        int V = 4;
        vector<tuple<int, int, int>> edges = {
            {0, 1, 1}, {2, 3, 1}
        };
        int source = 0;
        vector<int> dist;
        bool negative_cycle = bellmanFord(V, edges, source, dist);
        assert(!negative_cycle);
        vector<int> expected_dist = {0, 1, INF, INF};
        assert(dist == expected_dist);
    }

    {
        // Test case 4: Simple cycle with positive weights.
        int V = 3;
        vector<tuple<int, int, int>> edges = {
            {0, 1, 1}, {1, 2, 1}, {2, 0, 1}
        };
        int source = 0;
        vector<int> dist;
        bool negative_cycle = bellmanFord(V, edges, source, dist);
        assert(!negative_cycle);
        vector<int> expected_dist = {0, 1, 2};
        assert(dist == expected_dist);
    }

    {
        // Test case 5: Cycle with zero weights.
        int V = 3;
        vector<tuple<int, int, int>> edges = {
            {0, 1, 0}, {1, 2, 0}, {2, 0, 0}
        };
        int source = 0;
        vector<int> dist;
        bool negative_cycle = bellmanFord(V, edges, source, dist);
        assert(!negative_cycle);
        vector<int> expected_dist = {0, 0, 0};
        assert(dist == expected_dist);
    }

    {
        // Test case 6: Complex graph with a path containing negative weights, but no negative cycle.
        int V = 7;
        vector<tuple<int, int, int>> edges = {
            {0, 1, 1}, {0, 2, 2}, {1, 3, 3}, {2, 4, 4},
            {3, 5, 5}, {4, 6, 6}, {5, 6, -1}, {6, 3, -2}
        };
        int source = 0;
        vector<int> dist;
        bool negative_cycle = bellmanFord(V, edges, source, dist);
        assert(!negative_cycle);
        vector<int> expected_dist = {0, 1, 2, 4, 6, 9, 8};
        assert(dist == expected_dist);
    }
    
}

void runBellmanFordSample() {
    int V = 5;
    vector<tuple<int, int, int>> edges = {
        {0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2}, {1, 4, 2},
        {3, 2, 5}, {3, 1, 1}, {4, 3, -3}
    };
    int source = 0;
    vector<int> dist;

    bool negative_cycle = bellmanFord(V, edges, source, dist);

    if (negative_cycle) {
        cout << "Negative cycle detected!" << endl;
    } else {
        cout << "Shortest distances from source " << source << ":" << endl;
        for (int i = 0; i < V; ++i) {
            cout << "Vertex " << i << ": ";
            if (dist[i] == INF) {
                cout << "INF" << endl;
            } else {
                cout << dist[i] << endl;
            }
        }
    }
}

int main() {
    testBellmanFord();
    runBellmanFordSample();
    return 0;
}
