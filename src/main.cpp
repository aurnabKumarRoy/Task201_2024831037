#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

using namespace sf;

const int GRID_SIZE=20;
const int WIN_W=1200;
const int WIN_H=800;

struct GameState{
    std::vector<Vector2i>snake;
    Vector2i food;
    char direction;
    bool gameOver;
    int score;
};

void initState(GameState& state){
    state.snake.clear();
    state.snake.push_back(Vector2i(2,WIN_H/(2*GRID_SIZE)));
    state.snake.push_back(Vector2i(1,WIN_H/(2*GRID_SIZE)));
    state.snake.push_back(Vector2i(0,WIN_H/(2*GRID_SIZE)));
    state.food=Vector2i(rand()%(WIN_W/GRID_SIZE),rand()%(WIN_H/GRID_SIZE));
    state.direction='X'; 
    state.gameOver=false;
    state.score=0;
}

void drawSnake(RenderWindow& window,Color color ,Vector2i cordinate){
    RectangleShape snake(Vector2f({(float)GRID_SIZE,(float)GRID_SIZE}));
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

void drawSnakeEye(RenderWindow& window,const GameState& state){
        CircleShape eye1(2.5f);
        CircleShape eye2(2.5f);
        eye1.setFillColor(Color::Black);
        eye2.setFillColor(Color::Black);

        float x = state.snake[0].x * GRID_SIZE;
        float y= state.snake[0].y * GRID_SIZE;

        if (state.direction =='R' ||state.direction =='X') {
            eye1.setPosition({x + 12.f,y + 4.f});
            eye2.setPosition({x + 12.f,y +12.f});
        } 
        else if (state.direction == 'L') {
            eye1.setPosition({x + 4.f, y + 4.f});
            eye2.setPosition({x + 4.f, y +12.f});
        } 
        else if (state.direction == 'U') {
            eye1.setPosition({x + 4.f, y + 4.f});
            eye2.setPosition({x + 12.f,y + 4.f});
        } 
        else if (state.direction== 'D') {
            eye1.setPosition({x + 4.f, y +12.f});
            eye2.setPosition({x + 12.f,y +12.f});
        }
        window.draw(eye1);
        window.draw(eye2);
}

void scoreTracking(RenderWindow& window, const GameState& state){
    Font font;
    if(!font.openFromFile("fonts/ARIALN.TTF")){
        std::cout<<"Font did not load";
        return;
    }

    Text score(font, "Score: " + std::to_string(state.score), 40);
    score.setFillColor(Color::White);
    score.setPosition({20.f, 20.f});
    window.draw(score);
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
        state.score+=100;
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

    //collision check with Window border
    if(head.x<0 || head.x>=WIN_W/GRID_SIZE || head.y<0 || head.y>=WIN_H/GRID_SIZE){
        state.gameOver=true;
    }

}

void renderGame(RenderWindow& window ,const GameState& state){
    window.clear(Color::Black);
        drawFood(window,state.food);

    // Drawing Snake
    for(int i=0;i<state.snake.size();i++){
        drawSnake(window,Color::Green,state.snake[i]);
    }

    //SnakeEye
    drawSnakeEye(window,state);
     
    //Score Text
    scoreTracking(window,state);
    
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