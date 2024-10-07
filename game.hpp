#include <SFML/Graphics.hpp>
#include <array>


class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Vector2i mousePos);
    void render();
    void handleMouseClick(sf::Vector2i mousePos);
    bool checkWin(int player);
    void resetGame();
    void updateStatus(); // Ensure this is declared

    sf::RenderWindow window;
    std::array<std::array<int, 3>, 3> board;
    int currentPlayer;
    bool gameOver;
    sf::Font font;
    sf::Text statusText;
};
