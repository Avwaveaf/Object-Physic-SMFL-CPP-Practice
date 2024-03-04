#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>


// Global variable for gravitation
float gravitation = 0.2f;

// Implement polymorphism and dynamic memory allocation

// base class
class PhysicObjectBase
{
public:
    virtual ~PhysicObjectBase() = default;
    virtual void update(sf::RenderWindow& window) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
};

// derived class <Rectangle>
class PhysicObjectRectangle :public PhysicObjectBase
{
    sf::RectangleShape shape;
    sf::Vector2f position; // has X,Y
    sf::Vector2f moveSpeed; // has sX, sY
    float damping;

public:
    PhysicObjectRectangle(float posX, float posY, float sX, float sY) 
        : position(posX, posY), moveSpeed(sX, sY), damping(0.98f)
    {
        shape.setSize(sf::Vector2f(150.0f, 150.0f));
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Red);
    }

    void update(sf::RenderWindow& window)
    {
        // Check collision with the x-axis boundary
        if (position.x + shape.getSize().x >= window.getSize().x || position.x <= 0)
        {
            moveSpeed.x *= -1.0f; // Reverse the direction for x-axis
            moveSpeed.x *= damping; // Apply damping

            // Ensure the object stays within the window
            // make sure shape not touching border lefft
            if (position.x < 0)
            {
                position.x = 0;
            }
            // make sure shape not touching border lefft
            else if (position.x + shape.getSize().x > window.getSize().x)
            {
                position.x = window.getSize().x - shape.getSize().x;
            }
        }

        // Check collision with the y-axis boundary
        else if (position.y + shape.getSize().y >= window.getSize().y || position.y <= 0)
        {
            moveSpeed.y *= -1.0f; // Reverse the direction for y-axis
            moveSpeed.y *= damping; // Apply damping

            // Ensure the object stays within the window
            if (position.y < 0)
            {
                position.y = 0;
            }
            else if (position.y + shape.getSize().y > window.getSize().y)
            {
                position.y = window.getSize().y - shape.getGlobalBounds().height;
            }
        }

        // Simulate gravitation
        if (position.y + shape.getSize().y < window.getSize().y)
        {
            moveSpeed.y += gravitation;
        }

        // Update object position
        position.x += moveSpeed.x;
        position.y += moveSpeed.y;

        shape.setPosition(position);
    }

};

// derived class <Circle>
class PhysicObjectCircle :public PhysicObjectBase
{
    sf::CircleShape shape;
    sf::Vector2f position; // has X,Y
    sf::Vector2f moveSpeed; // has sX, sY
    float damping;

public:
    PhysicObjectCircle(float posX, float posY,float sX, float sY,  int radius)
        : position(posX, posY), moveSpeed(sX, sY), damping(0.98f)
    {
        shape.setRadius(radius);
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Red);
    }

    void update(sf::RenderWindow& window)
    {
        // Check collision with the x-axis boundary
        if (position.x + (shape.getRadius() * 2) >= window.getSize().x || position.x <= 0)
        {
            moveSpeed.x *= -1.0f; // Reverse the direction for x-axis
            moveSpeed.x *= damping; // Apply damping

            // Ensure the object stays within the window
            // make sure shape not touching border lefft
            if (position.x < 0)
            {
                position.x = 0;
            }
            // make sure shape not touching border lefft
            else if (position.x + (shape.getRadius() * 2) > window.getSize().x)
            {
                position.x = window.getSize().x - (shape.getRadius() * 2);
            }
        }

        // Check collision with the y-axis boundary
        else if (position.y + (shape.getRadius() * 2) >= window.getSize().y || position.y <= 0)
        {
            moveSpeed.y *= -1.0f; // Reverse the direction for y-axis
            moveSpeed.y *= damping; // Apply damping

            // Ensure the object stays within the window
            if (position.y < 0)
            {
                position.y = 0;
            }
            else if (position.y + (shape.getRadius() * 2) > window.getSize().y)
            {
                position.y = window.getSize().y - shape.getGlobalBounds().height;
            }
        }

        // Simulate gravitation
        if (position.y + (shape.getRadius() * 2) < window.getSize().y)
        {
            moveSpeed.y += gravitation;
        }

        // Update object position
        position.x += moveSpeed.x;
        position.y += moveSpeed.y;

        shape.setPosition(position);
    }

};

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
    int w_width;
    int w_height;

    std::ifstream fileInput("config.txt");

    // error stream file handling
    if (!fileInput.is_open())
    {
        std::cerr << "Error opening Config file \n";
        return -1;
    }

    // define keyword
    std::string keyword;

    while (fileInput >> keyword) {
        if (keyword == "Window")
        {
            fileInput >> w_width >> w_height;
        }
    }

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
