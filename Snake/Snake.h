#include <SFML/Graphics.hpp>
#include <vector>

struct SnakeSegment{
	SnakeSegment(int x, int y):position(x,y){}
	sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;
enum class Direction {None, Up, Down, Left, Right};

class Snake{
	public:
		Snake(int l_blocksize);
		~Snake();
		
		void SetDirection(Direction l_dir);
		Direction GetDirection();
		
		int GetSpeed();
		sf::Vector2i GetPosition();
		int GetLives();
		int GetScore();
		
		void IncreaseScore();
		bool HasLost();
		
		void Lose();
		void ToggleLost();
		
		void Extend();
		void Reset();
		void Move();
		
		void Tick();
		void Cut(int l_segments);
		
		Direction GetPhysicalDirection();
		
		void Render(sf::RenderWindow &l_window);
		
	private:
		SnakeContainer m_snakebody;
		int m_size;
		Direction m_direction;
		int m_speed;
		int m_lives;
		int m_score;
		bool m_lost;
		sf::RectangleShape m_bodyRect;
		
		void checkCollision();
};
