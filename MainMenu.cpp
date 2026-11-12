#include "MainMenu.h"

MainMenu::MainMenu(float width, float height)
    : mainMenu{sf::Text(font), sf::Text(font),
               sf::Text(font), sf::Text(font)}
{
    font.openFromFile("fonts/8514sys.ttf");

    //play
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(Color::White);
    mainMenu[0].setString("Play");
    mainMenu[0].setCharacterSize(70);
    mainMenu[0].setPosition({400,200});
    //options
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(Color::White);
    mainMenu[1].setString("Options");
    mainMenu[1].setCharacterSize(70);
    mainMenu[1].setPosition({400,300});
    //about
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(Color::White);
    mainMenu[2].setString("About");
    mainMenu[2].setCharacterSize(70);
    mainMenu[2].setPosition({400,400});
    //exit
    mainMenu[3].setFont(font);
    mainMenu[3].setFillColor(Color::White);
    mainMenu[3].setString("Exit");
    mainMenu[3].setCharacterSize(70);
    mainMenu[3].setPosition({400,500});
    MainMenuSelected=-1;
}
MainMenu::~MainMenu(){

}
//Draw MainMenu
void MainMenu::draw(RenderWindow& window) {
    for (int i=0;i<Max_main_menu;++i) {
        window.draw(mainMenu[i]);
    }
}
//Move up
void MainMenu::MoveUp() {
    if (MainMenuSelected-1>=0) {
        mainMenu[MainMenuSelected].setFillColor(Color::White);
        MainMenuSelected--;
        if (MainMenuSelected==-1) {
            MainMenuSelected=2;
        }
        mainMenu[MainMenuSelected].setFillColor(Color::Blue);
    }
}
//Move down
void MainMenu::MoveDown() {
    if (MainMenuSelected+1<=Max_main_menu) {
        mainMenu[MainMenuSelected].setFillColor(Color::White);
        MainMenuSelected++;
        if (MainMenuSelected==4) {
            MainMenuSelected=0;
        }
        mainMenu[MainMenuSelected].setFillColor(Color::Blue);
    }
}

//mouse hover
void MainMenu::updateMousePosition(Vector2f mousePos) {
    for (int i = 0; i < Max_main_menu; i++) {
        if (mainMenu[i].getGlobalBounds().contains(mousePos)) {
            MainMenuSelected = i;
            mainMenu[i].setFillColor(Color::Blue);
        }
        else {
            mainMenu[i].setFillColor(Color::White);
        }
    }
}

//mouse click
int MainMenu::getClickedItem(Vector2f mousePos) {
    for (int i = 0; i < Max_main_menu; i++) {
        if (mainMenu[i].getGlobalBounds().contains(mousePos)) {
            MainMenuSelected = i;
            return i;
        }
    }
    return -1;
}