#pragma once

#include <string>

#include "domain/NodePresenceTopics.h"
#include "ports/Clock.h"
#include "ports/MqttTransport.h"

// Publishes "online" and this node's MAC (never retained) when the broker
// connection comes up and then every kHeartbeatIntervalMs, so two nodes
// sharing an id can each see the other's MAC.
class NodePresenceAnnouncer
{
public:
    static constexpr unsigned long kHeartbeatIntervalMs = 30000;

    NodePresenceAnnouncer(MqttTransport& transport, Clock& clock, NodePresenceTopics topics, std::string ownMac);

    void update(bool currentlyConnected);

private:
    [[nodiscard]] bool announcementDue() const;
    void announce();

    MqttTransport& transport_;
    Clock& clock_;
    NodePresenceTopics topics_;
    std::string ownMac_;
    bool wasConnected_ = false;
    unsigned long lastAnnouncedAtMs_ = 0;
};
