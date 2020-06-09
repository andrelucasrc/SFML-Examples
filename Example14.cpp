#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(640,480),"Example 14 - Framerate independence and the new moviment style");
    window.setFramerateLimit(200);
    sf::Event event;

    float dt;
    sf::Clock clock;
    float multiplier = 60.f;

    sf::CircleShape circle;
    circle.setRadius(25.f);
    circle.setFillColor(sf::Color::White);
    circle.setPosition(window.getSize().x/2,window.getSize().y/2);

    sf::RectangleShape swaggy;
    swaggy.setSize(sf::Vector2f(50.f,50.f));
    swaggy.setFillColor(sf::Color::White);
    swaggy.setPosition(window.getSize().x/2 + 50,window.getSize().y/2 + 50);

    //Movement vector and variables:
    float maxSpeed = 10.f;
    float drag = 0.5f;
    float acceleration = 1;
    sf::Vector2f currVelocity;
    sf::Vector2f direction;

    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }//end of window close by the X
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                window.close();
            }//end of window closed by escape key
        }//end of while verifying if the window has to be closed
        dt = clock.restart().asSeconds();
        //Update:
        //Circle update
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            circle.move(-10.f * dt * multiplier,0.f);
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            circle.move(10.f * dt * multiplier,0.f);
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            circle.move(0.f,-10.f * dt * multiplier);
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            circle.move(0.f,10.f * dt * multiplier);
        }//end of if

        //Rectangle update:
        //Acceleration:
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            direction.x = -1;
            if(currVelocity.x > -maxSpeed){
                currVelocity.x += direction.x * acceleration * dt * multiplier;
            }//end of if direction not surprass the max speed
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            direction.x = 1;
            if(currVelocity.x < maxSpeed){
                currVelocity.x += direction.x * acceleration * dt * multiplier;
            }//end of if direction not surprass the max speed
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            direction.y = -1;
            if(currVelocity.y > -maxSpeed){
                currVelocity.y += direction.y * acceleration * dt * multiplier;
            }//end of if direction not surprass the max speed
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            direction.y = 1;
            if(currVelocity.y < maxSpeed){
                currVelocity.y += direction.y * acceleration * dt * multiplier;
            }//end of if direction not surprass the max speed
        }//end of if

        //Drag:
        if(currVelocity.x > 0.f){
            currVelocity.x -= drag * dt * multiplier;
            if(currVelocity.x < 0.f){
                currVelocity.x = 0.f;
            }//end of if
        } else if(currVelocity.x < 0.f){
            currVelocity.x += drag * dt * multiplier;
            if(currVelocity.x > 0.f){
                currVelocity.x = 0.f;
            }//end of if
        }//end of stop verification on x
        if(currVelocity.y > 0.f){
            currVelocity.y -= drag * dt * multiplier;
            if(currVelocity.y < 0.f){
                currVelocity.y = 0.f;
            }//end of if
        } else if(currVelocity.y < 0.f){
            currVelocity.y += drag * dt * multiplier;
            if(currVelocity.y > 0.f){
                currVelocity.y = 0.f;
            }//end of if
        }//end of stop verification on y
        
        //Final Move:
        swaggy.move(currVelocity.x * dt * multiplier,currVelocity.y * dt * multiplier);


        //Draw:
        std::cout<<"Time = " << dt << "\n";
        window.clear();
        //Draw stuff:
        window.draw(circle);
        window.draw(swaggy);

        //Show
        window.display();
    }//end of while window still open
    return 0;
}//end of main