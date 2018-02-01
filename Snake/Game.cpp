#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

Game::Game() : m_window("Snake", sf::Vector2u(600,400)),
				m_snake(m_world.GetBlockSize()),
				m_world(sf::Vector2u(600,400))
{
	m_textbox.Setup(5,12,350,sf::Vector2f(225.0, 0.0));
	m_textbox.Add("Seeded random number generator with: " + std::to_string(time(NULL)));
}

Game::~Game(){}

void Game::HandleInput(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && 
		m_snake.GetPhysicalDirection()!=Direction::Down){
		m_snake.SetDirection(Direction::Up);	
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && 
		m_snake.GetPhysicalDirection()!=Direction::Up){
		m_snake.SetDirection(Direction::Down);	
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && 
		m_snake.GetPhysicalDirection()!=Direction::Right){
		m_snake.SetDirection(Direction::Left);	
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && 
		m_snake.GetPhysicalDirection()!=Direction::Left){
		m_snake.SetDirection(Direction::Right);	
	}
}

void Game::Update(){
	m_window.Update();
	
	float timeStep = 1.0f/m_snake.GetSpeed();
	
	if(m_elapsed > timeStep){
		
		m_snake.Tick();
		m_world.Update(m_snake);
		m_elapsed -= timeStep;
		if(m_snake.HasLost()){
			m_textbox.Add("Game Over! Score = " + std::to_string(m_snake.GetScore()));
			m_snake.Reset();
		}
	}
}

void Game::Render(){
	m_window.BeginDraw();
	
	m_snake.Render(m_window.GetRenderWindow());
	m_world.Render(m_window.GetRenderWindow());
	m_textbox.Render(m_window.GetRenderWindow());
	
	m_window.EndDraw();
}

void Game::RestartClock(){
	m_elapsed += m_clock.restart().asSeconds();
}

Window* Game::GetWindow(){
	return &m_window;
}
