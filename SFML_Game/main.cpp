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
	sf::Text shapeName;
	std::string m_name;
	sf::RectangleShape shape;
	sf::Vector2f position; // has X,Y
	sf::Vector2f moveSpeed; // has sX, sY

	float damping;

public:
	PhysicObjectRectangle(std::string name, float posX, float posY, float sX, float sY, int r, int g, int b, float w, float h, sf::Font& font)
		: m_name(name), position(posX, posY), moveSpeed(sX, sY), damping(0.98f)
	{
		shape.setSize(sf::Vector2f(w, h));
		shape.setPosition(position);
		shape.setFillColor(sf::Color(r, g, b));

		shapeName.setFont(font);
		shapeName.setString(name);
		shapeName.setPosition(shape.getPosition() + (shape.getSize() / 2.f));

	}

	void update(sf::RenderWindow& window)  override
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
		// re draw the name each update
		// Center the text within the rectangle
		sf::Vector2f textCenter = shape.getPosition() + 0.5f * shape.getSize();
		shapeName.setPosition(textCenter - sf::Vector2f(0.5f * shapeName.getGlobalBounds().width, 0.7f * shapeName.getGlobalBounds().height));

	}


	void draw(sf::RenderWindow& window) const override
	{
		window.draw(shape);
		window.draw(shapeName);
	}
};

// derived class <Circle>
class PhysicObjectCircle :public PhysicObjectBase
{
	sf::Text shapeName;
	std::string m_name;
	sf::CircleShape shape;
	sf::Vector2f position; // has X,Y
	sf::Vector2f moveSpeed; // has sX, sY
	float damping;

public:
	PhysicObjectCircle(std::string name, float posX, float posY, float sX, float sY, int r, int g, int b, float radius, sf::Font& font)
		: m_name(name), position(posX, posY), moveSpeed(sX, sY), damping(0.98f)
	{
		shape.setRadius(radius);
		shape.setPosition(position);
		shape.setFillColor(sf::Color(r, g, b));

		shapeName.setFont(font);
		shapeName.setString(m_name);
		shapeName.setPosition(shape.getPosition() + sf::Vector2f(shape.getRadius(), shape.getRadius()));
	}

	void update(sf::RenderWindow& window) override
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

		// Center the text within the rectangle

		// defining the offset by getting the whole width of text and divide it in half for x axis
		// and doing also for y axis
		sf::Vector2f textOffset((shapeName.getGlobalBounds().width * 0.5f), (shapeName.getGlobalBounds().height * 0.7f));

		// then setting the posiition based on shape fposition and added it with the radius then substrating it with the offset
		shapeName.setPosition((shape.getPosition().x + shape.getRadius()) - textOffset.x, (shape.getPosition().y + shape.getRadius())-textOffset.y);

	}

	void draw(sf::RenderWindow& window) const override
	{
		window.draw(shape);
		// draw name to the screen
		window.draw(shapeName);
	}
};


int main()
{
	sf::Font font;


	if (!font.loadFromFile("resources/fonts/Sendcat.ttf"))
	{
		std::cerr << "Fail to load font! \n";
		return -1;
	}



	int w_width = 0;
	int w_height = 0;



	std::ifstream fileInput("config.txt");

	// error stream file handling
	if (!fileInput.is_open())
	{
		std::cerr << "Error opening Config file \n";
		return -1;
	}

	// Container of each shapes on config file using smart pointer for auto garbage collecting
	std::vector<std::unique_ptr<PhysicObjectBase>> physicObjects;

	// define keyword
	std::string keyword;

	while (fileInput >> keyword) {
		if (keyword == "Window")
		{
			fileInput >> w_width >> w_height;
		}
		else if (keyword == "Rectangle")
		{
			std::string name;
			int r, g, b;
			float x, y, sx, sy, w, h;

			fileInput >> name >> x >> y >> sx >> sy >> r >> g >> b >> w >> h;

			physicObjects.push_back(std::make_unique<PhysicObjectRectangle>(name, x, y, sx, sy, r, g, b, w, h, font));
		}
		else if (keyword == "Circle")
		{
			std::string name;
			int r, g, b;
			float radius, x, y, sx, sy;
			fileInput >> name >> x >> y >> sx >> sy >> r >> g >> b >> radius;
			physicObjects.push_back(std::make_unique<PhysicObjectCircle>(name, x, y, sx, sy, r, g, b, radius, font));
		}
	}






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

		// render each Shape
		for (const auto& obj : physicObjects)
		{
			obj->update(window);
			obj->draw(window);
		}


		// End the current frame
		window.display();
	}

	return 0;
}
