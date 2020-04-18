#include <SFML/Graphics.hpp>
#include <iostream>
#include "Mouse.h"

#define HEIGTH 600
#define WIDTH 800

int main()
{
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	window.setFramerateLimit(30);
	sf::Vector2f mouse_position (400,300);
	Mouse mouse(mouse_position,360,window);
	
	
	
	sf::VertexArray wall (sf::Lines,2);
	
	wall[0].position = sf::Vector2f (400,0);
	wall[0].color = sf::Color::Yellow;
	
	wall[1].position = sf::Vector2f (400,275);
	wall[1].color = sf::Color::Blue;
	
	sf::VertexArray wall2 (sf::Lines,2);
	
	wall2[0].position = sf::Vector2f (400,325);
	wall2[0].color = sf::Color::Green;
	
	wall2[1].position = sf::Vector2f (400,600);
	wall2[1].color = sf::Color::Red;
	
	std::vector<sf::VertexArray> walls;
	walls.push_back(wall);
	walls.push_back(wall2);

	
	while (window.isOpen())
	{
	   // Event processing
	   sf::Event event;
	   while (window.pollEvent(event))
	   {
	       // Request for closing the window
	       if (event.type == sf::Event::Closed)
	           window.close();
	           
	        if(event.type == sf::Event::MouseMoved){
	        	
	        	mouse_position= (sf::Vector2f)sf::Mouse::getPosition(window); 
	        	mouse_position= window.mapPixelToCoords((sf::Vector2i)mouse_position);
				mouse.UpdateMouse(mouse_position,window);
			}   
	          
	           
	   }
	   window.clear();
	   mouse.Draw(window);
	   for(int i=0;i<walls.size();i++){
	   		window.draw(walls[i]);	
	   }
	   mouse.ShadowCasting(walls,window);
	   
	   	window.display();
	   
	}
	
    return EXIT_SUCCESS;
}
