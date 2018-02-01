#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Constants.h"	

Tile::Tile(sf::Vector2f l_size, sf::Vector2f l_position, float l_speed)
	:m_position(l_position), m_speed(l_speed){
	
	m_tile.setSize(sf::Vector2f(l_size.x-TILE_GAP, l_size.y));
	m_tile.setPosition(m_position);
	m_tile.setFillColor(sf::Color::Red);	
}

Tile::~Tile(){}

void Tile::Update(){
	m_position.x -= m_speed;
	m_tile.setPosition(m_position);
}

void Tile::Render(sf::RenderWindow *l_window){
	l_window->draw(m_tile);
}

sf::Vector2f Tile::GetPosition(){
	return m_position;
}
