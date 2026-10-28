#include "application/NodePresenceAnnouncer.h"

#include <utility>

NodePresenceAnnouncer::NodePresenceAnnouncer(MqttTransport& transport, Clock& clock, NodePresenceTopics topics,
                                              std::string ownMac)
    : transport_(transport), clock_(clock), topics_(std::move(topics)), ownMac_(std::move(ownMac))
{
}

void NodePresenceAnnouncer::update(const bool currentlyConnected)
{
    if (currentlyConnected && announcementDue())
    {
        announce();
    }
    wasConnected_ = currentlyConnected;
}

bool NodePresenceAnnouncer::announcementDue() const
{
    const bool justConnected = !wasConnected_;
    const bool heartbeatDue = clock_.nowMilliseconds() - lastAnnouncedAtMs_ >= kHeartbeatIntervalMs;
    return justConnected || heartbeatDue;
}

void NodePresenceAnnouncer::announce()
{
    transport_.publish(topics_.statusTopic(), "online", false);
    transport_.publish(topics_.macTopic(), ownMac_, false);
    lastAnnouncedAtMs_ = clock_.nowMilliseconds();
}
