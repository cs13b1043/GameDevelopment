#include <SFML/Graphics.hpp>

class Tile{
	private:
		sf::RectangleShape m_tile;
		sf::Vector2f m_position;
		float m_speed;
	
	public:
		Tile(sf::Vector2f l_size, sf::Vector2f l_position, float l_speed);
		~Tile();
		
		void Update();
		void Render(sf::RenderWindow *l_window);
		
		sf::Vector2f GetPosition();
};
