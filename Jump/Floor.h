#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"

using Tiles = std::vector<Tile>;

class Floor{
	private:
		std::vector<Tile> m_tiles;
		sf::Vector2f m_tileSize;
		float m_speed;
	
	public:
		Floor(sf::Vector2f l_size, float l_speed);
		~Floor();
		
		void Update();
		void Render(sf::RenderWindow *l_window);
		bool IsTilePresent();
};
