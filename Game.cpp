#include "Game.hpp"
#include <cstdio>





Game::Game() {
	window = NULL;
	SpriteDeplacement = NULL;
	rolee = player1;
	cmpNoir = 0;
	cmpBlanc = 0;
	NombrePionBlancBox = 9;
	NombrePionNoirBox = 9;
	for (int i = 0; i < 24; i++) {
		grille[i].valeur = -1;
		grille[i].etat = vide;
	}
	
}

Game::~Game()
{
}


void Game::AddWindow(RenderWindow* Win)
{
	window = Win;
}

int Game::AddBackground(string chemin)
{

	// Charger l'image pour l'arrière-plan
	if (!BackgroundTexture.loadFromFile(chemin)) {
		std::cerr << "Erreur : Impossible de charger l'image pour l'arrière-plan." << std::endl;
		return EXIT_FAILURE;
	}
	cerr << "chargement de l'image success!!" << endl;
	BackgroundSprite.setTexture(BackgroundTexture);
	BackgroundSprite.setScale(
		static_cast<float>(window->getSize().x) / BackgroundSprite.getLocalBounds().width,
		static_cast<float>(window->getSize().y) / BackgroundSprite.getLocalBounds().height
	);
	return EXIT_SUCCESS;
}

int Game::SetPlateau(string chemin, float PosX, float PosY, float height, float width)
{
	if (!PlateauTexture.loadFromFile(chemin)) {
		cout << "Erreur de chargement l'image de chemin " << chemin << endl;
		return EXIT_FAILURE;
	}
	PlateauTexture.setSmooth(true); // Optionnel : activer l'antialiasing pour un rendu lisse lors de la mise à l'échelle
	PlateauTexture.setRepeated(false);
	PlateauSprite.setTexture(PlateauTexture);
	PlateauSprite.setScale(height, width);
	PlateauSprite.setPosition(PosX, PosY);
	FILE* file= nullptr;
	const char* filename = "fichier/EmplacementCases.txt";
	const char* mode = "r";
	errno_t errorCode = fopen_s(&file, filename, mode);
	if (errorCode != 0) {
		cout << "IMPOSIBLE OVRIR LE FICHIER" << endl;
		return EXIT_FAILURE;
	}
	board.InitialiserCase(PlateauTexture, file);
	fclose(file);
	return EXIT_SUCCESS;
}

int Game::SetPionBlanc(string chemin, float PosX, float PosY, float height, float width)
{
	if (!PionBlanc.loadFromFile(chemin)) {
		cout << "Erreur de chargement l'image de chemin " << chemin << endl;
		return EXIT_FAILURE;
	}
	PionBlanc.setSmooth(true); // Optionnel : activer l'antialiasing pour un rendu lisse lors de la mise à l'échelle
	PionBlanc.setRepeated(false);
	for (int i = 0; i < 9; i++) {
		Sprite Blanc;
		Blanc.setTexture(PionBlanc);
		Blanc.setScale(height, width);
		Blanc.setPosition(PosX + i * 10, PosY);
		BoxPionBlanc.push_back(Blanc);
	}
	return EXIT_SUCCESS;
}

int Game::SetPionNoir(string chemin, float PosX, float PosY, float height, float width)
{
	if (!PionNoir.loadFromFile(chemin)) {
		cout << "Erreur de chargement l'image de chemin " << chemin << endl;
		return EXIT_FAILURE;
	}
	PionNoir.setSmooth(true); // Optionnel : activer l'antialiasing pour un rendu lisse lors de la mise à l'échelle
	PionNoir.setRepeated(false);
	for (int i = 0; i < 9; i++) {
		Sprite Noir;
		Noir.setTexture(PionNoir);
		Noir.setScale(height, width);
		Noir.setPosition(PosX + i * 10, PosY);
		BoxPionNoir.push_back(Noir);
	}
	return EXIT_SUCCESS;
}

