#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Network.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(1920,1080),"SFML Examples",sf::Style::Default);
    sf::Event event;
    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }//end of if
        }//end of while
        //Update

        //Draw
        window.display();
        //Draw Stuff
        
        //Clear
        window.clear();
    }//end of while
    return 0;
}//end of main