#pragma once
class GridGraph;

class PathFinder
{
public:
	PathFinder(std::weak_ptr<GridGraph> graph)
	{
		m_pGraph = graph;
	}

	~PathFinder() = default;

	PathFinder(PathFinder& rhs) = delete;
	PathFinder(PathFinder&& rhs) = delete;

	PathFinder& operator=(PathFinder& rhs) = delete;
	PathFinder& operator=(PathFinder&& rhs) = delete;

	virtual void Render() const {}

	virtual Direction GetDirectionOutPut() = 0;

protected:
	std::weak_ptr<GridGraph> m_pGraph;
};

