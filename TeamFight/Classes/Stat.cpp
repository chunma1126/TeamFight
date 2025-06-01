#include "Stat.h"

Stat::Stat() : _value(0.0f), _amountValue(0.0f)
{
}

Stat::Stat(float value) : _value(value), _amountValue(0.0f)
{
}

float Stat::getValue() const
{
    return _value + _amountValue;
}

void Stat::setValue(float value)
{
    _value = value;
}

void Stat::addStat(float value)
{
    _amountValue += value;
    _onChangeValueEvent.invoke(getValue());
}

void Stat::removeStat(float value)
{
    _amountValue = std::max(_amountValue - value, 0.0f);
    _onChangeValueEvent.invoke(getValue());
}

void Stat::addOnChangeValueEvent(std::function<void(float)> callback)
{
    _onChangeValueEvent.add(callback);
}

void Stat::removeOnChangeValueEvent(std::function<void(float)> callback)
{
    _onChangeValueEvent.remove(callback);
}