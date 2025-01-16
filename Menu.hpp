#pragma once
#include "Bouton.h"





class Menu
{


public:
	Menu();
	~Menu();


	int SetBackground(string chemin_background);
	int SetMusic(String chemin_music);
	int SetIcon(String chemin_icon);
	void AddWindow(RenderWindow* Win);
	void AddBackground(string chemin);

	void SetBoutonPlay(String titre, string chemin_image, float posX, float posY, float height, float width);
	void SetBoutonExit(String titre, string chemin_image, float posX, float posY, float height, float width);
	void SetBoutonRegle(string titre, string chemin_image, float posX, float posY, float height, float width);
	void SetBoutonInfo(string titre, string chemin_image, float posX, float posY, float height, float width);
	void DRAW();
	void SetSongBouton(string chemin_song);
	int EVENT(Event& event);
	void PlayMusic();
	void StopMusic();
	void AfficherInfo();
	void SetParamImage(string chemin_image);



	static int NombreMenu;

private:

	RenderWindow* window;
	Sprite backgroundSprite;
	Texture backgroundTexture;
	Bouton Play;
	Bouton Exit;
	Bouton Regle;
	Bouton Info;
	Music music;
	Image icon;


	// Bouton de son
	bool soundOn = true;
	Texture soundOnTexture;
	Texture soundOffTexture;
	Sprite soundButton;

	// Membres pour l'image de param?tres transparente
	Texture paramTexture;
	Sprite paramSprite;
	bool showParamImage = false; // Indicateur pour afficher l'image










};

class GameModeMenu {
public:
	GameModeMenu();
	~GameModeMenu();

	void AddWindow(RenderWindow* Win);
	void SetBoutonPlayer(String titre, string chemin_image, float posX, float posY, float height, float width);
	void SetBoutonMachine(String titre, string chemin_image, float posX, float posY, float height, float width);
	void SetBoutonRetour(String titre, string chemin_image, float posX, float posY, float height, float width);
	int SetBackground(string chemin_background);
	void DRAW();

	void SetSongBouton(string chemin_song);
	int EVENT(Event& event);


private:
	RenderWindow* window;
	Sprite backgroundSprite;
	Texture backgroundTexture;

	Bouton PlayerPlayer;
	Bouton PlayerMachine;
	Bouton Retour;





};