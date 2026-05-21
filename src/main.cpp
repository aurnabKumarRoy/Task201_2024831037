#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

using namespace sf;

const int GRID_SIZE=20;
const int WIN_W=800;
const int WIN_H=600;

struct GameState{
    std::vector<Vector2i>snake;
};

void initState(GameState& state){
    state.snake.clear();
    state.snake.push_back(Vector2i(1,WIN_H/(2*GRID_SIZE)));
    state.snake.push_back(Vector2i(0,WIN_H/(2*GRID_SIZE)));
    state.snake.push_back(Vector2i(2,WIN_H/(2*GRID_SIZE)));
}

void drawSnake(RenderWindow& window,Color color ,Vector2i cordinate){
    RectangleShape snake(Vector2f({(float)GRID_SIZE-.5f,(float)GRID_SIZE}));
    snake.setPosition({(float)(cordinate.x * GRID_SIZE) ,(float)(cordinate.y * GRID_SIZE)});
    snake.setFillColor(color);
    window.draw(snake);
}

void renderGame(RenderWindow& window ,const GameState& state){
    window.clear(Color(154,247,100));

    for(int i=0;i<state.snake.size();i++){
        drawSnake(window,Color(0,119,182),state.snake[i]);
    }
    window.display();

}

void closeWindow(RenderWindow &window){
    while(auto event=window.pollEvent()){
        if (event->is <Event::Closed>()){
            window.close();
        }
    }
}

int main(){
    RenderWindow window(VideoMode({WIN_W, WIN_H}),"Snake Game");
    window.setFramerateLimit(60);

    GameState state;
    initState(state);

    while (window.isOpen()){

        closeWindow(window);
        renderGame(window,state);

    }
}