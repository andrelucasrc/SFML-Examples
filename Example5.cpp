#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(640,400),"Example 05");
    sf::Event event;
    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }//end of if
            //if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
            //    window.close();
            //}//end of if
        }//end of while
        //Update
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            window.close();
        }//end of if
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            window.close();
        }//end of if
        window.clear();
        //Draw
        //Draw stuff
        //Show
        window.display();
    }//end of while
    return 0;
}//end of main