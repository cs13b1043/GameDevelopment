#include "World.h"
#include "Window.h"
#include "Textbox.h"

class Game{
	public:
		Game();
		~Game();
		
		void HandleInput();
		void Update();
		void Render();
		Window* GetWindow();
		void RestartClock();
		
	private:
		World m_world;
		Snake m_snake;
		Textbox m_textbox;
		Window m_window;
		
		sf::Clock m_clock;
		float m_elapsed;
};
