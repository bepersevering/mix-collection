#include <iostream>
#include <queue>
#include <vector>

class Graph {

private:
  int numVertices;
  std::vector<std::vector<int>> adj;

public:
  // Constructor to create a graph with n vertices
  Graph(int n) : numVertices(n), adj(n) {}

  // add an edge to the graph
  void addEdge(int src, int dest) {
    adj[src].push_back(dest);
    adj[dest].push_back(src);
  }

  // Perform BFS traversal and return the order of visited nodes
  std::vector<int> bfs(int start) {
    std::vector<bool> visited(numVertices, false);
    std::queue<int> queue;
    std::vector<int> visitOrder;

    // Mark the starting vertex as visted an enqueue it
    visited[start] = true;
    queue.push(start);

    // stanard bfs loop
    while (!queue.empty()) {
      // dequeue a vertex adnd add to visit order
      int current = queue.front();

      queue.pop();
      visitOrder.push_back(current);

      for (int neighbor : adj[current]) {
        if (!visited[neighbor]) {
          queue.push(neighbor);
          visited[neighbor] = true;
        }
      }
    }

    return visitOrder;
  }
};

void runTests() {
  {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 4);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    std::vector<int> visitOrder = g.bfs(0);
    std::cout << "Test case 1-BFS from vertes 0: ";
    for (int vertex : visitOrder) {
      std::cout << vertex << " ";
    }

    std::cout << std::endl;
  }

  // Test case 2: Different start
  {
    Graph g(3);
    g.addEdge(0, 1);
    g.addEdge(1, 2);

    std::vector<int> visitOrder = g.bfs(2);

    std::cout << "Test case 2 - BFS from vertex 2: ";
    for (int vertex : visitOrder) {
      std::cout << vertex << " ";
    }
    std::cout << std::endl;
  }

  // Test case 3: With cycle
  {
    Graph g(3);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);

    std::vector<int> visitOrder = g.bfs(0);

    std::cout << "Test case 3 - BFS with cycle from vertex 0: ";
    for (int vertex : visitOrder) {
      std::cout << vertex << " ";
    }
    std::cout << std::endl;
  }

  // Test case 4: Single node
  {
    Graph g(1);

    std::vector<int> visitOrder = g.bfs(0);

    std::cout << "Test case 4 - BFS single node: ";
    for (int vertex : visitOrder) {
      std::cout << vertex << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  runTests();
  return 0;
}
