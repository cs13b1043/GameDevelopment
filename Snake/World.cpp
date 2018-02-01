#include <SFML/Graphics.hpp>
#include "World.h"

World::World(const sf::Vector2u& l_windsize){
	m_blockSize = 20;
	
	m_windowSize = l_windsize;
	RespawnApple();
	
	m_appleShape.setFillColor(sf::Color::Blue);
	m_appleShape.setRadius(m_blockSize/2);
	
	// draw walls on boundaries
	// left =1, top=2, right=3, bottom=4
	for(int i=0; i<4; i++){
		m_bounds[i].setFillColor(sf::Color(150,0,0));
		if((i+1)%2==0){ //top & bottom
			m_bounds[i].setSize(sf::Vector2f(m_windowSize.x, m_blockSize));
		}
		else{ //left & right
			m_bounds[i].setSize(sf::Vector2f(m_blockSize, m_windowSize.y));
		}
		
		if(i<2){ //top-left corner
			m_bounds[i].setPosition(sf::Vector2f(0,0));
		}
		else{ //bottom-right corner
			m_bounds[i].setOrigin(m_bounds[i].getSize());
			m_bounds[i].setPosition(sf::Vector2f(m_windowSize));
		}
	}
}
World::~World(){}

void World::RespawnApple(){
	int maxX = m_windowSize.x/m_blockSize -2;
	int maxY = m_windowSize.y/m_blockSize -2;
	
	m_applePosition = sf::Vector2i( rand()%maxX+1, rand()%maxY+1);
	m_appleShape.setPosition(m_applePosition.x*m_blockSize, m_applePosition.y*m_blockSize);
}

void World::Update(Snake& l_player){
	if(l_player.GetPosition() == m_applePosition){
		l_player.Extend();
		l_player.IncreaseScore();
		RespawnApple();
	}
	
	int gridX = m_windowSize.x/m_blockSize;
	int gridY = m_windowSize.y/m_blockSize;
	
	if(l_player.GetPosition().x <= 0 || l_player.GetPosition().x >= gridX - 1
	 || l_player.GetPosition().y <= 0 || l_player.GetPosition().y >= gridX - 1){
		l_player.Lose();
	}
}

void World::Render(sf::RenderWindow& l_window){
	for(int i=0; i<4; i++){
		l_window.draw(m_bounds[i]);
	}
	l_window.draw(m_appleShape);
}

int World::GetBlockSize(){
	return m_blockSize;
}
