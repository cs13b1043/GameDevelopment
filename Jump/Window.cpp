#include <SFML/Graphics.hpp>
#include "Window.h"

Window::Window(){
	Setup("Default Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string l_title, sf::Vector2u l_size){
	Setup(l_title, l_size);
}

void Window::Setup(const std::string l_title, sf::Vector2u l_size){
	m_title = l_title; m_size = l_size;
		
	m_isDone = false;
	m_isFullScreen = false;
	Create();
}

Window::~Window(){
	Destroy();
}

void Window::Create(){
	auto style = (m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.create({m_size.x, m_size.y, 32}, m_title, style); 
}

void Window::Destroy(){
	m_window.close();
}

void Window::BeginDraw() {//clear
	m_window.clear();
}

void Window::EndDraw() {// display
	m_window.display();
}

void Window::Update() {// events - close & full screen
	sf::Event event;
	while(m_window.pollEvent(event)){
		if(event.type==sf::Event::Closed){
			m_isDone=true;
		}
		if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::F5){
			ToggleFullScreen();
		}
	}	
}

void Window::ToggleFullScreen(){
	m_isFullScreen = !m_isFullScreen;
	Destroy();
	Create();
}

bool Window::IsDone(){
	return m_isDone;
}

sf::RenderWindow* Window::GetRenderWindow(){
	return &m_window;
}
