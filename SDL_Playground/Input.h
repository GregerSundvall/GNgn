#pragma once

struct Input
{
    int Esc, W, S, A, D;
    // int W = 0;
    // int S = 0;
    // int A = 0;
    // int D = 0;

    void Reset();
    
    void Update();
};
