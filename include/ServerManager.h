#pragma once

#include <vector>
#include "PlayerNode.h"
#include "TexasHoldemManager.h"
#include <string>
#include <boost/asio.hpp>


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
		acceptor(io_context, tcp::endpoint(tcp::v4(), port)) 
	{
		// TODO: change nullptr to NetworkOutputHandler
		this->manager = TexasHoldemManager(nullptr);
	}

};
