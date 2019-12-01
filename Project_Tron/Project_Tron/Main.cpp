#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>


#include <time.h>
#include <string>
#include <cctype>
#include <iostream>
#include <string>


#include "Players.h"


using std::cin;

//Funciones
void GameLoop();

//Variables globales
bool game = 1;
unsigned int winOrLose = 0;
const int speedPlayer = 1;
const int screenWidth = 800;
const int screenHeight = 900;
bool field[screenWidth][screenHeight] = { 0 }; //Sirve para poder detectar la colisión
sf::IpAddress serverIp = sf::IpAddress::getLocalAddress();

int main() {

	GameLoop();
	return 0;
}

void GameLoop() {
	
	std::string answer;
	
	sf::TcpSocket socketPlayer;
	sf::Packet packetServerP1;
	sf::Packet packetServerP2;

	std::cout << "\nIngresa s para ser el server o play, para jugar\n";
	std::cout << "- - >";
	cin >> answer;

	if (answer == "s") {
		
		sf::TcpListener listenerServer;

		listenerServer.listen(5000);

		//Aceptación de entrada del jugador 1
		if (listenerServer.accept(socketPlayer) == sf::Socket::Done) {

			std::cout << "\nEl server acepta al usuario 1\n";

		}
		else {

			std::cout << "\nE R R O R no se acepta la entrada\n";
		}
	}

	else if (answer == "play") {
		
		socketPlayer.connect(serverIp, 5000);
	}

	// Inicializa el generador de números aleatorios.
	srand(time(0));

	//Para poder mostrar la ventana
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "- > TRON < -");

	//Limite de fps
	window.setFramerateLimit(60);

	socketPlayer.setBlocking(false);

	//Declaración de variables
	sf::Texture texture;
	sf::Texture gameOver;
	sf::Sprite sprite;
	sf::RenderTexture rTexture;
	sf::Font fontWinner;

	texture.loadFromFile("background.jpg");	//Para cargar el fondo de imagen

	sf::Sprite spriteBackground(texture);

	//Necesario para poder dibujar el fondo del tamaño de la pantalla
	rTexture.create(screenWidth, screenHeight);
	rTexture.setSmooth(true); //Función la textura aparece más suave para que los píxeles sean menos visibles.

	sprite.setTexture(rTexture.getTexture());

	rTexture.clear(); //Llamada de la función para borrar los contenidos anteriores del objetivo.
	rTexture.draw(spriteBackground);

	//Creación de jugadores
	Player p1(sf::Color(rand() % 255, rand() % 255, rand() % 255), screenWidth, screenHeight);
	Player p2(sf::Color(rand() % 255, rand() % 255, rand() % 255), screenWidth, screenHeight);

	//Texto
	fontWinner.loadFromFile("tron.ttf");	//Para cargar el tipo de fuente

	sf::Text textP1("JUGADOR 2, ES EL GANADOR", fontWinner, 45);
	sf::Text textP2("JUGADOR 1, ES EL GANADOR", fontWinner, 45);

	textP1.setPosition((screenWidth * 0.16) - 80, 520);	//Indicamos la posición en pantalla del texto
	textP2.setPosition((screenWidth * 0.16) - 80, 520);

	while (window.isOpen()) {

		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); }
		}

		sf::Packet clientPacket1;
		sf::Packet clientPacket2;

		//Inputs del jugador 1
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

			if (p1.m_dir != 0) {

				p1.m_dir = 3;
			}
		}

		//---
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			
			if (p1.m_dir != 3) {

				p1.m_dir = 0;
			}
		}

		//---
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

			if (p1.m_dir != 2) {

				p1.m_dir = 1;
			}
		}

		//---
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

			if (p1.m_dir != 1) {

				p1.m_dir = 2;
			}
		}


		//Inputs del jugador 2
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { 
				
			if (p2.m_dir != 0) {

				p2.m_dir = 3;
			}
		}

		//---
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				
			if (p2.m_dir != 3) {

				p2.m_dir = 0;
			}
		}

		//---
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { 
				
			if (p2.m_dir != 2) {

				p2.m_dir = 1;
			}
		}
		
		//---
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			
			if (p2.m_dir != 1) {

				p2.m_dir = 2;
			}
		}

		//Condición para finalizar el juego
		if (!game) {

			window.clear();

			sf::Texture finalTexture;
			sf::Sprite finalSprite;

			finalTexture.loadFromFile("gameover.jpg");

			finalSprite.setTexture(finalTexture);


			if (winOrLose == 1) {

					textP1.setFillColor(sf::Color::Green);
					window.draw(textP1);
				}
			if (winOrLose == 2) {

					textP2.setFillColor(sf::Color::Green);
					window.draw(textP2);
				}

			window.draw(finalSprite);
			window.display();
			continue;
		}

		for (int i = 0; i < speedPlayer; i++) {

			p1.Mark(screenWidth, screenHeight);
			p2.Mark(screenWidth, screenHeight);

			if (field[p1.m_x][p1.m_y] == 1) {

				game = 0;
				winOrLose = 1;
			}
			if (field[p2.m_x][p2.m_y] == 1) {

				game = 0;
				winOrLose = 2;
			}

			field[p1.m_x][p1.m_y] = 1;
			field[p2.m_x][p2.m_y] = 1;

			sf::CircleShape circle(3);
			circle.setPosition(p1.m_x, p1.m_y);
			circle.setFillColor(p1.m_color);
			rTexture.draw(circle);

			circle.setPosition(p2.m_x, p2.m_y);
			circle.setFillColor(p2.m_color);
			rTexture.draw(circle);
			rTexture.display();
		}

		//Dibujamos
		window.clear();
		window.draw(sprite);
		window.display();
	}
}