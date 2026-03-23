#pragma once

#include "IInputHandler.h"
#include "IOutputHandler.h"
#include "NetworkCommands.h"
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <string>


class ClientNetworkManager
{
private:
	boost::asio::ip::tcp::socket socket;

	std::shared_ptr<IOutputHandler> pOutputHandler;
	std::shared_ptr<IInputHandler> pInputHandler;

public:
	ClientNetworkManager(
		boost::asio::io_context& io_context,
		std::shared_ptr<IOutputHandler> output,
		std::shared_ptr<IInputHandler> input) : socket(io_context), pOutputHandler(output),
		pInputHandler(input)
	{}

	void handleRenderTable(const nlohmann::json& jReceived)
	{
		
	}


	void runLoop()
	{	

		while (true)
		{
			boost::asio::streambuf receiveBuffer;
			boost::asio::read_until(this->socket, receiveBuffer, '\n');


			std::istream is(&receiveBuffer);
			std::string message;

			std::getline(is, message);

			nlohmann::json jReceived = nlohmann::json::parse(message);

			NetworkCommand methodName = jReceived["method"].get<NetworkCommand>();

			// TODO: finish cases handlers
			switch (methodName)
			{
			case NetworkCommand::RENDER_TABLE:
				
				break;
			case NetworkCommand::ON_PLAYER_ACTION:

				break;
			case NetworkCommand::ON_COMMUNITY_CARD_DEALT:

				break;
			case NetworkCommand::REQUEST_ACTION:

				break;
			case NetworkCommand::ON_SHOWDOWN:

				break;
			case NetworkCommand::UNKNOWN:
			default:
				break;
			}


		}
	}

	void tryToConnectToServer(const std::string& ipAddress, const int& port)
	{
		boost::system::error_code error;

		this->socket.connect(boost::asio::ip::tcp::endpoint
		(boost::asio::ip::make_address(ipAddress), port), error);

		if (error)
		{
			std::cout << "ERROR: " << error.message() << "\n";
		}
	}

	


};