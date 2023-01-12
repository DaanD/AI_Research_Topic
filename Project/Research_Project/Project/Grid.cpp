#include "pch.h"
#include "Grid.h"

Grid::Grid(const Point2f& screenCentre, float gridDimensions, int gridAmount)
{
	//If the gridamount given is more than the minimum required, set new gridamount
	if (gridAmount > m_GridAmount)
		m_GridAmount = gridAmount;

	m_SquareSize = gridDimensions / m_GridAmount;

	//Get the top left corner
	Point2f topLeftCorner{ screenCentre.x - gridDimensions/2 + m_SquareSize/2, screenCentre.y + gridDimensions / 2 - m_SquareSize / 2 };

	for (int y{}; y < m_GridAmount; y++)
	{
		for (int x{}; x < m_GridAmount; x++ )
		{
			m_SquareCenters.push_back(Point2f{topLeftCorner.x + x * m_SquareSize, topLeftCorner.y - y * m_SquareSize});
		}
	}

}

Grid::~Grid()
{
}

int Grid::GetSnakeStartPos()
{
	//Get the approximate middle point of the grid
	int middle{ int(m_SquareCenters.size()) / 2 };
	if (m_GridAmount % 2 == 0)
		middle += m_GridAmount / 2;

	//Set the apple to the right of the middle
	m_Apple = middle + m_GridAmount / 4;

	//Return a position a little to the left of the middle
	return middle - m_GridAmount / 4;
}

void Grid::NewApple(const std::deque<int> snake)
{
	bool newApple{ false };

	while (!newApple)
	{
		//Get a new position for the apple in range of the grid
		m_Apple = rand() % m_SquareCenters.size();
		newApple = true;
		//Check if the new position is part of the snake, if it is, get a new position
		for (auto& number : snake)
		{
			if (m_Apple == number)
			{
				newApple = false;
				break;
			}
		}
	}
}

void Grid::Draw(const std::deque<int> snake, bool isSnakeDead) const
{
	utils::SetColor(Color4f{0, 0, 0, 1});

	float halfSquareSize{ m_SquareSize / 2.f };

	//Draw the squares of the grid
	for (auto& center : m_SquareCenters)
	{
		utils::DrawRect(Point2f{ center.x - halfSquareSize, center.y - halfSquareSize }, m_SquareSize, m_SquareSize, 1.0);
	}


	//Draw the apple
	utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 1.f });
	utils::FillRect(Point2f{ m_SquareCenters[m_Apple].x - halfSquareSize,
		m_SquareCenters[m_Apple].y - halfSquareSize }, m_SquareSize, m_SquareSize);

	//Draw the snake
	//if the snake is dead, set color to read, if not, set color to green
	if (!isSnakeDead)
		utils::SetColor(Color4f{ 0, 0.39f, 0, 1 });
	else
		utils::SetColor(Color4f{ 0.8f, 0.f, 0, 1 });

	for (int i{isSnakeDead}; i < snake.size(); i++)
	{
		utils::FillRect(Point2f{ m_SquareCenters[snake[i]].x - halfSquareSize, m_SquareCenters[snake[i]].y - halfSquareSize}, m_SquareSize, m_SquareSize);
	}
}

bool Grid::IsSnakeDead(const std::deque<int> snake) const
{
	//Get the front of the snake
	int snakeHead{ snake[0] };
	//Get the second part of the snake
	int snakeNeck{ snake[1] };

	//If the head occupies another space of the snake, the snake is dead
	for (int i{ 1 }; i < snake.size(); i++)
	{
		if (snake[i] == snake[0])
			return true;
	}

	//If the head of the snake is outside the range of the grid, the snake is dead
	if (snakeHead < 0)
		return true;
	if (snakeHead > m_SquareCenters.size())
		return true;

	//If the head is in the right column and the second part in the left column, the snake is dead
	if (snakeHead % m_GridAmount == m_GridAmount - 1 &&
		snakeNeck % m_GridAmount == 0)
		return true;

	//If the head is in the left column and the second part in the right column, the snake is dead
	if (snakeNeck % m_GridAmount == m_GridAmount - 1 &&
		snakeHead % m_GridAmount == 0)
		return true;


	return false;
}
