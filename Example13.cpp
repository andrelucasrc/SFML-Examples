#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<iostream>

int main(){
    sf::RenderWindow window(sf::VideoMode(640,480),"Example 13 - Rotation and origin");
    window.setFramerateLimit(60);
    sf::Event event;

    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::White);
    rect.setSize(sf::Vector2f(100.f,50.f));

    sf::CircleShape circle;
    circle.setFillColor(sf::Color::Green);
    circle.setRadius(10.f);
    circle.setOrigin(10.f,10.f);
    circle.setPosition(window.getSize().x/2,window.getSize().y/2);
    
    sf::RectangleShape rect2;
    rect2.setFillColor(sf::Color::White);
    rect2.setSize(sf::Vector2f(100.f,50.f));
    rect2.setOrigin(50.f,25.f);
    rect2.setPosition(window.getSize().x - 50.f,25.f);

    bool intersectsR1;
    bool intersectsR2;

    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }//end of if
        }//end of while
        //Update:
        //Rect update
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            rect.move(-10.f,0.f);
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            rect.move(10.f,0.f);
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            rect.move(0.f,-10.f);
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            rect.move(0.f,10.f);
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
            rect.rotate(10.f);
        }//end of if

        //Rect2 update
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            rect2.move(-10.f,0.f);
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            rect2.move(10.f,0.f);
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            rect2.move(0.f,-10.f);
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            rect2.move(0.f,10.f);
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)){
            rect2.rotate(10.f);
        }//end of if

        //Boolean update:
        intersectsR1 = circle.getGlobalBounds().intersects(rect.getGlobalBounds());
        intersectsR2 = circle.getGlobalBounds().intersects(rect2.getGlobalBounds());

        //Circle update:
        if(intersectsR1 && intersectsR2){
            circle.setFillColor(sf::Color::Magenta);
        } else if(intersectsR1){
            circle.setFillColor(sf::Color::Red);
        } else if(intersectsR2){
            circle.setFillColor(sf::Color::Yellow);
        } else {
            circle.setFillColor(sf::Color::Green);
        }//end of circle update

        //Draw:
        window.clear();

        //Draw stuff:
        window.draw(rect);
        window.draw(rect2);
        window.draw(circle);

        //Show:
        window.display();
    }//end of while
}//end of main