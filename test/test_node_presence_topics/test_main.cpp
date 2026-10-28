#include <catch2/catch_test_macros.hpp>

#include "domain/NodePresenceTopics.h"

TEST_CASE("status topic is <prefix>/<id>/status")
{
    REQUIRE(NodePresenceTopics("panel", 5).statusTopic() == "panel/5/status");
}

TEST_CASE("mac topic is <prefix>/<id>/mac")
{
    REQUIRE(NodePresenceTopics("panel", 5).macTopic() == "panel/5/mac");
}

TEST_CASE("identify topic is <prefix>/<id>/identify")
{
    REQUIRE(NodePresenceTopics("panel", 42).identifyTopic() == "panel/42/identify");
}

TEST_CASE("a multi-segment prefix is kept as given")
{
    REQUIRE(NodePresenceTopics("mcs/turnout", 3).statusTopic() == "mcs/turnout/3/status");
}
