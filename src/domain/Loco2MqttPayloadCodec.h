#pragma once

#include <optional>
#include <string>

#include "domain/Loco2MqttPosition.h"

class Loco2MqttPayloadCodec
{
public:
    [[nodiscard]] std::string encode(const Loco2MqttPosition position) const
    {
        return position == Loco2MqttPosition::Closed ? "CLOSED" : "THROWN";
    }

    [[nodiscard]] std::optional<Loco2MqttPosition> decode(const std::string& payload) const
    {
        if (payload == "CLOSED")
        {
            return Loco2MqttPosition::Closed;
        }
        if (payload == "THROWN")
        {
            return Loco2MqttPosition::Thrown;
        }
        return std::nullopt;
    }
};
