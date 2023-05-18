#ifndef TERRAIN_H
#define TERRAIN_H


class Terrain
{
private:
    int c;
    int l;
    char** map;
    int g;
    int t;
    bool trail;
public:
    Terrain(int l, int c);
    void printterrain()const;
    void random(int lm, int dt, int nt);
    void alligned(int dc, int dl);
    void update(int i, int j);
    void revert();

    friend class Game;
    friend class Player;
};




#endif // TERRAIN_H
