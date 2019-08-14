#include <iostream>
#include <sqlite3.h>
#include "Game.h"

int main(int argc, char** argv)
{
    Game* gameVar = new Game();
    gameVar->setup();
    int result = 0;
    result = gameVar->play();
    return result;
}
