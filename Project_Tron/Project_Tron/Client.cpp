#include "Client.h"
#include "SFML/Graphics.hpp"
#include <iostream>

//Variables Globales
sf::IpAddress serverIp = sf::IpAddress::getLocalAddress();
const int screenWidth = 800;
const int screenHeight = 900;

void Client::InitializeClient() {
	
	mc_socket.connect(serverIp, 5000);

	if (mc_socket.receive(mc_packet) == sf::Socket::Done) {

		std::cout << "\nExito desde CLIENTE desde el INICIO, se recibio el paquete del server\n";
		mc_packet >> mc_x >> mc_y >> mc_dir >> mc_color.r >> mc_color.g >> mc_color.b >> mc_color.a;
	}
	else {

		std::cout << "\nError desde el CLIENTE desde el INICIO, no se recibio nada\n";
	}

	srand(time(0));	// Inicializa el generador de números aleatorios.

	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "- > TRON < -");	//Para poder mostrar la ventana

	window.setFramerateLimit(60);	//Limite de fps

	//Declaración de variables
	sf::Texture texture;
	sf::Texture gameOver;
	sf::Sprite sprite;
	sf::RenderTexture rTexture;
	sf::Font fontWinner;

	texture.loadFromFile("background.jpg");	//Para cargar el fondo de imagen

	sf::Sprite spriteBackground(texture);

	rTexture.create(screenWidth, screenHeight);	//Necesario para poder dibujar el fondo del tamaño de la pantalla
	rTexture.setSmooth(true); //Función la textura aparece más suave para que los píxeles sean menos visibles.

	sprite.setTexture(rTexture.getTexture());

	rTexture.clear(); //Llamada de la función para borrar los contenidos anteriores del objetivo.
	rTexture.draw(spriteBackground);

	//Texto
	fontWinner.loadFromFile("tron.ttf");	//Para cargar el tipo de fuente

	sf::Text textP1("JUGADOR 2, ES EL GANADOR", fontWinner, 45);
	sf::Text textP2("JUGADOR 1, ES EL GANADOR", fontWinner, 45);

	textP1.setPosition((screenWidth * 0.16) - 80, 520);	//Indicamos la posición en pantalla del texto
	textP2.setPosition((screenWidth * 0.16) - 80, 520);

	while (window.isOpen()) {

		if (mc_socket.receive(mc_packet) == sf::Socket::Done) {

			std::cout << "\nExito desde CLIENTE parte del WINDOW.ISOPEN, se recibio el paquete del server\n";
			mc_packet >> mc_x >> mc_y >> mc_dir;
		}
		else {

			std::cout << "\nError desde el CLIENTE parte del WINDOW.ISOPEN, no se recibio nada\n";
		}

		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) { window.close(); }
		}

		//Inputs
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { 
			
			if (mc_dir != 0) {
				
				mc_dir = 3; 
				mc_packet << mc_dir;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { 
			
			if (mc_dir != 3) {
			
				mc_dir = 0; 
				mc_packet << mc_dir;
			} 
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			
			if (mc_dir != 2) {
			
				mc_dir = 1;
				mc_packet << mc_dir;
			} 
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { 
			
			if (mc_dir != 1) {
			
				mc_dir = 2; 
				mc_packet << mc_dir;
			}
		}

		//Envío de los nuevos datos
		if (mc_socket.send(mc_packet) == sf::Socket::Done) {

			std::cout << "\nExito desde el CLIENTE, se envio el paquete\n";
		}
		else {

			std::cout << "\nError desde el CLIENTE, no se puedo enviar nada\n";
		}

		mc_socket.setBlocking(false);

		/*
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { 
		
			mc_packet << sf::Keyboard::W;
			std::cout << "\nCliente - se guardo la W\n";
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			
			mc_packet << sf::Keyboard::S;
			std::cout << "\nCliente - se guardo la S\n";
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { 

			mc_packet << sf::Keyboard::A;
			std::cout << "\nCliente - se guardo la A\n";
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { 

			mc_packet << sf::Keyboard::D;
			std::cout << "\nCliente - se guardo la D\n";
		}

		mc_socket.setBlocking(false);
		*/

		sf::CircleShape circle(3);
		circle.setPosition(mc_x, mc_y);
		circle.setFillColor(mc_color);
		rTexture.draw(circle);

		//Dibujamos
		window.clear();
		window.draw(sprite);
		window.display();
	}
}

//---IMPORTANTE---
Client::Client() {}
Client::~Client() {}