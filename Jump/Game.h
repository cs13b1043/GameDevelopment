#include "Window.h"
#include "Ball.h"
#include "Floor.h"
#include "Scorebox.h"

class Game{
	private:
		Window m_window;
		Ball m_ball;
		Floor m_floor;
		Scorebox m_scorebox;
		
		bool m_isLost;
		
		sf::Clock m_clock;
		sf::Time m_elapsed;
	
	public:
		Game();
		~Game();
		
		void HandleInput();
		void Update();
		void Render();
		
		bool IsLost();
		
		Window& GetWindow();
		
		void RestartClock();
		
};
