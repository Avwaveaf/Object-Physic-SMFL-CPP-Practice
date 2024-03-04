#include <iostream>
#include <SFML/Graphics.hpp>

#include <fstream>

template <typename T>
class PhysicsObject
{
private:
    T shape;
    sf::Vector2f position;
    sf::Vector2f moveSpeed;
    float gravitation;
    float damping;

public:
    PhysicsObject(float posX, float posY) : position(posX, posY), moveSpeed(10.0f, 3.0f), gravitation(0.2f), damping(0.98f)
    {
        // define a shape for Rectangle
        sf::Vector2f rSize(posX, posY);
        shape.setSize(rSize);
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Red);
    }

    PhysicsObject(int radius, float posX, float posY) : position(posX, posY), moveSpeed(10.0f, 3.0f), gravitation(0.2f), damping(0.7f)
    {
       // Construct a shape for Circle
        shape.setRadius(radius);
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Red);
    }

    void update(sf::RenderWindow& window)
    {
        // Check collision with the x-axis boundary
        if (position.x + shape.getGlobalBounds().width >= window.getSize().x || position.x <= 0)
        {
            moveSpeed.x *= -1.0f; // Reverse the direction for x-axis
            moveSpeed.x *= damping; // Apply damping

            // Ensure the object stays within the window
            if (position.x < 0)
            {
                position.x = 0;
            }
            else if (position.x + shape.getGlobalBounds().width > window.getSize().x)
            {
                position.x = window.getSize().x - shape.getGlobalBounds().width;
            }
        }

        // Check collision with the y-axis boundary
        else if (position.y + shape.getGlobalBounds().height >= window.getSize().y || position.y <= 0)
        {
            moveSpeed.y *= -1.0f; // Reverse the direction for y-axis
            moveSpeed.y *= damping; // Apply damping

            // Ensure the object stays within the window
            if (position.y < 0)
            {
                position.y = 0;
            }
            else if (position.y + shape.getGlobalBounds().height > window.getSize().y)
            {
                position.y = window.getSize().y - shape.getGlobalBounds().height;
            }
        }

        // Simulate gravitation
        if (position.y + shape.getGlobalBounds().height < window.getSize().y)
        {
            moveSpeed.y += gravitation;
        }

        // Update object position
        position.x += moveSpeed.x;
        position.y += moveSpeed.y;

        shape.setPosition(position);
    }

    void draw(sf::RenderWindow& window) const
    {
        window.draw(shape);
    }
};

int main()
{
    const int w_width = 640;
    const int w_height = 480;

    PhysicsObject<sf::RectangleShape> physicCircle(150.0f, 150.0f);
    PhysicsObject<sf::CircleShape> myCircle(75, 100.0f, 250.0f);



    
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




        // Clear the window with black color
        window.clear(sf::Color::Black);

        // Draw everything here...
        physicCircle.draw(window);
        physicCircle.update(window);

        myCircle.draw(window);
        myCircle.update(window);

        // End the current frame
        window.display();
    }

    return 0;
}
