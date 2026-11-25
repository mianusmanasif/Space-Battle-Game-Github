#include "MainMenu.h"

int MainMenuSelected = 0;
int GameOverOptionsSelected=0;
Font font;
Text mainMenu[Max_main_menu] = {
    Text(font), Text(font), Text(font), Text(font)
};
Text GameOverOptions[2]={Text(font),Text(font)};

// Background Texture and Sprite
Texture menuBgTexture;
Sprite menuBackground(menuBgTexture);


//Initialize MainMenu
void initializeMainMenu(float width, float height) {

    font.openFromFile("Font/8514sys.ttf");
    // Load the background image & scale it to fill the window
    if (menuBgTexture.loadFromFile("Texture/space1.JPG")) {
        menuBackground.setTexture(menuBgTexture, true);
        menuBackground.setScale({
            width / menuBgTexture.getSize().x,
            height / menuBgTexture.getSize().y
            });
    }

    //play
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(Color::White);
    mainMenu[0].setString("Play");
    mainMenu[0].setCharacterSize(70);
    mainMenu[0].setPosition({width/2 - 70,400});

    // about
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(Color::White);
    mainMenu[1].setString("About");
    mainMenu[1].setCharacterSize(70);
    mainMenu[1].setPosition({ width / 2 - 70,500});

    //exit
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(Color::White);
    mainMenu[2].setString("Exit");
    mainMenu[2].setCharacterSize(70);
    mainMenu[2].setPosition({ width / 2 - 70,600});
}

//Initialize Options to send to Main Menu or to Play Again
void initializeGameOver(float width,float height) {
    font.openFromFile("Font/Orbitron.ttf");
    //Play Again
    GameOverOptions[0].setFont(font);
    GameOverOptions[0].setFillColor(Color::White);
    GameOverOptions[0].setString("Play Again");
    GameOverOptions[0].setCharacterSize(70);
    GameOverOptions[0].setPosition({300,550});
    //Exit to Menu
    GameOverOptions[1].setFont(font);
    GameOverOptions[1].setFillColor(Color::White);
    GameOverOptions[1].setString("Exit to Menu");
    GameOverOptions[1].setCharacterSize(70);
    GameOverOptions[1].setPosition({275,650});


}

//Draw MainMenu
void draw(RenderWindow& window) {
    window.draw(menuBackground);
    for (int i=0;i<Max_main_menu;++i) {
        window.draw(mainMenu[i]);
    }
}

//Draw GameOverOptions
void drawGameOverOptions(RenderWindow& window) {
    for (int i=0;i<2;++i) {
        window.draw(GameOverOptions[i]);
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
void GameOverMoveUp() {
    if (GameOverOptionsSelected > 0) {
        GameOverOptions[GameOverOptionsSelected].setFillColor(Color::White);
        GameOverOptionsSelected--;
        GameOverOptions[GameOverOptionsSelected].setFillColor(Color::Blue);
    }
}

void GameOverMoveDown() {
    if (GameOverOptionsSelected < 1) {
        GameOverOptions[GameOverOptionsSelected].setFillColor(Color::White);
        GameOverOptionsSelected++;
        GameOverOptions[GameOverOptionsSelected].setFillColor(Color::Blue);
    }
}

//Mouse hover
void updateMousePosition(Vector2f mousePos) {
    for (int i = 0; i < 3; i++) {
        if (mainMenu[i].getGlobalBounds().contains(mousePos)) {
            MainMenuSelected = i;
            GameOverOptionsSelected=i;
            mainMenu[i].setFillColor(Color::Blue);
        }
        else {
            mainMenu[i].setFillColor(Color::White);
        }
    }

}

void updateGameOverMousePosition(Vector2f mousePos) {
    for (int i = 0; i < 2; i++) {
        if (GameOverOptions[i].getGlobalBounds().contains(mousePos)) {
            GameOverOptionsSelected = i;
            GameOverOptions[i].setFillColor(Color::Blue);
        }
        else {
            GameOverOptions[i].setFillColor(Color::White);
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
int getClickedGameOverOption(Vector2f mousePos) {
    for (int i = 0; i < 2; i++) {
        if (GameOverOptions[i].getGlobalBounds().contains(mousePos)) {
            GameOverOptionsSelected = i;
            return i;
        }
    }
    return -1;
}


//Get selected item
int MainMenuPressed() {
    return MainMenuSelected;
}

int GameOverOptionsPressed() {
    return GameOverOptionsSelected;
}