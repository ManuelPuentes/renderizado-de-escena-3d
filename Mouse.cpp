#include "Mouse.h"

Mouse::Mouse(sf::Vector2f &posicion, int num_rayos,sf::RenderWindow &window,int fov)
{
	
	this->fov=fov;
	dt=0;
	float i=-(fov/2)-dt;
	angle=(float)fov/num_rayos;

	coordx=0;
	coordy=0;
	rayo = sf::VertexArray(sf::Lines,2);
	radio=100;	
	puntero.setRadius(4);
	puntero.setPosition(sf::Vector2f(WIDTH/2,HEIGTH/2));
	puntero.setOrigin(sf::Vector2f(4,4));
	
	while(i<(fov/2)-dt){
				
		rayo[0].position= posicion;
		rayo[0].color= sf::Color::White;
		
		coordx= radio*cos(i*DEGTORAD);
		coordy= radio*sin(i*DEGTORAD);
	
		rayo[1].position= sf::Vector2f(coordx + posicion.x,coordy+posicion.y);
		rayo[1].color= sf::Color::White;
		
		rayos.push_back(rayo);
		
		i+=angle;	
	}
}
Mouse::UpdateMouse(sf::Vector2f mouse, sf::RenderWindow &window){
	
	float i=-(fov/2)-dt;
	rayos.clear();
	puntero.setPosition(mouse);
	
	while(i<(fov/2)-dt){
		rayo[0].position=mouse;
		rayo[0].color= sf::Color::White;
		
		coordx= radio*cos(i*DEGTORAD);
		coordy= radio*sin(i*DEGTORAD);	
		rayo[1].position= sf::Vector2f(coordx + mouse.x,coordy+mouse.y);
		rayo[1].color= sf::Color::White;
		
		rayos.push_back(rayo);
		i+=angle;	
	}
}

Mouse::ShadowCasting(std::vector<sf::VertexArray> &walls, sf::RenderWindow &window){
	
	sf::VertexArray linea(sf::Lines,2);
	
	sf::Vector2f colision_mas_cercana;
	sf::Vector2f pos_colision;
	sf::Vector2f vec_distancia;
	float modulo=0;
	bool  band=false;
	
	float distancia=0;
	float aux=-(fov/2)-dt;
	
	for(int i=0;i<rayos.size();i++){
		
		distancia = 99999999;
		
		for(int y=0;y<walls.size();y++){
					
			if(Cast(walls[y],rayos[i],window,pos_colision)){
				
				//si se detecta una colision 
				vec_distancia.x= pow((rayos[i][0].position.x- pos_colision.x),2);
				vec_distancia.y= pow((rayos[i][0].position.y- pos_colision.y),2);
				
				modulo= sqrt(vec_distancia.x+vec_distancia.y);
				
				linea[0].position= rayos[i][0].position;
				
				if(modulo<distancia){
					
					distancia=modulo;
					colision_mas_cercana=pos_colision;
				}
				band=true;				
			}
		}
		if(band){
			
			distancia=fabs(cos(aux*DEGTORAD)*modulo);
			
//			std::cout<<distancia <<std::endl;
			linea[1].position= colision_mas_cercana;
			linea[1].color= sf::Color::White;
			window.draw(linea);
		}
		aux+=angle;
	}
}

bool Mouse::Cast(sf::VertexArray &wall, sf::VertexArray &rayo , sf::RenderWindow &window, sf::Vector2f &pos_colision){
	
	float x1= wall[0].position.x;
	float y1= wall[0].position.y;
	float x2= wall[1].position.x;
	float y2= wall[1].position.y;
	
	float x3= rayo[0].position.x;
	float y3= rayo[0].position.y;
	float x4= rayo[1].position.x;
	float y4= rayo[1].position.y;
	
	int denominador = (x1-x2)*(y3-y4) - (y1-y2) * (x3-x4);
	sf::Vector2f colision;
	
	if(denominador!=0){
		
		float t = ((x1-x3)*(y3-y4)-(y1-y3)*(x3-x4))/denominador;
		float u = -((x1-x2)*(y1-y3)-(y1-y2)*(x1-x3))/denominador;
		
		if(t>0 && t<1 && u>0){
			
			colision.x=  x1 + t*(x2-x1);
			colision.y=  y1 + t*(y2-y1);
			
			pos_colision=colision;			
			return true;	
		}
	}
	
	return false;	
}	
