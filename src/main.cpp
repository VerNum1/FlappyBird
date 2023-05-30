#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;

int score;
bool gameRunning, gameOvered;
float delta;

sf::Texture *backgroundTexture;

sf::RenderWindow *window;

class MainWindowEntity {
public:
    virtual void draw() {};

    virtual void update() {};
};

class Bird : public MainWindowEntity {
private:
    sf::Texture *texture;
    float y;
    float vel;
    float currentFrames{};
    sf::Clock *animationClock;
    vector<sf::Texture *> frames;

public:
    Bird() {
        animationClock = new sf::Clock;

        for (const auto &path: {
                "C:\\Users\\vadim\\CLionProjects\\FlappyBird\\resources\\textures\\bird\\2-2.png",
                "C:\\Users\\vadim\\CLionProjects\\FlappyBird\\resources\\textures\\bird\\2-3.png",
                "C:\\Users\\vadim\\CLionProjects\\FlappyBird\\resources\\textures\\bird\\2-2.png",
                "C:\\Users\\vadim\\CLionProjects\\FlappyBird\\resources\\textures\\bird\\2-1.png"
        }) {
            auto frame = new sf::Texture();
            frame->loadFromFile(path);
            frames.push_back(frame);
        }
        texture = frames[0];

        y = 400;
        vel = 0;
    }

    Bird(const Bird &);

    Bird &operator=(Bird &);


    ~Bird() {
        for (const auto &ptr: frames) {
            delete ptr;
        }
        delete animationClock;
    }

    sf::FloatRect getRect() {
        auto size = texture->getSize();

        return {
                50, y,
                (float) size.x, (float) size.y
        };
    }

    void flap() {
        if (not gameRunning or gameOvered) return;
        vel = -420;
    }

    void draw() override {
        sf::Sprite birdSprite(*texture);
        birdSprite.setRotation(8 * (vel / 400));
        birdSprite.setPosition(50, y);

        window->draw(birdSprite);
    }

    void update() override {
        currentFrames += delta * 4;
        if (currentFrames > frames.size()) {
            currentFrames -= frames.size();
        }

        texture = frames[(int) currentFrames];

        if (gameRunning) {
            vel += delta * 1200;
            y += delta * vel;

            if (y < 0 or y + texture->getSize().y > backgroundTexture->getSize().y) {
                gameOvered = true;
            }

            if (y + texture->getSize().y > backgroundTexture->getSize().y) {
                y = (float) backgroundTexture->getSize().y + texture->getSize().y;
                vel = 0;
            }
        }
    }
};

Bird *bird;

sf::Texture *upperPipe;
sf::Texture *lowerPipe;

class Pipe : MainWindowEntity {
private:
    float x;
    float y;
    bool scored;

public:
    Pipe() {
        x = (float) (window->getSize().x + upperPipe->getSize().x);
        y = 100.0f + (float) ((rand() % 5 - 3) * 50);
        scored = false;
    }

    sf::FloatRect getUpperRect() {
        auto size = upperPipe->getSize();

        return {
                x, y + 340,
                (float) size.x, (float) size.y
        };
    }

    sf::FloatRect getLowerRect() {
        auto size = lowerPipe->getSize();

        return {
                x, y - 340,
                (float) size.x, (float) size.y
        };
    }

    void draw() override {
        sf::Sprite upperPipeSprite(*upperPipe);
        upperPipeSprite.setPosition(x, y + 340);
        sf::Sprite lowerPipeSprite(*lowerPipe);
        lowerPipeSprite.setPosition(x, y - 340);

        window->draw(upperPipeSprite);
        window->draw(lowerPipeSprite);
    }

    void update() override {
        if (not gameRunning or gameOvered) return;

        x -= 100 * delta;
        auto birdRect = bird->getRect();

        if (birdRect.intersects(getUpperRect()) or birdRect.intersects(getLowerRect())) {
            gameOvered = true;
        }

        if (x + upperPipe->getSize().x < birdRect.left and not scored) {
            scored = true;
            score++;
        }
    }
};

