
#include <lib/graph/Graph.hpp>

/// --------------------- ///
/// ----    NODE     ---- ///
/// --------------------- ///

Node::Node(const int id) : _id(id)
{
}

int Node::get_id(void) const
{
	return _id;
}

void Node::add_edge(const std::shared_ptr<Edge> edge)
{
	_edges.push_back(edge);
}

std::vector<std::shared_ptr<Edge>> Node::get_edges(void) const
{
	return _edges;
}

std::vector<std::shared_ptr<Edge>>& Node::get_edges_to_modify(void)
{ 
	return _edges;
}

std::string Node::to_string(void) const
{
	std::string s = "Node " + std::to_string(_id) + ":";
	for(const auto &e : _edges) {
		int id = 0;
		if(e->get_nodes().first->get_id() == _id)
			id = e->get_nodes().second->get_id();
		else
			id = e->get_nodes().first->get_id();
		s += "\n\t----> " + std::to_string(id);
	}
	return s;
}

/// --------------------- ///
/// ----    EDGE     ---- ///
/// --------------------- ///

Edge::Edge(std::shared_ptr<Node> node1, std::shared_ptr<Node> node2)
: _node1(node1), _node2(node2)
{
}

std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> Edge::get_nodes(void) const
{
	using namespace std;
	return pair<shared_ptr<Node>, shared_ptr<Node>>{_node1, _node2};
}

void Edge::set_nodes(std::shared_ptr<Node> node1, std::shared_ptr<Node> node2)
{
	_node1 = node1;
	_node2 = node2;
}

std::string Edge::to_string(void) const
{
	return std::to_string(_node1->get_id())
		+ " <------> " + std::to_string(_node2->get_id());
}

