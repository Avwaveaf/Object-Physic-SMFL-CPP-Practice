#include <iostream>
#include <SFML/Graphics.hpp>

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

    sf::CircleShape circle(50); // draw a circle with a radius of 50;
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(300.0f, 300.0f);

    PhysicsObject<sf::RectangleShape> physicCircle(150.0f, 150.0f);
    PhysicsObject<sf::CircleShape> myCircle(75, 100.0f, 250.0f);

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
        physicCircle.draw(window);
        physicCircle.update(window);

        myCircle.draw(window);
        myCircle.update(window);

        // End the current frame
        window.display();
    }

    return 0;
}
