#pragma once

struct Player
{
    float posX = 0;
    float posY = 0;
    float moveInputX = 0;
    float moveInputY = 0;
    // float velocityX = 0.0;
    // float velocityY = 0.0;
    float speed = 200.0;
    
    bool isAlive = true;
    int score = 0;
    int level = 1;
    
    int r = 100;
    int g = 100;
    int b = 100;
    int a = 255;

    void Update();
};
