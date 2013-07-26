#pragma once

template <class Graph, class CostType, class LocMap>
class distance_heuristic : public boost::astar_heuristic<Graph, CostType>
{
	public:
	  typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;

	  distance_heuristic(LocMap l, Vertex goal): m_location(l), m_goal(goal) {}
	  CostType operator()(Vertex u)
	  {
		  return (m_location.at((int)u) + m_location.at(m_goal));
		//	return 0.0f;
	  }

	private:
	  LocMap m_location;
	  Vertex m_goal;
};

struct found_goal {}; // exception for termination

// visitor that terminates when we find the goal
template <class Vertex>
class astar_goal_visitor : public boost::default_astar_visitor
{
	public:
	  astar_goal_visitor(Vertex goal) : m_goal(goal) {}

	  template <class Graph>
	  void examine_vertex(Vertex u, Graph& g) 
	  {
		if(u == m_goal)
		  throw found_goal();
	  }

	private:
	  Vertex m_goal;
};

typedef float cost;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, cost> > mygraph_t;
typedef boost::property_map<mygraph_t, boost::edge_weight_t>::type WeightMap;
typedef mygraph_t::edge_descriptor edge_descriptor;
typedef mygraph_t::vertex_iterator vertex_iterator;

class ActorAnimGraph
{	
typedef std::pair<int, int> edge;
typedef mygraph_t::vertex_descriptor vertex;

private:
	std::vector<std::string> nodes;
	std::vector<float> durations;
	std::vector<edge> edge_array;
	std::vector<cost> weights;

	unsigned int num_edges;
	unsigned int N;
	
private:
	std::string ActorName;

public:
	ActorAnimGraph(const char* Name)
	{
		ActorName = Name;
		num_edges = 0;
		N = 0;
	};

	void AddNode(const char* name, float duration)
	{
		nodes.push_back(name);
		durations.push_back(duration);
		N++;
	}

	void AddEdge(const char* name_source, const char* name_dest)
	{
		int n1 = -1;
		int n2 = -1;

		bool f1 = 0;
		bool f2 = 0;

		for (std::vector<const char*>::size_type i = 0; i < nodes.size(); i++) 
		{
			if (!f1 && !nodes.at(i).compare(name_source))
			{
				n1 = i;
				f1 = true;
			}

			if (!f2 && !nodes.at(i).compare(name_dest))
			{
				n2 = i;
				f2 = true;
			}

			if (f1 && f2)
				break;
		}

		if (n1 >=0 && n2 >= 0)
		{
			edge new_edge;
			new_edge.first = n1;
			new_edge.second = n2;

			edge_array.push_back(new_edge);
			num_edges = edge_array.size();
			weights.push_back(durations.at(n1) + durations.at(n2));
		}
		else
		{
			if (n1 < 0)
				printf("\nAddEdge: Node (%s) isnt found!\n", name_source);

			if (n2 < 0)
				printf("\nAddEdge: Node (%s) isnt found!\n", name_dest);
		}
	}

	std::vector<std::string>* GetPath(const char* name_source, const char* name_goal)
	{
		std::vector<std::string>* result = new std::vector<std::string>;
		int n1 = -1;
		int n2 = -1;

		bool f1 = 0;
		bool f2 = 0;

		for (std::vector<const char*>::size_type i = 0; i < nodes.size(); i++) 
		{
			if (!f1 && !nodes.at(i).compare(name_source))
			{
				n1 = i;
				f1 = true;
			}

			if (!f2 && !nodes.at(i).compare(name_goal))
			{
				n2 = i;
				f2 = true;
			}

			if (f1 && f2)
				break;
		}

		if (n1 >=0 && n2 >= 0)
		{
			mygraph_t g(N + 1);

			WeightMap weightmap = get(boost::edge_weight, g);
			for(std::size_t j = 0; j < num_edges; ++j) 
			{
				edge_descriptor e; bool inserted;
				boost::tie(e, inserted) = add_edge(edge_array[j].first, edge_array[j].second, g);
				weightmap[e] = weights[j];
			}

			vertex start(n1);
			vertex goal(n2);

			std::vector<mygraph_t::vertex_descriptor> p1(num_vertices(g));
			std::vector<cost> d1(num_vertices(g));

			try{
				 astar_search
				  (g, start,
			   distance_heuristic<mygraph_t, cost, std::vector<float>>
				(durations, goal),
			   boost::predecessor_map(&p1[0]).distance_map(&d1[0]).visitor(astar_goal_visitor<vertex>(goal)));
			}
			catch(found_goal) 
			{ // found a path to the goal
				std::list<vertex> shortest_path;
				for(vertex v = goal;; v = p1[v]) 
				{
				  shortest_path.push_front(v);
				  if(p1[v] == v)
					break;
				}
				std::list<vertex>::iterator spi = shortest_path.begin();
				result->push_back(nodes.at(start));
				for(++spi; spi != shortest_path.end(); ++spi)
				{
				  result->push_back(nodes.at(*spi));
				}

				return result;
			}
		}
		else
		{
			if (n1 < 0)
				printf("\GetPath: Node (%s) isnt found!\n", name_source);

			if (n2 < 0)
				printf("\GetPath: Node (%s) isnt found!\n", name_goal);
		}

		return NULL;
	}

	std::string	GetName(void){ return ActorName; };

	virtual ~ActorAnimGraph(void)
	{
	};
};