void Game::DRAW()
{
	window->clear();
	//int i = 0;
	board.DRAW(window);
	window->draw(BackgroundSprite);
	//std::cout << i << endl;
	window->draw(PlateauSprite);
	Retour.DRAW_BOUTON(window);
	//i++;
	//std::cout << i << endl;
	for (vector<Sprite>::iterator it = BoxPionBlanc.begin(); it != BoxPionBlanc.end(); it++) {
		window->draw(*it);
	}
	for (vector<Sprite>::iterator it = BoxPionNoir.begin(); it != BoxPionNoir.end(); it++) {
		window->draw(*it);
	}
	if (SpriteDeplacement != NULL) {
		// Calculer le vecteur de déplacement
		sf::Vector2f displacement = destination - SpriteDeplacement->getPosition();

		// Calculer la distance totale à parcourir
		float distance = std::sqrt(displacement.x * displacement.x + displacement.y * displacement.y);

		// Normaliser le vecteur de déplacement
		sf::Vector2f normalizedDisplacement = displacement / distance;

		// Déplacer le sprite jusqu'à ce qu'il atteigne la destination
		while (SpriteDeplacement->getPosition() != destination) {
			// Calculer le déplacement à chaque itération
			sf::Vector2f movement = normalizedDisplacement * 1.0f; // Changer 1.0f pour ajuster la vitesse du déplacement

			// Vérifier si le déplacement dépasse la destination
			if (std::abs(destination.x - SpriteDeplacement->getPosition().x) < std::abs(movement.x) ||
				std::abs(destination.y - SpriteDeplacement->getPosition().y) < std::abs(movement.y)) {
				SpriteDeplacement->setPosition(destination); // Arrêter le déplacement si nous sommes près de la destination
			}
			else {
				SpriteDeplacement->move(movement); // Sinon, continuer le déplacement
			}

			// Effacer la fenêtre et dessiner le sprite déplacé
			window->clear();
			window->draw(BackgroundSprite);
			window->draw(PlateauSprite);
			Retour.DRAW_BOUTON(window);
			for (vector<Sprite>::iterator it = BoxPionBlanc.begin(); it != BoxPionBlanc.end(); it++) {
				window->draw(*it);
			}
			for (vector<Sprite>::iterator it = BoxPionNoir.begin(); it != BoxPionNoir.end(); it++) {
				window->draw(*it);
			}
			window->draw(*SpriteDeplacement);
			window->display();
		}
		SpriteDeplacement = NULL;

	}
	if (!CadrePion.empty()) {
		
		for (const auto& cadre : CadrePion) {
			cout << "Posion cadre : ("<< cadre.getPosition().x<<","<<cadre.getPosition().y<<")" << endl;
			window->draw(cadre);
		}
	 
	
	}

	if (!CadreCase.empty()) {

		for (const auto& cadre : CadreCase) {
			cout << "Posion cadre : (" << cadre.getPosition().x << "," << cadre.getPosition().y << ")" << endl;
			window->draw(cadre);
		}
	}
	if (estWinner) {
		window->draw(SpriteWinner);
	}

	//window->display();
}

void Game::SetBoutonRetour(String titre, string chemin_image, float posX, float posY, float height, float width)
{
	Retour.SetBouton(titre, chemin_image, height, width);
	Retour.SetPositionBouton(posX, posY);

}

void Game::SetSongBouton(string chemin_song)
{
	Retour.SetSoundBouton(chemin_song);
}

int Game::EVENT(Event& event,int choix)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
			if (Retour.GetSpriteBouton().getGlobalBounds().contains(mousePos)) {
				Retour.PlaySong();
				std::cout << "Retour button clicked!" << std::endl;
				RenitialiserGame();
				return 1;
				
				
			}
			
			/*if (PlateauSprite.getGlobalBounds().contains(mousePos)) {
				std::cout << "Position de la souris sur Plateau : (" << mousePos.x << ", " << mousePos.y << ")" <<endl;
			}*/
			
		}
		// Obtenir la position de la souris par rapport à la fenêtre
		//sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);

		//// Afficher les coordonnées de la souris dans la console
		//std::cout << "Position de la souris : (" << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
		if (choix == 2) {
			playerVSplayer(event);
			return 2;
		}
		
	}
	
	if (choix == 3) {
		playerVSmachine(event);
		return 3;
	}
	return 2;
}

void Game::ChangerPlayer()
{
	if (rolee == player1) {
		rolee = player2;
	}
	else {
		rolee = player1;
	}
}

