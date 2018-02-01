#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Constants.h"

#include <iostream>

Ball::Ball(float l_radius, sf::Vector2f l_position)
	:m_position(l_position) {
	
	m_isJumping = false;
	m_incr = JUMP_SPEED;
	
	m_ball.setOrigin(sf::Vector2f(l_radius, l_radius));
	m_ball.setRadius(l_radius);
	m_ball.setPosition(m_position);
	m_ball.setFillColor(sf::Color::Blue);
}
Ball::~Ball(){}


void Ball::Jump(){
	if(m_position.y < (BALL_POS.y - m_height)){ //change direction
		m_incr = -m_incr;
	}
	if(m_incr>0 && m_position.y >= BALL_POS.y){ //stop jumping
		m_incr = -m_incr;
		m_isJumping = false;
		return;
	}
	m_position.y += m_incr; 
	m_ball.setPosition(m_position);
}

void Ball::Update(){
	if(m_isJumping)
		Jump();
}
void Ball::Render(sf::RenderWindow *l_window){
	l_window->draw(m_ball);
}

void Ball::SetJumping(float l_height){
	m_isJumping = true;
	m_height = l_height;
}

bool Ball::IsJumping(){
	return m_isJumping;
}
