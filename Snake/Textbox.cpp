#include <SFML/Graphics.hpp>
#include "Textbox.h"

Textbox::Textbox(){
	Setup(5, 14, 200, sf::Vector2f(0,0));
}

Textbox::Textbox(int l_visible, int l_charSize, int l_width, sf::Vector2f l_pos){
	Setup(l_visible, l_charSize, l_width, l_pos);
}

Textbox::~Textbox(){}

void Textbox::Setup(int l_visible, int l_charSize, int l_width, sf::Vector2f l_pos){
	m_visible = l_visible;
	
	m_rect.setSize(sf::Vector2f(l_width, l_visible*l_charSize*1.2f));
	m_rect.setFillColor(sf::Color(90,90,90,90));
	m_rect.setPosition(l_pos);
	
	sf::Vector2f l_offset(2.0f, 2.0f);
	
	m_font.loadFromFile("arial.ttf");
	m_text.setFont(m_font);
	m_text.setCharacterSize(l_charSize);
	m_text.setColor(sf::Color::White);
	m_text.setPosition(l_pos + l_offset);
	m_text.setString("");
}

void Textbox::Add(std::string l_message){
	m_message.push_back(l_message);
	if(m_message.size()<6){return;}
	m_message.erase(m_message.begin());
}

void Textbox::Clear(){
	m_message.clear();
}

void Textbox::Render(sf::RenderWindow& l_window){
	std::string l_content;
	
	for(auto &itr : m_message){
		l_content.append(itr + "\n");
	}
	
	if(l_content!=""){
		m_text.setString(l_content);
		l_window.draw(m_rect);
		l_window.draw(m_text);
	}
}
