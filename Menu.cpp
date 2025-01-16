#include "Menu.hpp"

Menu::Menu() {

    window = NULL;
    NombreMenu++;

    if (!soundOnTexture.loadFromFile("image/icon/sound.png")){
        cout<<" failed to impload image"<<endl;
    }
    if (!soundOffTexture.loadFromFile("image/icon/soundoff.png")){
        cout << " failed to impload image" << endl;
    }
    soundButton.setTexture(soundOnTexture);
    soundButton.setScale(0.4f, 0.4f);
    soundButton.setPosition(710, 6);
}


Menu::~Menu() {

    NombreMenu--;
}

int Menu::SetBackground(string chemin_background)
{
    // Charger l'image pour l'arrière-plan
    if (!backgroundTexture.loadFromFile(chemin_background)) {
        std::cerr << "Erreur : Impossible de charger l'image pour l'arrière-plan." << std::endl;
        return EXIT_FAILURE;
    }
    cerr << "chargement de l'image success!!" << endl;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window->getSize().x) / backgroundSprite.getLocalBounds().width,
        static_cast<float>(window->getSize().y) / backgroundSprite.getLocalBounds().height
    );
    return EXIT_SUCCESS;
}

int Menu::SetMusic(String chemin_music)
{
    if (!music.openFromFile(chemin_music)) {
        // Gérer l'erreur si le chargement du fichier audio échoue
        cout << "Erreur de lecture la music" << endl;
        return 1;
    }
    cout << "lecture de music success!!" << endl;
    return 0;
}

int Menu::SetIcon(String chemin_icon)
{
    if (!icon.loadFromFile(chemin_icon)) {
        cout << "Imposible de charger l'image Icon" << endl;
        return EXIT_FAILURE;
    }
    cout << "chargement image success" << endl;
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    return EXIT_SUCCESS;
}

void Menu::AddWindow(RenderWindow* Win)
{
    window = Win;
}



void Menu::SetBoutonPlay(String titre, string chemin_image, float posX, float posY, float height, float width)
{
    Play.SetBouton(titre, chemin_image, height, width);
    Play.SetPositionBouton(posX, posY);
}

void Menu::SetBoutonExit(String titre, string chemin_image, float posX, float posY, float height, float width)
{
    Exit.SetBouton(titre, chemin_image, height, width);
    Exit.SetPositionBouton(posX, posY);
}

void Menu::SetBoutonRegle(string titre, string chemin_image, float posX, float posY, float height, float width)
{
    Regle.SetBouton(titre, chemin_image, height, width);
    Regle.SetPositionBouton(posX, posY);
}

void Menu::SetBoutonInfo(string titre, string chemin_image, float posX, float posY, float height, float width)
{
    Info.SetBouton(titre, chemin_image, height, width);
    Info.SetPositionBouton(posX, posY);
}

void Menu::DRAW()
{
    window->clear();
    window->draw(backgroundSprite);
    Play.DRAW_BOUTON(window);
    Exit.DRAW_BOUTON(window);
    Regle.DRAW_BOUTON(window);
    Info.DRAW_BOUTON(window);
    window->draw(soundButton);
    if (showParamImage) {
        window->draw(paramSprite);
    }
    

}

void Menu::SetSongBouton(string chemin_song)
{
    Play.SetSoundBouton(chemin_song);
    Exit.SetSoundBouton(chemin_song);
    Regle.SetSoundBouton(chemin_song);
    Info.SetSoundBouton(chemin_song);
}

int Menu::EVENT(Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
            if (Play.GetSpriteBouton().getGlobalBounds().contains(mousePos)) {
                Play.PlaySong();
                std::cout << "Play button clicked!" << std::endl;
                return 1;
            }
            else if (Regle.GetSpriteBouton().getGlobalBounds().contains(mousePos)) {
                Regle.PlaySong();
                std::cout << "Regle button clicked!" << std::endl;
                showParamImage = !showParamImage;
            }
            else if (Info.GetSpriteBouton().getGlobalBounds().contains(mousePos)) {
                Info.PlaySong();
                std::cout << "Info button clicked!" << std::endl;
                AfficherInfo();
            }
            else if (soundButton.getGlobalBounds().contains(mousePos)) {
                Play.PlaySong();
                std::cout << "Sound button clicked!" << std::endl;
                soundOn = !soundOn;
                if (soundOn) {
                    soundButton.setTexture(soundOnTexture);
                    music.play();
                }
                else {
                    soundButton.setTexture(soundOffTexture);
                    music.pause();
                }

            }
            else if (Exit.GetSpriteBouton().getGlobalBounds().contains(mousePos)) {
                Exit.PlaySong();
                std::cout << "Exit button clicked!" << std::endl;
                window->close();
            }
        }
    }
    return 0;
}

void Menu::PlayMusic()
{
    music.play();
}

void Menu::StopMusic()
{
    music.stop();
}

