#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>


#include <time.h>
#include <string>
#include <cctype>
#include <iostream>


#include "Players.h"
#include "Online.h"

using std::cin;

//Variables globales
bool game = 1;
bool winOrLose = true;
const int speedPlayer = 4;
const int screenWidth = 800;
const int screenHeight = 900;
bool field[screenWidth][screenHeight] = { 0 }; //Sirve para poder detectar la colisi�n


int main(){

	// Inicializa el generador de n�meros aleatorios.
	srand(time(0));

	//Para poder mostrar la ventana
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "- > TRON < -");

	//Limite de fps
	window.setFramerateLimit(60);

	//Declaraci�n de variables
	sf::Texture texture;
	sf::Texture gameOver;
	sf::Sprite sprite;
	sf::RenderTexture rTexture;
	sf::Font fontWinner;
	
	
	texture.loadFromFile("background.jpg");	//Para cargar el fondo de imagen

	sf::Sprite spriteBackground(texture);

	//Necesario para poder dibujar el fondo del tama�o de la pantalla
	rTexture.create(screenWidth, screenHeight);
	rTexture.setSmooth(true); //Funci�n la textura aparece m�s suave para que los p�xeles sean menos visibles.

	sprite.setTexture(rTexture.getTexture());

	rTexture.clear(); //Llamada de la funci�n para borrar los contenidos anteriores del objetivo.
	rTexture.draw(spriteBackground);

	//Creaci�n de jugadores
	Player p1(sf::Color(rand() % 255, rand() % 255, rand() % 255), screenWidth, screenHeight);
	Player p2(sf::Color(rand() % 255, rand() % 255, rand() % 255), screenWidth, screenHeight);

	//Texto
	fontWinner.loadFromFile("tron.ttf");	//Para cargar el tipo de fuente

	sf::Text textP1("JUGADOR 2, ES EL GANADOR", fontWinner, 45);
	sf::Text textP2("JUGADOR 1, ES EL GANADOR", fontWinner, 45);

	textP1.setPosition((screenWidth * 0.16) - 80, 520);	//Indicamos la posici�n en pantalla del texto
	textP2.setPosition((screenWidth * 0.16) - 80, 520);

	while (window.isOpen()){
		
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); }
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { if (p1.m_dir != 0) { p1.m_dir = 3; } }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { if (p1.m_dir != 3) { p1.m_dir = 0; } }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { if (p1.m_dir != 2) { p1.m_dir = 1; } }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { if (p1.m_dir != 1) { p1.m_dir = 2; } }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { if (p2.m_dir != 0) { p2.m_dir = 3; } }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { if (p2.m_dir != 3) { p2.m_dir = 0; } }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { if (p2.m_dir != 2) { p2.m_dir = 1; } }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { if (p2.m_dir != 1) { p2.m_dir = 2; } }



		//Condici�n para finalizar el juego
		if (!game) {
			window.clear();

			sf::Texture finalTexture;
			sf::Sprite finalSprite;

			finalTexture.loadFromFile("gameover.jpg");

			finalSprite.setTexture(finalTexture);


			if (winOrLose == true) {
				textP1.setFillColor(sf::Color::Green);
				window.draw(textP1);
			}
			if (winOrLose == false) {
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
				winOrLose = true;
			}
			if (field[p2.m_x][p2.m_y] == 1) { 
				game = 0;
				winOrLose = false;
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
	return 0;
}