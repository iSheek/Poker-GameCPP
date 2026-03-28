#pragma once

#include "PlayerNode.h"
#include "TexasHoldemManager.h"
#include "NetworkOutputHandler.h"
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>
#include <string>


using json = nlohmann::json;

class ServerManager
{
private:
	TexasHoldemManager manager;
	std::vector<PlayerNode> playerNodes;
	unsigned int playerCount;


	std::string ipAddress;
	unsigned int port;

	boost::asio::io_context io_context;
	boost::asio::ip::tcp::acceptor acceptor;
public:
	ServerManager(unsigned int playerCount, std::string ipAddress, unsigned int port) :
		playerCount(playerCount),
		ipAddress(ipAddress),
		port(port),
		acceptor(io_context, tcp::endpoint(tcp::v4(), port)),
		manager(nullptr) {}

	void acceptPlayers();

	void startGame(unsigned int startingChips);

};
