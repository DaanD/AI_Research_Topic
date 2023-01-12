#pragma once


class Snake final
{
public:
	Snake() = delete;
	Snake(int startPos);

	~Snake();

	Snake(Snake& rhs) = delete;
	Snake(Snake&& rhs) = delete;

	Snake& operator=(Snake& rhs) = delete;
	Snake& operator=(Snake&& rhs) = delete;

	void ChangeDirection(Direction newDirection);

	void GetSnake(std::deque<int>& snake);

	bool Update(int gridSize, int apple);

	Direction GetDirection() const { return m_Direction; }

private:
	std::deque<int> m_Snake{};

	bool m_DirectionUpdated{ false };

	int m_Size{ 3 };

	Direction m_Direction{ Direction::Right };
};

