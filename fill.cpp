#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <stdint-gcc.h>
#include <iostream>

void updateKeyboard();
void hackProgram();

constexpr uint16_t KEYBOARD = 24576;
constexpr uint16_t SCREEN = 16384;
int16_t MEMORY[KEYBOARD + 1];

void updateKeyboard()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        MEMORY[KEYBOARD] = 0x31;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        MEMORY[KEYBOARD] = 0x32;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        MEMORY[KEYBOARD] = 0x33;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
    {
        MEMORY[KEYBOARD] = 0x34;
    }
    else
    {
        MEMORY[KEYBOARD] = 0;
    }
}

void hackProgram()
{
    MEMORY[16] = 16384;

    while (true)
    {
        if (MEMORY[KEYBOARD] == 0)
        {
            if ((MEMORY[16] - 16384) > 0)
            {
                MEMORY[16] = MEMORY[16] - 1;
                MEMORY[MEMORY[16]] = 0x0000;
            }
        }
        else
        {
            if ((MEMORY[16] - 24576) < 0)
            {
                MEMORY[MEMORY[16]] = 0xFFFF;
                MEMORY[16] = MEMORY[16] + 1;
            }
        }
    }
}

int main()
{
    constexpr int W = 512;
    constexpr int H = 256;
    sf::RenderWindow window(sf::VideoMode(W, H), "HACK Display");
    sf::Uint8 *pixels = new sf::Uint8[W * H * 4];
    sf::Texture texture;
    sf::Sprite sprite;
    texture.create(W, H);
    sprite.setTexture(texture);

    sf::Thread hackThread(&hackProgram);
    hackThread.launch();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                // hackThread.terminate();
            }
        }

        updateKeyboard();

        // Update Display
        for (int i = 0; i < W * H * 4; i += 4)
        {
            if (((MEMORY[SCREEN + ((i / 4) / 16)] >> ((i / 4) % 16)) & 0x0001) != 0)
            {
                pixels[i] = 255;
                pixels[i + 1] = 0;
                pixels[i + 2] = 0;
                pixels[i + 3] = 255;
            }
            else
            {
                pixels[i] = 255;
                pixels[i + 1] = 255;
                pixels[i + 2] = 255;
                pixels[i + 3] = 255;
            }
        }
        texture.update(pixels);
        window.clear();
        window.draw(sprite);
        window.display();
    }
    exit(EXIT_SUCCESS);
}
