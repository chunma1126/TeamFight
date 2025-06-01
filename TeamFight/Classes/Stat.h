#pragma once
#include <Action.h>

enum class STAT_TYPE
{
    ATK,
    DEF,
    SPD,
    HP,
    END
};

class Stat
{
public:
    Stat();
    Stat(float value);

    float getValue() const;
    void setValue(float value);
    void addStat(float value);
    void removeStat(float value);
    void addOnChangeValueEvent(std::function<void(float)> callback);
    void removeOnChangeValueEvent(std::function<void(float)> callback);

private:
    float _value;
    float _amountValue;
    Action<float> _onChangeValueEvent;
};

