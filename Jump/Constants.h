#include <SFML/Graphics.hpp>
#include <vector>

const sf::Vector2u WINDOW_SIZE(620, 360);
const std::string WINDOW_TITLE = "Jump!!";

const float PADDING = 30;
const float BALL_RADIUS = 15;
const sf::Vector2f BALL_POS(PADDING + BALL_RADIUS, WINDOW_SIZE.y - BALL_RADIUS - PADDING);

const sf::Vector2f TILE_SIZE(75, PADDING/2); 
const float TILE_SPEED = 5;
const int TILE_GAP = 2;

const float HEIGHT = 100;
const float JUMP_SPEED = 6;

const sf::Vector2f SCOREBOX_SIZE(WINDOW_SIZE.x, 20);
const sf::Vector2f SCOREBOX_POS(0,0);
