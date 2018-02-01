#include "Game.h"
#include "Constants.h"

Game::Game()
	: m_window(WINDOW_TITLE, WINDOW_SIZE),
	  m_ball(BALL_RADIUS, BALL_POS),
	  m_floor(TILE_SIZE, TILE_SPEED),
	  m_scorebox(14, SCOREBOX_SIZE, SCOREBOX_POS){
		
		m_isLost = false;
}

Game::~Game(){}

void Game::HandleInput(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		m_ball.SetJumping(HEIGHT);
	}
}

void Game::Update(){
	float timeStep = 1.0f/50;
	static bool is_livesUpdated = false;
	static bool is_scoreUpdated = false;
	
	if(m_elapsed.asSeconds() > timeStep){
		m_window.Update();
		
		if(!m_isLost){
			m_ball.Update();
			m_floor.Update();
			
			/* score & lives update logic */
			if(!m_floor.IsTilePresent()){
				if(!m_ball.IsJumping()){
					if(is_livesUpdated==false){
						m_scorebox.UpdateLives(); 
						is_livesUpdated=true;
					}
				}
				else{
					if(is_scoreUpdated== false){
						m_scorebox.UpdateScore();
						is_scoreUpdated = true;
					}
				}
			}
			else{
				is_livesUpdated = false;
				is_scoreUpdated = false;
			}
			if(m_scorebox.GetLives()==0)
				m_isLost = true;
			
			m_scorebox.Update();
		}
	}
}

void Game::Render(){
	m_window.BeginDraw();
	
	if(!m_isLost){
		m_ball.Render(m_window.GetRenderWindow());
		m_floor.Render(m_window.GetRenderWindow());
		m_scorebox.Render(m_window.GetRenderWindow());
	}
	
	m_window.EndDraw();
}

Window& Game::GetWindow(){
	return m_window;
}

void Game:: RestartClock(){
	m_elapsed += m_clock.restart();
}

bool Game::IsLost(){
	return m_isLost;
}
