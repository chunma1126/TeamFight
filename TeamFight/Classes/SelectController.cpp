#include "SelectController.h"
#include "TeamController.h"
#include "UIController.h"

SelectController::SelectController()
{

}

void SelectController::init(TeamController* teamController, UIController* uiController)
{
    _teamController = teamController;
    _uiController = uiController;
}

Entity* SelectController::selectPlayerEntity()
{
    Entity* entity = _teamController->getPlayerEntity();

    auto sizeUpEvent = ScaleTo::create(0.1f, 1.15f);
    entity->runAction(sizeUpEvent);

    std::vector<std::string> skillPaths;
    for (const auto& skill : entity->getSkillList()) {
        skillPaths.push_back(skill->getIconPath());
    }

    _uiController->setSkillIcons(skillPaths);

    return entity;
}

Entity* SelectController::selectEnemyEntity(Vec2 worldMousePos)
{
    for (const auto& entity : _teamController->getAliveEnemies()) 
    {
        Rect entityRect = entity->getMainSprite()->getBoundingBox();
        entityRect.origin.x += entityRect.size.width / 4;
        entityRect.origin.y += entityRect.size.height / 4;
        entityRect.size.width /= 2;
        entityRect.size.height /= 2;

        Vec2 localPos = entity->convertToNodeSpace(worldMousePos);
        if (entityRect.containsPoint(localPos)) {
            return entity;
        }
    }

    return nullptr;
}