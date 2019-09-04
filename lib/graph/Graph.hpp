
#pragma once

#include <vector>
#include <memory>

class Edge; // Forward declaration for Node class

/// Representation of a node for a basic graph.
/// Nodes will have an identifier and hold a pointer
/// to all of the edges it belongs to
class Node 
{
public:
	/// Construcor
	/// @param [in] id Integer number unique to identify node
	Node(const int id);

	/// Default destructor
	~Node(void) = default;

	/// The identifier number for node
	/// @return Node ID
	int get_id(void) const;

	/// Add an edge to the node. The edge should already be
	/// fully defined and pointing to correct nodes. This method
	/// will not do any validation.
	/// @param [in] edge Pointer to the edge to be added
	void add_edge(const std::shared_ptr<Edge> edge);

	/// Get the list of the nodes edges
	/// @retrun Container of edges
	std::vector<std::shared_ptr<Edge>> get_edges(void) const;

	/// Get a reference to the edges of the node for the intention of
	/// modifying the contents
	/// @return Reference to container holding edges
	std::vector<std::shared_ptr<Edge>>& get_edges_to_modify(void);

	/// String representation of node for debugging
	/// @return String showing the node id and edges
	std::string to_string(void) const;

private:
	/// Identifier for node
	int _id;

	/// Container for edges containing node.
	std::vector<std::shared_ptr<Edge>> _edges;
};

/// Representation of an edge for a basi graph.
/// Edge will contain pointer to the two nodes
/// that make up the edge.
class Edge
{
public:
	/// Construtor
	/// @param [in] node1 The first node that makes up the edge
	/// @param [in] node2 The second node that makes up the edge
	Edge(std::shared_ptr<Node> node1, std::shared_ptr<Node> node2);

	/// Default destructor
	~Edge(void) = default;

	/// Re-define the edge with new nodes
	/// @param [in] node1 First node of edge
	/// @param [in] node2 Second node of edge
	void set_nodes(std::shared_ptr<Node> node1, std::shared_ptr<Node> node2);

	/// Get the pair of nodes that make up the edge
	/// @return Pair of pointers to the nodes
	std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> get_nodes(void) const;

	/// String representaiton of edge for debugging
	/// @return String showing the two nodes
	std::string to_string(void) const;

private:
	/// First node in edge
	std::shared_ptr<Node> _node1;

	/// Second node in edge
	std::shared_ptr<Node> _node2;
};
