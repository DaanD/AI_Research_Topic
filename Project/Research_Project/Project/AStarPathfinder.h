#pragma once
#include "PathFinder.h"
#include "Node.h"
#include "Connection.h"
class GridGraph;

class AStarPathfinder : public PathFinder
{
public:
	AStarPathfinder(std::weak_ptr<GridGraph> graph)
		:PathFinder(graph)
	{
		m_HeuristicFunction = HeuristicFunctions::Manhattan;
	}

	virtual void Render() const override;

	virtual Direction GetDirectionOutPut() override;

private:
	
	std::vector<int> m_Path{};

	std::vector<int> GetPath();

	Heuristic m_HeuristicFunction;

	float GetHeuristicCost(Node* pStartNode, Node* pEndNode) const;
};

struct NodeRecord
{
	Node* pNode = nullptr;
	Connection* pConnection = nullptr;
	float costSoFar = 0.f; // accumulated g-costs of all the connections leading up to this one
	float estimatedTotalCost = 0.f; // f-cost (= costSoFar + h-cost)

	bool operator==(const NodeRecord& other) const
	{
		return pNode == other.pNode
			&& pConnection == other.pConnection
			&& costSoFar == other.costSoFar
			&& estimatedTotalCost == other.estimatedTotalCost;
	};

	bool operator<(const NodeRecord& other) const
	{
		return estimatedTotalCost < other.estimatedTotalCost;
	};
};
