
#include <lib/file_ops/FileOperations.hpp>
#include <lib/graph/Graph.hpp>

#include <map>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <limits>

using NodePtr = std::shared_ptr<Node>;
using EdgePtr = std::shared_ptr<Edge>;

void create_graph(const std::map<int, std::vector<int>>& adjacency_list,
		std::map<int, NodePtr> &nodes, 
		std::vector<EdgePtr> &edges);

int random_cut(std::map<int, NodePtr>& nodes, 
		std::vector<EdgePtr>& edges);

int combine_nodes(std::pair<NodePtr, NodePtr> nodes);

void delete_edges(std::vector<EdgePtr> &edges);

void print_graph(const std::map<int, NodePtr> &nodes, 
		const std::vector<EdgePtr> &edges);
	

int main(int argc, const char* argv[])
{
	if(argc < 2) {
		std::cout << "Invalid number of arguments." << std::endl;
		std::cout << "Please include filename." << std::endl;
		return -1;
	}

	// Read list from file
	std::string filename(argv[1]);
	std::vector<std::string> input = get_lines_from_file(filename); 
	
	std::map<int, std::vector<int>> adjacency_list;
	for(const auto& line : input) {	
		std::vector<int> num;	
		get_integers_from_line(line, num);	
		adjacency_list[num[0]] = std::vector<int>(num.begin()+1, num.end());
	}

	// Loop X times
	int min_cut = std::numeric_limits<int>::max();
	std::map<int, NodePtr> nodes;
	std::vector<EdgePtr> edges;

	int num_loops = adjaceny_list.size() * adjaceny_list.size();
	for(int i = 0; i < num_loops; ++i) {
		create_graph(adjacency_list, nodes, edges);		
		int cut = random_cut(nodes, edges);
		min_cut = cut < min_cut ? cut : min_cut;
	}

	std::cout << "Random Cut\n";
	std::cout << std::to_string(min_cut) << std::endl;

	return 0;
}

int random_cut(std::map<int, NodePtr>& nodes, 
		std::vector<EdgePtr>& edges)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine gen(seed);

	// While >2 nodes remain
	while(nodes.size() > 2) {
		// Pick a random edge
		std::uniform_int_distribution<int> distribution(0, edges.size()-1);
		int edge_index = distribution(gen);

		// Combine two nodes into single nodes
		int id = combine_nodes(edges[edge_index]->get_nodes());
		nodes.erase(id);
		delete_edges(edges);	
	} 

	return edges.size();
}

int combine_nodes(std::pair<NodePtr, NodePtr> nodes)
{
	// ID for the node we are about to delete
	int id = nodes.second->get_id();

	// Move all edges from node2 to node1
	// OK (and expected) to have both node1 be the nodes for a single node
	for(auto e : nodes.second->get_edges()) {
		std::pair<NodePtr, NodePtr> n = e->get_nodes();
		NodePtr n_other = n.first->get_id() == nodes.second->get_id() ? n.second : n.first;
		e->set_nodes(nodes.first, n_other);
		nodes.first->add_edge(e);
	}

	delete_edges(nodes.first->get_edges_to_modify());

	return id;
}

void delete_edges(std::vector<EdgePtr> &edges)
{
	for(auto it = edges.begin(); it != edges.end();) {
		std::pair<NodePtr, NodePtr> n = (*it)->get_nodes();
		if(n.first->get_id() == n.second->get_id()) {
			edges.erase(it);
		} else {
			++it;
		}
	}
}


void create_graph(const std::map<int, std::vector<int>>& adjacency_list,
		std::map<int, NodePtr> &nodes, 
		std::vector<EdgePtr> &edges)
{
	// Create all the Nodes
	nodes.clear();
	for( auto &elem : adjacency_list ) {
			nodes[elem.first] = std::make_shared<Node>(elem.first);
	}
	
	// Create edges, add to correct nodes
	edges.clear();
	for( auto &elem : adjacency_list ) {
		int id1 = elem.first;
		for(auto &id2 : elem.second) {
			// Does edge already exist?
			if(!std::any_of(edges.begin(), edges.end(), [id1, id2](EdgePtr e) 
					{ std::pair<NodePtr, NodePtr> n = e->get_nodes(); 
						return (n.first->get_id() == id1 && n.second->get_id() == id2) ||
							   (n.first->get_id() == id2 && n.second->get_id() == id1); })) {	
				// If not, create edge and place into
				// edge list for both nodes
				EdgePtr e = std::make_shared<Edge>(nodes[id1], nodes[id2]);
				nodes[id1]->add_edge(e);
				nodes[id2]->add_edge(e);
				edges.push_back(e);
			}

		}
	}
}

void print_graph(const std::map<int, NodePtr> &nodes, 
		const std::vector<EdgePtr> &edges)
{
	std::cout << "Nodes\n----------------" << std::endl;
	for(auto &n : nodes) {
		std::cout << n.second->to_string() << std::endl;
	}

	std::cout << "Edges\n----------------" << std::endl;
	for(auto &e : edges) {
		std::cout << e->to_string() << std::endl;
	}
}

