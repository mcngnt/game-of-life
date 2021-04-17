#include <utils.h>
#include <SFML/Graphics.hpp>

sf::Vector2f operator/(const sf::Vector2f&, const sf::Vector2f&);
void print_sfvector(sf::Vector2f);
sf::Vector2f normalize(sf::Vector2f);
float length(sf::Vector2f);
float dist(sf::Vector2f, sf::Vector2f);
float dot(sf::Vector2f, sf::Vector2f);