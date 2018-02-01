#include <SFML/Graphics.hpp>

class Ball{
	private:
		sf::Vector2f m_position;
		sf::CircleShape m_ball;
		
		float m_incr;
		
		bool m_isJumping;
		float m_height;
		
		void Jump();

	public:
		Ball(float l_radius, sf::Vector2f l_center);
		~Ball();

		void Update();
		void SetJumping(float l_height);
		bool IsJumping();
		
		void Render(sf::RenderWindow *l_window);
};
