#include <SFML/Graphics.hpp>
#include <vector>

const sf::Vector2u WINDOW_SIZE(500, 600);
const std::string WINDOW_TITLE = "Towering Stack";
const int TOWER_SIZE = 5;

const sf::Vector2f BOX_SIZE(100,60);
const std::vector<sf::Color> COLORS = {sf::Color(255, 122, 90), sf::Color(0,170,160), sf::Color(255, 184, 95)};
const float RADIUS = WINDOW_SIZE.x/4;
const sf::Vector2f CENTER(WINDOW_SIZE.x/2, 0);
const float SPEED = 3;

const float ANGLE_LIMIT_R = 315;
const float ANGLE_LIMIT_L = 225;

const sf::Vector2f SCOREBOX_SIZE(620, 20);
const sf::Vector2f SCOREBOX_POS(0,0);

