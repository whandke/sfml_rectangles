#include <SFML/Graphics.hpp>
#include <vector>
#include <iomanip>
#include <unistd.h>

#define HEIGHT 600
#define WIDTH 800

class CustomRectangle : public sf::RectangleShape {
public:
    CustomRectangle(float x, float y)
        : sf::RectangleShape(sf::Vector2<float>(x, y)) {
            setOrigin(x/2, y/2);
        }
    
    void setPosition(float x, float y, float r) {
        posX = x;
        posY = y;
        angle = r;
    }

    void setMovement(float x, float y, float r) {
        movX = x;
        movY = y;
        movR = r;
    }

    void setColors(std::vector<sf::Color> c) {
        colors = c;
    }

    void update(float deltaTime) {

        sf::FloatRect bounds = getGlobalBounds();

        if(bounds.top < 0 && movY < 0){
            movY *= -1;
            currentColor++;
        }
        if(bounds.top + bounds.height > HEIGHT && movY > 0){
            movY *= -1;
            currentColor++;
        }
        if(bounds.left < 0 && movX < 0){
            movX *= -1;
            currentColor++;
        }
        if(bounds.left + bounds.width > WIDTH && movX > 0){
            movX *= -1;
            currentColor++;
        }

        currentColor %= colors.size();

        posX += movX * deltaTime;
        posY += movY * deltaTime;
        angle += movR * deltaTime;

        sf::RectangleShape::setPosition(sf::Vector2f(posX, posY));
        sf::RectangleShape::setRotation(angle);
        sf::RectangleShape::setFillColor(colors[currentColor]);
    }
    
private:
    float movX = 0;
    float movY = 0;
    float movR = 0;

    float posX = WIDTH/2;
    float posY = HEIGHT/2;
    float angle = 0;

    std::vector<sf::Color> colors;
    int currentColor = 0;
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::Clock clock;
    std::vector<float> frameTimes;

    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text text("", font);
    text.setCharacterSize(10);
    text.setFillColor(sf::Color(255, 255, 255));
    text.setPosition(sf::Vector2<float>(10, 10));

    std::vector<sf::Color> colors {sf::Color(255, 0, 0), sf::Color(0, 255, 0), sf::Color(0, 0, 255)};

    CustomRectangle shape = CustomRectangle(100, 200);
    shape.setMovement(50.0f, 50.0f, 45.0f);
    shape.setColors(colors);

    CustomRectangle movingRectangle = CustomRectangle(20, 30);
    movingRectangle.setMovement(100, 200, 180);
    movingRectangle.setColors(colors);

    CustomRectangle square = CustomRectangle(50, 50);
    square.setMovement(300, 50, 270);
    square.setColors(colors);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        float fps = 0;
        frameTimes.insert(frameTimes.begin(), deltaTime);
        if(frameTimes.size() >= 100)
            frameTimes.pop_back();
        for(float frameTimes : frameTimes) {
            fps += frameTimes;
        }
        if(frameTimes.size() != 0)
            fps /= frameTimes.size();
            fps = 1.f / fps;

        text.setString("FPS: " + std::to_string(int(fps)));

        shape.update(deltaTime);
        movingRectangle.update(deltaTime);
        square.update(deltaTime);

        window.clear();
        window.draw(shape);
        window.draw(movingRectangle);
        window.draw(text);
        window.draw(square);
        window.display();

        while(clock.getElapsedTime().asMilliseconds() < 16.6f){
            usleep(50);
        }
    }

    return 0;
}