#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

int main()
{
    const int w_width = 640;
    const int w_height = 480;

    sf::CircleShape circle(50); // draw a circle with a radius of 50;
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(300.0f, 300.0f);

    sf::Vector2f circleMoveSpeed(10.0f, 3.0f);

    float gravitation = 0.2f;
    float damping = 0.7f; // Adjust damping factor for desired effect

    sf::RenderWindow window(sf::VideoMode(w_width, w_height), "Welcome to SFML!!");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Check collision with the x-axis boundary
        if (circle.getPosition().x + (circle.getRadius() * 2) >= w_width || circle.getPosition().x <= 0)
        {
            circleMoveSpeed.x *= -1.0f; // Reverse the direction for x axis
            circleMoveSpeed.x *= damping; // Apply damping

            // Ensure the circle stays within the window
            if (circle.getPosition().x < 0)
            {
                circle.setPosition(0, circle.getPosition().y);
            }
            else if (circle.getPosition().x + (circle.getRadius() * 2) > w_width)
            {
                circle.setPosition(w_width - (circle.getRadius() * 2), circle.getPosition().y);
            }
        }
        // Check collision with the y-axis boundary
        else if (circle.getPosition().y + (circle.getRadius() * 2) >= w_height || circle.getPosition().y <= 0)
        {
            circleMoveSpeed.y *= -1.0f; // Reverse the direction for y axis
            circleMoveSpeed.y *= damping; // Apply damping

            // Ensure the circle stays within the window
            if (circle.getPosition().y < 0)
            {
                circle.setPosition(circle.getPosition().x, 0);
            }
            else if (circle.getPosition().y + (circle.getRadius() * 2) > w_height)
            {
                circle.setPosition(circle.getPosition().x, w_height - (circle.getRadius() * 2));
            }
        }

        // Simulate gravitation
        if (circle.getPosition().y + (circle.getRadius() * 2) < w_height)
        {
            circleMoveSpeed.y += gravitation;
        }

        // Update circle position
        circle.setPosition(circle.getPosition().x + circleMoveSpeed.x, circle.getPosition().y + circleMoveSpeed.y);

        // Clear the window with black color
        window.clear(sf::Color::Black);

        // Draw everything here...
        window.draw(circle);

        // End the current frame
        window.display();
    }

    return 0;
}
