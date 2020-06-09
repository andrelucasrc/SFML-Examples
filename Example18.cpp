#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include<vector>
#include<sstream>

int main(){
    //Window size const init:
    const float WINDOW_WIDTH = 800;
    const float WINDOW_HEIGHT = 600;
    
    //Window init:
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"Example 18 - Tileset, grid and view");
    sf::Event event;
    sf::View view;
    view.setSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    view.setCenter(window.getSize().x/2,window.getSize().y/2);

    //Important variables init:
    float gridSizeF = 50.f;
    unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
    float dt;
    float dtMultiplier = 60.f;
    sf::Clock clock;

    //Just a random rectangle init:
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(gridSizeF,gridSizeF));
    shape.setFillColor(sf::Color::White);
    shape.setPosition(sf::Vector2f(2*gridSizeF, 2*gridSizeF));

    //Just a tile selector init:
    sf::RectangleShape tileSelector;
    tileSelector.setSize(sf::Vector2f(gridSizeF,gridSizeF));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineThickness(1.f);
    tileSelector.setOutlineColor(sf::Color::Green);

    //Vectors of position init:
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2u mousePosGrid;


    //Text on screen init:
    sf::Font font;
    if(!font.loadFromFile("Fonts/VCR_OSD_MONO_1.001.ttf")){
        throw("Error to load font VCR_OSD_MONO_1.001.ttf");
    }//end of if
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(12);
    std::stringstream string;

    //Just a Complicated Grid Init:
    const int mapSize = 100;
    std::vector<std::vector<sf::RectangleShape>> tileMap;
    sf::RectangleShape defaultTile;
    defaultTile.setFillColor(sf::Color::White);
    defaultTile.setOutlineThickness(1.f);
    defaultTile.setOutlineColor(sf::Color::Black);
    defaultTile.setSize(sf::Vector2f(gridSizeF,gridSizeF));

    tileMap.resize(mapSize, std::vector<sf::RectangleShape>());
    
    for(int i = 0; i < mapSize; i++){
        tileMap[i].resize(mapSize, sf::RectangleShape());
        for(int j = 0; j < mapSize; j++){
            tileMap[i][j] = sf::RectangleShape(defaultTile);
            tileMap[i][j].setPosition(sf::Vector2f(i * gridSizeF, j * gridSizeF));
        }//end of for j
    }//end of for i

    std::vector<std::vector<sf::RectangleShape>> map;
    sf::RectangleShape tile;
    tile.setFillColor(sf::Color::Yellow);
    tile.setOutlineThickness(1.f);
    tile.setOutlineColor(sf::Color::Black);
    tile.setSize(sf::Vector2f(gridSizeF,gridSizeF));

    map.resize(mapSize, std::vector<sf::RectangleShape>());
    
    for(int i = 0; i < mapSize; i++){
        map[i].resize(mapSize, sf::RectangleShape());
        for(int j = 0; j < mapSize; j++){
            map[i][j] = sf::RectangleShape(tile);
            map[i][j].setPosition(sf::Vector2f(i * gridSizeF, j * gridSizeF));
        }//end of for j
    }//end of for i

    //Complicated grid variavles draw control init:
    int fromX;
    int toX;
    int fromY;
    int toY;

    int fromXMap;
    int toXMap;
    int fromYMap;
    int toYMap;

    
    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }//end of if
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                window.close();
            }//end of if
        }//end of while
        dt = clock.restart().asSeconds();
        //Update:
        //Vectors Update:
        mousePosScreen = sf::Mouse::getPosition();
        mousePosWindow = sf::Mouse::getPosition(window);
        window.setView(view);
        mousePosView = window.mapPixelToCoords(mousePosWindow);
        if(mousePosView.x >= 0)
            mousePosGrid.x = mousePosView.x / gridSizeU;
        if(mousePosView.y >= 0)
            mousePosGrid.y = mousePosView.y / gridSizeU;
        window.setView(window.getDefaultView());

        //Variables grid control update section:
        fromX = mousePosGrid.x - 1;
        toX = mousePosGrid.x + 2;
        fromY = mousePosGrid.y - 1;
        toY = mousePosGrid.y + 2;
        
        if(fromX < 0){
            fromX = 0;
        }else if(fromX >= mapSize){
            fromX = mapSize -1;
        }//end of if

        if(toX < 0){
            toX = 0;
        }else if(toX >= mapSize){
            toX = mapSize -1;
        }//end of if

        if(fromY < 0){
            fromY = 0;
        }else if(fromY >= mapSize){
            fromY = mapSize -1;
        }//end of if

        if(toY < 0){
            toY = 0;
        }else if(toY >= mapSize){
            toY = mapSize -1;
        }//end of if

        fromXMap = view.getCenter().x/gridSizeF - 9;
        toXMap = view.getCenter().x/gridSizeF + 9;
        fromYMap = view.getCenter().y/gridSizeF - 7;
        toYMap = view.getCenter().y/gridSizeF + 7;
        
        if(fromXMap < 0){
            fromXMap = 0;
        }else if(fromXMap >= mapSize){
            fromXMap = mapSize -1;
        }//end of if

        if(toXMap < 0){
            toXMap = 0;
        }else if(toXMap >= mapSize){
            toXMap = mapSize -1;
        }//end of if

        if(fromYMap < 0){
            fromYMap = 0;
        }else if(fromYMap >= mapSize){
            fromYMap = mapSize -1;
        }//end of if

        if(toYMap < 0){
            toYMap = 0;
        }else if(toYMap >= mapSize){
            toYMap = mapSize -1;
        }//end of if       

        //String on screen update:
        string.str("");

        string << "MousePos on screen: " << mousePosScreen.x << "," << mousePosScreen.y << "\n" <<
                  "MousePos on window: " << mousePosWindow.x << "," << mousePosWindow.y << "\n" <<
                  "MousePos on view: " << mousePosView.x << "," << mousePosView.y << "\n" <<
                  "MousePos on grid: " << mousePosGrid.x << "," << mousePosGrid.y << "\n";
        
        text.setString(string.str());

        //Tile Selector Update
        tileSelector.setPosition(sf::Vector2f(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF));

        //View update:
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            view.move(-10 * dt * dtMultiplier,0);
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            view.move(10 * dt * dtMultiplier,0);
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            view.move(0,-10 * dt * dtMultiplier);
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            view.move(0,10 * dt * dtMultiplier);
        }//end of if

        //Draw:
        window.clear();
        window.setView(view);
        //Draw stuff:
        window.draw(shape);

        for(int i = fromXMap; i < toXMap; i++){
            for(int j = fromYMap; j < toYMap; j++){
                window.draw(map[i][j]);
            }//end of for j
        }//end of for i
    
        for(int i = fromX; i < toX; i++){
            for(int j = fromY; j < toY; j++){
                window.draw(tileMap[i][j]);
            }//end of for j
        }//end of for i

        window.draw(tileSelector);
    

        //Draw UI stuff:
        window.setView(window.getDefaultView());
        window.draw(text);

        //Show stuff:
        window.display();
    }//end of while
    return 0;
}//end of main