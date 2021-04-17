#define SFML_STATIC
#include "sfmlvec.h"


class Slider
{
public:
	Slider(sf::Vector2f startPos_, sf::Vector2f endPos_,sf::Color color_, float value_, float maxValue_, float minValue_, float buttonRadius_);
	void draw(sf::RenderWindow* window);
	bool intersect(sf::Vector2f mousePos);
	void follow_cursor(sf::Vector2f mousePos);
	void update(sf::Vector2f mousePos);
	void unfollow_cursor();


	sf::Vector2f startPos;
	sf::Vector2f endPos;
	sf::Color color;
	float value;
	float maxValue;
	float minValue;
	float buttonRadius;
	sf::Vector2f buttonPos;
	bool isFollowing = false;

	
};