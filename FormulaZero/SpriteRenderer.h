#pragma once
#include "SFML/Graphics.hpp" 
#include "Vector.h"
#include "Drawable.h"

class SpriteRenderer
{
	Drawable* drawable;
	sf::RenderWindow* window;

	sf::Sprite sprite;

public:
	void init(Drawable* d, sf::RenderWindow* w, sf::Texture& t, float scale){
		drawable = d;
		window = w;
		sprite.setTexture(t);
		sprite.setScale(scale, scale);
		sprite.setOrigin(t.getSize().x/2, t.getSize().y/2);

	}
	
	void draw() {
		Vector pos = drawable->getPosition();

		sprite.setPosition(pos.x,pos.y);
		sprite.setRotation(drawable->getRotation());
		window->draw(sprite);
	}
};

