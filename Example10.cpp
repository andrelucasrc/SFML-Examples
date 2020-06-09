#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include<cstdlib>
#include<math.h>
#include<vector>

//LENGTH OF VECTOR: |V| = sqrt(V.x^2 + V.y^2)
//VECTOR NORMALIZE: U = V / |V|

class Bullet{
    public:
        sf::CircleShape shape;
        float maxSpeed;
        sf::Vector2f currSpeed;

        Bullet(float radius = 5.f)
            : currSpeed(0.f,0.f), maxSpeed(15.f){
            this->shape.setRadius(radius);
            this->shape.setFillColor(sf::Color::White);
        }

};

int main(){
    sf::RenderWindow window(sf::VideoMode(800,600),"Example 10 - 360 degress shooter");
    window.setFramerateLimit(60);
    sf::Event event;

    //Player:
    sf::CircleShape player;
    player.setRadius(25.f);
    player.setFillColor(sf::Color::White);

    //Bullet:
    Bullet bullet;
    std::vector<Bullet> bullets;

    //Enemies:
    sf::RectangleShape enemy;
    enemy.setFillColor(sf::Color(200,200,200));
    enemy.setSize(sf::Vector2f(40.f,40.f));
    std::vector<sf::RectangleShape> enemies;
    int spawnTimer = 20;
    
    //Vector:
    sf::Vector2f playerCenter;
    sf::Vector2f mousePosWindow;
    sf::Vector2f aimDir;
    sf::Vector2f aimDirNormalize;

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
        //Player update:
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            if(player.getPosition().x>0){
                player.move(-5.f,0.f);
            }//end of if
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            if(player.getPosition().x<window.getSize().x-player.getRadius()*2){
                player.move(5.f,0.f);
            }//end of if
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            if(player.getPosition().y>0){
                player.move(0.f,-5.f);
            }//end of if
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            if(player.getPosition().y<window.getSize().y-player.getRadius()*2){
                player.move(0.f,5.f);
            }//end of if
        }//end of if

        //Vectors update:
        playerCenter = sf::Vector2f(player.getPosition().x + player.getRadius(),
                                    player.getPosition().y + player.getRadius());
        mousePosWindow = sf::Vector2f(sf::Mouse::getPosition(window));
        aimDir = sf::Vector2f(playerCenter - mousePosWindow);
        aimDirNormalize = sf::Vector2f(aimDir.x / sqrt(pow(aimDir.x,2) + pow(aimDir.y,2)),
                                       aimDir.y / sqrt(pow(aimDir.x,2) + pow(aimDir.y,2)));

        //Bullets update:
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            bullet.currSpeed = -bullet.maxSpeed*aimDirNormalize;
            bullet.shape.setPosition(playerCenter);
            bullets.push_back(bullet);
        }//end of if
        for(int i = 0;i<bullets.size(); i++){
            bullets[i].shape.move(bullets[i].currSpeed);
            if(bullets[i].shape.getPosition().x <= -bullets[i].shape.getRadius() ||
               bullets[i].shape.getPosition().x > window.getSize().x+bullets[i].shape.getRadius() ||
               bullets[i].shape.getPosition().y <= -bullets[i].shape.getRadius() ||
               bullets[i].shape.getPosition().y > window.getSize().y+bullets[i].shape.getRadius() ){
                   bullets.erase(bullets.begin()+i);
            }else{
                for(int j = 0; j < enemies.size(); j++){
                    if(bullets[i].shape.getGlobalBounds().intersects(enemies[j].getGlobalBounds())){
                        enemies.erase(enemies.begin() + j);
                        bullets.erase(bullets.begin() + i);
                        j = enemies.size();
                    }//end of if
                }//end of for
            }//end of else
        }//end of for

        //Enemies update:
        if(spawnTimer < 20){
            spawnTimer++;
        } else {
            enemy.setPosition(sf::Vector2f(rand()%int(window.getSize().x-enemy.getSize().x),
                                           rand()%int(window.getSize().y-enemy.getSize().y)));
            enemies.push_back(enemy);
            spawnTimer = 0;
        }//end of if
        
        //Draw:
        window.clear();
        //Draw Stuff:
        window.draw(player);
        for(int i = 0; i<bullets.size(); i++){
            window.draw(bullets[i].shape);
        }//end of for
        for(int i = 0; i<enemies.size(); i++){
            window.draw(enemies[i]);
        }//end of for

        //Show window:
        window.display();
    }//end of while
    return 0;
}//end of main