#include "pch.h"
#include "Snake.h"

Snake::Snake(int startPos)
{
	//Create the snake
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
	//If the direction was already updated this frame, return
	if (m_DirectionUpdated)
		return;

	//Make sure the snake cant turn 180 degrees
	if ((m_Direction == Direction::Up && newDirection == Direction::Down) ||
		(m_Direction == Direction::Right && newDirection == Direction::Left) || 
		(m_Direction == Direction::Down && newDirection == Direction::Up) || 
		(m_Direction == Direction::Left && newDirection == Direction::Right))
		return;
	
	//update direction
	m_Direction = newDirection;
	m_DirectionUpdated = true;
}

void Snake::GetSnake(std::deque<int>& snake)
{
	snake = m_Snake;
}

bool Snake::Update(int gridSize, int apple)
{
	//Make sure the direction can only be updated once per update
	m_DirectionUpdated = false;
	bool gotApple{ false };
	int newSnake{};

	//Calculate the new position of the head
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

	//Check if the snake got the apple
	if (newSnake == apple)
	{
		gotApple = true;
		m_Size++; //Makes the snake grow witch each apple
	}

	//Push the new location of the head to the front of the deque
	m_Snake.push_front(newSnake);


	//if the snake is bigger than it should be, remove the tail
	while (m_Snake.size() > m_Size)
	{
		m_Snake.pop_back();
	}

	//Return if the snake got the apple or not
	return gotApple;
}
