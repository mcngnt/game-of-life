#include "slider.h"


Slider::Slider(sf::Vector2f startPos_, sf::Vector2f endPos_, sf::Color color_, float value_, float maxValue_, float minValue_, float buttonRadius_)
:startPos(startPos_), endPos(endPos_), color(color_), value(value_), maxValue(maxValue_), minValue(minValue_), buttonRadius(buttonRadius_)
{
	float ratio = (value - minValue)/(maxValue - minValue);
	buttonPos = startPos + (endPos - startPos) * ratio;
}

bool Slider::intersect(sf::Vector2f mousePos)
{
	if (dist(mousePos, buttonPos) < buttonRadius * 2)
	{
		sf::Vector2f startToMouse = mousePos - startPos;
		sf::Vector2f startToEnd = endPos - startPos;
		sf::Vector2f mouseProjection = startPos + dot(startToMouse, startToEnd)/dot(startToEnd, startToEnd) * startToEnd;

		return true;
	}
	return false;
}

void Slider::follow_cursor(sf::Vector2f mousePos)
{
	sf::Vector2f startToMouse = mousePos - startPos;
	sf::Vector2f startToEnd = endPos - startPos;
	sf::Vector2f mouseProjection = startPos + dot(startToMouse, startToEnd)/dot(startToEnd, startToEnd) * startToEnd;
	if (dist(mouseProjection, endPos) < dist(startPos, endPos) && dist(mouseProjection, startPos) < dist(endPos, startPos))
	{
		buttonPos = mouseProjection;
		value = (dist(startPos, mousePos)/dist(startPos, endPos)) * (maxValue - minValue) + minValue;
	}
}

void Slider::update(sf::Vector2f mousePos)
{
	if (isFollowing or intersect(mousePos))
	{
		isFollowing = true;
		follow_cursor(mousePos);
	}
}

void Slider::unfollow_cursor()
{
	isFollowing = false;
}


void Slider::draw(sf::RenderWindow* window)
{
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = startPos;
	line[1].position = endPos;
	line[0].color = color;
	line[1].color = color;
	window->draw(line);
	sf::CircleShape circle(buttonRadius);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(buttonPos);
	window->draw(circle);
}