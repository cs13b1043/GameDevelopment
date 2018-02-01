#include <SFML/Graphics.hpp>

class Scorebox{
	private:
		int score;
		int lives;
		
		sf::RectangleShape m_rect;
		sf::Text m_text;
		sf::Font m_font;
	
	public:
		Scorebox(int l_charSize, sf::Vector2f l_size, sf::Vector2f l_pos);
		
		void UpdateScore();
		void UpdateLives();
		void Update();
		
		int GetLives();
		
		void Render(sf::RenderWindow* l_window);
};
