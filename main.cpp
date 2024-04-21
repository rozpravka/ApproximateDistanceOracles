#include "graph.hpp"

int main() {
    Graph graph;
    //num_of_vertices, num_of_edges, seed
    create_graph(graph, 50, 300, 42);
    print_graph(graph);

    return 0;
}
