#pragma once

class Grid final
{
public:
	Grid() = delete;
	Grid(const Point2f& screenCentre, float gridDimensions, int gridAmount);

	~Grid();

	Grid(Grid& rhs) = delete;
	Grid(Grid&& rhs) = delete;

	Grid& operator=(Grid& rhs) = delete;
	Grid& operator=(Grid&& rhs) = delete;

	std::vector<Point2f>* GetGrid() { return &m_SquareCenters; }

	float GetCellSize()const { return m_SquareSize / 4.f; }

	int GetGridSize() const { return m_GridAmount; }

	int GetSnakeStartPos();

	int GetApplePos() const { return m_Apple; }

	void NewApple(const std::deque<int> snake);

	void Draw(const std::deque<int> snake, bool isSnakeDead) const;

	bool IsSnakeDead(const std::deque<int> snake) const;


private:
	int m_GridAmount{10};

	int m_Apple{};

	std::vector<Point2f> m_SquareCenters{};
	float m_SquareSize{};
};

