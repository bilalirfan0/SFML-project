#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;


int main()
{
    // Part 1 - Bilal: load artwork and set up the window and player.
    Texture backgroundTexture, bulletTexture;
    Texture playerTextures[1], enemyTextures[2];
    if (!backgroundTexture.loadFromFile("img/abdullah.jpg") ||
        !bulletTexture.loadFromFile("img/enemy_laser.png") ||
        !playerTextures[0].loadFromFile("img/level1c.png") ||
        !enemyTextures[0].loadFromFile("img/PNG/Enemies/enemyGreen1.png") ||
        !enemyTextures[1].loadFromFile("img/PNG/Enemies/enemyBlue1.png"))
    {
        cerr << "Could not load artwork. Run run.cmd.\n";
        return 1;
    }

    Sprite background(backgroundTexture), player(playerTextures[0]);
    background.setScale({0.75f, 1.2f});
    player.setPosition({340.f, 700.f});
    player.setScale({0.2f, 0.2f});
    RenderWindow window(VideoMode({780, 780}), "SPACE SHOOTER");
    window.setKeyRepeatEnabled(false);

    // Shared preview support: keep the window responsive until it is closed.
    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
        }
        if (!window.isOpen())
            break;

        // Bilal: continuous movement using the four arrow keys.
        if (Keyboard::isKeyPressed(Keyboard::Key::Left))  player.move({-0.3f, 0.f});
        if (Keyboard::isKeyPressed(Keyboard::Key::Right)) player.move({0.3f, 0.f});
        if (Keyboard::isKeyPressed(Keyboard::Key::Up))    player.move({0.f, -0.3f});
        if (Keyboard::isKeyPressed(Keyboard::Key::Down))  player.move({0.f, 0.3f});

        // Shared preview support: display Bilal's background and player.
        window.clear(Color::Black);
        window.draw(background);
        window.draw(player);
        window.display();
    }
    return 0;
}
