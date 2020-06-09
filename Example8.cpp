#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<vector>
#include<iostream>
#include<ctime>

int main(){
    sf::RenderWindow window(sf::VideoMode(640,480),"Example 08 - Squares X Circles");
    window.setFramerateLimit(60);
    sf::Event event;

    //Player:
    sf::CircleShape player;
    player.setRadius(50.f);
    player.setFillColor(sf::Color::Blue);
    player.setPosition(sf::Vector2f(window.getSize().x/2-player.getRadius(),
                       window.getSize().y - player.getRadius()*2 - 20));
    sf::Vector2f playerPosition = player.getPosition();


    //Projectile:
    sf::CircleShape projectile;
    std::vector<sf::CircleShape> projectiles;
    projectile.setPointCount(3);
    projectile.setRadius(10.f);
    projectile.setFillColor(sf::Color::Red);
    projectile.setOutlineThickness(2.f);
    projectile.setOutlineColor(sf::Color::White);
    int blastTime = 0;

    //Enemy:
    sf::RectangleShape enemy;
    std::vector<sf::RectangleShape> enemies;
    enemy.setSize(sf::Vector2f(50.f,50.f));
    enemy.setFillColor(sf::Color::Magenta);
    enemy.setOutlineThickness(2.f);
    enemy.setOutlineColor(sf::Color::White);
    int spawnTime = 0;

    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }//end of if
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                window.close();
            }//end of if
        }//end of while
        //Update:
        //Player:
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            if(playerPosition.x>=10){
                player.move(-5.f,0.f);
            }//end of if
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            if(playerPosition.x<=window.getSize().x-player.getRadius()*2-10){
                player.move(5.f,0.f);
            }//end of if
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            if(playerPosition.y>=10){
                player.move(0.f,-5.f);
            }//end of if
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            if(playerPosition.y<=window.getSize().y-player.getRadius()*2-10){
                player.move(0.f,5.f);
            }//end of if
        }//end of if
        playerPosition = player.getPosition();
        if(blastTime < 20){
            blastTime++;
        }//end of if

        //Projectile:
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&blastTime>=20){
            projectile.setPosition(sf::Vector2f(playerPosition.x + player.getRadius()/2,
                                                playerPosition.y + player.getRadius()/2));
            projectiles.push_back(projectile);
            blastTime = 0;
        }//end of if
        for(int i = 0; i < projectiles.size(); i++){
            projectiles[i].move(0.f,-5.f);
            if(projectiles[i].getPosition().y <=-projectile.getRadius()){
                projectiles.erase(projectiles.begin() + i);
            }//end of if
        }//end of for

        //Enemies:
        if(spawnTime < 20){
            spawnTime++;
        }//end of if
        if(spawnTime >= 20){
            enemy.setPosition(rand()%int(window.getSize().x-enemy.getSize().x),0.f);
            enemies.push_back(enemy);
            spawnTime = 0;
        }//end of if
        for(int i = 0; i < enemies.size(); i++){
            enemies[i].move(0.f,5.f);
            if(enemies[i].getPosition().y <=0 || 
               enemies[i].getPosition().y >=window.getSize().y){
                enemies.erase(enemies.begin() + i);
            }//end of if
        }//end of for

        //Colision:
        for(int i = 0; i < enemies.size(); i++){
            for(int j = 0; j < projectiles.size(); j++){
                if(enemies[i].getGlobalBounds().intersects(projectiles[j].getGlobalBounds())){
                    enemies.erase(enemies.begin()+i);
                    projectiles.erase(projectiles.begin()+j);
                    j = projectiles.size();
                }//end of if
            }//end of for
        }//end of for

        //Draw:
        window.clear();
        //Draw stuff:
        window.draw(player);
        for(int i = 0; i < enemies.size(); i++){
            window.draw(enemies[i]);
        }//end of for
        for(int i = 0; i < projectiles.size(); i++){
            window.draw(projectiles[i]);
        }//end of for

        //Show:
        window.display();
    }//end of while
}//end of main