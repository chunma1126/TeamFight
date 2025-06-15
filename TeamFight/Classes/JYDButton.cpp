#include "JYDButton.h"
#include "Enum.h"

USING_NS_CC;
using namespace ui;

JYDButton* JYDButton::create(const std::string& iconPath, const std::string& tooltipText)
{
    JYDButton* ret = new (std::nothrow) JYDButton();
    if (ret && ret->init(iconPath, tooltipText))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool JYDButton::init(const std::string& iconPath, const std::string& tooltipText)
{
    if (!Node::init())
        return false;

    auto texture = Director::getInstance()->getTextureCache()->addImage(iconPath);
    if (texture)
        texture->setAliasTexParameters();

    _button = Button::create();
    _button->loadTextureNormal(iconPath);
    this->addChild(_button);

    _tooltipLabel = Label::createWithTTF("", FONT_HEIROF_BOLD, 7);
    _tooltipLabel->setColor(Color3B::WHITE);
    _tooltipLabel->setVisible(false);
    _tooltipLabel->setAnchorPoint(Vec2(0.5f, 0));
    Director::getInstance()->getRunningScene()->addChild(_tooltipLabel,LAYER::UI + 101);
    
    _button->addClickEventListener([&](Ref* ref)
    {
        if (_clickCallback)
            _clickCallback();
    });

    setupMouseEvents();

    return true;
}

void JYDButton::setPosition(const Vec2& position)
{
    Node::setPosition(position);
    _tooltipLabel->setPosition({position.x , position.y + _button->getContentSize().height/2 + 20});
}

void JYDButton::setTooltipText(const std::string& text)
{
    if (_tooltipLabel)
    {
        _tooltipLabel->setString(text);
    }
}

void JYDButton::setTooltipColor(Color3B color)
{
    if (_tooltipLabel)
    {
        _tooltipLabel->setColor(color);
    }
}

void JYDButton::setIcon(const std::string& iconPath)
{
    if (_button)
    {
        auto texture = Director::getInstance()->getTextureCache()->addImage(iconPath);
        if (texture)
            texture->setAliasTexParameters();

        _button->loadTextureNormal(iconPath);
    }
}

void JYDButton::setIcon(const std::string& iconPath, const std::string& iconName, float startX, float startY, float width, float height)
{
    auto texture = Director::getInstance()->getTextureCache()->addImage(iconPath);
    if (texture)
        texture->setAliasTexParameters();
    auto frame = SpriteFrame::createWithTexture(texture, Rect(startX, startY, width, height));
    SpriteFrameCache::getInstance()->addSpriteFrame(frame, iconName);

    _button->loadTextureNormal(iconName, Widget::TextureResType::PLIST);
}


void JYDButton::setClickCallback(const std::function<void()>& callback)
{
    hideTooltip();
    _clickCallback = callback;
}

void JYDButton::setHoverCallback(const std::function<void(bool)>& callback)
{
    _hoverCallback = callback;
}

void JYDButton::showTooltip()
{
    _tooltipLabel->setVisible(true);
}

void JYDButton::hideTooltip()
{
    _tooltipLabel->setVisible(false);
}

void JYDButton::setupMouseEvents()
{
    auto listener = EventListenerMouse::create();
    listener->onMouseMove = [=](Event* event)
    {
        if (this->isVisible() == false) {
            hideTooltip();
            return;
        }
        
        EventMouse* mouseEvent = static_cast<EventMouse*>(event);
        Vec2 locationInNode = this->convertToNodeSpace(mouseEvent->getLocationInView());
        Rect bounds = _button->getBoundingBox();

        bool isInside = bounds.containsPoint(locationInNode);
        if (isInside && !_hoverState)
        {
            _hoverState = true;
            showTooltip();
            if (_hoverCallback)
                _hoverCallback(true);
        }
        else if (!isInside && _hoverState)
        {
            _hoverState = false;
            hideTooltip();
            if (_hoverCallback) 
                _hoverCallback(false);
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
