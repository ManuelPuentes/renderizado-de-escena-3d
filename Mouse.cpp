#include "Mouse.h"

Mouse::Mouse(sf::Vector2f &posicion, int num_rayos,sf::RenderWindow &window)
{
	float i=0;
	angle=360/num_rayos;
	coordx=0;
	coordy=0;
	rayo = sf::VertexArray(sf::Lines,2);
	radio=100;	
	puntero.setRadius(4);
	puntero.setPosition(sf::Vector2f(WIDTH/2,HEIGTH/2));
	puntero.setOrigin(sf::Vector2f(4,4));
	
	while(i<=360){
				
		rayo[0].position= posicion;
		rayo[0].color= sf::Color::White;
		
		coordx= radio*cos(i*DEGTORAD);
		coordy= radio*sin(i*DEGTORAD);
	
		rayo[1].position= sf::Vector2f(coordx + posicion.x,coordy+posicion.y);
		rayo[1].color= sf::Color::White;
		
		rayos.push_back(rayo);
		
		i+=angle;	
	}
	Draw(window);
}
Mouse::Draw(sf::RenderWindow & window){
	
	for(int i=0;i<rayos.size();i++){
		
		window.draw(rayos[i]);		
	}
	window.draw(puntero);
}
Mouse::UpdateMouse(sf::Vector2f mouse, sf::RenderWindow &window){
	
	float i=0;
	rayos.clear();
	puntero.setPosition(mouse);
	
	while(i<360){
		
		rayo[0].position=mouse;
		rayo[0].color= sf::Color::White;
		
		coordx= radio*cos(i*DEGTORAD);
		coordy= radio*sin(i*DEGTORAD);	
		rayo[1].position= sf::Vector2f(coordx + mouse.x,coordy+mouse.y);
		rayo[1].color= sf::Color::White;
		
		rayos.push_back(rayo);
		i+=angle;	
	}
	
	Draw(window);	
}

Mouse::ShadowCasting(std::vector<sf::VertexArray> &walls, sf::RenderWindow &window){
	
	
	for(int i=0;i<walls.size();i++){
		
		for(int y=0;y<rayos.size();y++){
					
			Cast(walls[i],rayos[y],window);	
		}
	}
}

Mouse::Cast(sf::VertexArray &wall, sf::VertexArray &rayo , sf::RenderWindow &window){
	
	float x1= wall[0].position.x;
	float y1= wall[0].position.y;
	float x2= wall[1].position.x;
	float y2= wall[1].position.y;
	
	float x3= rayo[0].position.x;
	float y3= rayo[0].position.y;
	float x4= rayo[1].position.x;
	float y4= rayo[1].position.y;
	
	int denominador = (x1-x2)*(y3-y4) - (y1-y2) * (x3-x4);
	
	sf::CircleShape pt(4);
	
	pt.setOrigin(sf::Vector2f(4,4));
	
	sf::Vector2f colision;
	
	
	if(denominador!=0){
		
		float t = ((x1-x3)*(y3-y4)-(y1-y3)*(x3-x4))/denominador;
		float u = -((x1-x2)*(y1-y3)-(y1-y2)*(x1-x3))/denominador;
		
		if(t>0 && t<1 && u>0){
			
			colision.x=  x1 + t*(x2-x1);
			colision.y=  y1 + t*(y2-y1);
			pt.setPosition(colision);
			window.draw(pt);	
		}
	}
	
}	
