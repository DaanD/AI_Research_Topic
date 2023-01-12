#pragma once
#include "pch.h"
#include "GraphEnums.h"

class Node final
{
public:
	Node() : m_Index(invalid_node_index) {}
	explicit Node(int idx) : m_Index(idx){}

	~Node() = default;

	Node(Node& rhs) = delete;
	Node(Node&& rhs) = delete;

	Node& operator=(Node& rhs) = delete;
	Node& operator=(Node&& rhs) = delete;

	void Render(float cellSize) const
	{
		switch (m_Type)
		{
		case NodeType::Normal:
			utils::SetColor(Color4f{ 0.6f, 0.6f, 0.6f, .5f });
			break;
		case NodeType::Snake:
			utils::SetColor(Color4f{ 0, 0.39f, 0, 1 });
			break;
		case NodeType::Apple:
			utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 1.f });
			break;
		}

		utils::FillEllipse(m_Position, cellSize, cellSize);
	}

	int GetIndex() const { return m_Index; }
	void SetIndex(int newIdx) { m_Index = newIdx; }

	Point2f GetPosition() const { return m_Position; }
	void SetPosition(const Point2f& newPos) { m_Position = newPos; }

	NodeType GetNodeType() const { return m_Type; }
	void SetType(NodeType newType) { m_Type = newType; }

private:
	int m_Index;
	Point2f m_Position;
	NodeType m_Type{ NodeType::Normal };
};

