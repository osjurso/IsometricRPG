#include "include/states/state_character.h"
#include "include/gameEngine/resource_holder.h"

StateCharacter::StateCharacter(StateStack &stack, Context context)
        : StateBase(stack, context)
{
    sf::Font& font = context.fonts->get(Fonts::Main);

    mBackdrop.setTexture(context.textures->get(Textures::SettingsBackdorp));
    mBackdrop.setPosition(0,0);

    mCharacterBox1.setTexture(context.textures->get(Textures::CharacterBox));
    mCharacterBox2.setTexture(context.textures->get(Textures::CharacterBox));
    mCharacterBox3.setTexture(context.textures->get(Textures::CharacterBox));

    mCharacterBox1.setPosition(500, 80);
    mCharacterBox2.setPosition(500, 80 + mCharacterBox1.getGlobalBounds().height +50);
    mCharacterBox3.setPosition(500, 80 + 2*(mCharacterBox1.getGlobalBounds().height +50));

    mCharacterName1.setString("Name: ");
    mCharacterClass1.setString("Class: ");
    mCharacterName1.setPosition(800,100);
    mCharacterClass1.setPosition(800,150);
    mCharacterClass1.setFont(font);
    mCharacterName1.setFont(font);


    mCharacterName2.setString("Name: ");
    mCharacterClass2.setString("Class: ");
    mCharacterName2.setPosition(800,100+ mCharacterBox1.getGlobalBounds().height +50);
    mCharacterClass2.setPosition(800,150+ mCharacterBox1.getGlobalBounds().height +50);
    mCharacterClass2.setFont(font);
    mCharacterName2.setFont(font);

    mCharacterName3.setString("Name: ");
    mCharacterClass3.setString("Class: ");
    mCharacterName3.setPosition(800,100 + 2*(mCharacterBox1.getGlobalBounds().height +50));
    mCharacterClass3.setPosition(800,150 + 2*(mCharacterBox1.getGlobalBounds().height +50));
    mCharacterClass3.setFont(font);
    mCharacterName3.setFont(font);



}
void StateCharacter::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackdrop);
    window.draw(mCharacterBox1);
    window.draw(mCharacterName1);
    window.draw(mCharacterClass1);

    window.draw(mCharacterBox2);
    window.draw(mCharacterName2);
    window.draw(mCharacterClass2);

    window.draw(mCharacterBox3);
    window.draw(mCharacterName3);
    window.draw(mCharacterClass3);





}

bool StateCharacter::update(sf::Time dt)
{
    return true;
}

bool StateCharacter::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        requestStackPop();
        requestStackPush(States::Game);
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {

    }

    return true;
}
