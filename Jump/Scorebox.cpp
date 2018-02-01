#include <SFML/Graphics.hpp>
#include "Scorebox.h"

Scorebox::Scorebox(int l_charSize, sf::Vector2f l_size, sf::Vector2f l_pos){
	score = 0;
	lives = 3;
	
	m_rect.setSize(l_size);
	m_rect.setFillColor(sf::Color(90,90,90,90));
	m_rect.setPosition(l_pos);
	
	sf::Vector2f l_offset(2.0f, 2.0f);
	
	m_font.loadFromFile("arial.ttf");
	m_text.setFont(m_font);
	m_text.setCharacterSize(l_charSize);
	m_text.setColor(sf::Color::White);
	m_text.setPosition(l_pos + l_offset);
}

void Scorebox::UpdateScore(){
	score += 10;
}
void Scorebox::UpdateLives(){
	lives -= 1;
}

void Scorebox::Update(){
	m_text.setString("Score: " + std::to_string(score) + "\tLives: " + std::to_string(lives));
}

int Scorebox::GetLives(){
	return lives;
}

void Scorebox::Render(sf::RenderWindow* l_window){
	l_window->draw(m_rect);
	l_window->draw(m_text);
}
