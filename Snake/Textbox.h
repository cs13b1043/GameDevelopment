#include <SFML/Graphics.hpp>

using MessageContainer = std::vector<std::string>;

class Textbox{
	
	public:
		Textbox();
		Textbox(int l_visible, int l_charSize, int l_width, sf::Vector2f l_pos);
		~Textbox();
		
		void Setup(int l_visible, int l_charSize, int l_width, sf::Vector2f l_pos);
		void Add(std::string l_message);
		void Clear();
		
		void Render(sf::RenderWindow& l_window);
		
	private:
		MessageContainer m_message;
		int m_visible;
		
		sf::RectangleShape m_rect;
		sf::Text m_text;
		sf::Font m_font;
};
