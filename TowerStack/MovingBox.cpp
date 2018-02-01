#include "MovingBox.h"
#include "Constants.h"

float radians(float degree){
	return degree*M_PI/180;
}

sf::Vector2f ConvertToXY(float angle, float radius, sf::Vector2f center){
	return sf::Vector2f( center.x + radius*cos(radians(angle)), -(center.y + radius*sin(radians(angle))) );
}

MovingBox::MovingBox(sf::Vector2f l_size, float l_angle, sf::Color l_color, float l_limit)
	: Box(l_size, ConvertToXY(l_angle, RADIUS, CENTER), l_color, l_limit) {
	
	m_currAngle = l_angle;	  
	m_angleInc = SPEED;
	
	m_isMoving = true;
}

MovingBox::~MovingBox(){}

void MovingBox::Update(){
	if(m_isMoving){
		UpdateToFro();
	}
	else if(m_isFalling){
		UpdateFall(10);
	}
}

void MovingBox::UpdateToFro(){	
	if(m_currAngle < ANGLE_LIMIT_L || m_currAngle > ANGLE_LIMIT_R){
		m_angleInc = -m_angleInc;
	}
	m_currAngle += m_angleInc;
	
	m_position = ConvertToXY(m_currAngle, RADIUS, CENTER);
	m_box.setPosition(m_position);
}

void MovingBox::StopMoving(){
	m_isMoving = false;
}

bool MovingBox::IsMoving(){
	return m_isMoving;
}
