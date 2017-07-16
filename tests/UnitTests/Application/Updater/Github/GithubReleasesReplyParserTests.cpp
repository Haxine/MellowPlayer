#include <catch.hpp>
#include <MellowPlayer/Application/Updater/Github/GithubReleasesReplyParser.hpp>
#include <QtTest/QSignalSpy>
#include "Utils/Helpers.hpp"

using namespace MellowPlayer::Application;

SCENARIO("parse github reply") {
    GIVEN("a reply parser and a spy object") {
        GithubReleasesReplyParser parser;
        QSignalSpy spy(&parser, &GithubReleasesReplyParser::ready);
        REQUIRE(spy.count() == 0);

        WHEN("parsing a valid github releases reply data without stopping") {
            parser.parse(getValidReplyData());

            THEN("ready signal has been called 26 times") {
                REQUIRE(spy.count() == 26);
            }
        }

        WHEN("parsing a valid github releases reply data and stopping after the third release") {
            int count = 0;
            QObject::connect(&parser, &GithubReleasesReplyParser::ready, [&]() {
                ++count;
                if (count == 3)
                    parser.stop();
            });
            parser.parse(getValidReplyData());

            THEN("ready signal has been called 3 times") {
                REQUIRE(spy.count() == 3);
            }
        }
    }
}

