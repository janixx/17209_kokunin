#include "game.h"

std::pair<size_t, size_t> Game::maxSize = std::make_pair(2000,1500);
std::pair<size_t, size_t> Game::minSize = std::make_pair(80,60);
std::pair<int, int> Game::maxRange = std::make_pair(1,9);

Game::Game(std::pair<size_t, size_t> sz, std::pair<int, int> rg) : //ADD CHECK PARAMETRS
    size(sz),
    range(rg)
{
    universe.resize((size.first + 2) * (size.second + 2));
    generation.resize((size.first + 2) * (size.second + 2));
}

bool Game::newGenerate()
{
    size_t notChanged = 0;
    generation.clear();
    generation.resize((size.first + 2) * (size.second + 2));
    for(size_t x=1; x <= size.first; x++) {
        for(size_t y=1; y <= size.second; y++) {
            generation[y * size.first + x] = isAlive(x,y);
            if(generation[y * size.first + x] == universe[y * size.first + x])
                notChanged++;
        }
    }
    if(notChanged == size.first * size.second) {
        return false;
    }
    universe = generation;
    return true;
}

bool Game::isAlive(size_t x, size_t y)
{
    int power = 0;
    power += universe[(y + 1) * size.first +  x];
    power += universe[(y - 1) * size.first +  x];
    power += universe[y * size.first +  x + 1];
    power += universe[y * size.first +  x - 1];
    power += universe[(y - 1) * size.first +  x - 1];
    power += universe[(y - 1) * size.first +  x + 1];
    power += universe[(y + 1) * size.first +  x - 1];
    power += universe[(y + 1) * size.first +  x + 1];
    if (universe[y * size.first +  x] == true && power >= range.first && power <= range.second)
           return true;
    return false;
}

void Game::clear()
{
    universe.clear();
    generation.clear();
    universe.resize((size.first + 2) * (size.second + 2));
}

void Game::resize(std::pair<size_t, size_t> newSize)//FIX ME
{
    //FIX!!!!!!!!
    size = newSize;
    clear();
}

void Game::setHeight(size_t height)//FIX - ADD CHECK
{
    size.second = height;
}

void Game::setWidth(size_t width)//FIX - ADD CHECK
{
    size.first = width;
}

void Game::setCellAlive(size_t x, size_t y)
{
    universe[y * size.first +  x] = true;
}

void Game::setRange(std::pair<int, int> newRange)//FIX - ADD CHECK
{
    range = newRange;
}

const std::vector<bool> & Game::getUniverse() const
{
    return universe;
}

const std::pair<size_t, size_t> & Game::getSize() const
{
    return size;
}

const std::pair<int, int> & Game::getRange() const
{
    return range;
}

void Game::setMinSize(std::pair<size_t, size_t> newMin) //FIX - ADD CHECK
{
    Game::minSize = newMin;
}

void Game::setMaxSize(std::pair<size_t, size_t> newMax) //FIX - ADD CHECK
{
    Game::maxSize = newMax;
}
