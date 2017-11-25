//
// Created by Bjornar on 13.11.2017.
//

#ifndef ISORPG_RESOLVE_MOVMENT_H
#define ISORPG_RESOLVE_MOVMENT_H


#include <anax/System.hpp>



class ResolveMovment
{
public:
ResolveMovment()
{

}

    void resolveMovment(anax::Entity& entity, std::string Occurrence, float deltaTime);

private:
    void Walk(anax::Entity& entity, float deltaTime);

    void Idle(anax::Entity& entity, float deltaTime);

    void Attack(anax::Entity& entity, float deltaTime);

    void Defend(anax::Entity& entity, float deltaTime);

};

#endif //ISORPG_RESOLVE_MOVMENT_H
