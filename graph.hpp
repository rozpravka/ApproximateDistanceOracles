#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, 
    boost::no_property, boost::property<boost::edge_weight_t, int>> Graph;

typedef boost::graph_traits<Graph>::edge_descriptor Edge;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::adjacency_iterator AdjacencyIterator;

void create_graph(Graph& graph, int num_vertices, int num_edges, unsigned int seed);
void print_graph(const Graph& graph);
void run_dijkstra(const Graph& graph, Vertex start_vertex);

#endif