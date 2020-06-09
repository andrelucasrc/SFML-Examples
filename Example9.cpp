#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(640,480),"Example 09 - Chrono Trigger 2");
    sf::Event event;
    window.setFramerateLimit(60);

    //Player
    sf::Texture chronoTex;
    sf::Sprite chrono;

    if(!chronoTex.loadFromFile("Textures/Chrono.png"))
        throw printf("Não foi possível carregar Chrono.png");

    chrono.setTexture(chronoTex);
    chrono.setScale(sf::Vector2f(0.3f,0.3f));
    chrono.setPosition(sf::Vector2f(20.f,sf::Mouse::getPosition(window).y));

    //Enemies:
    sf::Texture magusTex;
    sf::Sprite magus;

    if(!magusTex.loadFromFile("Textures/Magus.png"))
        throw printf("Não foi possível carregar Magus.png");

    magus.setTexture(magusTex);
    magus.setScale(sf::Vector2f(0.3f,0.3f));
    magus.setPosition(sf::Vector2f(window.getSize().x-magus.getGlobalBounds().width,0));

    std::vector<sf::Sprite> maguses;
    int spawnTimer = 30;

    //HP bar:
    int hp = 10;
    sf::RectangleShape hpBar;
    hpBar.setSize(sf::Vector2f(hp*2.f,5.f));
    hpBar.setPosition(sf::Vector2f(window.getSize().x/3 - 100, 30.f));
    hpBar.setFillColor(sf::Color::Red);

    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(hp <= 0){
                window.close();
            }//end of if
            if(event.type == sf::Event::Closed){
                window.close();
            }//end of if
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                window.close();
            }//end of if
        }//end of while
        //Update:
        //Player:
        chrono.setPosition(sf::Vector2f(20.f,sf::Mouse::getPosition(window).y));
        if(sf::Mouse::getPosition(window).y <= 0){
            chrono.setPosition(sf::Vector2f(chrono.getPosition().x,0));
        }//end of if
        if(sf::Mouse::getPosition(window).y >= window.getSize().y - chrono.getGlobalBounds().height){
            chrono.setPosition(sf::Vector2f(chrono.getPosition().x,
                               window.getSize().y - chrono.getGlobalBounds().height));
        }//end of if

        //Enemies::
        if(spawnTimer<=30){
            spawnTimer++;
        } else {
            spawnTimer = 0;
            magus.setPosition(magus.getPosition().x,rand()%int(window.getSize().y-magus.getGlobalBounds().height));
            maguses.push_back(magus);
        }//end of if

        for(int i = 0; i < maguses.size(); i++){
            maguses[i].move(-5.f,0.f);
            if(maguses[i].getPosition().x <= -maguses[i].getGlobalBounds().width){
                maguses.erase(maguses.begin() + i);
            } else if(maguses[i].getGlobalBounds().intersects(chrono.getGlobalBounds())){
                maguses.erase(maguses.begin() + i);
                hp--;
            }//end of else
        }//end of for
        
        //Hp Bar:
        hpBar.setScale(sf::Vector2f(hp*2.f,5.f));

        //Draw:
        window.clear();

        //Draw Stuff:
        window.draw(chrono);
        for(int i = 0; i < maguses.size(); i++){
            window.draw(maguses[i]);
        }//end of for
        window.draw(hpBar);

        //Display:
        window.display();

    }//end of while
}//end of main