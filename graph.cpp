#include "graph.hpp"
#include <boost/graph/random.hpp>
#include <boost/random.hpp>
#include <iostream>
#include <ctime>

void create_graph(Graph& graph, int num_vertices, int num_edges, unsigned int seed) {
    boost::mt19937 rng; rng.seed(seed);
    boost::generate_random_graph(graph, num_vertices, num_edges, rng, false, true);

    boost::graph_traits<Graph>::edge_iterator curr_edge, out_of_scope;
    for (boost::tie(curr_edge, out_of_scope) = edges(graph); curr_edge != out_of_scope; ++curr_edge) {
        int weight = std::rand() % 11; // weights will be in the range 0 to 10
        put(boost::edge_weight, graph, *curr_edge, weight);
    }
}

void print_graph(const Graph& graph) {
    for (int vertex = 0; vertex < num_vertices(graph); ++vertex) {
        std::cout << vertex << " - ";
        std::pair<AdjacencyIterator, AdjacencyIterator> neighbors = adjacent_vertices(vertex, graph);

        for (AdjacencyIterator neighboring_vertex = neighbors.first; neighboring_vertex != neighbors.second; ++neighboring_vertex) {
            std::cout << *neighboring_vertex << " " 
                      << get(boost::edge_weight, graph, edge(vertex, *neighboring_vertex, graph).first) << ", ";
        }
        std::cout << std::endl;
    }
}
