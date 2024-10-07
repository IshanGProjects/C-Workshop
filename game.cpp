#include "game.hpp" // Ensure this matches the filename's case
#include <iostream>

using namespace std;

Game::Game() : window(sf::VideoMode(600, 600), "Tic Tac Toe"), currentPlayer(1), gameOver(false) {
    window.setFramerateLimit(30);
    board.fill({{0, 0, 0}});
    if (!font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        cerr << "Failed to load font" << endl;
        exit(1);
    }
    statusText.setFont(font);
    statusText.setCharacterSize(24);
    statusText.setFillColor(sf::Color::Black);
    statusText.setPosition(10, 560);
    updateStatus();
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !gameOver) {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);  // This gives you world coordinates
            sf::Vector2i gridPos(static_cast<int>(worldPos.x), static_cast<int>(worldPos.y));  // Convert to grid position if needed
            handleMouseClick(gridPos);  // Pass integer coordinates to your function
        }
    }
}



void Game::update(sf::Vector2i mousePos) {
    int row = mousePos.y / 200;
    int col = mousePos.x / 200;
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == 0) {
        board[row][col] = currentPlayer;
        if (checkWin(currentPlayer)) {
            statusText.setString((currentPlayer == 1 ? "X" : "O") + string(" wins!"));
            gameOver = true;
        } else {
            currentPlayer = 3 - currentPlayer; // Switch player
            updateStatus();
        }
    }
}

void Game::render() {
    window.clear(sf::Color::White);

    // Enhanced grid lines using RectangleShape for better control over appearance
    sf::RectangleShape verticalLine(sf::Vector2f(5, 600));  // Thickness of 5 pixels
    sf::RectangleShape horizontalLine(sf::Vector2f(600, 5)); // Thickness of 5 pixels

    // Set color for grid lines
    verticalLine.setFillColor(sf::Color::Black);
    horizontalLine.setFillColor(sf::Color::Black);

    // Draw vertical grid lines
    for (int i = 1; i <= 2; ++i) {
        verticalLine.setPosition(200 * i - 2.5f, 0);  // Positioning the line in the middle of the cells
        window.draw(verticalLine);
    }

    // Draw horizontal grid lines
    for (int i = 1; i <= 2; ++i) {
        horizontalLine.setPosition(0, 200 * i - 2.5f);  // Positioning the line in the middle of the cells
        window.draw(horizontalLine);
    }

    // Draw X's and O's
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(100);  // Character size set to 100 for large symbols
            text.setFillColor(board[i][j] == 1 ? sf::Color::Red : (board[i][j] == 2 ? sf::Color::Blue : sf::Color::White));
            text.setString(board[i][j] == 1 ? "X" : (board[i][j] == 2 ? "O" : ""));

            // Center text within each cell
            sf::FloatRect textRect = text.getLocalBounds();
            text.setOrigin(textRect.width / 2, textRect.height / 2);
            text.setPosition(j * 200 + 100, i * 200 + 100);  // Adjust to center within each grid cell

            window.draw(text);
        }
    }

    // Draw the status text at the bottom of the window
    window.draw(statusText);
    window.display();
}


void Game::handleMouseClick(sf::Vector2i mousePos) {
    update(mousePos);
}

bool Game::checkWin(int player) {
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

void Game::updateStatus() {
    string player = (currentPlayer == 1 ? "X's" : "O's");
    statusText.setString("Player " + player + " turn");
}

