#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

using namespace sf;

const int GRID_SIZE=20;
const int WIN_W=1600;
const int WIN_H=900;

struct GameState{
    std::vector<Vector2i>snake;
    Vector2i food;
};

void initState(GameState& state){
    state.snake.clear();
    state.snake.push_back(Vector2i(2,WIN_H/(2*GRID_SIZE)));
    state.snake.push_back(Vector2i(1,WIN_H/(2*GRID_SIZE)));
    state.snake.push_back(Vector2i(0,WIN_H/(2*GRID_SIZE)));
    state.food=Vector2i(rand()%(WIN_W/GRID_SIZE),rand()%(WIN_H/GRID_SIZE));
}

void drawSnake(RenderWindow& window,Color color ,Vector2i cordinate){
    RectangleShape snake(Vector2f({(float)GRID_SIZE-1.5f,(float)GRID_SIZE-1.5f}));
    snake.setPosition({(float)(cordinate.x * GRID_SIZE) ,(float)(cordinate.y * GRID_SIZE)});
    snake.setFillColor(color);
    window.draw(snake);
}

void drawFood(RenderWindow& window ,Vector2i cordinate){
    CircleShape food(GRID_SIZE/2,100);
    food.setFillColor(Color::Red);
    food.setPosition({(float)(cordinate.x * GRID_SIZE) ,(float)(cordinate.y * GRID_SIZE)});
    window.draw(food);
}

void renderGame(RenderWindow& window ,const GameState& state){
    window.clear(Color::Black);
        drawFood(window,state.food);

    for(int i=0;i<state.snake.size();i++){
        drawSnake(window,Color::Green,state.snake[i]);
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