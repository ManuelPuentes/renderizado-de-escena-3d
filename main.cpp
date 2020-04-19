#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string.h>
#include "Mouse.h"

#define HEIGTH 600
#define WIDTH 800
void CargarMapa(std::vector<sf::VertexArray> &walls);
int main()
{
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	window.setFramerateLimit(30);
	sf::Vector2f mouse_position (400,300);
	Mouse mouse(mouse_position,66,window,66);
	
	std::vector<sf::VertexArray> walls;

	CargarMapa(walls);
	
	while (window.isOpen())
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))mouse.setDt(-4,mouse_position,window);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))mouse.setDt(4,mouse_position,window);
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
	   for(int i=0;i<walls.size();i++){
	   		window.draw(walls[i]);	
	   }
	   mouse.ShadowCasting(walls,window);
	   
	   	window.display();
	   
	}
	
    return EXIT_SUCCESS;
}

void CargarMapa(std::vector<sf::VertexArray> &walls){
	
	std::fstream archivo;
	archivo.open("walls.txt",std::ios::in);
	std::string linea;
	float x;
	float y;
	
	sf::VertexArray wall(sf::Lines,2);
	
	
	if(!archivo.fail()){
		while(true){
		
			archivo>>linea;
			x=atof(linea.c_str());

			archivo>>linea;
			y=atof(linea.c_str());
			
			wall[0].position=sf::Vector2f(x,y);
			wall[0].color=sf::Color::Blue;
			
			
			archivo>>linea;
			x=atof(linea.c_str());

			archivo>>linea;
			y=atof(linea.c_str());
			
			wall[1].position=sf::Vector2f(x,y);
			wall[1].color=sf::Color::Blue;
				
			archivo>>linea;
			walls.push_back(wall);		
				
			if(archivo.eof())break;
		}
			
		}
	
	
}
