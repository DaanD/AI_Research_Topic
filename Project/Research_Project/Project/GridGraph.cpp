#include "pch.h"
#include "GridGraph.h"

GridGraph::GridGraph(Grid* pGrid)
	:m_GridAmount{pGrid->GetGridSize()}, m_CellSize(pGrid->GetCellSize())
{
	InitializeGrid(pGrid);
}

GridGraph::~GridGraph()
{
	for (int i{}; i < m_Nodes.size(); i++)
	{
		delete m_Nodes[i];
		m_Nodes[i] = nullptr;
	}
	m_Nodes.clear();

	for (int i{}; i < m_Nodes.size(); i++)
	{
		delete m_Nodes[i];
		m_Nodes[i] = nullptr;
	}
	m_Nodes.clear();
}

void GridGraph::InitializeGrid(Grid* pGrid)
{
	auto nodeCenters{*pGrid->GetGrid()};

	m_Nodes.resize(nodeCenters.size());

	for (int i{}; i < nodeCenters.size(); i++)
	{
		m_Nodes[i] = new Node{ i };
		m_Nodes[i]->SetPosition(nodeCenters[i]);
		AddConnectionsToAdjacentCells(i);
	}
}

void GridGraph::Render()
{
	for (auto& node : m_Nodes)
	{
		node->Render(m_CellSize);
	}

	utils::SetColor(Color4f{ 0.f, 0.f, 0.f, 1.f });
	for (auto& connection : m_Connections)
	{
		connection->Render(m_Nodes[connection->GetFrom()]->GetPosition(), m_Nodes[connection->GetTo()]->GetPosition());
	}
}

void GridGraph::Update(const Grid* pGrid, const std::deque<int>& snake)
{
	ResetGraph();

	for (auto index : snake)
	{
		m_Nodes[index]->SetType(NodeType::Snake);
		RemoveConnectionssToAdjacentNodes(index);
	}

	m_Nodes[pGrid->GetApplePos()]->SetType(NodeType::Apple);
}

void GridGraph::ResetGraph()
{
	for (int i{}; i < m_Nodes.size(); i++)
	{
		switch (m_Nodes[i]->GetNodeType())
		{
		case NodeType::Normal:
		default:
			break;
		case NodeType::Snake:
			AddConnectionsToAdjacentCells(i);
		case NodeType::Apple:
			m_Nodes[i]->SetType(NodeType::Normal);
			break;
		}
	}
}

void GridGraph::RemoveConnectionssToAdjacentNodes(int idx)
{
	m_Connections.erase(std::remove_if(m_Connections.begin(), m_Connections.end(), [&](Connection* connection)
		{
			return connection->GetFrom() == idx || connection->GetTo() == idx;
		}
	), m_Connections.end());
}

void GridGraph::AddConnectionsToAdjacentCells(int idx)
{
	int newIdx{};

	//If node is in upper row, don't add connection up
	if (idx >= m_GridAmount)
	{
		newIdx = idx - m_GridAmount;
		if (IsUniqueConnection(idx, newIdx))
		{
			m_Connections.push_back(new Connection{idx, newIdx});
		}
	}

	//If node is in right column, don't add connection to the right
	if (idx % m_GridAmount != m_GridAmount - 1)
	{
		newIdx = idx + 1;
		if (IsUniqueConnection(idx, newIdx))
		{
			m_Connections.push_back(new Connection{ idx, newIdx });
		}
	}

	//If node is in lower row, don't add connection down
	if (idx < m_GridAmount * (m_GridAmount - 1))
	{
		newIdx = idx + m_GridAmount;
		if (IsUniqueConnection(idx, newIdx))
		{
			m_Connections.push_back(new Connection{ idx, newIdx });
		}
	}

	//If node is in left column, don't add connection to the left
	if (idx % m_GridAmount != 0)
	{
		newIdx = idx - 1;
		if (IsUniqueConnection(idx, newIdx))
		{
			m_Connections.push_back(new Connection{ idx, newIdx });
		}
	}
}

bool GridGraph::IsUniqueConnection(int from, int to) const
{
	for (int i{}; i < m_Connections.size(); i++)
	{
		if (m_Connections[i]->GetFrom() == from)
		{
			if (m_Connections[i]->GetTo() == to)
			{
				return false;
			}
		}
	}

	return true;
}
