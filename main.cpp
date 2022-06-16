#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <time.h>
#include <iostream>
#include <vector>

#define WINDOWX 400
#define WINDOWY 533

using namespace sf;

struct point
{
    int x, y, hspeed;
};

// Entity Class inherited from Sprite
class Entity : public Sprite
{
public:
    bool alive;
    bool escape;
    float vspeed;
    Vector2f position;

public:
    // Constructor
    Entity(Texture &texture, float speed)
    {
        setTexture(texture);
        vspeed = speed;
        alive = true;
        escape = false;
    }

    virtual ~Entity() {} // Destructor
};

class Shuriken : public Entity
{
public:
    Shuriken(Texture &texture, float speed) : Entity(texture, speed) {}

public:
    void animate()
    {
        move(0, vspeed);
        // Check if entity went out of screen
        if(getGlobalBounds().top > WINDOWY)
        {
            escape = true;
        }
        position = getPosition();
    }
};

class Pizza : public Entity
{
public:
    Pizza(Texture &texture, float speed) : Entity(texture, speed) {}

public:
    void animate()
    {
        move(0, vspeed);
        // Check if entity went out of screen
        if(getGlobalBounds().top > WINDOWY)
        {
            escape = true;
            alive = false;
        }
        position = getPosition();
    }
};


