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
    char direction;
    bool gameOver;
};

void initState(GameState& state){
    state.snake.clear();
    state.snake.push_back(Vector2i(2,WIN_H/(2*GRID_SIZE)));
    state.snake.push_back(Vector2i(1,WIN_H/(2*GRID_SIZE)));
    state.snake.push_back(Vector2i(0,WIN_H/(2*GRID_SIZE)));
    state.food=Vector2i(rand()%(WIN_W/GRID_SIZE),rand()%(WIN_H/GRID_SIZE));
    state.direction='X'; 
    state.gameOver=false;
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

void keyInput(GameState& state){
    if(Keyboard::isKeyPressed(Keyboard::Key::Left ) && state.direction!='R') state.direction='L';
    if(Keyboard::isKeyPressed(Keyboard::Key::A ) && state.direction!='R') state.direction='L';

    if(Keyboard::isKeyPressed(Keyboard::Key::Right) && state.direction!='L') state.direction='R';
    if(Keyboard::isKeyPressed(Keyboard::Key::D ) && state.direction!='L') state.direction='R';

    if(Keyboard::isKeyPressed(Keyboard::Key::Up) && state.direction!='D') state.direction='U';
    if(Keyboard::isKeyPressed(Keyboard::Key::W) && state.direction!='D') state.direction='U';
    
    if(Keyboard::isKeyPressed(Keyboard::Key::Down) && state.direction!='U') state.direction='D';
    if(Keyboard::isKeyPressed(Keyboard::Key::S) && state.direction!='U') state.direction='D';
}

void update(GameState& state){
    if(state.gameOver==true){
        return initState(state);
    }

    if(state.direction=='X') return;

    Vector2i head=state.snake[0];

    if(state.direction=='L') head.x--;
    if(state.direction=='R') head.x++;
    if(state.direction=='U') head.y--;
    if(state.direction=='D') head.y++;

    state.snake.insert(state.snake.begin(),head);

    if (head==state.food){
        state.food.x=rand()%(WIN_W/GRID_SIZE);
        state.food.y=rand()%(WIN_H/GRID_SIZE);
    }
    else{
        state.snake.pop_back();
    }

    //Collision check with Own body
    for(size_t i=1;i<state.snake.size();i++){
        if(head==state.snake[i]){
            state.gameOver=true;
        }
    }

    //collision check with WIndow border
    if(head.x<0 || head.x>WIN_W/GRID_SIZE || head.y<0 || head.y>WIN_H/GRID_SIZE){
        state.gameOver=true;
    }

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
    window.setFramerateLimit(10);

    GameState state;
    initState(state);

    while (window.isOpen()){

        closeWindow(window);
        keyInput(state);
        update(state);
        renderGame(window,state);  

    }
}