void Game::playerVSplayer(Event& event)
{
	sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
	if (NombrePionBlancBox > 0 || NombrePionNoirBox>0) {
		bool changerole = false;
			for (int i = 0; i < 24; i++) {
				if (board.GetSpriteCase(i).getGlobalBounds().contains(mousePos)) {
					if (grille[i].etat == vide) {
						if (rolee == player1) {
							SpriteDeplacement = &BoxPionNoir[NombrePionNoirBox-1];
							destination = board.GetSpriteCase(i).getPosition();
							grille[i].etat = noir;
							grille[i].valeur = NombrePionNoirBox-1;
							NombrePionNoirBox--;
							changerole = true;
						}
						else {
							SpriteDeplacement = &BoxPionBlanc[NombrePionBlancBox-1];
							destination = board.GetSpriteCase(i).getPosition();
							grille[i].etat = blanc;
							grille[i].valeur = NombrePionBlancBox-1;
							NombrePionBlancBox--;
							changerole = true;
						}
						DRAW();
					}
					if (rolee == player1) {
						if (checkMillFormation(i, grille, noir)) {
							vector <int> indice;
							for (int j = 0; j < 24; j++) {
								if (grille[j].etat == blanc && !checkMillFormation(j, grille, blanc)) {
										indice.push_back(j);
									
								}
							}
							if (indice.size() == 0) {
								for (int j = 0; j < 24; j++) {
									if (grille[j].etat == blanc) {
										indice.push_back(j);

									}
								}
							}
							CadrerPion(rolee, indice, Color::Red);
							DRAW();
							window->display();
							bool estRemove = false;
							do {
							  Event event2;
							    while (window->pollEvent(event2)) {
								
									if (event2.type == Event::Closed) {
										window->close();
									}
									
									if (event2.type == sf::Event::MouseButtonPressed) {
										sf::Vector2f mousePos2 = sf::Vector2f(event2.mouseButton.x, event2.mouseButton.y);
										for (vector<int>::iterator it = indice.begin(); it!=indice.end(); it++) {
											if (board.GetSpriteCase(*it).getGlobalBounds().contains(mousePos2)) {
												

													SpriteDeplacement = &BoxPionBlanc[grille[*it].valeur];
													destination.x = 500;
													destination.y = 480;
													grille[*it].etat = vide;
													grille[*it].valeur = -1;
													estRemove = true;
													
												
											}
											
										}
									}

									
								}
								

							} while (estRemove == false);
							CadrePion.clear();
							DRAW();
							

						}

					}
					else {
						if (checkMillFormation(i, grille, blanc)) {
							vector <int> indice;
							for (int j = 0; j < 24; j++) {
								if (grille[j].etat == noir && !checkMillFormation(j, grille, noir)) {
									indice.push_back(j);

								}
							}
							if (indice.size() == 0) {
								for (int j = 0; j < 24; j++) {
									if (grille[j].etat == noir ) {
										indice.push_back(j);

									}
								}
							}
							CadrerPion(rolee, indice, Color::Red);
							DRAW();
							window->display();
							bool estRemove = false;
							do {
							  Event event2;
							    while (window->pollEvent(event2)) {


								  if (event2.type == sf::Event::MouseButtonPressed) {
									sf::Vector2f mousePos2 = sf::Vector2f(event2.mouseButton.x, event2.mouseButton.y);
									for (vector<int>::iterator it = indice.begin(); it != indice.end(); it++) {
										if (board.GetSpriteCase(*it).getGlobalBounds().contains(mousePos2)) {
											
												SpriteDeplacement = &BoxPionNoir[grille[*it].valeur];
												destination.x = 500;
												destination.y = 35;
												grille[*it].etat = vide;
												grille[*it].valeur = -1;
												estRemove = true;
											
										}
									}
								   }  
							   }

							 } while (estRemove == false);
							

							CadrePion.clear();
							DRAW();

						}
					}
					

				}
			}
			if (changerole == true) {
				rolee = (rolee == player1 ? player2 : player1); // Switch player
			}
	}
	else {
		cmpNoir = 0;
		cmpBlanc = 0;
		for (int k = 0; k < 24; k++) {
			
			if (grille[k].etat == noir) {
				cmpNoir++;
			}
			if (grille[k].etat == blanc) {
				cmpBlanc++;
			}

		}
		cout << "PION BLANC : " << cmpBlanc << endl;
		cout << "PION NOIR : " << cmpNoir << endl;

		if (cmpNoir != 2 && cmpBlanc != 2) {
			bool changerole = false;
			int to;
			if (rolee == player1) {
				for (int i = 0; i < 24; i++) {
					if (board.GetSpriteCase(i).getGlobalBounds().contains(mousePos) && grille[i].etat == noir) {
						vector<int> indiceCase;
						if (VoisinPlein(grille, i)) {
							cout << "Voisin sont Plein" << endl;
							goto fin;
						}
						else {
							if (cmpNoir > 3) {
								int* tab = voisin(i);
								for (int j = 0; tab[j] != -1 && j<4; j++) {
									if (grille[tab[j]].etat == vide) {
										indiceCase.push_back(tab[j]);
									}
								}
							}
							else if (cmpNoir == 3) {
								for (int j = 0; j < 24; j++) {
									if (grille[j].etat == vide) {
										indiceCase.push_back(j);
									}
								}
							}
						}
						CadrerCase(rolee, indiceCase, Color::Green);
						DRAW();
						window->display();
						//bool estmove = false;
						 //do{
							Event event2;
							do {
								while (window->pollEvent(event2)) {

									if (event2.type == Event::Closed) {
										window->close();
									}

									if (event2.type == sf::Event::MouseButtonPressed) {
										sf::Vector2f mousePos2 = sf::Vector2f(event2.mouseButton.x, event2.mouseButton.y);
										for (vector<int>::iterator it = indiceCase.begin(); it != indiceCase.end(); it++) {
											if (board.GetSpriteCase(*it).getGlobalBounds().contains(mousePos2)) {

												cout << i << " " << *it << endl;
												SpriteDeplacement = &BoxPionNoir[grille[i].valeur];
												destination = board.GetSpriteCase(*it).getPosition();
												grille[*it].etat = noir;
												grille[*it].valeur = grille[i].valeur;
												grille[i].etat = vide;
												grille[i].valeur = -1;
												//estmove = true;
												changerole = true;
												to = *it;


											}
											else {
												CadreCase.clear();
											}

										}
									}
								}
							} while (event2.type != sf::Event::MouseButtonPressed);
							

						//} while (estmove == false);


						CadreCase.clear();
						DRAW();
					}
				}
				if (changerole == true) {
					if (checkMillFormation(to, grille, noir)) {
						vector <int> indice;
						for (int j = 0; j < 24; j++) {
							if (grille[j].etat == blanc && !checkMillFormation(j, grille, blanc)) {
								indice.push_back(j);

							}
						}
						if (indice.size() == 0) {
							for (int j = 0; j < 24; j++) {
								if (grille[j].etat == blanc) {
									indice.push_back(j);

								}
							}
						}
						CadrerPion(rolee, indice, Color::Red);
						DRAW();
						window->display();
						bool estRemove = false;
						
							Event event2;
							do {
							while (window->pollEvent(event2)) {


								if (event2.type == sf::Event::MouseButtonPressed && event2.mouseButton.button == sf::Mouse::Left) {
									sf::Vector2f mousePos2 = sf::Vector2f(event2.mouseButton.x, event2.mouseButton.y);
									for (vector<int>::iterator it = indice.begin(); it != indice.end(); it++) {
										if (board.GetSpriteCase(*it).getGlobalBounds().contains(mousePos2)) {
											 
												SpriteDeplacement = &BoxPionBlanc[grille[*it].valeur];
												destination.x = 500;
												destination.y = 480;
												grille[*it].etat = vide;
												grille[*it].valeur = -1;
												estRemove = true;
											
										}
									}
								}
							}

						
					        } while (estRemove==false);


						CadrePion.clear();
						DRAW();
					}
				}
			}

			else {
				for (int i = 0; i < 24; i++) {
					if (board.GetSpriteCase(i).getGlobalBounds().contains(mousePos) && grille[i].etat == blanc) {
						vector<int> indiceCase;
						if (VoisinPlein(grille, i)) {
							cout << "Voisin sont Plein" << endl;
							goto fin;
						}
						else {
							if (cmpBlanc > 3) {
								int* tab = voisin(i);
								for (int j = 0; tab[j] != -1 && j<4; j++) {
									if (grille[tab[j]].etat == vide) {
										indiceCase.push_back(tab[j]);
									}
								}
							}
							else if (cmpBlanc == 3) {
								for (int j = 0; j < 24; j++) {
									if (grille[j].etat == vide) {
										indiceCase.push_back(j);
									}
								}
							}
						}
						CadrerCase(rolee, indiceCase, Color::Green);
						DRAW();
						window->display();
						bool estmove = false;
						
						Event event2;
						do {
						   while (window->pollEvent(event2)) {


							   if (event2.type == sf::Event::MouseButtonPressed && event2.mouseButton.button == sf::Mouse::Left) {
								   sf::Vector2f mousePos2 = sf::Vector2f(event2.mouseButton.x, event2.mouseButton.y);
								   for (vector<int>::iterator it = indiceCase.begin(); it!=indiceCase.end();it++) {
									   if (board.GetSpriteCase(*it).getGlobalBounds().contains(mousePos2)) {
										            cout << i << " " << *it << endl;
													cout << grille[i].valeur << " " << grille[*it].valeur << endl;
												   SpriteDeplacement = &BoxPionBlanc[grille[i].valeur];
												   destination = board.GetSpriteCase(*it).getPosition();
												   grille[*it].etat = blanc;
												   grille[*it].valeur = grille[i].valeur;
												   grille[i].etat = vide;
												   grille[i].valeur = -1;
												   cout << grille[i].valeur << " " << grille[*it].valeur << endl;
												   estmove = true;
												   changerole = true;
												   to = *it;
											   
										   
									   }
									   else {
										   CadreCase.clear();
									   }
								   }
							   }
						   }

						} while (event2.type != sf::Event::MouseButtonPressed);
						
						CadreCase.clear();
						DRAW();
					}
				}
				if (changerole == true) {
					if (checkMillFormation(to, grille, blanc)) {
						vector <int> indice;
						for (int j = 0; j < 24; j++) {
							if (grille[j].etat == noir && !checkMillFormation(j, grille, noir)) {
								indice.push_back(j);

							}
						}
						if (indice.size() == 0) {
							for (int j = 0; j < 24; j++) {
								if (grille[j].etat == noir) {
									indice.push_back(j);

								}
							}
						}
						CadrerPion(rolee, indice, Color::Red);
						DRAW();
						window->display();
						bool estRemove = false;
						do {
							Event event2;
							while (window->pollEvent(event2)) {


								if (event2.type == sf::Event::MouseButtonPressed) {
									sf::Vector2f mousePos2 = sf::Vector2f(event2.mouseButton.x, event2.mouseButton.y);
									for (vector<int>::iterator it = indice.begin(); it != indice.end();it++) {
										if (board.GetSpriteCase(*it).getGlobalBounds().contains(mousePos2)) {
											
												SpriteDeplacement = &BoxPionNoir[grille[*it].valeur];
												destination.x = 500;
												destination.y = 35;
												grille[*it].etat = vide;
												grille[*it].valeur = -1;
												estRemove = true;
											
										}
									}
								}
							}

						} while (estRemove == false);

						CadrePion.clear();

						DRAW();

					}
				}

			}
		fin:

			if (changerole == true) {
				rolee = (rolee == player1 ? player2 : player1); // Switch player
			}
		}
		else {
			if (cmpBlanc == 2) {
				cout << "PLAYER1 EST GAGNE" << endl;
			}
			else {
				cout << "PLAYER2 EST GANGE" << endl;
			}
		}

		
	}
	

}