int main()
{
    srand(time(nullptr)); // Random seed

    RenderWindow window(VideoMode(WINDOWX, WINDOWY), "TURTLE JUMP");
    window.setFramerateLimit(60);

    // Load Font
    sf::Font myfont;
    if(!myfont.loadFromFile("Font/arial.ttf")) std::cerr << "Could not load font." << std::endl;

    // Score Text
    int score = 0;
    sf::Text score_text;
    score_text.setString("Score: " + std::to_string(score));
    score_text.setStyle(sf::Text::Bold);
    score_text.setFillColor(sf::Color::Black);
    score_text.setOutlineColor(sf::Color::Green);
    score_text.setOutlineThickness(0.5);
    score_text.setFont(myfont);
    score_text.setCharacterSize(25);
    score_text.setPosition(0 +5, 0); // +5 for better visibility

    // Load textures
    Texture t1,t2,t3;
    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/platform.png");
    t3.loadFromFile("images/turtle.png");
    Texture t4, t5;
    t4.loadFromFile("images/shuriken.png");
    t5.loadFromFile("images/pizza.png");

    Sprite sBackground(t1), sPlatform(t2), sCharacter(t3); // Create sprites
    float scale = 0.5;
    sCharacter.setScale(scale, scale);

    // Create shurikens and pizzas
    int total = 1;
    std::vector<Shuriken> shurikens;
    std::vector<Pizza> pizzas;
    for(int i = 0; i < total; i++)
    {
        Shuriken shuriken(t4, 2);
        shuriken.position.x = (rand()%400) - shuriken.getGlobalBounds().width; // Set random X coordinate
        shuriken.setPosition(shuriken.position.x, 0-shuriken.getGlobalBounds().height);
        shurikens.emplace_back(shuriken);

        Pizza pizza(t5, 2);
        pizza.position.x = (rand()%400) - pizza.getGlobalBounds().width;
        pizza.setPosition(pizza.position.x, 0-pizza.getGlobalBounds().height);
        pizzas.emplace_back(pizza);
    }


    int platformnum = 12; // number of platforms at a time on screen
    point platforms[platformnum];

    // Create platforms
    for (int i=0;i<platformnum;i++)
    {
        platforms[i].x = (rand()%400) - 34; // 34 so that at least half of the platform will always be on screen
        platforms[i].y = (rand()%533) - 7;
        platforms[i].hspeed = 1.0;
    }

    int x=100,y=100,h=200; // x,y are intial coordinates of character. h is a constant.
    float dy=0; // dy is gravity variable.

    bool flip = false; // Current direction status of the character texture

    bool gameover = false; // Status of game
    Texture gameover_t;
    gameover_t.loadFromFile("images/gameover.png");
    Sprite sgameover;
    sgameover.setTexture(gameover_t);
    sgameover.setPosition(0, 100);

    // Start menu
    // Start Menu
    sf::Text title_text;
    title_text.setString("\t   TURTLE \n     \tJUMP");
    title_text.setStyle(sf::Text::Bold);
    title_text.setFillColor(sf::Color::Green);
    title_text.setOutlineColor(sf::Color::Blue);
    title_text.setOutlineThickness(2);
    title_text.setFont(myfont);
    title_text.setCharacterSize(50);
    title_text.setPosition(0, 50);

    bool startmenu = true;
    // Start Button
    sf::Text start_button;
    start_button.setString("START");
    start_button.setStyle(sf::Text::Bold | sf::Text::Underlined);
    start_button.setFillColor(sf::Color::Cyan);
    start_button.setOutlineColor(sf::Color::Red);
    start_button.setOutlineThickness(2);
    start_button.setFont(myfont);
    start_button.setCharacterSize(50);
    start_button.setPosition(WINDOWX/4 - start_button.getGlobalBounds().width/2 +10, 350);
    sf::Text start_help;
    start_help.setString("[Press ENTER]");
    start_help.setStyle(sf::Text::Bold);
    start_help.setFillColor(sf::Color::Cyan);
    start_help.setOutlineColor(sf::Color::Red);
    start_help.setOutlineThickness(2);
    start_help.setFont(myfont);
    start_help.setCharacterSize(25);
    start_help.setPosition(WINDOWX/4 - start_help.getGlobalBounds().width/2 +10, 420);
    // Quit Button
    sf::Text quit_button;
    quit_button.setString("QUIT");
    quit_button.setStyle(sf::Text::Bold | sf::Text::Underlined);
    quit_button.setFillColor(sf::Color::Cyan);
    quit_button.setOutlineColor(sf::Color::Red);
    quit_button.setOutlineThickness(2);
    quit_button.setFont(myfont);
    quit_button.setCharacterSize(50);
    quit_button.setPosition(WINDOWX * (0.75) - quit_button.getGlobalBounds().width/2, 350);
    sf::Text quit_help;
    quit_help.setString("[Press Q]");
    quit_help.setStyle(sf::Text::Bold);
    quit_help.setFillColor(sf::Color::Cyan);
    quit_help.setOutlineColor(sf::Color::Red);
    quit_help.setOutlineThickness(2);
    quit_help.setFont(myfont);
    quit_help.setCharacterSize(25);
    quit_help.setPosition(WINDOWX * (0.75) - quit_help.getGlobalBounds().width/2, 420);

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed) window.close();

            if(startmenu)
            {
                if(e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Enter) startmenu = false;
            }

            // Quit
            if(e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Q) return 0;
        }

        // Start game
        if(startmenu==true)
        {
            window.draw(title_text);
            window.draw(start_button);
            window.draw(start_help);
            window.draw(quit_button);
            window.draw(quit_help);
            // display window
            window.display();
        }

        if(startmenu) continue; // Dont start game when in start menu

        // Restart Game
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            gameover = false;
            // Reset game
            score = 0;
            for (int i=0;i<platformnum;i++)
            {
                platforms[i].x = (rand()%400) - 34; // 34 so that at least half of the platform will always be on screen
                platforms[i].y = rand()%533;
            }
            x = 100;
            y = 100;
            dy = 0;

            shurikens.clear();
            pizzas.clear();
            for(int i = 0; i < total; i++)
            {
                Shuriken shuriken(t4, 2);
                shuriken.position.x = (rand()%400) - shuriken.getGlobalBounds().width;
                shuriken.setPosition(shuriken.position.x, 0-shuriken.getGlobalBounds().height);
                shurikens.emplace_back(shuriken);

                Pizza pizza(t5, 2);
                pizza.position.x = (rand()%400) - pizza.getGlobalBounds().width;
                pizza.setPosition(pizza.position.x, 0-pizza.getGlobalBounds().height);
                pizzas.emplace_back(pizza);
            }
        }

        if(gameover) continue; // Stop game when gameover

        // Move character
        FloatRect bounds = sCharacter.getGlobalBounds(); // Get bounds of character
        if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) && bounds.left + bounds.width/2 < 400.0)
        {
            // Change direction of character texture
            sCharacter.setScale(-scale, scale);
            flip = true;
            x+=3; // Horizontal Speed of the character
        }
        if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && bounds.left + bounds.width/2 > 0.0)
        {
            // Change direction of character texture
            sCharacter.setScale(scale, scale);
            flip = false;
            x-=3;
        }

        dy+=0.2; // Increase the vertical speed by 0.2
        y+=dy; // Increase the position by dy

        if (y >= 500.0) // When character hits the bottom
        {
            gameover = true;
        }

        if (y < h) // When character jumps above a certain height
        {
//            std::cout << "Current y = " << y << "\t\tCurrent dy = " << dy << '\n';
            for (int i=0; i<platformnum; i++)
            {
                y=h; // Set character y-coordinate to certain height
                platforms[i].y -= dy; // Move platform downwards
                if (platforms[i].y > 533) // if platform leaves screen through the bottom
                {
                    platforms[i].y = 0; // Reset it to the top
                    platforms[i].x = (rand()%400) - 34; // Give it a random x coordinate

                    // Commented out to because score system was changed
//                    score += 1; // Add 1 point for every platform crossed
                }
            }
            for(int i = 0; i < total; i++)
            {
                shurikens[i].position.y -= dy;
                shurikens[i].setPosition(shurikens[i].position.x, shurikens[i].position.y);

                pizzas[i].position.y -= dy;
                pizzas[i].setPosition(pizzas[i].position.x, pizzas[i].position.y);
            }
        }

        // Collision Detection
        for (int i=0; i<platformnum; i++) // Iterate through current platforms
        {
            // Collision of character with platform
            if ((x+50>platforms[i].x) && (x+20<platforms[i].x+68) // if character sides are colliding with platform length
                    && (y+70>platforms[i].y) && (y+70<platforms[i].y+14) // if character bottom is colliding with thickness of platform
                    && (dy>0)) // if character is moving downwards
            {
                dy = -10; // Give upward speed
            }
        }

        // Platform bouncing off of sides
        for (int i=0; i<platformnum; i++) // Iterate through current platforms
        {
            platforms[i].x += platforms[i].hspeed; // Move platform
            if(platforms[i].x + sPlatform.getGlobalBounds().width > WINDOWX) // Bounce off right side
            {
                platforms[i].hspeed = -std::abs(platforms[i].hspeed);
            }
            else if(platforms[i].x < 0) // Bounce off left side
            {
                platforms[i].hspeed = std::abs(platforms[i].hspeed);
            }
        }

        // Set position of character
        if(flip) sCharacter.setPosition(x+bounds.width,y);
        else sCharacter.setPosition(x,y);

        // Move shurikens and pizzas
        for(int i = 0; i < total; i++)
        {
            shurikens[i].animate();
            pizzas[i].animate();
        }
        // Collision detection for shurikens and pizzas
        for(int i = 0; i < total; i++)
        {
            FloatRect charbounds = sCharacter.getGlobalBounds();
            if(shurikens[i].getGlobalBounds().intersects(charbounds)) // If shuriken collides with character
            {
                gameover = true;
                shurikens[i].alive = false;
            }
            if(pizzas[i].getGlobalBounds().intersects(charbounds)) // if pizza collides with character
            {
                score += 10;
                pizzas[i].alive = false;
            }

            // Remove entities that are collided or out of screen
            if(shurikens[i].escape == true)
            {
                shurikens[i].position.x = (rand()%400) - shurikens[i].getGlobalBounds().width;
                shurikens[i].position.y = 0;
                shurikens[i].setPosition(shurikens[i].position.x, 0-shurikens[i].getGlobalBounds().height);
                shurikens[i].escape = false;
            }
            if(pizzas[i].alive == false || pizzas[i].escape == true)
            {
                pizzas[i].position.x = (rand()%400) - pizzas[i].getGlobalBounds().width;
                pizzas[i].position.y = 0;
                pizzas[i].setPosition(pizzas[i].position.x, 0-pizzas[i].getGlobalBounds().height);
                pizzas[i].alive = true;
                pizzas[i].escape = false;
            }
        }

        // Draw stuff
        window.draw(sBackground);
        window.draw(sCharacter);
        for (int i=0; i<platformnum; i++)
        {
            // Set position of the platform
            sPlatform.setPosition(platforms[i].x,platforms[i].y);
            window.draw(sPlatform); // draw platform
        }

        // Draw shurikens and pizzas
        for(int i = 0; i < total; i++)
        {
            window.draw(shurikens[i]);
            window.draw(pizzas[i]);
        }

        score_text.setString("Score: " + std::to_string(score)); // Set score
        window.draw(score_text);
        if(gameover) window.draw(sgameover);

        // display window
        window.display();
    }
    return 0;
}
