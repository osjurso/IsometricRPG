#include <include/components/Comp_animation.h>


AnimationComponent::AnimationComponent(sf::Texture& texture, sf::Vector2u imageCount, float switchTime) {
    this->imageCounter = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    animationRect.width = pixleWidth;
    animationRect.height = pixleHeight;

}

AnimationComponent::~AnimationComponent() {}

void AnimationComponent::walk(int row, float deltaTime, bool faceRight, bool faceUp, sf::Vector2f speed) {
    currentImage.y = row;

    bool isMooving = false;

    if (speed.x != 0)
        isMooving = true;
    if (speed.y != 0){
        isMooving = true;
    }

    if (!isMooving && !idle){
        idle = true;
        currentImage.x = 0;
    }
    else if(isMooving && idle){
        idle = false;
        currentImage.x = 4;
    }

    totalTime += deltaTime;

    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage.x++;

        if (idle) {
            if (currentImage.x >= 3)
                currentImage.x = 0;

        } else if (!idle) {
            if (currentImage.x >= 11)
                currentImage.x = 3;

        }
    }

    animationRect.top = currentImage.y * animationRect.height;

    if (!faceRight) {
        animationRect.left = (currentImage.x + 1) * abs(animationRect.width);
    }

    if(faceRight) {
        animationRect.left = currentImage.x * abs(animationRect.width);
    }

    if (!faceUp) {
        animationRect.left = (currentImage.x + 1) * abs(animationRect.width);
    }
    if (faceUp) {
        animationRect.left = (currentImage.x + 1) * abs(animationRect.width);
    }
}