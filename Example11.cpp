#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(640,480),"Example 11 - Fonts on SFML");
    window.setFramerateLimit(60);
    sf::Event event;
    
    sf::Font font;
    font.loadFromFile("Fonts/comic-sans-ms-4.ttf");
    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setCharacterSize(24.f);
    text.setString("SFML text is working on this computer! BEATCH!");
    text.setPosition(10.f,window.getSize().y/2);
    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }//end of if
            if(event.type == sf::Event::KeyPressed &&  event.key.code == sf::Keyboard::Escape){
                window.close();
            }//end of if
        }//end of while
        //Update:
        if(text.getPosition().x <= window.getSize().x+text.getScale().x){
            text.move(2.f,0.f);
        } else {
            text.setPosition(-text.getScale().x,window.getSize().y/2);
        }//end of else


        //Draw:
        window.clear();
        //Draw stuff:
        window.draw(text);

        //Show window:
        window.display();
    }//end of while
    return 0;
}//end of main