#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <ctime>
#include "Floor.h"
#include "Constants.h"

//#include <iostream>

// 0(75), 1/2(10), 1(10), 3/2(5)
float Random(){
	float num = (double)rand() / RAND_MAX;
	
	if(num < 0.75) return 0;
	else if(num < 0.85) return 0.5;
	else if(num <0.95) return 1;
	else return 1.5;
}

Floor::Floor(sf::Vector2f l_size, float l_speed):
	m_tileSize(l_size), m_speed(l_speed){
		
	srand(time(NULL));
	int num_tiles = ceil(WINDOW_SIZE.x/l_size.x);
	for(int i=0; i<num_tiles; i++){
		m_tiles.push_back(Tile(m_tileSize, sf::Vector2f(i*TILE_SIZE.x, WINDOW_SIZE.y-PADDING), m_speed));
	}
}

Floor::~Floor(){}

void Floor::Update(){
	for(auto itr=m_tiles.begin(); itr!=m_tiles.end(); itr++){
		itr->Update();
	}
	//remove front tiles
	if(m_tiles.front().GetPosition().x + TILE_SIZE.x <= 0){
		m_tiles.erase(m_tiles.begin());
	}
	//add back tiles
	float x_pos = m_tiles.back().GetPosition().x + TILE_SIZE.x;
	if( x_pos <= WINDOW_SIZE.x){
		float new_x_pos = x_pos + Random() * TILE_SIZE.x;
		m_tiles.push_back( Tile(m_tileSize, sf::Vector2f(new_x_pos, WINDOW_SIZE.y-PADDING), m_speed) );
	}
}

void Floor::Render(sf::RenderWindow *l_window){
	for(auto itr=m_tiles.begin(); itr!=m_tiles.end(); itr++){
		itr->Render(l_window);
	}
}

bool Floor::IsTilePresent(){
	if(m_tiles[0].GetPosition().x + TILE_SIZE.x < BALL_POS.x && 
		m_tiles[1].GetPosition().x > BALL_POS.x)
		return false;
	else
		return true;
	
}
