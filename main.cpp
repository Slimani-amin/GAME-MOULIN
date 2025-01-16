

#include <SFML/Graphics.hpp>

#include <SFML/Audio.hpp>
#include "Menu.hpp"
#include "Game.hpp"



// Constante de Programme
const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;

// Namespace 
using namespace std;
using namespace sf;

//fenêtre de jeu
sf::RenderWindow window;




int main() {


	window.create(VideoMode(WIN_WIDTH, WIN_HEIGHT, 32), "MOULIN");
	Sprite BackgroundSprite;
	Texture BackgroundTexture;



	//Gerer Menu
	Menu menu;
	menu.AddWindow(&window);
	//menu.AddBackground(&BackgroundTexture, &BackgroundSprite);
	menu.SetBoutonPlay("Play", "image/icon/bouton-start.png", 295, 130, 0.8f, 0.8f);
	menu.SetBoutonExit("Exit", "image/icon/sortir.png", 295, 355, 0.82f, 0.82f);
	menu.SetBoutonRegle("Regle", "image/icon/parametres.png", 20, 10, 0.1f, 0.1f);
	menu.SetBoutonInfo("Info", "image/icon/info.png", 590, 6, 0.4f, 0.4f);
	menu.SetParamImage("image/background/background2.jpg");
	menu.SetBackground("image/background/background1.jpg");
	menu.SetSongBouton("sound/effect/cliq.wav");
	menu.SetMusic("sound/music_background/music1.mp3");
	menu.SetIcon("image/icon/icons8-xbox-controller-48.png");

	//Gerer Mode
	GameModeMenu Mode;
	Mode.AddWindow(&window);
	Mode.SetBoutonPlayer("Player vs Player", "image/icon/player.png", 295, 130, 0.8f, 0.8f);
	Mode.SetBoutonMachine("Plater vs Machine", "image/icon/machine.png", 295, 340, 0.83f, 0.83f);
	Mode.SetBoutonRetour("Retour", "image/icon/bouton-retour.png", 10, 10, 0.08f, 0.1f);
	Mode.SetBackground("image/background/background1.jpg");
	Mode.SetSongBouton("sound/effect/cliq.wav");



	//Gere Game
	sf::Vector2u windowSize = window.getSize();
	// Pos Plateau
	float PLATEAU_WIDTH = 0.4f;
	float PLATEAU_HEIGHT = 0.4f;
	float BOX_PION_WIDTH = 50;
	float BOX_PION_HEIGHT = 100;
	float PLATEAU_POSX = 200;
	float PLATEAU_POSY = 80;

	// Info Pion
	int SPED_MOV_PION = 2;
	float PION_WIDTH_BLANC = 0.1f;
	float PION_HEIGHT_BLANC = 0.1f;
	float PION_WIDTH_NOIR = 0.13f;
	float PION_HEIGHT_NOIR = 0.13f;


	Game game;
	int cmp = 0;
	game.AddWindow(&window);
	game.AddBackground("image/background/background1.jpg");
	game.SetPlateau("image/background/Board2.png", PLATEAU_POSX, PLATEAU_POSY, PLATEAU_HEIGHT, PLATEAU_WIDTH);
	game.SetPionBlanc("image/icon/PionBlanc.png", PLATEAU_POSX, PLATEAU_POSY - 45, PION_HEIGHT_BLANC, PION_WIDTH_BLANC);
	game.SetPionNoir("image/icon/PionNoir.png", PLATEAU_POSX, PLATEAU_POSY + 400, PION_HEIGHT_NOIR, PION_WIDTH_NOIR);
	game.SetBoutonRetour("Retour", "image/icon/bouton-retour.png", 10, 10, 0.08f, 0.1f);
	game.SetSongBouton("sound/effect/cliq.wav");


	menu.PlayMusic();
	int a = 0;
	while(window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else {
				if (a == 0) {
					a = menu.EVENT(event);
				}
				else if (a == 1) {
					a = Mode.EVENT(event);
				}
				else if (a == 2 || a== 3) {
					a = game.EVENT(event,a);
				}
			}

		}
		//window.clear();
		if (a == 0) {
			
			menu.DRAW();
			window.display();
		}
		else if (a == 1) {
			
			Mode.DRAW();
			window.display();
		}
		else if (a == 2 || a == 3) {
			game.DRAW();
		}
		
			//game.DRAW();
		
		
	}
	menu.StopMusic();




	/*VideoMode mode(800, 600);
	Menu MenuGame(mode, "MOULIN");
	MenuGame.SetSoundBouton("sound/effect/cliq.wav");
	MenuGame.AjouterBouton("Play", "image/icon/bouton-start.png",315,100,0.3f,0.3f);
	MenuGame.AjouterBouton("Exit", "image/icon/sortir.png", 315, 300, 0.3f, 0.3f);
	MenuGame.AjouterBouton("Parametre", "image/icon/parametres.png", 20, 10, 0.1f, 0.1f);
	MenuGame.SetBackground("image/background/background1.jpg");
	MenuGame.SetIcon("image/icon/icons8-xbox-controller-48.png");
	MenuGame.SetMusic("sound/music_background/music1.mp3");
	MenuGame.start();*/



	return 0;

}
