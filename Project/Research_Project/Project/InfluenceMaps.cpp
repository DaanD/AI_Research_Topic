#include "pch.h"
#include "InfluenceMaps.h"

void InfluenceMaps::Render() const
{
    Color4f color{};

    for (int i{ 0 }; i < m_InfluenceList.size(); i++)
    {
        float influenceScale{ abs(m_InfluenceList[i]) / 100.f};

        if (m_InfluenceList[i] > 0)
            color = Color4f{ 0.f, 0.f, influenceScale, 1.f };
        else
            color = Color4f{ influenceScale, 0.f, 0.f, 1.f };

        color.a = abs(m_InfluenceList[i]) / 100.f;

        utils::SetColor(color);
        utils::FillEllipse(m_pGraph.lock()->GetNode(i)->GetPosition(), 5, 5);
    }
}

Direction InfluenceMaps::GetDirectionOutPut(Direction lastDirection)
{
    int apple{m_pGraph.lock()->GetEndNode()->GetIndex()};

    for (int i{}; i < m_InfluenceList.size(); i++)
    {
        if (i == apple)
        {
            m_InfluenceList[i] = 100;
            continue;
        }
        else m_InfluenceList[i] = 0;

       if(i < m_GridSize)
           m_InfluenceList[i] -= 40;
       if(i % m_GridSize == m_GridSize - 1)
           m_InfluenceList[i] -= 40;
       if(i > m_GridSize * (m_GridSize - 1))
           m_InfluenceList[i] -= 40;
        if(i % m_GridSize == 0)
           m_InfluenceList[i] -= 40;
    }

   std::deque<int>* snake{m_pGraph.lock()->GetSnake()};

    for (int i{ 1 }; i < snake->size(); i++)
    {
        m_InfluenceList[(*snake)[i]] -= 50;
    }


    for(int i{}; i < m_PropagateLoops; i++)
        PropagateInfluence();


    for (int i{}; i < m_InfluenceList.size(); i++)
    {
        if (i == apple)
        {
            m_InfluenceList[i] = 100;
            continue;
        }

        if (i < m_GridSize)
            m_InfluenceList[i] -= 40;
        if (i % m_GridSize == m_GridSize - 1)
            m_InfluenceList[i] -= 40;
        if (i > m_GridSize * (m_GridSize - 1))
            m_InfluenceList[i] -= 40;
        if (i % m_GridSize == 0)
            m_InfluenceList[i] -= 40;
    }

    for (int i{ 1 }; i < snake->size(); i++)
    {
        m_InfluenceList[(*snake)[i]] -= 100;
    }


    int head{ m_pGraph.lock()->GetStartNode()->GetIndex() };
    int newCell{};
    float highestInfluence{-5000};
    Direction direction{};

    //check up
    if (head > m_GridSize && lastDirection != Direction::Down)
    {
        newCell = head - m_GridSize;
        if (m_InfluenceList[newCell] > highestInfluence)
        {
            highestInfluence = m_InfluenceList[newCell];
            direction = Direction::Up;
        }
    }

    //check right
    if (head % m_GridSize != m_GridSize - 1 && lastDirection != Direction::Left)
    {
        newCell = head + 1;
        if (m_InfluenceList[newCell] >= highestInfluence)
        {
            highestInfluence = m_InfluenceList[newCell];
            direction = Direction::Right;
        }
    }

    //check down
    if (head < m_GridSize * (m_GridSize - 1) && lastDirection != Direction::Up)
    {
        newCell = head + m_GridSize;
        if (m_InfluenceList[newCell] >= highestInfluence)
        {
            highestInfluence = m_InfluenceList[newCell];
            direction = Direction::Down;
        }
    }

    //check right
    if (head % m_GridSize != 0 && lastDirection != Direction::Right)
    {
        newCell = head - 1;
        if (m_InfluenceList[newCell] >= highestInfluence)
        {
            highestInfluence = m_InfluenceList[newCell];
            direction = Direction::Left;
        }
    }

    std::cout << int(direction) << "\n";

	return direction;
}

void InfluenceMaps::PropagateInfluence()
{
    auto pGraph{ m_pGraph.lock() };

    for (int i{}; i < m_InfluenceList.size(); i++)
    {
        auto connections{ pGraph->GetNodeConnections(pGraph->GetNode(i))};

        float highestInfluence{ FLT_MIN };

        for (const auto& connection : connections)
        {
            float influence = m_InfluenceList[connection->GetTo()] * expf(-connection->GetCost() * m_Decay);
            if (abs(influence) > abs(highestInfluence))
                highestInfluence = influence;
        }

        m_DoubleBuffer[i] = highestInfluence;
    }

    for (int i{}; i < m_InfluenceList.size(); i++)
    {
        float newInfluence{ m_DoubleBuffer[i] };

        newInfluence = utils::Lerp(newInfluence, m_InfluenceList[i], m_Momentum);

        newInfluence = std::clamp(newInfluence, -95.f, 95.f);

        m_InfluenceList[i] = newInfluence;
    }
}
