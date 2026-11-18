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
     // Part 2 - Humail: sprite containers and two rows of enemies.
    vector<Sprite> enemies;
    vector<Sprite> bullets;
    const float firstX[2] = {200.f, 60.f}, spacing[2] = {145.f, 300.f};
    for (int row = 0; row < 2; ++row)
        for (int column = 0; column < 3; ++column)
        {
            Sprite enemy(enemyTextures[row]);
            enemy.setScale({0.6f, 0.6f});
            enemy.setPosition({firstX[row] + spacing[row] * column, 70.f + 100.f * row});
            enemies.push_back(enemy);
        }
    // Part 3 - Abdullah: firing state and event handling.
    bool canFire = true;

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            const auto* pressed = event->getIf<Event::KeyPressed>();
            if (event->is<Event::Closed>() ||
                (pressed && pressed->code == Keyboard::Key::Escape))
            {
                window.close();
                break;
            }
            const auto* released = event->getIf<Event::KeyReleased>();
            if (released && released->code == Keyboard::Key::Space)
                canFire = true;
        }
        if (!window.isOpen())
            break;

   

        // Bilal: continuous movement using the four arrow keys.
        if (Keyboard::isKeyPressed(Keyboard::Key::Left))  player.move({-0.3f, 0.f});
        if (Keyboard::isKeyPressed(Keyboard::Key::Right)) player.move({0.3f, 0.f});
        if (Keyboard::isKeyPressed(Keyboard::Key::Up))    player.move({0.f, -0.3f});
        if (Keyboard::isKeyPressed(Keyboard::Key::Down))  player.move({0.f, 0.3f});

        
       // Abdullah: create one bullet, then wait for Space to be released.
        if (Keyboard::isKeyPressed(Keyboard::Key::Space) && canFire)
        {
            Sprite bullet(bulletTexture);
            bullet.setPosition(player.getPosition());
            bullets.push_back(bullet);
            canFire = false;
        }
            // Abdullah: move bullets upward and remove them safely off-screen.
            for (size_t i = 0; i < bullets.size();)
            {
                bullets[i].move({0.f, -0.75f});
                if (bullets[i].getPosition().y < 0.f)
                    bullets.erase(bullets.begin() + i);
                else
                    ++i;
            }
    
    // Humail: clear, draw the scene in order, and show the frame.
        window.clear(Color::Black);
        window.draw(background);
        window.draw(player);
        for (const auto& bullet : bullets)
            window.draw(bullet);
        for (const auto& enemy : enemies)
            window.draw(enemy);
        window.display();
    }
    return 0;
    
}
