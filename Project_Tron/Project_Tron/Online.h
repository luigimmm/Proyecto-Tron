#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>

class Client
{
	public:
	
		//Miembros
		sf::TcpSocket m_socketP1;
		sf::TcpSocket m_socketP2;
	
		//Metodos
		void
		InitializeClient(std::string _jugador);	//Función para inicializar el server
		
		Client();	//Constructor
		~Client();	//Destructor
};

class Server 
{
	public:

		//Miembros
		sf::TcpListener m_listenerServer;
		Client m_objClient;

		//Metodos
		void
		InitializeServer();	//Función para inicializar el server

		Server();	//Constructor
		~Server();	//Destructor
};