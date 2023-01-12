#pragma once
#include "GraphEnums.h"
#include "Node.h"
#include "Connection.h"
#include "Grid.h"

class GridGraph final
{
public:
	GridGraph(Grid* pGrid);

	~GridGraph();

	GridGraph(GridGraph& rhs) = delete;
	GridGraph(GridGraph&& rhs) = delete;

	GridGraph& operator=(GridGraph& rhs) = delete;
	GridGraph& operator=(GridGraph&& rhs) = delete;

	void InitializeGrid(Grid* pGrid);

	void Render();

	void Update(const Grid* pGrid, const std::deque<int>& snake);
	void ResetGraph();

	Node* GetNode(int idx) const { return m_Nodes[idx]; };
	bool IsNodeValid(int idx) const { return (idx < (int)m_Nodes.size() && idx != invalid_node_index); };

	int GetGraphSize() const { return m_GridAmount; }

	int GetIndex(int col, int row) const { return row * m_GridAmount + col; }

	void RemoveConnectionssToAdjacentNodes(int idx);
	void AddConnectionsToAdjacentCells(int idx);

	int GetNrOfNodes() const { return (int)m_Nodes.size(); }
	bool IsEmpty() const { return m_Nodes.empty(); }
	bool IsUniqueConnection(int from, int to) const;

	float GetNoteRadius() const { return m_NoteRadius; };
	Point2f GetNodePos(Node* pNode) const { return pNode->GetPosition(); };
	Point2f GetNodePos(int idx) const { return GetNodePos(GetNode(idx)); }

	Node* GetStartNode() { return m_Nodes[m_Head]; }
	Node* GetEndNode() { return m_Nodes[m_Apple]; }

	std::vector<Connection*>GetNodeConnections(Node* pNode);

private:
	float m_NoteRadius{ 5.f };

	int m_Head{};
	int m_Apple{};

	int m_GridAmount;
	float m_CellSize;

	const std::vector<Point2f> m_Directions = { Point2f{ 1, 0 }, Point2f{ 0, 1 }, Point2f{ -1, 0 }, Point2f{ 0, -1 } };

	std::vector<Connection*> m_Connections{};
	std::vector<Node*> m_Nodes{};

	int m_NextNodeIndex{};
};

