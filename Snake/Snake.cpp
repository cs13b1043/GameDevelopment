#include <SFML/Graphics.hpp>
#include <vector>
#include "Snake.h"


Snake::Snake(int l_blocksize){
	m_size = l_blocksize;
	m_bodyRect.setSize(sf::Vector2f(m_size-1, m_size-1));
	Reset();
}
Snake::~Snake(){}

/* reset the snake to its starting position */
void Snake::Reset(){
	m_snakebody.clear();
	
	m_snakebody.push_back(SnakeSegment(5,7));
	m_snakebody.push_back(SnakeSegment(5,6));
	m_snakebody.push_back(SnakeSegment(5,5));
	
	SetDirection(Direction::None);
	
	m_speed = 5;
	m_lives = 3;
	m_lost = false;
	m_score = 0;
}

/* extend the snake body on colliding apple */
void Snake::Extend(){
	if(m_snakebody.empty()){
		return;
	}
	SnakeSegment& tail_head = m_snakebody[m_snakebody.size()-1];
	if(m_snakebody.size()>1){
		SnakeSegment& tail_bone = m_snakebody[m_snakebody.size()-2];
		
		if(tail_head.position.x == tail_bone.position.x){
			if(tail_head.position.y > tail_bone.position.y){
				m_snakebody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
			}
			else{
				m_snakebody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
			}
		}
		else if(tail_head.position.y == tail_bone.position.y){
			if(tail_head.position.x > tail_bone.position.y){
				m_snakebody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
			}
			else{
				m_snakebody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
			}		
		}
	}
	else{ //only one block snake
		if(m_direction == Direction::Up){
			m_snakebody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
		}
		else if(m_direction == Direction::Down){
			m_snakebody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
		}
		else if(m_direction == Direction::Left){
			m_snakebody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
		}
		else if(m_direction == Direction::Right){
			m_snakebody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
		}
	}
}

void Snake::Lose(){
	m_lost = true;
}

/* move snake based on direction */
void Snake::Move(){
	//first move the rest of the body of snake towards its head
	for(int i=m_snakebody.size()-1; i>0; i--){
		m_snakebody[i].position = m_snakebody[i-1].position;
	}
	if(m_direction == Direction::Up){
		m_snakebody[0].position.y -= 1;
	}
	else if(m_direction == Direction::Down){
		m_snakebody[0].position.y += 1;
	}
	else if(m_direction == Direction::Left){
		m_snakebody[0].position.x -= 1;
	}
	else if(m_direction == Direction::Right){
		m_snakebody[0].position.x += 1;
	}
}

/* update */
void Snake::Tick(){
	if(m_snakebody.empty())
		return;
	if(m_direction == Direction::None)
		return;
	Move();
	checkCollision();
}

/* to check if head of snake is collided with its body */
void Snake::checkCollision(){
	if(m_snakebody.size() <= 4){
		return;
	}
	SnakeSegment& head = m_snakebody.front();
	for(auto itr = m_snakebody.begin()+1; itr!=m_snakebody.end(); itr++){
		if(head.position == itr->position){
			int segments = m_snakebody.end() - itr;
			Cut(segments);
			break;
		}
	}
}

/* cut the tail of snake */
void Snake::Cut(int l_segments){
	for(int i=0; i<l_segments; i++){
		m_snakebody.pop_back();
	}
	--m_lives;
	if(m_lives < 0){
		Lose();
	}
}

/* Draw the snake to window */
void Snake::Render(sf::RenderWindow &l_window){
	if(m_snakebody.empty())
		return;
	
	auto head = m_snakebody.begin();
	m_bodyRect.setFillColor(sf::Color::Yellow);
	m_bodyRect.setPosition(head->position.x*m_size, head->position.y*m_size);
	l_window.draw(m_bodyRect);
	
	m_bodyRect.setFillColor(sf::Color::Green);
	for(auto itr=m_snakebody.begin()+1; itr!=m_snakebody.end(); itr++){
		m_bodyRect.setPosition(itr->position.x*m_size, itr->position.y*m_size);
		l_window.draw(m_bodyRect);
	}
}

Direction Snake::GetPhysicalDirection(){
	if(m_snakebody.size()==1)
		return Direction::None;
		
	SnakeSegment& head = m_snakebody[0];
	SnakeSegment& neck = m_snakebody[1];
	
	if(head.position.x == neck.position.x){
		if(head.position.y > neck.position.y){
			return Direction::Down;
		}
		else{
			return Direction::Up;
		}
	}
	if(head.position.y == neck.position.y){
		if(head.position.x > neck.position.x){
			return Direction::Right;
		}
		else{
			return Direction::Left;
		}
	}
	return Direction::None;
}

/* Helper methods */		
void Snake::SetDirection(Direction l_dir){
	m_direction = l_dir;
}
Direction Snake::GetDirection(){
	return m_direction;
}
int Snake::GetSpeed(){
	return m_speed;
}
sf::Vector2i Snake::GetPosition(){
	return (m_snakebody.empty() ? sf::Vector2i(1,1) : m_snakebody.front().position);
}
int Snake::GetLives(){
	return m_lives;
}
int Snake::GetScore(){
	return m_score;
}
void Snake::IncreaseScore(){
	m_score += 10;
}
bool Snake::HasLost(){
	return m_lost;
}
void Snake::ToggleLost(){
	m_lost = !m_lost;
}
