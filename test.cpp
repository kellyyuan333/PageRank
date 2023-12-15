#include "main.cpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#define private public

using namespace std;

TEST_CASE("Test 1", "[flag]") //One line
{
	AdjacencyList graph;
    ostringstream oss;
    vector<string> fromValues;
    fromValues.push_back("youtube.com");
    vector<string> toValues;
    toValues.push_back("twitch.com");
	graph.insert(fromValues, toValues, 1);
	graph.pageRank(2, oss);
	REQUIRE(oss.str() == "twitch.com 0.50\nyoutube.com 0.00\n");
}

TEST_CASE("Test 2", "[flag]") //p = 1
{
	AdjacencyList graph;
    ostringstream oss;
    vector<string> fromValues;
    fromValues.push_back("yahoo.com");
    fromValues.push_back("spotify.com");
    fromValues.push_back("slack.com");
    fromValues.push_back("hotmail.com");
    vector<string> toValues;
    toValues.push_back("hotmail.com");
    toValues.push_back("yahoo.com");
    toValues.push_back("spotify.com");
    toValues.push_back("slack.com");
    graph.insert(fromValues, toValues, 4);
    graph.pageRank(1, oss);
    REQUIRE(oss.str() == "hotmail.com 0.25\nslack.com 0.25\nspotify.com 0.25\nyahoo.com 0.25\n");
}

TEST_CASE("Test 3", "[flag]") //URL not pointing to any other URLs (amazon.com)
{
	AdjacencyList graph;
    ostringstream oss;
    vector<string> fromValues;
    fromValues.push_back("disney.com");
    fromValues.push_back("discord.com");
    fromValues.push_back("stackoverflow.com");
    fromValues.push_back("symbolab.com");
    fromValues.push_back("discord.com");
    vector<string> toValues;
    toValues.push_back("amazon.com");
    toValues.push_back("disney.com");
    toValues.push_back("amazon.com");
    toValues.push_back("discord.com");
    toValues.push_back("stackoverflow.com");
    graph.insert(fromValues, toValues, 5);
    graph.pageRank(2, oss);
    REQUIRE(oss.str() == "amazon.com 0.40\ndiscord.com 0.20\ndisney.com 0.10\nstackoverflow.com 0.10\nsymbolab.com 0.00\n");
}

TEST_CASE("Test 4", "[flag]") //URL with no other URLs pointing to it (zybooks.com)
{
	AdjacencyList graph;
    ostringstream oss;
    vector<string> fromValues;
    fromValues.push_back("textcompare.com");
    fromValues.push_back("schoology.com");
    fromValues.push_back("zoom.com");
    fromValues.push_back("nitrotype.com");
    fromValues.push_back("nitrotype.com");
    fromValues.push_back("zybooks.com");
    vector<string> toValues;
    toValues.push_back("nitrotype.com");
    toValues.push_back("textcompare.com");
    toValues.push_back("schoology.com");
    toValues.push_back("zoom.com");
    toValues.push_back("schoology.com");
    toValues.push_back("zoom.com");
    graph.insert(fromValues, toValues, 6);
    graph.pageRank(3, oss);
    REQUIRE(oss.str() == "nitrotype.com 0.20\nschoology.com 0.40\ntextcompare.com 0.30\nzoom.com 0.10\nzybooks.com 0.00\n");
}

TEST_CASE("Test 5", "[flag]") //randomly generated (from https://chasemooncheese.github.io/Project2Tester/)
{
	AdjacencyList graph;
    ostringstream oss;
    vector<string> fromValues;
    fromValues.push_back("python.org");
    fromValues.push_back("google.com");
    fromValues.push_back("google.com");
    fromValues.push_back("apple.com");
    fromValues.push_back("apple.com");
    fromValues.push_back("pcbuildinguf.com");
    fromValues.push_back("apple.com");
    fromValues.push_back("apple.com");
    fromValues.push_back("python.org");
    fromValues.push_back("apple.com");
    fromValues.push_back("github.com");
    fromValues.push_back("pcbuildinguf.com");
    vector<string> toValues;
    toValues.push_back("pcbuildinguf.com");
    toValues.push_back("pcbuildinguf.com");
    toValues.push_back("apple.com");
    toValues.push_back("python.org");
    toValues.push_back("pcbuildinguf.com");
    toValues.push_back("google.com");
    toValues.push_back("twitter.com");
    toValues.push_back("github.com");
    toValues.push_back("twitter.com");
    toValues.push_back("google.com");
    toValues.push_back("pcbuildinguf.com");
    toValues.push_back("python.org");
    graph.insert(fromValues, toValues, 12);
    graph.pageRank(17, oss);
    REQUIRE(oss.str() == "apple.com 0.01\ngithub.com 0.00\ngoogle.com 0.02\npcbuildinguf.com 0.02\npython.org 0.02\ntwitter.com 0.01\n");
}