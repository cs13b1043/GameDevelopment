#include <SFML/Graphics.hpp>
#include "Box.h"

enum Direction {TO, FRO};

class MovingBox: public Box{
	private:
		float m_currAngle;
		float m_angleInc;
		bool m_isMoving;
		
		void UpdateToFro();
	
	public:
		MovingBox(sf::Vector2f l_size, float l_angle, sf::Color l_color, float l_limit);
		~MovingBox();
		
		void Update();
		void StopMoving();
		bool IsMoving();
};
