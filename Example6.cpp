#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>

void update(sf::RectangleShape &rect,sf::RenderWindow &window);
void draw(sf::RenderWindow &window,sf::RectangleShape &rect);

int main(){
    sf::RenderWindow window(sf::VideoMode(640,480),"Example 06 - Square Swag");
    window.setFramerateLimit(60);
    sf::RectangleShape rect(sf::Vector2f(100.f,100.f));
    rect.setFillColor(sf::Color::Red);
    rect.setPosition(sf::Vector2f(window.getSize().x/2,window.getSize().y/2));
    sf::Event event;
    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }//end of if
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                window.close();
            }//end of if
        }//end of while
        update(rect,window);
        draw(window,rect);
    }//end of while
    return 0;
}//end of main

void update(sf::RectangleShape &rect,sf::RenderWindow &window){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)&&rect.getPosition().x >= 0){
        rect.move(-5.f,0.f);
    }//end of if
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)&&
       rect.getPosition().x + rect.getSize().x < window.getSize().x){
        rect.move(5.f,0.f);
    }//end of if
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)&&rect.getPosition().y >= 0){
        rect.move(0.f,-5.f);
    }//end of if
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)&&
       rect.getPosition().y + rect.getSize().y < window.getSize().y){
        rect.move(0.f,5.f);
    }//end of if
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        rect.setFillColor(sf::Color::Blue);
    } else {
        rect.setFillColor(sf::Color::Red);
    }//end of else
}//end of update function

void draw(sf::RenderWindow &window,sf::RectangleShape &rect){
    window.clear(sf::Color::White);
    window.draw(rect);
    window.display();
}//end of draw function