#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<math.h>
#include<cstdlib>
#include<iostream>
#include<vector>

class Bullets{
public:
    sf::Sprite shape;

    Bullets(sf::Texture *texture){
        this->shape.setTexture(*texture);
    }//end of bullets constructor

    ~Bullets(){}
};

class Player{
public:
    int HP;
    int maxHP;
    sf::Sprite shape;
    std::vector<Bullets> bullets;

    Player(sf::Texture *texture,int HP){
        this->HP = HP;
        this->maxHP = HP;
        this->shape.setTexture(*texture);
    }//end of player constructor

    ~Player(){}

};

class Enemy{
public:
    int HP;
    int maxHP;
    sf::Sprite shape;

    Enemy(sf::Texture *texture,int HP){
        this->HP = HP;
        this->maxHP = HP;
        this->shape.setTexture(*texture);
    }//end of enemy constructor

    ~Enemy(){}

};

int main(){
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(640,480),"Example 15 - A simple game with framerate independence");
    window.setFramerateLimit(200);
    sf::Event event;

    sf::Clock clock;
    float dt = 0.f;
    float dtMultiplier = 60.f;

    //Player init:
    sf::Texture playerTex;
    if(!playerTex.loadFromFile("Textures/Spaceship.png")){
        throw("Failed to open Spaceship.png texture!");
    }//Failed to open texture
    Player player(&playerTex,10);

    //Bullet init:
    sf::Texture bulletTex;
    if(!bulletTex.loadFromFile("Textures/Bullet.png")){
        throw("Failed to open Bullet.png texture!");
    }//Failed to load bullet texture
    Bullets bullet(&bulletTex);
    float bulletTimer = 20;
    sf::Vector2f bulletPosStart;

    //Enemy init:
    sf::Texture enemyTex;
    if(!enemyTex.loadFromFile("Textures/Enemy.png")){
        throw("Failed to open Enemy.png texture!");
    }//Failed to load enemy texture
    Enemy enemy(&enemyTex,rand()%3 + 1);
    std::vector<Enemy> enemies;
    float mobSpawnTimer = 30;

    //Fonts init:
    sf::Font defaultFont;
    if(!defaultFont.loadFromFile("Fonts/VCR_OSD_MONO_1.001.ttf")){
        throw("Couldn't load pixelart.tff font");
    }//end of could not load font

    //Texts init:
    sf::Text playerHP;
    playerHP.setFont(defaultFont);
    playerHP.setFillColor(sf::Color::Green);
    playerHP.setCharacterSize(10);
    sf::Text enemyHP;
    enemyHP.setFont(defaultFont);
    enemyHP.setFillColor(sf::Color::Red);
    enemyHP.setCharacterSize(10);
    sf::Text score;
    score.setFont(defaultFont);
    score.setFillColor(sf::Color::White);
    score.setCharacterSize(20);
    score.setPosition((window.getSize().x + score.getGlobalBounds().width)/2,10.f);
    sf::Text gameOver;
    gameOver.setFont(defaultFont);
    gameOver.setFillColor(sf::Color::Yellow);
    gameOver.setOutlineThickness(3.f);
    gameOver.setOutlineColor(sf::Color::Red);
    gameOver.setCharacterSize(40);
    gameOver.setString("You died beatch!");
    gameOver.setPosition(100.f,window.getSize().y/2);

    //Game Score init:
    int gameScore = 0;

    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }//end of if
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                window.close();
            }//end of if
        }//end of while
        dt = clock.restart().asSeconds();
        if(player.HP > 0){
        //Update:
        //Player Update:
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            player.shape.move(-7.f * dt * dtMultiplier,0.f);
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            player.shape.move(7.f * dt * dtMultiplier,0.f);
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            player.shape.move(0.f,-7.f * dt * dtMultiplier);
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            player.shape.move(0.f,7.f * dt * dtMultiplier);
        }//end of if
        if(bulletTimer < 15){
            bulletTimer += 1 * dt * dtMultiplier;
        } else if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            bulletPosStart = sf::Vector2f(player.shape.getPosition().x + player.shape.getGlobalBounds().width,
                                          player.shape.getPosition().y + player.shape.getGlobalBounds().height/2 - 
                                          bullet.shape.getGlobalBounds().height/2);
            bullet.shape.setPosition(bulletPosStart);
            player.bullets.push_back(bullet);
            bulletTimer = 0; //Bullet Timer reset
        }//end of if

        //Player out of window:
        if(player.shape.getPosition().x <= 0){
            player.shape.setPosition(0.f,player.shape.getPosition().y);
        }//end of if
        if(player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width){
            player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width,player.shape.getPosition().y);
        }//end of if
        if(player.shape.getPosition().y <= 0){
            player.shape.setPosition(player.shape.getPosition().x,0.f);
        }//end of if
        if(player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height){
            player.shape.setPosition(player.shape.getPosition().x,window.getSize().y - player.shape.getGlobalBounds().height);
        }//end of if

        //Player UI Update:
        playerHP.setString(std::to_string(player.HP) + "/" + std::to_string(player.maxHP));
        playerHP.setPosition(player.shape.getPosition());

        //Enemie update:
        if(mobSpawnTimer < 30){
            mobSpawnTimer += 1 * dt * dtMultiplier;
        } else {
            enemy.shape.setPosition(window.getSize().x,
                                    rand()%int(window.getSize().y - enemy.shape.getGlobalBounds().height));
            enemy.HP = rand()%3 + 1;
            enemy.maxHP = enemy.HP;
            enemies.push_back(enemy);
            mobSpawnTimer = 0;
        }//end of else
        for(int i = 0; i < enemies.size(); i++){
            enemies[i].shape.move(-5.f * dt * dtMultiplier,0.f);
            if(enemies[i].shape.getPosition().x <= -enemies[i].shape.getGlobalBounds().height){
                enemies.erase(enemies.begin() + i);
            }//end of if
        }//end of enemies movement

        //Bullet update:
        for(int i = 0; i < player.bullets.size(); i++){
            player.bullets[i].shape.move(7.f * dt * dtMultiplier,0.f);
            if(player.bullets[i].shape.getPosition().x >= window.getSize().x){
                player.bullets.erase(player.bullets.begin()+i);
            }//end of if
        }//end of bullet movement

        //Colision check-up:
        for(int i = 0; i < player.bullets.size(); i++){
            for(int j = 0; j < enemies.size(); j++){
                if(player.bullets[i].shape.getGlobalBounds().intersects(enemies[j].shape.getGlobalBounds())){
                    if(enemies[j].HP <= 1){
                        gameScore += 10*enemies[j].maxHP;
                        player.bullets.erase(player.bullets.begin() + i);
                        enemies.erase(enemies.begin() + j);
                        j = enemies.size(); //Break up internal loop
                    } else {
                        enemies[j].HP--;
                        player.bullets.erase(player.bullets.begin() + i);
                        j = enemies.size(); //Break up internal loop
                    }//end of else
                }//end of bullet colision with enemies
            }//end of colision internal check-up
        }//end of colision check-up

        //Player colision with enemies:
        for(int i = 0; i < enemies.size(); i++){
            if(player.shape.getGlobalBounds().intersects(enemies[i].shape.getGlobalBounds())){
                gameScore-=10*enemies[i].HP;
                enemies.erase(enemies.begin() + i);
                player.HP--;
            }//end of enemy colision verification
        }//end of player colision with enemies

        score.setString("Score: " + std::to_string(gameScore));
        }//end of player has HP to play

        //Draw:
        window.clear();
        //Draw stuff:
        //Player Draw
        window.draw(player.shape);
        //Enemies Draw:
        for(int i = 0; i < enemies.size(); i++){
            enemyHP.setString(std::to_string(enemies[i].HP) + "/" + std::to_string(enemies[i].maxHP));
            enemyHP.setPosition(enemies[i].shape.getPosition());
            window.draw(enemyHP);
            window.draw(enemies[i].shape);
        }//end of for drawing enemies
        //Bullets Draw:
        for(int i = 0; i < player.bullets.size(); i++){
            window.draw(player.bullets[i].shape);
        }//end of for drawing player bullets
        //UI draw:
        window.draw(playerHP);
        window.draw(score);
        if(player.HP <= 0){
            window.draw(gameOver);
        }//end of if


        //Show:
        window.display();
        
    }//end of if
    return 0;
}//end of main