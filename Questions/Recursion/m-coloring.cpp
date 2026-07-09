#include <bits/stdc++.h>
using namespace std;

/*
    Function: isSafe()

    Purpose:
    Checks whether assigning the given color 'col' to the current node
    is valid.

    A color is valid if none of the adjacent vertices already have
    the same color.

    Parameters:
    node   -> Current vertex to color
    color  -> Array storing colors assigned to each vertex
    graph  -> Adjacency matrix representation of the graph
    n      -> Number of vertices
    col    -> Color that we want to assign

    Returns:
    true  -> Safe to assign this color
    false -> Another adjacent vertex already has this color
*/
bool isSafe(int node, int color[], bool graph[101][101], int n, int col)
{
    // Traverse every vertex to check if it is adjacent to the current node.
    for (int k = 0; k < n; k++)
    {
        // k != node
        // Ensures we do not compare the current node with itself.

        // graph[k][node] == 1
        // Checks whether vertex 'k' is adjacent (connected) to the current node.

        // color[k] == col
        // Checks whether the adjacent vertex already has the col that we are trying to assign to the current node.
        if (k != node && graph[k][node] == 1 && color[k] == col)
        {
            // Same color found on an adjacent vertex,
            // so this color assignment is not valid.
            return false;
        }
    }
    return true;
}

bool solve(int node, int color[], int m, int N, bool graph[101][101])
{
    // node == N
    // Means all N vertices have been successfully assigned colors.
    if (node == N)
    {
        return true;
    }

    // Try every available color from 1 to m.
    for (int i = 1; i <= m; i++)
    {
        // Checks whether color 'i' can be assigned to the current node.
        if (isSafe(node, color, graph, N, i))
        {
            // Assign the chosen color to the current node.
            color[node] = i;

            // Recursively color the next vertex.
            if (solve(node + 1, color, m, N, graph))
                return true;

            // Backtracking:
            // Remove the assigned color because this choice
            // could not produce a valid coloring for the entire graph.

            color[node] = 0; // backtracking condition where we make the color = 0, means remove the color
        }
    }
    // None of the m colors can be assigned to this node.
    return false;
}

// function to determine if graph can be colored with at most M colors such
// that no two adjacent vertices of graph are colored with same color
bool graphColoring(bool graph[101][101], int m, int N)
{
    // Initially all vertices are uncolored (0 means no color assigned).
    int color[N] = {0};

    // Start coloring from vertex 0.
    if (solve(0, color, m, N, graph))
        return true;

    // No valid coloring exists using at most m colors.
    return false;
}

/*

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;   // N = number of vertices, M = number of edges

    bool graph[101][101] = {0};   // Initially no edges are present

    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;

        // Since the graph is undirected,
        // an edge exists from u to v and from v to u.
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    return 0;
}

*/