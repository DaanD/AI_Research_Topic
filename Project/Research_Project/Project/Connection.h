#pragma once
#include "pch.h"
#include "GraphEnums.h"

class Connection final
{
public:
	explicit Connection(int from = invalid_node_index, int to = invalid_node_index)
		:m_From{from}, m_To{to}{}

	~Connection() = default;

	Connection(Connection& rhs) = delete;
	Connection(Connection&& rhs) = delete;

	Connection& operator=(Connection& rhs) = delete;
	Connection& operator=(Connection&& rhs) = delete;

	void Render(const Point2f& from, const Point2f& to) const
	{
		utils::DrawLine(from, to);
	}

	int GetFrom() const { return m_From; }
	void SetFrom(int newFrom) { m_From = newFrom; }

	int GetTo() const { return m_To; }
	void SetTo(int newTo) { m_To = newTo; }

	bool IsValid() const { return (m_From != -1 && m_To != -1); }

	bool operator==(const Connection& rhs) const
	{
		return rhs.m_From == this->m_From &&
			rhs.m_To == this->m_To;
	}

	bool operator!=(const Connection& rhs) const
	{
		return !(*this == rhs);
	}

private:
	int m_From{};
	int m_To{};
};

