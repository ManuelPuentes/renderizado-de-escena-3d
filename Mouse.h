#ifndef MOUSE_H
#define MOUSE_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <math.h>

#define WIDTH 800
#define HEIGTH 600

class Mouse
{

	
	public:
	sf::CircleShape puntero;
	static const float DEGTORAD = 0.017453f;
	sf::Vector2f posicion;
	std::vector<sf::VertexArray> rayos;
	float angle;
	float coordx,coordy;
	int radio;
	int fov;
	float dt;
	sf::VertexArray rayo;
		Mouse(){};
		Mouse(sf::Vector2f &posicion, int num_rayos,sf::RenderWindow &window,int fov);
		Draw(sf::RenderWindow &window);
		UpdateMouse(sf::Vector2f mouse,sf::RenderWindow &window);
		
		ShadowCasting(std::vector<sf::VertexArray> &walls, sf::RenderWindow &window);
		bool Cast(sf::VertexArray &wall, sf::VertexArray &rayo , sf::RenderWindow &window, sf::Vector2f &pt);
		setDt(int dt,sf::Vector2f mouse,sf::RenderWindow &window ){
			
			this->dt+=dt;
			UpdateMouse(mouse,window);
		}
		
		
	protected:
};

#endif
