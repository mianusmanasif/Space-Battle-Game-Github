#include <SFML/Graphics.hpp>
#include "MainMenu.h"
void StartGame();
using namespace sf;
int main() {
    //Make a main window
    RenderWindow MENU(VideoMode({1920,1080}),"Main Menu",Style::Default);
    MainMenu mainMenu(MENU.getSize().x,MENU.getSize().y);
    //set background
    RectangleShape background;
    background.setSize(Vector2f(1920,1080));
    Texture MainTexture;
    MainTexture.loadFromFile("Texture/gamephoto.jpg");
    background.setTexture(&MainTexture);

    //Photo to the game
    RectangleShape Pbackground;
    Pbackground.setSize(Vector2f(1920,1080));
    Texture back_texture;
    back_texture.loadFromFile("Texture/gamephoto.jpg");
    Pbackground.setTexture(&back_texture);

    //photo to option
    RectangleShape Obackground;
    Obackground.setSize(Vector2f(1920,1080));
    Texture Optiontexture;
    Optiontexture.loadFromFile("Texture/gamephoto.jpg");
    Obackground.setTexture(&Optiontexture);

    //About our Projects
    RectangleShape ABbackground;
    ABbackground.setSize(Vector2f(1920,1080));
    Texture About_texture;
    About_texture.loadFromFile("Texture/gamephoto.jpg");
    ABbackground.setTexture(&About_texture);

    while (MENU.isOpen()) {
        while (const optional event = MENU.pollEvent()) {
            int x = -1;
            if (event->is<Event::Closed>()) {
                MENU.close();
            }

            // KEYBOARD INPUT
            if (const auto* key = event->getIf<Event::KeyReleased>()) {
                if (key->code == Keyboard::Key::Up) {
                    mainMenu.MoveUp();
                }
                if (key->code == Keyboard::Key::Down) {
                    mainMenu.MoveDown();
                }
                if (key->code == Keyboard::Key::Enter) {
                    x = mainMenu.MainMenuPressed();
                }
            }

            // MOUSE HOVERING
            if (const auto* mouse = event->getIf<Event::MouseMoved>()) {
                Vector2f mousePos = MENU.mapPixelToCoords(mouse->position);
                mainMenu.updateMousePosition(mousePos);
            }

            // MOUSE CLICKING
            if (const auto* mouse = event->getIf<Event::MouseButtonPressed>()) {
                if (mouse->button == Mouse::Button::Left) {
                    Vector2f mousePos = MENU.mapPixelToCoords(mouse->position);
                    x = mainMenu.getClickedItem(mousePos);
                }
            }

            // MENU SELECTION
            if (x != -1) {
                RenderWindow ABOUT(VideoMode({1920,1080}), "ABOUT");
                if (x == 0) {
                    MENU.close();
                    StartGame();
                }
                if (x == 1) {

                    Font font;
                    font.openFromFile("Font/Orbitron.ttf");

                    Text aboutText(font);
                    aboutText.setString("Made by Usman, Sami and Arif");
                    aboutText.setCharacterSize(50);
                    aboutText.setFillColor(Color::Red);
                    aboutText.setPosition({960, 540});
                    FloatRect bounds = aboutText.getGlobalBounds();

                    aboutText.move({
                        -bounds.size.x / 2.0f,
                        -bounds.size.y / 2.0f
                    });
                    while (ABOUT.isOpen()) {

                        while (const optional Aevent = ABOUT.pollEvent()) {
                            if (Aevent->is<Event::Closed>()) {
                                ABOUT.close();
                            }

                            if (const auto* Akey = Aevent->getIf<Event::KeyPressed>()) {
                                if (Akey->code == Keyboard::Key::Escape) {
                                    ABOUT.close();
                                }
                            }
                        }

                        ABOUT.clear();
                        ABOUT.draw(aboutText);
                        ABOUT.display();
                    }
                }
                if (x == 2) {
                    MENU.close();
                }
                break;
            }
        }
        MENU.clear();
        mainMenu.draw(MENU);
        MENU.display();
    }
    return 0;
}