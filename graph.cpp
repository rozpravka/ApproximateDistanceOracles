#include "graph.hpp"
#include <boost/graph/random.hpp>
#include <boost/random.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <iostream>
#include <vector>
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

void run_dijkstra(const Graph& graph, Vertex start_vertex) {
    int num_v = num_vertices(graph);
    std::vector<Vertex> predecessors(num_v, num_v);
    std::vector<int> distances(num_v, std::numeric_limits<int>::max());

    auto indexmap = get(boost::vertex_index, graph);
    auto weightmap = get(boost::edge_weight, graph);

    dijkstra_shortest_paths(graph, start_vertex,
        predecessor_map(boost::make_iterator_property_map(predecessors.begin(), indexmap)).
        distance_map(boost::make_iterator_property_map(distances.begin(), indexmap)).
        weight_map(weightmap));

    std::cout << "Distances from vertex " << start_vertex << ":\n";
    for (Vertex v = 0; v < num_v; ++v) {
        if (distances[v] == std::numeric_limits<int>::max()) {
            std::cout << "Vertex " << v << " is unreachable\n";
            continue;
        }
        std::cout << "Total distance: " << distances[v] << " => Path: {";
        std::vector<Vertex> path;
        for (Vertex u = v; u != start_vertex && u != num_v; u = predecessors[u]) {
            path.push_back(u);
        }
        path.push_back(start_vertex);
        std::reverse(path.begin(), path.end());
        for (size_t i = 0; i < path.size(); ++i) {
            if (i > 0) std::cout << " -> ";
            std::cout << path[i];
        }
        std::cout << "}" << std::endl;
    }
}