void Menu::AfficherInfo() {
    RenderWindow infoWindow(VideoMode(300, 400), "Information");

    // Définir le texte
    // Font font;
    // if (!font.loadFromFile("fonts/Adorable Handmade.ttf")) {
    // std::cerr << "Erreur : Impossible de charger la police." << std::endl;
    // return;
    // }
    Texture backgroundtext;
    if (!backgroundtext.loadFromFile("image/background/info.jpg")) {
        std::cerr << "Erreur : Impossible de charger background" << std::endl;
        return;
    }
    Sprite backgroundsprt(backgroundtext);
    backgroundsprt.setScale(
        static_cast<float>(infoWindow.getSize().x) / backgroundsprt.getLocalBounds().width,
        static_cast<float>(infoWindow.getSize().y) / backgroundsprt.getLocalBounds().height
    );

    // Text infoText;
    // infoText.setFont(font);
    // infoText.setString("Développé par\n Omaima Bonouara \n Noureddiine Yassiene\net Mohamed Amine Slimani");
    // infoText.setCharacterSize(20);
    // infoText.setFillColor(Color::White);
    // infoText.setPosition(50, 50);

    while (infoWindow.isOpen()) {
        Event event;
        while (infoWindow.pollEvent(event)) {
            if (event.type == Event::Closed) {
                infoWindow.close();
            }
        }

        infoWindow.clear();
        infoWindow.draw(backgroundsprt);
        // infoWindow.draw(infoText);
        infoWindow.display();
    }
}

void Menu::SetParamImage(string chemin_image) {
    if (!paramTexture.loadFromFile(chemin_image)) {
        std::cerr << "Erreur : Impossible de charger l'image pour les paramètres." << std::endl;
        return;
    }
    paramSprite.setTexture(paramTexture);
    paramSprite.setColor(Color(255, 255, 255)); // 192 pour 75% de transparence
    paramSprite.setScale(
        500.0f / paramSprite.getLocalBounds().width,
        500.0f / paramSprite.getLocalBounds().height
    ); // Redimensionner l'image à 200x200 pixels
    paramSprite.setPosition(170, 80); // Positionnez l'image où vous le souhaitez
}
int Menu::NombreMenu = 0;




GameModeMenu::GameModeMenu()
{
}

GameModeMenu::~GameModeMenu()
{
}

void GameModeMenu::AddWindow(RenderWindow* Win)
{
    window = Win;
}

void GameModeMenu::SetBoutonPlayer(String titre, string chemin_image, float posX, float posY, float height, float width)
{
    PlayerPlayer.SetBouton(titre, chemin_image, height, width);
    PlayerPlayer.SetPositionBouton(posX, posY);
}

void GameModeMenu::SetBoutonMachine(String titre, string chemin_image, float posX, float posY, float height, float width)
{
    PlayerMachine.SetBouton(titre, chemin_image, height, width);
    PlayerMachine.SetPositionBouton(posX, posY);
}

void GameModeMenu::SetBoutonRetour(String titre, string chemin_image, float posX, float posY, float height, float width)
{
    Retour.SetBouton(titre, chemin_image, height, width);
    Retour.SetPositionBouton(posX, posY);
}

int GameModeMenu::SetBackground(string chemin_background)
{
    // Charger l'image pour l'arrière-plan
    if (!backgroundTexture.loadFromFile(chemin_background)) {
        std::cerr << "Erreur : Impossible de charger l'image pour l'arrière-plan." << std::endl;
        return EXIT_FAILURE;
    }
    cerr << "chargement de l'image success!!" << endl;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window->getSize().x) / backgroundSprite.getLocalBounds().width,
        static_cast<float>(window->getSize().y) / backgroundSprite.getLocalBounds().height
    );
    return EXIT_SUCCESS;
}

void GameModeMenu::DRAW()
{
    window->clear();
    window->draw(backgroundSprite);
    PlayerPlayer.DRAW_BOUTON(window);
    PlayerMachine.DRAW_BOUTON(window);
    Retour.DRAW_BOUTON(window);
    
}

void GameModeMenu::SetSongBouton(string chemin_song)
{
    PlayerPlayer.SetSoundBouton(chemin_song);
    PlayerMachine.SetSoundBouton(chemin_song);
    Retour.SetSoundBouton(chemin_song);
}

int GameModeMenu::EVENT(Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
            if (PlayerPlayer.GetSpriteBouton().getGlobalBounds().contains(mousePos)) {
                PlayerPlayer.PlaySong();
                std::cout << "Player vs Player button clicked!" << std::endl;
                return 2;
            }
            else if (PlayerMachine.GetSpriteBouton().getGlobalBounds().contains(mousePos)) {
                PlayerMachine.PlaySong();
                std::cout << "Player vs Machine button clicked!" << std::endl;
                return 3;
            }
            else if (Retour.GetSpriteBouton().getGlobalBounds().contains(mousePos)) {
                Retour.PlaySong();
                std::cout << "Retour button clicked!" << std::endl;
                return 0;
            }
          
        }
    }
    return 1;
}
