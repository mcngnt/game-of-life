#include "sfmlvec.h"

sf::Vector2f operator/(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return sf::Vector2f(a.x/b.x, a.y/b.y);
}

void print_sfvector(sf::Vector2f vec)
{
	std::cout << vec.x << " " << vec.y << std::endl;
}

float length(sf::Vector2f vec)
{
	return sqrt(vec.x*vec.x + vec.y*vec.y);
}

sf::Vector2f normalize(sf::Vector2f vec)
{
	float vecLength = length(vec);
	if (vecLength == 0)
	{
		return vec;
	}
	return vec/length(vec);
}

float dist(sf::Vector2f a, sf::Vector2f b)
{
	return length(a - b);
}

float dot(sf::Vector2f a, sf::Vector2f b)
{
	return a.x*b.x + a.y*b.y;
}