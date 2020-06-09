#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Network.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(640,400),"SFML Examples",sf::Style::Default);
    window.setFramerateLimit(60);
    sf::Event event;
    sf::CircleShape shape(50.f);
    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }//end of if
        }//end of while
        //Update
        shape.move(0.5f,0.1f);

        //Draw
        window.clear(sf::Color::Red);
        //Draw everthing
        window.draw(shape);

        window.display();
    }//end of while
    return 0;
}//end of main