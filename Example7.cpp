#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(640,480),"Example 07 - A simple game");
    window.setFramerateLimit(60);
    sf::Event event;
    sf::CircleShape hoop;
    hoop.setRadius(40.f);
    hoop.setFillColor(sf::Color::Red);
    hoop.setOutlineThickness(3.f);
    hoop.setOutlineColor(sf::Color::Black);
    hoop.setPosition(sf::Vector2f(window.getSize().x/2.f,10.f));
    int direction = 0;
    sf::CircleShape ball;
    ball.setRadius(20.f);
    ball.setFillColor(sf::Color::Blue);
    ball.setOutlineThickness(1.5f);
    ball.setOutlineColor(sf::Color::Black);
    ball.setPosition(sf::Vector2f(window.getSize().x/2,(window.getSize().y/3.f)*2.f));
    bool isShot = false;
    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }//end of if
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                window.close();
            }//end of if
        }//end of while condition to close window
        //Update hoop block:
        // If and else to not let the hoop bypass the screen in the left or in the right
        if(hoop.getPosition().x + hoop.getRadius()*2 >= window.getSize().x){
            direction = 1;                                                  
        } else if(hoop.getPosition().x <= 0){ 
            direction = 0;
        }//end of else 
        //According in the direction of the variable, the hoop will move to the left or right
        if(direction == 0){
            hoop.move(sf::Vector2f(5.f,0.f));
        } else {
            hoop.move(sf::Vector2f(-5.f,0.f));
        }//end of if
        //end of hoop update block
        //Ball update block:
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            isShot = true;
        }//end of if
        if(isShot){
            if(ball.getGlobalBounds().intersects(hoop.getGlobalBounds()) || ball.getPosition().y <= 0){
                ball.setPosition(window.getSize().x/2,(window.getSize().y/3.f)*2.f);
                isShot = false;
            } else {
                ball.move(sf::Vector2f(0.f,-5.f));
            }//end of if
        } else {
            ball.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x,ball.getPosition().y));
        }//end of if
        //end of ball update block
        window.clear(sf::Color::White);
        window.draw(hoop);
        window.draw(ball);
        window.display();
    }//end of while
    return 0;
}//end of main