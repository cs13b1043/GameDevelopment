#include <SFML/Graphics.hpp>

class Window{
	private:
		sf::RenderWindow m_window;
		std::string m_title;
		sf::Vector2u m_size;
		
		bool m_isDone;
		bool m_isFullScreen;
		
		void Setup(const std::string l_title, sf::Vector2u l_size);
		void Create();
		void Destroy();
		
	public:
		Window();
		Window(const std::string l_title, sf::Vector2u l_size);
		~Window();
		
		void BeginDraw(); //clear
		void EndDraw(); // display
		void Update(); // events - close & full screen
		
		void ToggleFullScreen();
		bool IsDone();
		sf::RenderWindow* GetRenderWindow();
};
