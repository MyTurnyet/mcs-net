#pragma once

#include "domain/Loco2MqttPosition.h"

struct Loco2MqttStateUpdate
{
    int channel;
    Loco2MqttPosition position;
};
