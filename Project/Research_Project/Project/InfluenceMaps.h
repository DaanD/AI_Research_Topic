#pragma once
#include "PathFinder.h"
#include "GridGraph.h"

class InfluenceMaps : public PathFinder
{
public:
	InfluenceMaps(std::weak_ptr<GridGraph> graph)
		:PathFinder(graph)
	{
		m_GridSize = graph.lock()->GetGraphSize();

		m_InfluenceList.resize(m_GridSize * m_GridSize);
		m_DoubleBuffer.resize(m_InfluenceList.size());

		m_PropagateLoops = int(m_GridSize/1.4);
	}

	virtual void Render() const override;

	virtual Direction GetDirectionOutPut(Direction lastDirection) override;

private:
	float m_Momentum = 0.1f;
	float m_Decay = 0.01f;

	int m_GridSize{};
	int m_PropagateLoops{ 5 };

	std::vector<float> m_InfluenceList{};
	std::vector<float> m_DoubleBuffer{};

	void PropagateInfluence();
};

