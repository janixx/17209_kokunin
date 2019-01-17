#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>


class Game
{
public:
    Game(std::pair<size_t, size_t> sz = minSize, std::pair<int, int> rg = std::make_pair(2,3));
    ~Game() {}

    bool newGenerate();// true -- if new gen is differ from all old gens
    bool isAlive(size_t x, size_t y);

    void clear();
    void resize(std::pair<size_t, size_t> newSize);
    void setHeight(size_t height);
    void setWidth(size_t width);
    void setRange(std::pair<int, int> newRange);
    void setCellAlive(size_t x, size_t y);

    const std::vector<bool> & getUniverse() const;
    const std::pair<int, int> & getRange() const;
    const std::pair<size_t, size_t> & getSize() const;

    static void setMinSize(std::pair<size_t, size_t> newMin);
    static void setMaxSize(std::pair<size_t, size_t> newMax);

private:
    static std::pair<int, int> maxRange;
    static std::pair<size_t, size_t> maxSize;
    static std::pair<size_t, size_t> minSize;

    std::pair<size_t, size_t> size;
    std::pair<int, int> range;
    std::vector<bool> universe;
    std::vector<bool> generation;

};

#endif // GAME_H
