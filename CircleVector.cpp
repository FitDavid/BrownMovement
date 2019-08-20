#include "CircleVector.h"

CircleVector::CircleVector(SDL_Renderer* renderer)
    : mRenderer(renderer)
{
    SDL_Surface* circleSurface;
    circleSurface = SDL_LoadBMP("circ.bmp");
    if(circleSurface == NULL)
        throw "File not found.";
    diameter = circleSurface->w;
    SDL_SetColorKey(circleSurface, SDL_TRUE, SDL_MapRGB(circleSurface->format, 0, 0xFF, 0xFF));
    circleTexture = SDL_CreateTextureFromSurface(renderer, circleSurface);
    SDL_FreeSurface(circleSurface);
}

CircleVector::~CircleVector()
{
    SDL_DestroyTexture(circleTexture);
}

bool CircleVector::haveCollided(Circle* circle_1, Circle* circle_2)
{
    // if distance squared less than diameter squared
    if((double)(circle_1->posX - circle_2->posX) * (circle_1->posX - circle_2->posX) +
            (circle_1->posY - circle_2->posY) * (circle_1->posY - circle_2->posY) <
            diameter * diameter)
    {
        return true;
    }
    return false;
}

/**
 * @brief Moves all the circles in the vector at constant velocity, checks for collisions with
 * the screen border and other circles.
 * @todo Collision detection with other circles is simple and unrealistic. The angle is not taken
 * into account.
 */
void CircleVector::move()
{
    for(iterator it = begin(); it < end(); it++)
    {
        it->posX += it->velX;
        it->posY += it->velY;
        if(it->posX < diameter / 2 || it->posX > 800 - diameter / 2)
        {
            it->velX = -it->velX;
        }
        if(it->posY < diameter / 2 || it->posY > 600 - diameter / 2)
        {
            it->velY = -it->velY;
        }
		it->coordinatesToVector();
    }
    for(iterator it = begin(); it < end(); it++)
    {
        for(iterator it2 = it+1; it2 < end(); it2++)
        {
            if(haveCollided(it, it2))
            {
                Vector CenterLine = it->pos - it2->pos;
				Vector ContactLine;
				ContactLine.x = CenterLine.y;
				ContactLine.y = -CenterLine.x;
				CenterLine.norm();
				ContactLine.norm();
				Vector i, j, i2, j2;
				i = it->vel.project(CenterLine);
				j = it->vel.project(ContactLine);
				i2 = it2->vel.project(CenterLine);
				j2 = it2->vel.project(ContactLine);
				Vector temp;
				temp = i;
				i = i2;
				i2 = temp;
				it->vel = i + j;
				it2->vel = i2 + j2;
				it->vectorToCoordinates();
				it2->vectorToCoordinates();
            }
        }
    }
}

void CircleVector::render()
{
    iterator _end = end();
    for(iterator it = begin(); it < _end; it++)
    {
        SDL_Rect dst = { it->posX - diameter / 2, it->posY - diameter / 2, diameter, diameter };
        SDL_RenderCopy(mRenderer, circleTexture, NULL, &dst);
    }
}

Vector Vector::operator-(Vector& v)
{
	Vector result;
	result.x = x - v.x;
	result.y = y - v.y;
	return result;
}

Vector Vector::operator+(Vector& v)
{
	Vector result;
	result.x = x + v.x;
	result.y = y + v.y;
	return result;
}

double Vector::dotProduct(Vector& v)
{
	return x * v.x + y * v.y;
}

void Vector::norm()
{
	double length = sqrt(dotProduct(*this));
	x /= length;
	y /= length;
}

Vector Vector::project(Vector& n)
{
	double length = dotProduct(n);
	Vector projection;
	projection.x = n.x*length;
	projection.y = n.y*length;
	return projection;
}

void Circle::vectorToCoordinates()
{
	velX = round(vel.x);
	velY = round(vel.y);
}

void Circle::coordinatesToVector()
{
	pos.x = posX;
	pos.y = posY;
	vel.x = velX;
	vel.y = velY;
}