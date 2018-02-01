#include <SFML/Graphics.hpp>

enum class STATE {STEADY, MOVING, FALLING};

class Box{
	protected:
		sf::Vector2f m_size;
		sf::Vector2f m_position;
		sf::RectangleShape m_box;
		bool m_isFalling;
		float m_limit;
		
	private:
		void Setup(sf::Vector2f l_size, sf::Vector2f l_position, sf::Color l_color, float l_limit);
	
	public:
		Box();
		Box(sf::Vector2f l_size, sf::Vector2f l_position, sf::Color l_color, float l_limit);
		~Box();
		void Render(sf::RenderWindow* l_window);
		
		sf::Vector2f GetPosition();
		void SetPositionY(int l_y);
		
		void UpdateFall(float l_increment);
		
		void SetFalling(bool l_flag);
		bool IsFalling();
		void SetLimit(float l_limit);
		float GetLimit();
};
