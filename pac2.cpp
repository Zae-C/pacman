#include<iostream>
#include "SFML/Graphics.hpp"
using namespace std;

enum DIRECTIONS { LEFT, RIGHT, UP, DOWN }; //left is 0, right is 1, up is 2, down is 3

int main() {
    //game set up (you'll need these lines in every game)
    sf::RenderWindow screen(sf::VideoMode(700, 775), "breakout"); //set up screen
    sf::Event event; //set up event queue
    sf::Clock clock; //set up the clock (needed for game timing)
    const float FPS = 60.0f; //FPS
    screen.setFramerateLimit(FPS); //set FPS

    //load in images


    sf::Texture powerpellet;//-1
    powerpellet.loadFromFile("powerpellet.png");
    sf::Sprite power;
    power.setTexture(powerpellet);

    sf::Texture pellet;//0
    pellet.loadFromFile("pellet.png");
    sf::Sprite consume;
    consume.setTexture(pellet);

    sf::Texture out;//1
    out.loadFromFile("owall.png");
    sf::Sprite wall;
    wall.setTexture(out);

    sf::Texture out2;//2
    out2.loadFromFile("owall.png");
    sf::Sprite wall2;
    wall2.setTexture(out2);
    wall2.setOrigin(0, 25);
    wall2.setRotation(90.f);

    sf::Texture out3;//3
    out3.loadFromFile("owall.png");
    sf::Sprite wall3;
    wall3.setTexture(out3);
    wall3.setOrigin(25, 25);
    wall3.setRotation(180.f);

    sf::Texture out4;//4
    out4.loadFromFile("owall.png");
    sf::Sprite wall4;
    wall4.setTexture(out4);
    wall4.setOrigin(25, 0);
    wall4.setRotation(270.f);

    sf::Texture side;//5
    side.loadFromFile("iwall.png");
    sf::Sprite is;
    is.setTexture(side);

    sf::Texture side2;//6
    side2.loadFromFile("iwall.png");
    sf::Sprite is2;
    is2.setTexture(side2);
    is2.setOrigin(0, 25);
    is2.setRotation(90.f);

    sf::Texture side3;//7
    side3.loadFromFile("iwall.png");
    sf::Sprite is3;
    is3.setTexture(side3);
    is3.setOrigin(25, 25);
    is3.setRotation(180.f);

    sf::Texture side4;//8
    side4.loadFromFile("iwall.png");
    sf::Sprite is4;
    is4.setTexture(side4);
    is4.setOrigin(25, 0);
    is4.setRotation(270.f);

    sf::Texture corner;//9
    corner.loadFromFile("ocorner.png");
    sf::Sprite oc;
    oc.setTexture(corner);

    sf::Texture corner2;//10
    corner2.loadFromFile("ocorner.png");
    sf::Sprite oc2;
    oc2.setTexture(corner2);
    oc2.setOrigin(0, 25);
    oc2.setRotation(90.f);

    sf::Texture corner3;//11
    corner3.loadFromFile("ocorner.png");
    sf::Sprite oc3;
    oc3.setTexture(corner3);
    oc3.setOrigin(25, 25);
    oc3.setRotation(180.f);

    sf::Texture corner4;//12
    corner4.loadFromFile("ocorner.png");
    sf::Sprite oc4;
    oc4.setTexture(corner4);
    oc4.setOrigin(25, 0);
    oc4.setRotation(270.f);

    sf::Texture icorner;//13
    icorner.loadFromFile("icorner.png");
    sf::Sprite ic;
    ic.setTexture(icorner);

    sf::Texture icorner2;//14
    icorner2.loadFromFile("icorner.png");
    sf::Sprite ic2;
    ic2.setTexture(icorner2);
    ic2.setOrigin(0, 25);
    ic2.setRotation(90.f);

    sf::Texture icorner3;//15
    icorner3.loadFromFile("icorner.png");
    sf::Sprite ic3;
    ic3.setTexture(icorner3);
    ic3.setOrigin(25, 25);
    ic3.setRotation(180.f);

    sf::Texture icorner4;//16
    icorner4.loadFromFile("icorner.png");
    sf::Sprite ic4;
    ic4.setTexture(icorner4);
    ic4.setOrigin(25, 0);
    ic4.setRotation(270.f);



    int map[31][28] = {
        9 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,10,
        4 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,8 ,6 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2 ,
        4 ,0 ,13,5 ,5 ,14,0 ,13,5 ,5 ,5 ,14,0 ,8 ,6 ,0 ,13,5 ,5 ,5 ,14,0 ,13,5 ,5 ,14,0 ,2 ,
        4 ,-1,8 ,-2,-2,6 ,0 ,8 ,-2,-2,-2,6 ,0 ,8 ,6 ,0 ,8 ,-2,-2,-2,6 ,0 ,8 ,-2,-2,6 ,-1,2 ,
        4 ,0 ,16,7 ,7 ,15,0 ,16,7 ,7 ,7 ,15,0 ,16,15,0 ,16,7 ,7 ,7 ,15,0 ,16,7 ,7 ,15,0 ,2 ,
        4 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2 ,
        4 ,0 ,13,5 ,5 ,14,0 ,13,14,0 ,13,5 ,5 ,5 ,5 ,5 ,5 ,14,0 ,13,14,0 ,13,5 ,5 ,14,0 ,2 ,
        4 ,0 ,16,7 ,7 ,15,0 ,8 ,6 ,0 ,16,7 ,7 ,14,13,7 ,7 ,15,0 ,8 ,6 ,0 ,16,7 ,7 ,15,0 ,2 ,
        4 ,0 ,0 ,0 ,0 ,0 ,0 ,8 ,6 ,0 ,0 ,0 ,0 ,8 ,6 ,0 ,0 ,0 ,0 ,8 ,6 ,0 ,0 ,0 ,0 ,0 ,0 ,2 ,
        12,1 ,1 ,1 ,1 ,10,0 ,8 ,16,5 ,5 ,14,-2,8 ,6 ,-2,13,5 ,5 ,15,6 ,0 ,9 ,1 ,1 ,1 ,1 ,11,
        -2,-2,-2,-2,-2,2 ,0 ,8 ,13,7 ,7 ,15,-2,16,15,-2,16,7 ,7 ,14,6 ,0 ,4 ,-2,-2,-2,-2,-2,
        -2,-2,-2,-2,-2,2 ,0 ,8 ,6 ,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,8 ,6 ,0 ,4 ,-2,-2,-2,-2,-2,
        -2,-2,-2,-2,-2,2 ,0 ,8 ,6 ,-2,9 ,1 ,1 ,1 ,1 ,1 ,1 ,10,-2,8 ,6 ,0 ,4 ,-2,-2,-2,-2,-2,
        3 ,3 ,3 ,3 ,3 ,11,0 ,16,15,-2,4 ,-2,-2,-2,-2,-2,-2,2 ,-2,16,15,0 ,12,3 ,3 ,3 ,3 ,3 ,
        -2,-2,-2,-2,-2,-2,0 ,-2,-2,-2,4 ,-2,-2,-2,-2,-2,-2,2 ,-2,-2,-2,0 ,-2,-2,-2,-2,-2,-2,
        1 ,1 ,1 ,1 ,1 ,10,0 ,13,14,-2,4 ,-2,-2,-2,-2,-2,-2,2 ,-2,13,14,0 ,9 ,1 ,1 ,1 ,1 ,1 ,
        -2,-2,-2,-2,-2,2 ,0 ,8 ,6 ,-2,12,3 ,3 ,3 ,3 ,3 ,3 ,11,-2,8 ,6 ,0 ,4 ,-2,-2,-2,-2,-2,
        -2,-2,-2,-2,-2,2 ,0 ,8, 6 ,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,8 ,6 ,0 ,4 ,-2,-2,-2,-2,-2,
        -2,-2,-2,-2,-2,2 ,0 ,8 ,6 ,-2,13,5 ,5 ,5 ,5 ,5 ,5 ,14,-2,8 ,6 ,0 ,4 ,-2,-2,-2,-2,-2,
        9 ,3 ,3 ,3 ,3 ,11,0 ,16,15,-2,16,7 ,7 ,14,13,7 ,7 ,15,-2,16,15,0 ,12,1 ,1 ,1 ,1 ,10,
        4 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,8 ,6 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2 ,
        4 ,0 ,13,5 ,5 ,14,0 ,13,5 ,5 ,5 ,14,0 ,8 ,6 ,0 ,13,5 ,5 ,5 ,14,0 ,13,5 ,5 ,14,0 ,2 ,
        4 ,0 ,16,5 ,14,6 ,0 ,16,7 ,7 ,7 ,15,0 ,16,15,0 ,16,7 ,7 ,7 ,15,0 ,8 ,13,7 ,15,0 ,2 ,
        4 ,-1,0 ,0 ,8 ,6 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,8 ,6 ,0 ,0 ,-1,2 ,
        4 ,5 ,14,0 ,8 ,6 ,0 ,13,14,0 ,13,5 ,5 ,5 ,5 ,5 ,5 ,14,0 ,13,14,0 ,8 ,6 ,0 ,13,5 ,2 ,
        4 ,7 ,15,0 ,16,15,0 ,8 ,6 ,0 ,16,7 ,7 ,14,13,7 ,7 ,15,0 ,8 ,6 ,0 ,16,15,0 ,16,7 ,2 ,
        4 ,0 ,0 ,0 ,0 ,0 ,0 ,8 ,6 ,0 ,0 ,0 ,0 ,8 ,6 ,0 ,0 ,0 ,0 ,8 ,6 ,0 ,0 ,0 ,0 ,0 ,0 ,2 ,
        4 ,0 ,13,5 ,5 ,5 ,5 ,15,16,5 ,5 ,14,0 ,8 ,6 ,0 ,13,5 ,5 ,15,16,5 ,5 ,5 ,5 ,14,0 ,2 ,
        4 ,0 ,16,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,15,0 ,16,15,0 ,16,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,15,0 ,2 ,
        4 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2 ,
        12,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,11,

    };

    //player setup
    int xpos = 338.5;
    int ypos = 575;
    int vx = 0;
    int vy = 0;
    int radius = 12.5;
    sf::CircleShape player(radius);
    player.setFillColor(sf::Color(250, 250, 0)); //using RGB value for color here (hex also works)
    player.setPosition(xpos, ypos); //top left "corner" of circle (not center!)
    bool keys[] = { false, false, false, false };

    //################### HOLD ONTO YOUR BUTTS, ITS THE GAME LOOP###############################################################
    while (screen.isOpen()) {//keep window open until user shuts it down

        while (screen.pollEvent(event)) { //look for events-----------------------

            //this checks if the user has clicked the little "x" button in the top right corner
            if (event.type == sf::Event::EventType::Closed)
                screen.close();
            //KEYBOARD INPUT 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                keys[LEFT] = true;
            }
            else keys[LEFT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                keys[RIGHT] = true;
            }
            else keys[RIGHT] = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                keys[UP] = true;
            }
            else keys[UP] = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                keys[DOWN] = true;
            }
            else keys[DOWN] = false;

        }//end event loop---------------------------------------------------------------

         //move Mr. Pac
        if (keys[LEFT] == true)
            vx = -3.5;

        else if (keys[RIGHT] == true)
            vx = 3.5;

        else vx = 0;

        if (keys[UP] == true)
        vy = -3.5;

        else if (keys[DOWN] == true)
        vy = 3.5;

        else vy = 0;

        

        if (vx > 0 && map[(ypos) / 25][(xpos + radius * 2 + 1) / 25] >= 1) {
            vx = 0;
            player.setFillColor(sf::Color::Color(255, 0, 0, 255));
        }  
        else
            player.setFillColor(sf::Color::Color(255, 255, 0, 255));
        if (vx < 0 && map[(ypos) / 25][(xpos - 1) / 25] >= 1) {
            vx = 0;
            player.setFillColor(sf::Color::Color(255, 0, 0, 255));
        }
        else
            player.setFillColor(sf::Color::Color(255, 255, 0, 255));
        if (vy > 0 && map[(ypos + radius * 2 + 1) / 25][(xpos) / 25] >= 1) {
            vy = 0;
            player.setFillColor(sf::Color::Color(255, 0, 0, 255));
        }
        else
            player.setFillColor(sf::Color::Color(255, 255, 0, 255));
        if (vy < 0 && map[(ypos - 1) / 25][(xpos) / 25] >= 1) {
            vy = 0;
            player.setFillColor(sf::Color::Color(255, 0, 0, 255));
        }
        else
            player.setFillColor(sf::Color::Color(255, 255, 0, 255));

        if (vx > 0 && map[(ypos) / 25][(xpos + radius * 2 + 1) / 25] < 1) {
            map[(ypos) / 25][(xpos + radius * 2 + 1) / 25] = -2;
        }
        if (vx < 0 && map[(ypos) / 25][(xpos - 1) / 25] < 1) {
            map[(ypos) / 25][(xpos - 1) / 25] = -2;
        }
        if (vy > 0 && map[(ypos + radius * 2 + 1) / 25][(xpos) / 25] < 1) {
            map[(ypos + radius * 2 + 1) / 25][(xpos) / 25] = -2;
        }
        if (vy < 0 && map[(ypos - 1) / 25][(xpos) / 25] < 1) {
            map[(ypos - 1) / 25][(xpos) / 25] = -2;
        }
        if (xpos < 0) {
            xpos = 674;
        }
        if (xpos > 674) {
            xpos = 0;
        }
        xpos += vx;
        ypos += vy;
        player.setPosition(xpos, ypos);
                //render section-----------------------------------------
        screen.clear(); //wipes screen, without this things smear
        for (int rows = 0; rows < 31; rows++)
            for (int cols = 0; cols < 28; cols++) {
                if (map[rows][cols] == -1) {
                    power.setPosition(cols * 25, rows * 25);
                    screen.draw(power);
                }
                if (map[rows][cols] == 0) {
                    consume.setPosition(cols * 25, rows * 25);
                    screen.draw(consume);
                }
                if (map[rows][cols] == 1) {
                    wall.setPosition(cols * 25, rows * 25);
                    screen.draw(wall);
                }
                if (map[rows][cols] == 2) {
                    wall2.setPosition(cols * 25, rows * 25);
                    screen.draw(wall2);
                }
                if (map[rows][cols] == 3) {
                    wall3.setPosition(cols * 25, rows * 25);
                    screen.draw(wall3);
                }
                if (map[rows][cols] == 4) {
                    wall4.setPosition(cols * 25, rows * 25);
                    screen.draw(wall4);
                }
                if (map[rows][cols] == 5) {
                    is.setPosition(cols * 25, rows * 25);
                    screen.draw(is);
                }
                if (map[rows][cols] == 6) {
                    is2.setPosition(cols * 25, rows * 25);
                    screen.draw(is2);
                }
                if (map[rows][cols] == 7) {
                    is3.setPosition(cols * 25, rows * 25);
                    screen.draw(is3);
                }
                if (map[rows][cols] == 8) {
                    is4.setPosition(cols * 25, rows * 25);
                    screen.draw(is4);
                }
                if (map[rows][cols] == 9) {
                    oc.setPosition(cols * 25, rows * 25);
                    screen.draw(oc);
                }
                if (map[rows][cols] == 10) {
                    oc2.setPosition(cols * 25, rows * 25);
                    screen.draw(oc2);
                }
                if (map[rows][cols] == 11) {
                    oc3.setPosition(cols * 25, rows * 25);
                    screen.draw(oc3);
                }
                if (map[rows][cols] == 12) {
                    oc4.setPosition(cols * 25, rows * 25);
                    screen.draw(oc4);
                }
                if (map[rows][cols] == 13) {
                    ic.setPosition(cols * 25, rows * 25);
                    screen.draw(ic);
                }
                if (map[rows][cols] == 14) {
                    ic2.setPosition(cols * 25, rows * 25);
                    screen.draw(ic2);
                }
                if (map[rows][cols] == 15) {
                    ic3.setPosition(cols * 25, rows * 25);
                    screen.draw(ic3);
                }
                if (map[rows][cols] == 16) {
                    ic4.setPosition(cols * 25, rows * 25);
                    screen.draw(ic4);
                }
            }
        screen.draw(player); //draw player
        screen.display(); //flips memory drawings onto screen

    }//######################## end game loop ###################################################################################

    cout << "goodbye!" << endl;
} //end of main
