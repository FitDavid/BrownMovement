#ifndef CIRCLEVECTOR_H
#define CIRCLEVECTOR_H
#include <SDL2/SDL.h>
#include <math.h>
#include <array>

const int numOfCircles = 10;

struct Vector
{
	double x, y;
	public:
	Vector(): x(0), y(0) {}
	Vector(double x, double y): x(x), y(y) {}
	Vector operator-(Vector& v);
	Vector operator+(Vector& v);
	double dotProduct(Vector& v);
	void norm();
	Vector project(Vector& n);
};

struct Circle
{
    Circle():
        posX(rand() % 780 + 10),
        posY(rand() % 580 + 10),
        velX(rand() % 2 - 1),
        velY(rand() % 2 - 1),
		pos(posX, posY),
		vel(velX, velY)
    {}
	void vectorToCoordinates();
	void coordinatesToVector();
    int posX;
    int posY;
    int velX;
    int velY;
	Vector pos;
	Vector vel;
};

class CircleVector : public std::array<Circle, numOfCircles>
{
public:
    CircleVector(SDL_Renderer* renderer);
    virtual ~CircleVector();
    void move();
    void render();
    bool haveCollided(Circle* circle_1, Circle* circle_2);

protected:

private:
    SDL_Texture * circleTexture;
    SDL_Renderer* mRenderer;
    int diameter;
};

#endif // CIRCLEVECTOR_H
