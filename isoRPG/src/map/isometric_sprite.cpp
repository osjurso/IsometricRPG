#include "include/map/isometric_sprite.h"
#include "include/util/maths.h"

IsometricSprite::IsometricSprite()
{

}

IsometricSprite::IsometricSprite(const sf::Image &image, const sf::Vector2f &position,
                                 const sf::Vector2f &scale, float rotation, const sf::Color &color)
{
    sf::Texture temp;
    temp.update(image);
    setTexture(temp);

    setPosition(position);
    setScale(scale);
    setRotation(rotation);
    setColor(color);
}

IsometricSprite::~IsometricSprite() {

}

void IsometricSprite::setWorldPosition(const sf::Vector2f &position)
{
    m_worldpos = position;
    sf::Vector2f screenpos = WorldToScreen(m_worldpos);
    screenpos.y -= m_z;
    setPosition(screenpos);
}

void IsometricSprite::setWorldPosition(float x, float y)
{
    m_worldpos = sf::Vector2f(x, y);
    sf::Vector2f screenpos = WorldToScreen(m_worldpos);
    screenpos.y -= m_z;
    setPosition(screenpos);
}

sf::Vector2f IsometricSprite::getWorldPosition() const {
    return m_worldpos;
}

void IsometricSprite::setWorldZ(float z)
{
    m_z=z;
    sf::Vector2f screenpos = WorldToScreen(m_worldpos);
    m_z * 0.866;
    screenpos.y -= m_z;
    setPosition(screenpos);
}