void Game::playerVSmachine(Event& event)
{
	bool changerole = false;
	cellule suivant[24];
	if (NombrePionBlancBox > 0 || NombrePionNoirBox > 0) {
		
		if (rolee == player1) {
			bool estremove = false;
			Node* racine;
			racine = CreeNode(grille, phase1, NombrePionNoirBox, NombrePionBlancBox);
			int a = minimax(racine, 4, true, -1000000000, 1000000000, player1);
			for (auto fil : racine->children) {
				if (a == fil->h) {
					for (int i = 0; i < 24; i++) {
						suivant[i].etat = fil->grille[i].etat;
					}
					break;
				}
			}
			for (int i = 0; i < 24; i++) {
				if (suivant[i].etat != grille[i].etat) {
					if (suivant[i].etat == noir) {
						SpriteDeplacement = &BoxPionNoir[NombrePionNoirBox - 1];
						destination = board.GetSpriteCase(i).getPosition();
						grille[i].etat = noir;
						grille[i].valeur = NombrePionNoirBox - 1;
						NombrePionNoirBox--;
						changerole = true;
						
						break;
					}
				}
			}
			DRAW();

			for (int i = 0; i < 24; i++) {
				if (suivant[i].etat != grille[i].etat) {
					if (suivant[i].etat == vide) {
						SpriteDeplacement = &BoxPionBlanc[grille[i].valeur];
						destination.x = 500;
						destination.y = 480;
						grille[i].etat = vide;
						grille[i].valeur = -1;
						estremove = true;
						break;

					}
				}
			}
			if (estremove) {
				DRAW();
			}

			DestroyNode(racine);
			//NombrePionNoirBox--;


		}
		else {
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
				for (int i = 0; i < 24; i++) {

					if (board.GetSpriteCase(i).getGlobalBounds().contains(mousePos)) {
						if (grille[i].etat == vide) {

							SpriteDeplacement = &BoxPionBlanc[NombrePionBlancBox - 1];
							destination = board.GetSpriteCase(i).getPosition();
							grille[i].etat = blanc;
							grille[i].valeur = NombrePionBlancBox - 1;
							NombrePionBlancBox--;
							changerole = true;
							
							

						}
						if (changerole) {
							DRAW();
						}

						if (checkMillFormation(i, grille, blanc)) {
							vector <int> indice;
							for (int j = 0; j < 24; j++) {
								if (grille[j].etat == noir && !checkMillFormation(j, grille, noir)) {
									indice.push_back(j);

								}
							}
							if (indice.size() == 0) {
								for (int j = 0; j < 24; j++) {
									if (grille[j].etat == noir) {
										indice.push_back(j);

									}
								}
							}
							CadrerPion(rolee, indice, Color::Red);
							DRAW();
							window->display();
							bool estRemove = false;
							do {
								Event event2;
								while (window->pollEvent(event2)) {


									if (event2.type == sf::Event::MouseButtonPressed) {
										sf::Vector2f mousePos2 = sf::Vector2f(event2.mouseButton.x, event2.mouseButton.y);
										for (vector<int>::iterator it = indice.begin(); it != indice.end(); it++) {
											if (board.GetSpriteCase(*it).getGlobalBounds().contains(mousePos2)) {

												SpriteDeplacement = &BoxPionNoir[grille[*it].valeur];
												destination.x = 500;
												destination.y = 35;
												grille[*it].etat = vide;
												grille[*it].valeur = -1;
												estRemove = true;

											}
										}
									}
								}

							} while (estRemove == false);


							CadrePion.clear();
							DRAW();

						}


					}

					

					

					if (changerole) {
						break;
					}

				}
			}
			
		}
	}
	else {
		cmpNoir = 0;
		cmpBlanc = 0;
		for (int k = 0; k < 24; k++) {

			if (grille[k].etat == noir) {
				cmpNoir++;
			}
			if (grille[k].etat == blanc) {
				cmpBlanc++;
			}

		}
		//cout << "PION BLANC : " << cmpBlanc << endl;
		//cout << "PION NOIR : " << cmpNoir << endl;

		if (cmpNoir != 2 && cmpBlanc != 2) {
		
			int to;
			if (rolee == player1) {

				Node* racine;
				if (cmpNoir > 3) {
					racine = CreeNode(grille, phase2, NombrePionNoirBox, NombrePionBlancBox);
				}
				else{
					racine = CreeNode(grille, phase3, NombrePionNoirBox, NombrePionBlancBox);
				}

				int a = minimax(racine, 4, true, -1000000000, 1000000000, player1);
				
				for (auto fil : racine->children) {
					if (a == fil->h) {
						for (int i = 0; i < 24; i++) {
							suivant[i].etat = fil->grille[i].etat;
						}
						break;
					}
				}
				for (int i = 0; i < 24; i++) {
					if (suivant[i].etat != grille[i].etat) {
						if (suivant[i].etat == noir) {
							for (int j = 0; j < 24; j++) {
								if (suivant[j].etat != grille[j].etat && grille[j].etat == noir) {
									cout << j << " " << i << endl;
									SpriteDeplacement = &BoxPionNoir[grille[j].valeur];
									destination = board.GetSpriteCase(i).getPosition();
									grille[i].etat = noir;
									grille[i].valeur = grille[j].valeur;
									grille[j].etat = vide;
									grille[j].valeur = -1;
									//estmove = true;
									changerole = true;
									
									break;
								}
							}
						}
					}
				}
				DRAW();
				for (int i = 0; i < 24; i++) {
					if (suivant[i].etat != grille[i].etat) {
						SpriteDeplacement = &BoxPionBlanc[grille[i].valeur];
						destination.x = 500;
						destination.y = 480;
						grille[i].etat = vide;
						grille[i].valeur = -1;
						
						break;
						
					}
				}
				DRAW();
				





				
			}

			else {
				if (event.type == sf::Event::MouseButtonPressed) {
					sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
					for (int i = 0; i < 24; i++) {
						if (board.GetSpriteCase(i).getGlobalBounds().contains(mousePos) && grille[i].etat == blanc) {
							vector<int> indiceCase;
							if (VoisinPlein(grille, i)) {
								cout << "Voisin sont Plein" << endl;
								goto fin;
							}
							else {
								if (cmpBlanc > 3) {
									int* tab = voisin(i);
									for (int j = 0; tab[j] != -1 && j < 4; j++) {
										if (grille[tab[j]].etat == vide) {
											indiceCase.push_back(tab[j]);
										}
									}
								}
								else if (cmpBlanc == 3) {
									for (int j = 0; j < 24; j++) {
										if (grille[j].etat == vide) {
											indiceCase.push_back(j);
										}
									}
								}
							}
							CadrerCase(rolee, indiceCase, Color::Green);
							DRAW();
							window->display();
							bool estmove = false;

							Event event2;
							do {
								while (window->pollEvent(event2)) {


									if (event2.type == sf::Event::MouseButtonPressed && event2.mouseButton.button == sf::Mouse::Left) {
										sf::Vector2f mousePos2 = sf::Vector2f(event2.mouseButton.x, event2.mouseButton.y);
										for (vector<int>::iterator it = indiceCase.begin(); it != indiceCase.end(); it++) {
											if (board.GetSpriteCase(*it).getGlobalBounds().contains(mousePos2)) {
												cout << i << " " << *it << endl;
												cout << grille[i].valeur << " " << grille[*it].valeur << endl;
												SpriteDeplacement = &BoxPionBlanc[grille[i].valeur];
												destination = board.GetSpriteCase(*it).getPosition();
												grille[*it].etat = blanc;
												grille[*it].valeur = grille[i].valeur;
												grille[i].etat = vide;
												grille[i].valeur = -1;
												cout << grille[i].valeur << " " << grille[*it].valeur << endl;
												estmove = true;
												changerole = true;
												to = *it;
												//CadreCase.clear();
												//DRAW();
												break;


											}
											else {
												CadreCase.clear();
												
											}
										}
									}
								}

							} while (event2.type != sf::Event::MouseButtonPressed);
							CadreCase.clear();
							DRAW();
					

							
						}
						if (changerole) {
							break;
						}
					}
				
				}
				if (changerole == true) {
					if (checkMillFormation(to, grille, blanc)) {
						vector <int> indice;
						for (int j = 0; j < 24; j++) {
							if (grille[j].etat == noir && !checkMillFormation(j, grille, noir)) {
								indice.push_back(j);

							}
						}
						if (indice.size() == 0) {
							for (int j = 0; j < 24; j++) {
								if (grille[j].etat == noir) {
									indice.push_back(j);

								}
							}
						}
						CadrerPion(rolee, indice, Color::Red);
						DRAW();
						window->display();
						bool estRemove = false;
						do {
							Event event2;
							while (window->pollEvent(event2)) {


								if (event2.type == sf::Event::MouseButtonPressed) {
									sf::Vector2f mousePos2 = sf::Vector2f(event2.mouseButton.x, event2.mouseButton.y);
									for (vector<int>::iterator it = indice.begin(); it != indice.end(); it++) {
										if (board.GetSpriteCase(*it).getGlobalBounds().contains(mousePos2)) {

											SpriteDeplacement = &BoxPionNoir[grille[*it].valeur];
											destination.x = 500;
											destination.y = 35;
											grille[*it].etat = vide;
											grille[*it].valeur = -1;
											estRemove = true;
											//CadrePion.clear();

											//DRAW();

										}
									}
								}
							}

						} while (estRemove == false);
						CadrePion.clear();
						DRAW();

					}
				}
			}
			   
		
			
		}
		else {
			if (cmpBlanc == 2) {
				cout << "PLAYER1 EST GAGNE" << endl;
				if (!TextureWinner.loadFromFile("image/background/NoirWinner.jpg")) {
					cout << "Failed to impload image!" << endl;
				}
				else {
					SpriteWinner.setTexture(TextureWinner);
					SpriteWinner.setScale(
						300.0f / SpriteWinner.getLocalBounds().width,
						300.0f / SpriteWinner.getLocalBounds().height
					); // Redimensionner l'image à 200x200 pixels
					SpriteWinner.setPosition(170, 70);
					estWinner = true;
				}


			}
			else {
				cout << " PLAYER2 EST GANGE" << endl;
				if (!TextureWinner.loadFromFile("image/background/BlancWinner.jpg")) {
					cout << "Failed to impload image!" << endl;
				}
				else {
					SpriteWinner.setTexture(TextureWinner);
					SpriteWinner.setScale(
						300.0f / SpriteWinner.getLocalBounds().width,
						300.0f / SpriteWinner.getLocalBounds().height
					); // Redimensionner l'image à 200x200 pixels
					SpriteWinner.setPosition(170, 70);
					estWinner = true;
				}
			}
			DRAW();
			window->display();
		}


	}
	fin :
	if (changerole == true) {
		rolee = (rolee == player1 ? player2 : player1); // Switch player
	}
    
}


