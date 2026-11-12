#include <SFML/Graphics.hpp>
#include "MainMenu.h"
using namespace sf;
int main() {
    //Make a main window
    RenderWindow MENU(VideoMode({960,720}),"Main Menu",Style::Default);
    MainMenu mainMenu(MENU.getSize().x,MENU.getSize().y);
    //set background
    RectangleShape background;
    background.setSize(Vector2f(960,720));
    Texture MainTexture;
    MainTexture.loadFromFile("Texture/gamephoto.jpg");
    background.setTexture(&MainTexture);

    //Photo to the game
    RectangleShape Pbackground;
    Pbackground.setSize(Vector2f(960,720));
    Texture back_texture;
    back_texture.loadFromFile("Texture/gamephoto.jpg");
    Pbackground.setTexture(&back_texture);

    //photo to option
    RectangleShape Obackground;
    Obackground.setSize(Vector2f(960,720));
    Texture Optiontexture;
    Optiontexture.loadFromFile("Texture/gamephoto.jpg");
    Obackground.setTexture(&Optiontexture);

    //About our Projects
    RectangleShape ABbackground;
    ABbackground.setSize(Vector2f(960,720));
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
                RenderWindow Play(VideoMode({960, 720}), "game_name");
                RenderWindow OPTIONS(VideoMode({960, 720}), "OPTIONS");
                RenderWindow ABOUT(VideoMode({960, 720}), "ABOUT");
                if (x == 0) {
                    while (Play.isOpen()) {
                        while (const optional Aevent = Play.pollEvent()) {
                            if (Aevent->is<Event::Closed>()) {
                                Play.close();
                            }
                            if (const auto* Akey = Aevent->getIf<Event::KeyPressed>()) {
                                if (Akey->code == Keyboard::Key::Escape) {
                                    Play.close();
                                }
                            }
                        }
                        OPTIONS.close();
                        ABOUT.close();

                        Play.clear();
                        Play.draw(Pbackground);
                        Play.display();
                    }
                }
                if (x == 1) {
                    while (OPTIONS.isOpen()) {
                        while (const optional Aevent = OPTIONS.pollEvent()) {
                            if (Aevent->is<Event::Closed>()) {
                                OPTIONS.close();
                            }
                            if (const auto* Akey = Aevent->getIf<Event::KeyPressed>()) {
                                if (Akey->code == Keyboard::Key::Escape) {
                                    OPTIONS.close();
                                }
                            }
                        }
                        Play.close();
                        ABOUT.close();
                        OPTIONS.clear();
                        OPTIONS.display();
                    }
                }
                if (x == 2) {
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

                        Play.close();
                        OPTIONS.close();

                        ABOUT.clear();
                        ABOUT.display();
                    }
                }
                if (x == 3) {
                    MENU.close();
                }
                break;
            }
        }
        MENU.clear();
        mainMenu.draw(MENU);
        MENU.display();
    }
}