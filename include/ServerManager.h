#pragma once

#include "PlayerNode.h"
#include "TexasHoldemManager.h"
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
		acceptor(io_context, tcp::endpoint(tcp::v4(), port)) 
	{
		// TODO: change nullptr to NetworkOutputHandler
		this->manager = TexasHoldemManager(nullptr);
	}

	void acceptPlayers()
	{
		std::cout << "Waiting for players...\n";

		while (this->playerNodes.size() < this->playerCount)
		{
			std::shared_ptr<tcp::socket> pSocket = 
				std::make_shared<tcp::socket>(this->io_context);

			boost::system::error_code error;

			this->acceptor.accept(*pSocket, error);
			if (error)
			{
				std::cout << "ERROR: " << error.message() << '\n';
				continue;
			}

			PlayerNode playerNode;
			playerNode.socket = pSocket;


			boost::asio::streambuf receiveBuffer;
			boost::asio::read_until(*pSocket, receiveBuffer, '\n', error);
			if (error)
			{
				std::cout << "ERROR: " << error.message() << '\n';
				continue;
			}

			std::istream is(&receiveBuffer);
			std::string message;
			std::getline(is, message);

			try {
				json jReceived = json::parse(message);

				playerNode.playerInfo = jReceived.get<PublicPlayerInfo>();
			}
			catch (const std::exception& e)
			{
				std::cout << "ERROR: " << e.what() << '\n';
				continue;
			}
			this->playerNodes.push_back(playerNode);

			std::cout << "Waiting for players " << this->playerNodes.size()
				<< "/" << playerCount << std::endl;
		}


	}

};
