#pragma once

#include <string>
#include <utility>

// Topics one node uses to announce itself: <prefix>/<nodeId>/status|mac|identify.
// Each project picks its own prefix ("panel", "mcs/turnout", ...).
class NodePresenceTopics
{
public:
    NodePresenceTopics(std::string prefix, const int nodeId)
        : base_(std::move(prefix) + "/" + std::to_string(nodeId) + "/")
    {
    }

    [[nodiscard]] std::string statusTopic() const
    {
        return base_ + "status";
    }

    [[nodiscard]] std::string macTopic() const
    {
        return base_ + "mac";
    }

    [[nodiscard]] std::string identifyTopic() const
    {
        return base_ + "identify";
    }

private:
    std::string base_;
};
