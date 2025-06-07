#pragma once
#include "Action.h"       

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

    const float getValue() const;
    void setValue(float value);
    void addStat(float value);
    void removeStat(float value);
public:
    ::Action<float> onChangeValueEvent;

private:
    float _value;
};

