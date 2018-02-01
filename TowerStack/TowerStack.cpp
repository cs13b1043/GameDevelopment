#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include "Constants.h"
#include "TowerStack.h"
	
float random(int min, int max){
	return min + rand()%(max-min);
}

TowerStack::TowerStack(int l_numDisplay)
	:m_numDisplay(l_numDisplay),
	 m_movingBox(BOX_SIZE, random(ANGLE_LIMIT_L, ANGLE_LIMIT_R), COLORS[0], WINDOW_SIZE.y - BOX_SIZE.y/2),
	 m_scorebox(14, SCOREBOX_SIZE, SCOREBOX_POS) {
		 
	srand(time(NULL));
	m_topY = WINDOW_SIZE.y;
	m_isLost = false;
}

TowerStack::~TowerStack(){}

void TowerStack::BoxFall(){
	m_movingBox.StopMoving();
	m_movingBox.SetFalling(true);
}

void TowerStack::RemoveBox(){
	m_boxes.erase(m_boxes.begin());
	
	for(auto itr=m_boxes.begin(); itr!=m_boxes.end(); ++itr){
		itr->SetLimit(itr->GetLimit()+BOX_SIZE.y);
		itr->UpdateFall(BOX_SIZE.y);
	}
}

bool TowerStack::CheckBalance(Box l_topBox, Box l_bottomBox){
	if(abs(l_topBox.GetPosition().x - l_bottomBox.GetPosition().x) > BOX_SIZE.x/2)
		return false;
	else
		return true;
}

void TowerStack::Update(){
	static int color_counter = 0;
	
	m_movingBox.Update(); // contains code for if box is moving or falling
	
	// if box is steady
	if(!m_movingBox.IsFalling() && !m_movingBox.IsMoving()){

		if(m_boxes.empty() || (!m_boxes.empty() && CheckBalance( (Box)m_movingBox, m_boxes.back()) )){
			m_scorebox.UpdateScore();
			m_boxes.push_back((Box)m_movingBox);
			if(m_boxes.size() > m_numDisplay){
				RemoveBox();
			}
			else{
				m_topY -= BOX_SIZE.y;
			}
			
			color_counter  = (color_counter + 1) % COLORS.size();
		}
		else{
			m_scorebox.UpdateLives();
			if(m_scorebox.GetLives()<=0) m_isLost = true;
		}
		m_movingBox = MovingBox(BOX_SIZE, random(ANGLE_LIMIT_L, ANGLE_LIMIT_R), COLORS[color_counter], m_topY - BOX_SIZE.y/2);
	}
	m_scorebox.Update();
}

void TowerStack::Render(sf::RenderWindow* l_window){
	for(auto itr=m_boxes.begin(); itr!=m_boxes.end(); ++itr){
		itr->Render(l_window);
	}
	m_movingBox.Render(l_window);
	m_scorebox.Render(l_window);
}

bool TowerStack::IsLost(){
	return m_isLost;
}
