#include "Game.h"
#include "Constants.h"

Game::Game()
	: m_window(WINDOW_TITLE, WINDOW_SIZE),
	  m_towerStack(TOWER_SIZE)
{}

Game::~Game(){}

void Game::HandleInput(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		m_towerStack.BoxFall();
	}
}

void Game::Update(){
	float timeStep = 1.0f/50;

	if(m_elapsed.asSeconds() > timeStep){
		m_window.Update();
		if(!m_towerStack.IsLost())
			m_towerStack.Update();
	}

}

void Game::Render(){
	m_window.BeginDraw();
	
	if(!m_towerStack.IsLost())
		m_towerStack.Render(m_window.GetRenderWindow());
	
	m_window.EndDraw();
}

Window& Game::GetWindow(){
	return m_window;
}

void Game:: RestartClock(){
	m_elapsed += m_clock.restart();
}
