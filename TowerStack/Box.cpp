#include <SFML/Graphics.hpp>
#include "Box.h"
	
Box::Box(){
	Setup(sf::Vector2f(100,100),sf::Vector2f(0.0f,0.0f), sf::Color::Red, 0.0f);
}

Box::Box(sf::Vector2f l_size, sf::Vector2f l_position, sf::Color l_color, float l_limit){
	Setup(l_size, l_position, l_color, l_limit);
}


void Box::Setup(sf::Vector2f l_size, sf::Vector2f l_position, sf::Color l_color, float l_limit){
	m_size = l_size; m_position = l_position;
	
	m_box.setSize(m_size);
	m_box.setFillColor(l_color);
	m_box.setOrigin(m_size.x/2, m_size.y/2);
	m_box.setPosition(m_position);
	
	m_isFalling = false;
	m_limit = l_limit;
}

Box::~Box(){}

void Box::Render(sf::RenderWindow* l_window){
	l_window->draw(m_box);
}

void Box::UpdateFall(float l_increment){
	if(m_position.y > m_limit){
		m_position.y = m_limit;
		m_isFalling = false;
	}
	else{
		m_position.y+=l_increment;
	}
	m_box.setPosition(m_position);
}

void Box::SetFalling(bool l_flag){
	m_isFalling = l_flag;
}

bool Box::IsFalling(){
	return m_isFalling;
}

sf::Vector2f Box::GetPosition(){
	return m_position;
}

void Box::SetPositionY(int l_y){
	m_position.y = l_y;
}

void Box::SetLimit(float l_limit){
	m_limit = l_limit;
}

float Box::GetLimit(){
	return m_limit;
}
