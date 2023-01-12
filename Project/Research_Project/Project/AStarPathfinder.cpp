#include "pch.h"
#include "AStarPathfinder.h"
#include "GridGraph.h"

void AStarPathfinder::Render() const
{
    if (m_Path.size() <= 1)
        return;


    Point2f pos1{m_pGraph.lock()->GetNode(m_Path[0])->GetPosition()};
    Point2f pos2{};

    utils::SetColor(Color4f{ 0.f, 0.f, 1.f, 1.f });

    for (int i{ 1 }; i < m_Path.size(); i++)
    {
        pos2 = m_pGraph.lock()->GetNode(m_Path[i])->GetPosition();
        utils::DrawLine(pos1, pos2, 2.f);
        pos1 = pos2;
    }

	utils::FillEllipse(m_pGraph.lock()->GetEndNode()->GetPosition(), 5, 5);
	utils::FillEllipse(m_pGraph.lock()->GetNode(m_Path[m_Path.size()-1])->GetPosition(), 5, 5);
}

Direction AStarPathfinder::GetDirectionOutPut(Direction lastDirection)
{
    m_Path = GetPath();

    if(m_Path.size() <= 1)
        return Direction::Down;

	int headIndex{ m_Path[0] };
	int nextIndex{ m_Path[1] };
	int difference{ nextIndex - headIndex };

	const int graphSize{ m_pGraph.lock()->GetGraphSize() };

    Direction direction{};

	if (difference == -graphSize)
		direction = Direction::Up;
	else if (difference == graphSize)
		direction = Direction::Down;
	else if (difference == -1)
		direction = Direction::Left;
	else if (difference == 1)
		direction = Direction::Right;

    return direction;
}

std::vector<int> AStarPathfinder::GetPath()
{
    auto pGraph{ m_pGraph.lock()};

    Node* pStartNode{ pGraph->GetStartNode() };
    Node* pEndNode{ pGraph->GetEndNode() };

    std::vector<int> path{};
    std::vector<NodeRecord> openList;
    std::vector<NodeRecord> closedList;
    NodeRecord currentRecord{};

    currentRecord.pNode = pStartNode;
    currentRecord.pConnection = nullptr;
    currentRecord.estimatedTotalCost = GetHeuristicCost(pStartNode, pEndNode);
    openList.push_back(currentRecord);

	while (!openList.empty())
	{
		currentRecord = *std::min_element(openList.begin(), openList.end());

		if (currentRecord.pNode == pEndNode)
		{
			break;
		}

		for (auto& connection : pGraph->GetNodeConnections(currentRecord.pNode))
		{
			float cost{ currentRecord.costSoFar + connection->GetCost() };

			bool isCheaper{ false };

			Node* pNextNode{ pGraph->GetNode(connection->GetTo()) };

			for (auto& item : closedList)
			{
				if (item.pNode == pNextNode)
				{
					if (item.costSoFar < cost)
					{
						isCheaper = true;
						break;
					}

					closedList.erase(std::remove(closedList.begin(), closedList.end(), item));
				}
			}

			if (isCheaper)
				continue;

			for (auto& item : openList)
			{
				if (item.pNode == pNextNode)
				{
					if (item.costSoFar < cost)
					{
						isCheaper = true;
						break;
					}
					openList.erase(std::remove(openList.begin(), openList.end(), item));
				}
			}

			if (!isCheaper)
			{
				NodeRecord newRecord;

				newRecord.pNode = pGraph->GetNode(connection->GetTo());
				newRecord.pConnection = connection;
				newRecord.costSoFar = cost;
				newRecord.estimatedTotalCost = cost + GetHeuristicCost(newRecord.pNode, pEndNode);

				openList.push_back(newRecord);
			}
		}
		openList.erase(std::remove(openList.begin(), openList.end(), currentRecord));
		closedList.push_back(currentRecord);
	}

	if (currentRecord.pNode != pEndNode)
	{
		for (const NodeRecord& existingRecord : closedList)
		{
			if (existingRecord.estimatedTotalCost - existingRecord.costSoFar < currentRecord.estimatedTotalCost - currentRecord.costSoFar)
			{
				currentRecord = existingRecord;
			}
		}
	}

	//check if there are cheaper connections left in open list
	for (const NodeRecord& upcomingRecord : openList)
	{
		bool isInClosedList{ false };

		//check all nodes in closed list
		for (NodeRecord& existingRecord : closedList)
		{
			//check if upcoming record already has existing connection in closed list
			if (upcomingRecord.pNode == existingRecord.pNode)
			{
				//if upcoming record has a cheaper cost so far, replace the connection and cost so far of that connection
				if (upcomingRecord.costSoFar < existingRecord.costSoFar)
				{
					existingRecord.pConnection = upcomingRecord.pConnection;
					existingRecord.costSoFar = upcomingRecord.costSoFar;
				}

				isInClosedList = true;

				break;
			}
		}

		//add upcoming record to closed list if it is not in it already
		if (!isInClosedList)
		{
			closedList.push_back(upcomingRecord);
		}
	}

	//backTracking
	while (currentRecord.pNode != pStartNode)
	{
		path.push_back(currentRecord.pNode->GetIndex());

		for (const auto& nodeRecord : closedList)
		{
			if (nodeRecord.pNode == pGraph->GetNode(currentRecord.pConnection->GetFrom()))
			{
				currentRecord = nodeRecord;

				break;
			}
		}
	}

	path.push_back(pStartNode->GetIndex());

	std::reverse(path.begin(), path.end());


    return path;
}

float AStarPathfinder::GetHeuristicCost(Node* pStartNode, Node* pEndNode) const
{
    Vector2f toDestination = m_pGraph.lock()->GetNodePos(pEndNode) - m_pGraph.lock()->GetNodePos(pStartNode);
    return m_HeuristicFunction(abs(toDestination.x), abs(toDestination.y));
}


