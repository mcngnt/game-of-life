#define SFML_STATIC

#include <SFML/Graphics.hpp>
#include "slider.h"

inline void shader_on_tex(sf::Shader* shader_,sf::RenderTexture* renderTex_)
{
    sf::Sprite tempS;
    sf::RenderTexture tempT;
    tempT.create(renderTex_->getSize().x, renderTex_->getSize().y);
    tempS.setTexture(tempT.getTexture());
    tempT.clear();
    sf::Sprite renderSprt;
    renderSprt.setTexture(renderTex_->getTexture());

    tempT.draw(renderSprt, shader_);
    renderTex_->draw(tempS);
}

void centerText(sf::Text* t_)
{
    sf::FloatRect textRect = t_->getLocalBounds();
    t_->setOrigin(textRect.left + textRect.width/2.0f,
    textRect.top  + textRect.height/2.0f);
}


int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H, 32), "Main", sf::Style::Default);
    // window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(120);

    sf::Shader* cellAuto = new sf::Shader;
    cellAuto->loadFromFile("res/cellauto.frag", sf::Shader::Fragment);

    sf::Shader* worldEditor = new sf::Shader;
    worldEditor->loadFromFile("res/worldEditor.frag", sf::Shader::Fragment);


    float zoomFactor = 1.f;
    int tick = 0;
    float timer = 0.f;
    float dt = 0.01f;
    bool leftMouseButtonPressed = false;
    bool rightMouseButtonPressed = false;
    sf::Color clearColor = sf::Color(20, 20, 20);
    // bool ctrlKeyPressed = 
    bool isUpdatingSim = true;

    sf::Vector2f canvasSize(SCREEN_H, SCREEN_H);
    sf::Vector2f canvasPos(SCREEN_W-SCREEN_H, 0);
    sf::Vector2f gridSize = canvasSize * zoomFactor;
    sf::Vector2f screenSize(SCREEN_W, SCREEN_H);

    Slider slider(sf::Vector2f((SCREEN_W - SCREEN_H)/2 - 70, 200 ), sf::Vector2f((SCREEN_W - SCREEN_H)/2 + 70, 200 ), sf::Color::Cyan, 0, 60, 0, SCREEN_W/100);



    sf::Sprite canvas;
    sf::RenderTexture canvasTex;
    canvasTex.create(gridSize.x, gridSize.y);
    canvas.setTexture(canvasTex.getTexture());
    canvasTex.clear(clearColor);
    canvas.setScale(sf::Vector2f(1.f, 1.f)/zoomFactor);
    canvas.setPosition(canvasPos);

    sf::Font font;
    font.loadFromFile("res/GoogleSans-Bold.ttf");

    sf::Text text;
    text.setFont(font);

    

    while(window.isOpen())
    {
    	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
        sf::Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
            {
                window.close();
                break;
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    leftMouseButtonPressed = true;
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    rightMouseButtonPressed = true;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    leftMouseButtonPressed = false;
                    slider.unfollow_cursor();
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    rightMouseButtonPressed = false;
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    isUpdatingSim = !isUpdatingSim;
                }
            }
            if (event.type == sf::Event::MouseWheelMoved)
            {
                zoomFactor = clamp(zoomFactor - event.mouseWheel.delta * 0.05 * zoomFactor, 0.05f, 1.f);
                // std::cout << zoomFactor << std::endl;
                gridSize = canvasSize * zoomFactor;
                canvasTex.create(gridSize.x, gridSize.y);
                canvas.setTexture(canvasTex.getTexture());
                canvasTex.clear(clearColor);
                canvas.setScale(sf::Vector2f(1.f, 1.f)/zoomFactor);

            }
        }

        tick++;
        timer += dt;
        window.clear(clearColor);

        if (leftMouseButtonPressed)
        {
            slider.update(mousePos);
        }

        if (mousePos.x > SCREEN_W - SCREEN_H)
        {
            slider.unfollow_cursor();
        }

        cellAuto->setUniform("time", timer);
        cellAuto->setUniform("unitVec", sf::Vector2f(1,1)/gridSize);
        cellAuto->setUniform("isPaused", isUpdatingSim);
        sf::Glsl::Vec4 emptyColor = clearColor;
        cellAuto->setUniform("emptyCellColor", emptyColor);

        worldEditor->setUniform("texSize", gridSize);
        worldEditor->setUniform("screenSize", screenSize);
        worldEditor->setUniform("texPosTL", canvasPos);
        worldEditor->setUniform("texPosBR", canvasPos + canvasSize);
        worldEditor->setUniform("mousePos", mousePos);
        worldEditor->setUniform("mouseLPressed", leftMouseButtonPressed);
        worldEditor->setUniform("mouseRPressed", rightMouseButtonPressed);
        worldEditor->setUniform("emptyCellColor", emptyColor);

        shader_on_tex(worldEditor, &canvasTex);
        if ((int)slider.value == 0 or tick % (int)slider.value == 0)
        {
            shader_on_tex(cellAuto, &canvasTex);
        }
        window.draw(canvas);

        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(SCREEN_W - SCREEN_H, 0);
        line[1].position = sf::Vector2f(SCREEN_W - SCREEN_H, SCREEN_H);
        line[0].color = sf::Color::White;
        line[1].color = sf::Color::White;
        window.draw(line);

        text.setString("CA Editor");
        text.setCharacterSize(24);
        text.setPosition(sf::Vector2f((SCREEN_W - SCREEN_H)/2, 20));
        centerText(&text);
        window.draw(text);

        text.setString("Current grid size : " + std::to_string((int)gridSize.x) + " x " + std::to_string((int)gridSize.y));
        text.setPosition(sf::Vector2f((SCREEN_W - SCREEN_H)/2, 100));
        centerText(&text);
        window.draw(text);

        text.setString("Game speed");
        text.setPosition(sf::Vector2f((SCREEN_W - SCREEN_H)/2, 170));
        centerText(&text);
        window.draw(text);

        slider.draw(&window);

        window.display();

    }

	return 0;
}