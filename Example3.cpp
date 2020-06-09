#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(640,400),"Example 03",sf::Style::Default);
    window.setFramerateLimit(60);

    sf::CircleShape circle(50.f);
    sf::RectangleShape rect(sf::Vector2f(50.f,100.f));
    rect.setPosition(400,200);
    circle.setPosition(100,200);
    rect.setFillColor(sf::Color(255,100,200,200));
    circle.setFillColor(sf::Color(100,255,200,100));
    
    sf::Event event;

    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }//end of if
        }//end of while
        //Update
        circle.move(0.3f,0.1f);
        circle.rotate(2.f);
        rect.move(-0.1f,-0.3f);
        rect.rotate(-5.f);

        //Draw
        window.clear();

        //Draw everthing
        window.draw(circle);
        window.draw(rect);

        //Show
        window.display();
    }//end of while
    return 0;
}//end of main