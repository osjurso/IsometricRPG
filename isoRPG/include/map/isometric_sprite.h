#ifndef ISORPG_ISOMETRIC_MAP_SPRITE_H
#define ISORPG_ISOMETRIC_MAP_SPRITE_H

#include <list>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

class IsometricSprite : public sf::Sprite
{
public:
    IsometricSprite();
    IsometricSprite(const sf::Image &image, const sf::Vector2f &position=sf::Vector2f(0,0),
                       const sf::Vector2f &scale=sf::Vector2f(1,1), float rotation=0.f, const sf::Color &color=sf::Color(255,255,255,255));
    ~IsometricSprite();

    void setWorldPosition(float x, float y);
    void setWorldPosition(const sf::Vector2f &position);
    sf::Vector2f getWorldPosition() const;

    void setWorldZ(float z);
    float getWorldZ(){return m_z;}

    void setUseLighting(bool use){m_uselighting=use;}
    bool getUseLighting(){return m_uselighting;}


protected:
    sf::Vector2f m_worldpos;
    float m_z;
    bool m_uselighting;
};

#endif //ISORPG_ISOMETRIC_MAP_SPRITE_H
