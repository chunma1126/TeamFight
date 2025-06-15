#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class JYDButton : public cocos2d::Node
{
public:
    static JYDButton* create(const std::string& iconPath, const std::string& tooltipText = "");

    void setPosition(const cocos2d::Vec2& position);
    void setTooltipText(const std::string& text);
    void setTooltipColor(cocos2d::Color3B color);

    void setIcon(const std::string& iconPath);
    void setIcon(const std::string& iconPath , const std::string& iconName, float startX , float startY , float widht , float height);

    void setClickCallback(const std::function<void()>& callback);
    void setHoverCallback(const std::function<void(bool)>& callback); // true = enter, false = exit

    cocos2d::ui::Button* getButton() const { return _button; }
    bool isHovered() const { return _hoverState; }

    void showTooltip();
    void hideTooltip();

    void setEnabled(bool enable);
protected:
    virtual bool init(const std::string& iconPath, const std::string& tooltipText);
    void setupMouseEvents();

private:
    cocos2d::ui::Button* _button = nullptr;
    cocos2d::Label* _tooltipLabel = nullptr;

    bool _hoverState = false;

    std::function<void()> _clickCallback = nullptr;
    std::function<void(bool)> _hoverCallback = nullptr;

};
