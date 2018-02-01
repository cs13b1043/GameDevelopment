#include <SFML/Graphics.hpp>

class Window{
	public:
		Window();
		Window(const std::string& title, const sf::Vector2u& win_size);
		~Window();
		
		void BeginDraw(); //clears the content
		void Update(); //handling events
		void EndDraw(); //display the changes
		
		void Draw(sf::Drawable& drawable);
		
		bool IsDone();
		bool IsFullScreen();
		void ToggleFullScreen();
		
		sf::Vector2u GetWindowSize();
		sf::RenderWindow& GetRenderWindow();
		
		
	private:
		void Setup(const std::string& title, const sf::Vector2u& win_size);
		void Create();
		void Destroy();
		
		sf::RenderWindow m_window;
		sf::Vector2u m_windowSize;
		std::string m_windowTitle;
		bool m_isDone;
		bool m_isFullScreen;
};
