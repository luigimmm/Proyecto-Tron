#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Player
{
	public:
		//---Miembros de SFML
		sf::Color mp_color;
		sf::CircleShape mp_circleS;
		//---Miembros
		int mp_x;
		int mp_y;
		int mp_dir;

		//---Métodos
		void
		Mark(const int _screenWidth, const int  _screenHeight, sf::Time _deltaTime);

		//---Constructores
		Player();	
		~Player();	//Destructor

		Player
		(sf::Color _anyColor, const int _screenWidth, const int  _screenHeight);	//Constructor para poder indicar el color del jugador
		
};