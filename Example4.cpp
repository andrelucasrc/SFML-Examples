#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(640,400),"Example 04",sf::Style::Default);
    sf::Event event;

    sf::CircleShape triangle(50.f);
    triangle.setPointCount(3);
    triangle.setFillColor(sf::Color::Red);
    triangle.setOutlineThickness(5.f);
    triangle.setOutlineColor(sf::Color::Blue);

    sf::Vertex line[] ={sf::Vertex(sf::Vector2f(50.f,200.f)),sf::Vertex(sf::Vector2f(100.f,300.f))};

    sf::ConvexShape convex;
    convex.setPosition(200.f,300.f);
    convex.setPointCount(6);

    convex.setPoint(0,sf::Vector2f(0.f,0.f));
    convex.setPoint(1,sf::Vector2f(50.f,50.f));
    convex.setPoint(2,sf::Vector2f(50.f,100.f));
    convex.setPoint(3,sf::Vector2f(100.f,50.f));
    convex.setPoint(4,sf::Vector2f(100.f,100.f));
    convex.setPoint(5,sf::Vector2f(200.f,50.f));

    convex.setFillColor(sf::Color::Green);

    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed){
                window.close();
            }//end of if
        }//end of while
        //update

        window.clear();
        //draw
        window.draw(triangle);
        window.draw(line, 2, sf::Lines);
        window.draw(convex);

        //show
        window.display();
    }//end of while
    return 0;
}//end of main