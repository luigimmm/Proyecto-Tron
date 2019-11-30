#pragma once
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

class Client
{
	public:
	
		//Miembros
		sf::TcpSocket mc_socket;
		sf::Packet mc_packet;
		sf::Color mc_color;

		int mc_x;
		int mc_y;
		int mc_dir;
	
		//Metodos
		void
		InitializeClient();	//Función para inicializar el server

		Client();	//Constructor
		~Client();	//Destructor
};