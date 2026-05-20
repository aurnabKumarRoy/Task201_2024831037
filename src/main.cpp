#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

const int WIN_W=800;
const int WIN_H=600;

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

    while (window.isOpen()){
        closeWindow(window);
        window.clear(Color(154,247,100));
        window.display();
    }
}