void Game::CadrerPion(tour player, vector<int>& indice, Color color) {
	vector<Sprite> PION;
	if (player == player1) {
		PION = BoxPionBlanc;
	}
	else {
		PION = BoxPionNoir;
	}


	for (vector<int>::iterator it = indice.begin(); it != indice.end(); it++) {
		cout << *it << endl; // Affiche l'indice courant pour débogage
		CircleShape cercle;
		// Vérifiez que l'indice est valide
		if (*it >= 0 && *it < 24) {
			// Obtenir les dimensions du sprite
			sf::FloatRect spriteBounds = PION[grille[*it].valeur].getGlobalBounds();

			// Calculer le rayon du cadre circulaire pour entourer le sprite
			float radius = std::max(spriteBounds.width, spriteBounds.height) / 2;

			// Créer un cercle pour le cadre
			cercle.setRadius(radius);
			cercle.setPosition(PION[grille[*it].valeur].getPosition().x + spriteBounds.width / 2 - radius,
				PION[grille[*it].valeur].getPosition().y + spriteBounds.height / 2 - radius);
			cercle.setFillColor(sf::Color::Transparent);  // Pas de remplissage pour le cadre
			cercle.setOutlineThickness(2);  // Épaisseur de la bordure
			cercle.setOutlineColor(color);  // Couleur de la bordure
			CadrePion.push_back(cercle);
			
		}
		else {
			cerr << "Indice invalide: " << *it << endl;
		}
	}
}

