#include "Window.h"
#include <SFML/Graphics.hpp>

Window::Window(){
	Setup("Window", sf::Vector2u(960, 620));
}
Window::Window(const std::string& title, const sf::Vector2u& win_size){
	Setup(title, win_size);
}

Window::~Window(){
	Destroy();
}

void Window::Setup(const std::string& title, const sf::Vector2u& win_size){
	m_windowTitle = title;
	m_windowSize = win_size;
	m_isDone = false;
	m_isFullScreen = false;
	m_window.setFramerateLimit(60);
	
	Create();
}

void Window::Create(){
	auto style = (m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.create({m_windowSize.x, m_windowSize.y, 32}, m_windowTitle, style);
}

void Window::Destroy(){
	m_window.close();
}

void Window::BeginDraw(){ //clears the content
	m_window.clear();
}

void Window::Update() {//handling events
	sf::Event event;
	while(m_window.pollEvent(event)){
		if(event.type == sf::Event::Closed){
			m_isDone = true;
		}
		else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5){
			ToggleFullScreen();
		}
	}
}

void Window::EndDraw() {//display the changes
	m_window.display();
}

void Window::Draw(sf::Drawable& drawable){
	m_window.draw(drawable);
}

bool Window::IsDone(){
	return m_isDone;
}
bool Window::IsFullScreen(){
	return m_isFullScreen;
}
void Window::ToggleFullScreen(){
	m_isFullScreen = !m_isFullScreen;
	Destroy();
	Create();
}

sf::Vector2u Window::GetWindowSize(){
	return m_windowSize;
}

sf::RenderWindow& Window::GetRenderWindow(){
	return m_window;
}
