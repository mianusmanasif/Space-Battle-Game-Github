#include "MainMenu.h"

int MainMenuSelected = 0;
Font font;
Text mainMenu[Max_main_menu] = {
    Text(font), Text(font), Text(font), Text(font)
};

//Initialize MainMenu
void initializeMainMenu(float width, float height) {

    font.openFromFile("Font/8514sys.ttf");

    //play
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(Color::White);
    mainMenu[0].setString("Play");
    mainMenu[0].setCharacterSize(70);
    mainMenu[0].setPosition({850,400});

    //about
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(Color::White);
    mainMenu[1].setString("About");
    mainMenu[1].setCharacterSize(70);
    mainMenu[1].setPosition({850,500});

    //exit
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(Color::White);
    mainMenu[2].setString("Exit");
    mainMenu[2].setCharacterSize(70);
    mainMenu[2].setPosition({850,600});
}

//Draw MainMenu
void draw(RenderWindow& window) {
    for (int i=0;i<Max_main_menu;++i) {
        window.draw(mainMenu[i]);
    }
}

//Move up
void MoveUp() {
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
void MoveDown() {
    if (MainMenuSelected+1<3) {
        mainMenu[MainMenuSelected].setFillColor(Color::White);
        MainMenuSelected++;

        if (MainMenuSelected==3) {
            MainMenuSelected=0;
        }

        mainMenu[MainMenuSelected].setFillColor(Color::Blue);
    }
}

//Mouse hover
void updateMousePosition(Vector2f mousePos) {
    for (int i = 0; i < 3; i++) {
        if (mainMenu[i].getGlobalBounds().contains(mousePos)) {
            MainMenuSelected = i;
            mainMenu[i].setFillColor(Color::Blue);
        }
        else {
            mainMenu[i].setFillColor(Color::White);
        }
    }
}

//Mouse click
int getClickedItem(Vector2f mousePos) {
    for (int i = 0; i < 3; i++) {
        if (mainMenu[i].getGlobalBounds().contains(mousePos)) {
            MainMenuSelected = i;
            return i;
        }
    }
    return -1;
}

//Get selected item
int MainMenuPressed() {
    return MainMenuSelected;
}