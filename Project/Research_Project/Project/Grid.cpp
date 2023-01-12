#include "pch.h"
#include "Grid.h"

Grid::Grid(const Point2f& screenCentre, float gridDimensions, int gridAmount)
{
	if (gridAmount > m_GridAmount)
		m_GridAmount = gridAmount;

	m_SquareSize = gridDimensions / m_GridAmount;

	Point2f topRightCorner{ screenCentre.x - gridDimensions/2 + m_SquareSize/2, screenCentre.y + gridDimensions / 2 - m_SquareSize / 2 };

	for (int y{}; y < m_GridAmount; y++)
	{
		for (int x{}; x < m_GridAmount; x++ )
		{
			m_SquareCenters.push_back(Point2f{topRightCorner.x + x * m_SquareSize, topRightCorner.y - y * m_SquareSize});
		}
	}

}

Grid::~Grid()
{
}

int Grid::GetSnakeStartPos()
{
	int middle{ int(m_SquareCenters.size()) / 2 };
	if (m_GridAmount % 2 == 0)
		middle += m_GridAmount / 2;

	m_Apple = middle + m_GridAmount / 4;

	middle -= m_GridAmount / 4;

	return middle;
}

void Grid::NewApple(const std::deque<int> snake)
{
	bool newApple{ false };

	while (!newApple)
	{
		m_Apple = rand() % m_SquareCenters.size();
		newApple = true;
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

	for (auto& center : m_SquareCenters)
	{
		utils::DrawRect(Point2f{ center.x - halfSquareSize, center.y - halfSquareSize }, m_SquareSize, m_SquareSize, 1.0);
	}

	utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 1.f });
	utils::FillRect(Point2f{ m_SquareCenters[m_Apple].x - halfSquareSize,
		m_SquareCenters[m_Apple].y - halfSquareSize }, m_SquareSize, m_SquareSize);

	if (!isSnakeDead)
	{
		utils::SetColor(Color4f{ 0, 0.39f, 0, 1 });
	}
	else
	{
		utils::SetColor(Color4f{ 0.8f, 0.f, 0, 1 });
	}

	for (int i{isSnakeDead}; i < snake.size(); i++)
	{
		utils::FillRect(Point2f{ m_SquareCenters[snake[i]].x - halfSquareSize, m_SquareCenters[snake[i]].y - halfSquareSize}, m_SquareSize, m_SquareSize);
	}
}

bool Grid::IsSnakeDead(const std::deque<int> snake) const
{
	int snakeHead{ snake[0] };
	int snakeNeck{ snake[1] };

	for (int i{ 1 }; i < snake.size(); i++)
	{
		if (snake[i] == snake[0])
			return true;
	}

	if (snakeHead < 0)
		return true;
	if (snakeHead > m_SquareCenters.size())
		return true;

	if (snakeHead % m_GridAmount == m_GridAmount - 1 &&
		snakeNeck % m_GridAmount == 0)
		return true;

	if (snakeNeck % m_GridAmount == m_GridAmount - 1 &&
		snakeHead % m_GridAmount == 0)
		return true;


	return false;
}
