#include "game.h"

std::pair<size_t, size_t> Game::maxSize = std::make_pair(500,500);
std::pair<size_t, size_t> Game::minSize = std::make_pair(10,10);
std::pair<int, int> Game::maxRange = std::make_pair(1,9);

Game::Game(std::pair<size_t, size_t> sz, std::pair<int, int> rg) : //ADD CHECK PARAMETRS
    size(sz),
    range(rg)
{
    universe.resize((size.first) * (size.second));
    generation.resize((size.first) * (size.second));
}

bool Game::newGenerate()
{
    size_t notChanged = 0;
    generation.clear();
    generation.resize((size.first) * (size.second));
    for(size_t x = 0; x < size.first; x++) {
        for(size_t y = 0; y < size.second; y++) {
            generation[y * size.first + x] = willAlive(x,y);
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
    return universe[y * size.first +  x];
}

bool Game::willAlive(size_t x, size_t y)
{
    int power = 0;
    size_t prev_x = (x > 0 ? x - 1 : size.first - 1),
        prev_y = (y > 0 ? y - 1 : size.second - 1),
        next_x = (x < size.first - 1 ? x + 1 : 0),
        next_y = (y < size.second - 1 ? y + 1 : 0);
    power += universe[prev_y * size.first +  x];
    power += universe[next_y * size.first +  x];
    power += universe[y * size.first +  next_x];
    power += universe[y * size.first +  prev_x];
    power += universe[prev_y * size.first +  prev_x];
    power += universe[prev_y * size.first +  next_x];
    power += universe[next_y * size.first +  prev_x];
    power += universe[next_y * size.first +  next_x];
    if (!isAlive(x,y) && power == range.second)
           return true;
    if (isAlive(x,y) && power >= range.first && power <= range.second)
           return true;

    return false;
}

void Game::reset()
{
    universe.clear();
    generation.clear();
    universe.resize((size.first) * (size.second));
    generation.resize((size.first) * (size.second));
}

void Game::resize(std::pair<size_t, size_t> newSize)//FIX ME
{
    //FIX!!!!!!!!
    size = newSize;
    reset();
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

void Game::setCellDead(size_t x, size_t y)
{
    universe[y * size.first + x] = false;
}

void Game::setCellReverse(size_t x, size_t y)
{
    universe[y * size.first + x] = !universe[y * size.first + x];
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

const std::pair<size_t, size_t> & Game::getMaxSize() const
{
    return Game::maxSize;
}
const std::pair<size_t, size_t> & Game::getMinSize() const
{
    return Game::minSize;
}
