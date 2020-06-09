#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<iostream>

int main(){
    sf::RenderWindow window(sf::VideoMode(1366,768),"Example 16 - View Screen basics!");
    window.setFramerateLimit(60);
    sf::Event event;

    sf::Clock clock;
    float dt = 0.f;
    float dtMultiplier = 60.f;

    sf::View defaultView;
    defaultView.setSize(640,480);

    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::White);
    rect.setSize(sf::Vector2f(100.f,100.f));
    sf::Vector2f direction;
    sf::Vector2f currVelocity;
    float acceleration = 1.f;
    float drag = 0.5f;
    float maxSpeed = 15.f;
    rect.setPosition(320,480);

    sf::RectangleShape uiAnything;
    uiAnything.setFillColor(sf::Color::White);
    uiAnything.setSize(sf::Vector2f(200.f,50.f));

    sf::RectangleShape rectAnything;
    rectAnything.setFillColor(sf::Color::Red);
    rectAnything.setSize(sf::Vector2f(100.f,100.f));
    rectAnything.setPosition(320,480);

    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }//end of if
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                window.close();
            }//end of if
        }//end of verification of user wants to close the screen

        dt = clock.restart().asSeconds();
        std::cout << "Time: " << dt << std::endl;

        //Update:
        //Aceleration update:
        direction = sf::Vector2f(0.f,0.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            direction.x = -1;
            if(currVelocity.x > -maxSpeed){
                currVelocity.x += acceleration * direction.x * dt * dtMultiplier;
            }//end of if
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            direction.x = 1;
            if(currVelocity.x < maxSpeed){
                currVelocity.x += acceleration * direction.x * dt * dtMultiplier;
            }//end of if
        }//end of if
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            direction.y = -1;
            if(currVelocity.y > -maxSpeed){
                currVelocity.y += acceleration * direction.y * dt * dtMultiplier;
            }//end of if
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            direction.y = 1;
            if(currVelocity.y < maxSpeed){
                currVelocity.y += acceleration * direction.y * dt * dtMultiplier;
            }//end of if
        }//end of if

        //Drag:
        if(currVelocity.x > 0){
            currVelocity.x -= drag * dt * dtMultiplier;
            if(currVelocity.x < 0.f){
                currVelocity.x = 0.f;
            }//end of if
        } else if(currVelocity.x < 0.f){
            currVelocity.x += drag * dt * dtMultiplier;
            if(currVelocity.x > 0.f){
                currVelocity.x = 0.f;
            }//end of if
        }//end of if
        if(currVelocity.y > 0){
            currVelocity.y -= drag * dt * dtMultiplier;
            if(currVelocity.y < 0.f){
                currVelocity.y = 0.f;
            }//end of if
        } else if(currVelocity.y < 0.f){
            currVelocity.y += drag * dt * dtMultiplier;
            if(currVelocity.y > 0.f){
                currVelocity.y = 0.f;
            }//end of if
        }//end of if

        //Final move:
        rect.move(currVelocity.x * dt * dtMultiplier,currVelocity.y * dt * dtMultiplier);

        defaultView.setCenter(rect.getPosition());

        //Draw:
        window.clear();
        //Draw stuff:
        window.setView(defaultView);
        window.draw(rect);
        window.draw(rectAnything);

        //Draw UI:
        window.setView(window.getDefaultView());
        window.draw(uiAnything);

        //Show:
        window.display();
    }//end of verification of window is open
    return 0;
}//end of main