#include "Bouton.h"


Bouton::Bouton() {
	cheminImageBouton = "PAS DE CHEMIN";
	cheminSoundBouton = "PAS DE CHEMIN";
	NombreBouton++;
}

Bouton::Bouton(string titre) {
	BoutonTitre = titre;
	cheminImageBouton = "PAS DE CHEMIN";
	cheminSoundBouton = "PAS DE CHEMIN";
	NombreBouton++;
}

Bouton::~Bouton() {
	NombreBouton--;
}

int Bouton::NombreBouton = 0;

int Bouton::SetBouton(string titre, string chemin_image, float height, float width) {
	BoutonTitre = titre;
	if (!BoutonTexture.loadFromFile(chemin_image)) {
		cout << "Erreur de chargement l'image de chemin " << chemin_image << endl;
		return EXIT_FAILURE;
	}
	cheminImageBouton = chemin_image;
	BoutonSprite.setTexture(BoutonTexture);
	BoutonSprite.setScale(height, width);
	boutonRect.setSize(sf::Vector2f(height, width));
	return EXIT_SUCCESS;

}

int Bouton::SetImageBouton(string chemin_image)
{
	if (!BoutonTexture.loadFromFile(chemin_image)) {
		cout << "Erreur de chargement l'image de chemin " << chemin_image << endl;
		return EXIT_FAILURE;
	}
	cheminImageBouton = chemin_image;
	BoutonSprite.setTexture(BoutonTexture);
	return EXIT_SUCCESS;
}

int Bouton::SetSoundBouton(string chemin_sound)
{
	if (!soundBuffer.loadFromFile(chemin_sound)) {
		cout << "Erreur de chargement effect son de chemin " << chemin_sound << endl;
		return EXIT_FAILURE;
	}
	cheminSoundBouton = chemin_sound;
	BoutonSound.setBuffer(soundBuffer);
	return EXIT_SUCCESS;

}

void Bouton::SetTitreBouton(string titre)
{
	BoutonTitre = titre;
}

void Bouton::SetDimensionBouton(float height, float width)
{
	BoutonSprite.setScale(height, width);
	boutonRect.setSize(sf::Vector2f(height, width));
}

string Bouton::GetImageBouton()
{
	cout << cheminImageBouton << endl;

	return cheminImageBouton;
}

string Bouton::GetSoundBouton()
{
	cout << cheminSoundBouton << endl;
	return cheminSoundBouton;
}

string Bouton::GetTitreImage()
{
	cout << BoutonTitre << endl;
	return BoutonTitre;
}

void Bouton::DRAW_BOUTON(RenderWindow* WIN)
{
	/*sf::Vector2f SpriteScale = BoutonSprite.getScale();
	sf::Vector2f SpriteSize = BoutonSprite.getGlobalBounds().getSize();
	sf::Vector2f SpritePosition = BoutonSprite.getPosition();
	if (AAA == false) {

		BoutonSprite.setScale(SpriteScale.x * 0.5f, SpriteScale.y * 0.5f);
		sf::Vector2f T = BoutonSprite.getGlobalBounds().getSize();
		float X = SpritePosition.x + (abs(SpriteSize.x - T.x) / 2);
		float Y = SpritePosition.y + (abs(SpriteSize.y - T.y) / 2);
		BoutonSprite.setPosition(X, Y);


		AAA = true;
	}
	else {
		BoutonSprite.setScale(SpriteScale.x * 2.0f, SpriteScale.y * 2.0f);
		sf::Vector2f T = BoutonSprite.getGlobalBounds().getSize();
		float X = SpritePosition.x - (abs(SpriteSize.x - T.x) / 2);
		float Y = SpritePosition.y - (abs(SpriteSize.y - T.y) / 2);
		BoutonSprite.setPosition(X, Y);
		AAA = false;
	}*/
	WIN->draw(BoutonSprite);
}

void Bouton::SetSizeCharcters(unsigned int Size)
{
	boutonTextObject.setCharacterSize(Size);
}

int Bouton::SetFontBouton(string chemin)
{
	if (!font.loadFromFile(chemin)) {
		cout << "EREUR DE TROUVER LE FONT DE CHEMIN " << chemin << endl;
		return EXIT_FAILURE; // Gérer l'erreur si le chargement de la police échoue
	}
	
	boutonTextObject.setFont(font);
}

void Bouton::SetTextBouton(string text)
{
	boutonTextObject.setString(text);
	sf::FloatRect textRect = boutonTextObject.getLocalBounds();
	boutonTextObject.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	boutonTextObject.setPosition(POSX + boutonRect.getSize().x / 2.0f, POSY + boutonRect.getSize().y / 2.0f);
}

void Bouton::DRAW_BOUTON_TXT(RenderWindow* Win)
{
	Win->draw(boutonRect);
	Win->draw(boutonTextObject);		
}

RectangleShape Bouton::GetRectBouton()
{
	return boutonRect;
}



Sprite Bouton::GetSpriteBouton()
{
	return BoutonSprite;
}

void Bouton::PlaySong()
{
	BoutonSound.play();
}



void Bouton::SetPositionBouton(float PosX, float PosY) {
	POSX = PosX;
	POSY = PosY;
	BoutonSprite.setPosition(PosX, PosY);
}
