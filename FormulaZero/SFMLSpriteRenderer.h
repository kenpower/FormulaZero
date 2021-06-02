#pragma once
#include "SFML/Graphics.hpp"
#include "Drawable.h"
#include "SpriteRenderer.h"

class SFMLSpriteRenderer :
    public SpriteRenderer
{
	Drawable* drawable{NULL};
	sf::RenderWindow* window{NULL};

	sf::Sprite sprite;

public:
	void init(Drawable* d, sf::RenderWindow* w, sf::Texture& t, float scale) {
		drawable = d;
		window = w;
		sprite.setTexture(t);
		sprite.setScale(scale, scale);
		sprite.setOrigin(t.getSize().x / 2, t.getSize().y / 2);

	}

	void draw() {
		Vector pos = drawable->getPosition();

		sprite.setPosition((float)pos.x, (float)pos.y);
		sprite.setRotation(drawable->getRotation());
		window->draw(sprite);
	}
};

