#include <SFML/Graphics.hpp>
#include <vector>
#include "MovingBox.h"
#include "Scorebox.h"

using BoxStack = std::vector<Box>;

class TowerStack{
	private:
		BoxStack m_boxes;
		MovingBox m_movingBox;
		Scorebox m_scorebox;
		
		bool m_isLost;
		int m_numDisplay;
		float m_topY;
		void RemoveBox();
		bool CheckBalance(Box l_topBox, Box l_bottomBox);
	
	public:
		TowerStack(int l_numDisplay);
		~TowerStack();
		
		void BoxFall();
		void Update();
		void Render(sf::RenderWindow* l_window);
		
		bool IsLost();
};
