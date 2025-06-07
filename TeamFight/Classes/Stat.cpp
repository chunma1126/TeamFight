#include "Stat.h"

Stat::Stat() : _value(0.0f)
{
}

Stat::Stat(float value) : _value(value)
{
}

const float Stat::getValue() const
{
    return _value;
}

void Stat::setValue(float value)
{
    _value = value;
}

void Stat::addStat(float value)
{
    _value += value;
    onChangeValueEvent.invoke(getValue());
}

void Stat::removeStat(float value)
{
    _value = std::max(_value - value, 0.0f);
    onChangeValueEvent.invoke(getValue());
}