void Game::CadrerCase(tour player, vector<int>& indice, Color color) {
	vector<Sprite> PION;
	if (player == player1) {
		PION = BoxPionBlanc;
	}
	else {
		PION = BoxPionNoir;
	}


	for (vector<int>::iterator it = indice.begin(); it != indice.end(); it++) {
		cout << *it << endl; // Affiche l'indice courant pour débogage
		CircleShape cercle;
		// Vérifiez que l'indice est valide
		if (*it >= 0 && *it < 24) {
			// Obtenir les dimensions du sprite
			sf::FloatRect spriteBounds = board.GetSpriteCase(*it).getGlobalBounds();

			// Calculer le rayon du cadre circulaire pour entourer le sprite
			float radius = std::max(spriteBounds.width, spriteBounds.height) / 2;

			// Créer un cercle pour le cadre
			cercle.setRadius(radius);
			cercle.setPosition(board.GetSpriteCase(*it).getPosition().x + spriteBounds.width / 2 - radius,
				board.GetSpriteCase(*it).getPosition().y + spriteBounds.height / 2 - radius);
			cercle.setFillColor(sf::Color::Transparent);  // Pas de remplissage pour le cadre
			cercle.setOutlineThickness(2);  // Épaisseur de la bordure
			cercle.setOutlineColor(color);  // Couleur de la bordure
			CadreCase.push_back(cercle);

		}
		else {
			cerr << "Indice invalide: " << *it << endl;
		}
	}
}

