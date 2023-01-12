#include "pch.h"
#include "Game.h"
#include "Grid.h"
#include "Snake.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
{
	Initialize( );

	m_pGrid = std::make_unique<Grid>(Point2f{window.width / 2, window.height / 2}, m_Window.height * 0.75f, 11);
	m_pSnake = std::make_unique<Snake>(m_pGrid->GetSnakeStartPos());
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
	if (!m_SnakeDead)
	{
		m_Timer += elapsedSec;

		if (m_Timer >= m_Time)
		{
			m_Timer -= m_Time;

			std::deque<int> snake;
			m_pSnake->GetSnake(snake);
			
			if (m_pSnake->Update(m_pGrid->GetGridSize(), m_pGrid->GetApplePos()))
			{
				m_pSnake->GetSnake(snake);
				m_pGrid->NewApple(snake);
			}
			else
			{
				m_pSnake->GetSnake(snake);
			}

			m_SnakeDead = m_pGrid->IsSnakeDead(snake);
		}
	}
}

void Game::Draw( ) const
{
	ClearBackground( );

	std::deque<int> snake;
	m_pSnake->GetSnake(snake);
	m_pGrid->Draw(snake, m_SnakeDead);
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
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
