#include "pch.h"
#include "Game.h"
#include "Grid.h"
#include "Snake.h"
#include "GridGraph.h"
#include "PathFinder.h"
#include "AStarPathfinder.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
{
	Initialize( );
	//Initialize the grid
	m_pGrid = std::make_unique<Grid>(Point2f{window.width / 2, window.height / 2}, m_Window.height * 0.75f, 15);
	//Initialize the snake
	m_pSnake = std::make_unique<Snake>(m_pGrid->GetSnakeStartPos());
	//Initialize the graph
	m_pGraph = std::make_shared<GridGraph>(m_pGrid.get());

	switch (m_SteeringMode)
	{
	case SteeringMode::AStar:
		m_pPathFinder = std::make_unique<AStarPathfinder>(m_pGraph);
		break;
	default:
		break;
	}
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	//Don't Update if the snake is dead
	if (!m_SnakeDead)
	{
		m_Timer += elapsedSec;

		//Only update the snake after a certain time to increase visibility
		if (m_Timer >= m_Time)
		{
			m_Timer -= m_Time;
			UpdateGame();
		}
	}
}

void Game::UpdateGame()
{
	std::deque<int> snake;
	m_pSnake->GetSnake(snake);
	m_pGraph->Update(m_pGrid.get(), snake);

	//Update the snake, if the update return true, the snake got the apple
	if (m_pSnake->Update(m_pGrid->GetGridSize(), m_pGrid->GetApplePos()))
	{
		m_Score++;
		//if the snake got the apple, get a new apple
		m_pSnake->GetSnake(snake);
		m_pGrid->NewApple(snake);
	}
	else
	{
		m_pSnake->GetSnake(snake);
	}

	//Check if the snake is dead
	m_SnakeDead = m_pGrid->IsSnakeDead(snake);

	if (!m_SnakeDead)
	{
		m_pGraph->Update(m_pGrid.get(), snake);
		if (m_SteeringMode != SteeringMode::Manual)
			m_pSnake->ChangeDirection(m_pPathFinder->GetDirectionOutPut());
	}
	else
		std::cout << "your score was " << m_Score << "\n";
}

void Game::Draw( ) const
{
	ClearBackground( );

	//Get the snake and draw the grid
	std::deque<int> snake;
	m_pSnake->GetSnake(snake);
	m_pGrid->Draw(snake, m_SnakeDead);

	//render the graph
	//m_pGraph->Render();

	//render the path
	if (m_SteeringMode != SteeringMode::Manual)
	{
		//m_pPathFinder->Render();
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	if (m_SteeringMode != SteeringMode::Manual)
		return;
	//Manual input to change snake directions
	switch (e.keysym.sym)
	{
	case SDLK_UP:
		m_pSnake->ChangeDirection(Direction::Up);
		break;
	case SDLK_RIGHT:
		m_pSnake->ChangeDirection(Direction::Right);
		break;
	case SDLK_DOWN:
		m_pSnake->ChangeDirection(Direction::Down);
		break;
	case SDLK_LEFT:
		m_pSnake->ChangeDirection(Direction::Left);
		break;

		break;
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

