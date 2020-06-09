#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<vector>

int main(){
    const float WINDOW_WIDTH = 800;
    const float WINDOW_HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),
                            "Example 17 - Colision with Screen and objects");
    window.setFramerateLimit(60);
    sf::Event event;

    sf::Clock clock;
    float dt;
    float gridSize = 50.f;

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(gridSize,gridSize));
    rectangle.setFillColor(sf::Color::Red);
    float maxSpeed = 200.f;
    sf::Vector2f currVelocity;

    sf::RectangleShape wall;
    wall.setSize(sf::Vector2f(gridSize,gridSize));
    wall.setFillColor(sf::Color::Green);
    wall.setPosition(sf::Vector2f(gridSize*5,gridSize*5));
    std::vector<sf::RectangleShape> walls;
    walls.push_back(wall);
    float spawnTimer = 20;

    sf::FloatRect rectBounds;
    sf::FloatRect wallBounds;
    sf::FloatRect nextPos;

    sf::Vector2f mousePosWindow;
    bool exists;
    int index;

    while(window.isOpen()){
        dt = clock.restart().asSeconds();
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }//end of if
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                window.close();
            }//end of if
        }//end of while
        //Update=======================================================================Update
        //===================================Player Update===================================
        rectBounds = rectangle.getGlobalBounds();
        currVelocity.x = 0;
        currVelocity.y = 0;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            currVelocity.x -= maxSpeed * dt;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            currVelocity.x += maxSpeed * dt;
        }if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            currVelocity.y -= maxSpeed * dt;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            currVelocity.y += maxSpeed * dt;
        }//end of if
        //===================================Wall Update=======================================
        mousePosWindow = sf::Vector2f(sf::Mouse::getPosition(window));
        mousePosWindow.x = ((int)mousePosWindow.x /(int)gridSize)*gridSize;
        mousePosWindow.y = ((int)mousePosWindow.y /(int)gridSize)*gridSize;
        if(spawnTimer < 20){
            spawnTimer ++;
        } else if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            spawnTimer = 0;
            exists = false;
            for(int i =0; i<walls.size(); i++){
                if(walls[i].getPosition() == mousePosWindow){
                    exists = true;
                    index = i;
                    i = walls.size();
                }//end of if
            }//end of for
            if(!exists){
                wall.setPosition(mousePosWindow);
                walls.push_back(wall);
            } else {
                walls.erase(walls.begin() + index);
            }//end of else
        }//end of if
        //==========================Player Colision with Walls=================================
        for(auto &wall : walls){
            wallBounds = wall.getGlobalBounds();
            nextPos = rectBounds;

            nextPos.left += currVelocity.x;
            nextPos.top  += currVelocity.y;

            if(nextPos.intersects(wallBounds)){
                //Top Collision
                if(rectBounds.top < wallBounds.top &&
                   rectBounds.top + rectBounds.height < wallBounds.top + wallBounds.height &&
                   rectBounds.left < wallBounds.left + wallBounds.width &&
                   rectBounds.left + rectBounds.width > wallBounds.left){
                    currVelocity.y = 0;
                    rectangle.setPosition(sf::Vector2f(rectBounds.left,wallBounds.top - rectBounds.height));
                }//end of if

                //Bottom Collision
                else if(rectBounds.top > wallBounds.top &&
                   rectBounds.top + rectBounds.height > wallBounds.top + wallBounds.height &&
                   rectBounds.left < wallBounds.left + wallBounds.width &&
                   rectBounds.left + rectBounds.width > wallBounds.left){
                    currVelocity.y = 0;
                    rectangle.setPosition(sf::Vector2f(rectBounds.left,wallBounds.top + wallBounds.height));
                }//end of if

                //Right Collision
                if(rectBounds.left < wallBounds.left &&
                   rectBounds.left + rectBounds.width < wallBounds.left + wallBounds.width &&
                   rectBounds.top < wallBounds.top + wallBounds.height &&
                   rectBounds.top + rectBounds.height > wallBounds.top){
                    currVelocity.x = 0;
                    rectangle.setPosition(sf::Vector2f(wallBounds.left - rectBounds.width,rectBounds.top));
                }//end of if
                
                //Left Collision
                else if(rectBounds.left > wallBounds.left &&
                   rectBounds.left + rectBounds.width > wallBounds.left + wallBounds.width &&
                   rectBounds.top < wallBounds.top + wallBounds.height &&
                   rectBounds.top + rectBounds.height > wallBounds.top){
                    currVelocity.x = 0;
                    rectangle.setPosition(sf::Vector2f(wallBounds.left + rectBounds.width,rectBounds.top));
                }//end of if
            }//end of verification of an intersection with wall
        }//end of loop opmization
        //============================Player Final Move========================================
        rectangle.move(currVelocity.x,currVelocity.y);
        //===========================Player Colision with Screen===============================
        if(rectangle.getPosition().x < 0){
            rectangle.setPosition(0.f,rectangle.getPosition().y);
        }else if(rectangle.getPosition().x + rectangle.getGlobalBounds().width > WINDOW_WIDTH){
            rectangle.setPosition(WINDOW_WIDTH - rectangle.getGlobalBounds().width,rectangle.getPosition().y);
        }//end of if on x pos of screen
        if(rectangle.getPosition().y < 0){
            rectangle.setPosition(rectangle.getPosition().x,0.f);
        }else if(rectangle.getPosition().y + rectangle.getGlobalBounds().height > WINDOW_HEIGHT){
            rectangle.setPosition(rectangle.getPosition().x,WINDOW_HEIGHT - rectangle.getGlobalBounds().height);
        }//end of if on x pos of screen
        //Draw============================================================================Draw
        window.clear();
        //Draw stuff=================================================================Draw stuff
        window.draw(rectangle);
        for(auto &i : walls){
            window.draw(i);
        }//end of for loop CPP 11 optimization
        //Show============================================================================Show
        window.display();
    }//end of while
    return 0;
}//end of main