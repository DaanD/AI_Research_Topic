#include "pch.h"
#include "Snake.h"

Snake::Snake(int startPos)
{
	for (int i{}; i < m_Size; i++)
	{
		m_Snake.push_back(startPos - i);
	}

}

Snake::~Snake()
{
}

void Snake::ChangeDirection(Direction newDirection)
{
	if (m_DirectionUpdated)
		return;

	if ((m_Direction == Direction::Up && newDirection == Direction::Down) ||
		(m_Direction == Direction::Right && newDirection == Direction::Left) || 
		(m_Direction == Direction::Down && newDirection == Direction::Up) || 
		(m_Direction == Direction::Left && newDirection == Direction::Right))
		return;
	
	
	m_Direction = newDirection;
	m_DirectionUpdated = true;
}

void Snake::GetSnake(std::deque<int>& snake)
{
	snake = m_Snake;
}

bool Snake::Update(int gridSize, int apple)
{
	m_DirectionUpdated = false;
	bool gotApple{ false };
	int newSnake{};

	switch (m_Direction)
	{
	case Direction::Up:
		newSnake = m_Snake[0] - gridSize;
		break;
	case Direction::Right:
		newSnake = m_Snake[0] + 1;
		break;
	case Direction::Down:
		newSnake = m_Snake[0] + gridSize;
		break;
	case Direction::Left:
		newSnake = m_Snake[0] - 1;
		break;
	default:
		break;
	}

	if (newSnake == apple)
	{
		gotApple = true;
		m_Size++;
	}

	m_Snake.push_front(newSnake);

	while (m_Snake.size() > m_Size)
	{
		m_Snake.pop_back();
	}

	return gotApple;
}
