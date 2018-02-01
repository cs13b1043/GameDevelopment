#include "Window.h"
#include "TowerStack.h"

class Game{
	private:
		Window m_window;
		TowerStack m_towerStack;
		
		sf::Clock m_clock;
		sf::Time m_elapsed;
	
	public:
		Game();
		~Game();
		
		void HandleInput();
		void Update();
		void Render();
		
		Window& GetWindow();
		
		void RestartClock();
		
};
