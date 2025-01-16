#pragma once
#include "Menu.hpp"
#include "Board.h"
#include "BoardLogique.hpp"
#include <memory>  // Pour utiliser std::unique_ptr




class Game {

public:
	Game();
	~Game();



	void AddWindow(RenderWindow* Win);
	int AddBackground(string chemin);
	int SetPlateau(string chemin, float PosX, float PosY, float height, float width);
	int SetPionBlanc(string chemin, float PosX, float PosY, float height, float width);
	int SetPionNoir(string chemin, float height, float width, float PosX, float PosY);
	void DRAW();
	void SetBoutonRetour(String titre, string chemin_image, float posX, float posY, float height, float width);
	void SetSongBouton(string chemin_song);
	int EVENT(Event& event, int choix);
	void ChangerPlayer();
	void playerVSplayer(Event& event);
	void playerVSmachine(Event& event);
	void CadrerPion(tour player, vector<int> &indice, Color color);
	void CadrerCase(tour player, vector<int>& indice, Color color);
	void RenitialiserGame();
	void AfficherWinner();

	//void moveSprite(sf::Sprite* sprite, sf::Vector2f destination);





private:
	int WidthPlateau;
	int HeightPlateau;
	RenderWindow* window;
	Sprite PlateauSprite;
	Texture PlateauTexture;
	Sprite BackgroundSprite;
	Texture BackgroundTexture;
	Font font;
	Text text1, text2;
	Texture PionBlanc;
	Texture PionNoir;
	vector<Sprite> BoxPionBlanc;
	vector<Sprite> BoxPionNoir;
	Bouton Retour;
	Board board;
	Sprite* SpriteDeplacement;
	vector<sf::CircleShape> CadrePion;
	vector<sf::CircleShape> CadreCase;
	sf::Vector2f destination;
	int cmpNoir = 0;
	int cmpBlanc = 0;
	int NombrePionBlancBox, NombrePionNoirBox;
	//bool grille[24];
	tour rolee;
	tour winner;
	bool estWinner=false;
	Texture TextureWinner;
	Sprite  SpriteWinner;
	cellule grille[24];


};