vector<Pipe *> pipes;
sf::Texture *groundTexture;
sf::Clock *pipesGeneratingClock;

sf::Font *font;
float groundOffset;

class MainWindow {
public :
    static void run() {
        srand((unsigned int) time(nullptr));
        pipesGeneratingClock = new sf::Clock;

        font = new sf::Font();
        font->loadFromFile("C:\\Users\\vadim\\CLionProjects\\FlappyBird\\resources\\fonts\\04B_19__.TTF");

        window = new sf::RenderWindow(sf::VideoMode(450, 700), "Flappy Bird");
        window->setPosition({1417, 120});

        bird = new Bird();

        backgroundTexture = new sf::Texture();
        backgroundTexture->loadFromFile(
                "C:\\Users\\vadim\\CLionProjects\\FlappyBird\\resources\\textures\\background\\impossible.png");

        groundTexture = new sf::Texture();
        groundTexture->loadFromFile("C:\\Users\\vadim\\CLionProjects\\FlappyBird\\resources\\textures\\ground.png");

        upperPipe = new sf::Texture();
        lowerPipe = new sf::Texture();

        sf::Image pipeImage;
        pipeImage.loadFromFile("C:\\Users\\vadim\\CLionProjects\\FlappyBird\\resources\\textures\\pipe.png");

        upperPipe->loadFromImage(pipeImage);
        pipeImage.flipVertically();
        lowerPipe->loadFromImage(pipeImage);

        pipes.push_back(new Pipe());
    }

    static void destroy() {
        delete window;
        delete bird;
        delete backgroundTexture;
        delete pipesGeneratingClock;
        delete font;
    }

    static void update() {
        bird->update();

        for (const auto &pipe: pipes) {
            pipe->update();
        }

        if (gameRunning and not gameOvered) {
            if (pipesGeneratingClock->getElapsedTime().asSeconds() > 3.5) {
                pipesGeneratingClock->restart();
                pipes.push_back(new Pipe());

                if (pipes.size() > 4) {
                    delete pipes[0];
                    pipes.erase(pipes.begin());
                }
            }
        }
    }

    static void handleEvent(sf::Event &event) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (not gameRunning) {
                gameRunning = true;
                pipesGeneratingClock->restart();
                pipes.push_back(new Pipe());
            }
            bird->flap();
        }
    }

    static void draw() {
        window->clear();
        window->draw(sf::Sprite(*backgroundTexture));

        for (const auto &pipe: pipes) {
            pipe->draw();
        }

        sf::Sprite groundSprite(*groundTexture);
        if (not(not gameRunning or gameOvered)) {
            groundOffset -= delta * 100;
            if (groundOffset <= -24) {
                groundOffset += 24;
            }
        }

        groundSprite.setPosition(groundOffset, (float) backgroundTexture->getSize().y);
        window->draw(groundSprite);

        sf::RectangleShape lowerRectangle({
                                                  (float) window->getSize().x,
                                                  (float) window->getSize().y - (float) backgroundTexture->getSize().y -
                                                  (float) groundTexture->getSize().y
                                          });
        lowerRectangle.setPosition(0, (float) backgroundTexture->getSize().y + (float) groundTexture->getSize().y);
        lowerRectangle.setFillColor({235, 100, 04});
        window->draw(lowerRectangle);

        bird->draw();

        sf::Text scoreText("Score: " + to_string(score), *font);
        scoreText.setPosition(window->getSize().x / 2 - scoreText.getLocalBounds().width / 2, 5);
        window->draw(scoreText);
    }

};

int main() {

    MainWindow::run();

    sf::Clock deltaClock;

    while (window->isOpen()) {
        sf::Event event{};

        while (window->pollEvent(event)) {
            MainWindow::handleEvent(event);
        }
        delta = deltaClock.getElapsedTime().asMicroseconds() / 1000.0f / 1000.0f;
        deltaClock.restart();

        MainWindow::update();
        MainWindow::draw();

        window->display();
    }

    MainWindow::destroy();

    return EXIT_SUCCESS;
}