void Game::RenitialiserGame()
{
	for (int i = 0; i < 24; i++) {
		grille[i].etat = vide;
		grille[i].valeur = -1;
	}
	BoxPionNoir.clear();
	BoxPionBlanc.clear();

	SetPionNoir("image/icon/PionNoir.png", 200, 480, 0.13f, 0.13f);
	SetPionBlanc("image/icon/PionBlanc.png", 200, 35, 0.1f, 0.1f);

	NombrePionBlancBox = 9;
	NombrePionNoirBox = 9;
	estWinner = false;
	rolee = player1;
}

	

	

	
	
	
	















//void Game::moveSprite(sf::Sprite& sprite, const sf::Vector2f& destination)
//{
//	// Calculer le vecteur de déplacement
//	sf::Vector2f displacement = destination - sprite.getPosition();
//
//	// Calculer la distance totale à parcourir
//	float distance = std::sqrt(displacement.x * displacement.x + displacement.y * displacement.y);
//
//	// Normaliser le vecteur de déplacement
//	sf::Vector2f normalizedDisplacement = displacement / distance;
//
//	// Déplacer le sprite jusqu'à ce qu'il atteigne la destination
//	while (sprite.getPosition() != destination) {
//		// Calculer le déplacement à chaque itération
//		sf::Vector2f movement = normalizedDisplacement * 1.0f; // Changer 1.0f pour ajuster la vitesse du déplacement
//
//		// Vérifier si le déplacement dépasse la destination
//		if (std::abs(destination.x - sprite.getPosition().x) < std::abs(movement.x) ||
//			std::abs(destination.y - sprite.getPosition().y) < std::abs(movement.y)) {
//			sprite.setPosition(destination); // Arrêter le déplacement si nous sommes près de la destination
//		}
//		else {
//			sprite.move(movement); // Sinon, continuer le déplacement
//		}
//
//		// Effacer la fenêtre et dessiner le sprite déplacé
//		window->clear();
//		window->draw(BackgroundSprite);
//		window->draw(PlateauSprite);
//		Retour.DRAW_BOUTON(window);
//		window->draw(sprite);
//		window->display();
//	}
//}


