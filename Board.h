#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;




class Board
{
public:
	Board();
	//Board(int state[24]);
	~Board();

	void InitialiserCase(Texture &texture, FILE* file);
	Sprite& GetSpriteCase(int i);
	void DRAW(RenderWindow *window);


	/*void color(int t, int f);
	void drop(int i);
	void drop2(int i);
	void afficher_grille();
	void ingame();
	int heuristique(int player, int* table, int p);
	bool moulinformation(int in, int player, int* table);
	bool validmove(int, int);
	void voisin(int i, vector<int>* v, int state[24], int with);*/




private:
	IntRect *CaseRect;
	Sprite *CaseSprite;

	/*int intersection_remplie[24];
	int player = 1;
	int times;
	int noir;
	int blanc;*/
	
};

void SerRect(IntRect rect, int x, int y, int h, int w);

