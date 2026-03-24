
#include "ClientNetworkManager.h"
#include "IInputHandler.h"
#include "IOutputHandler.h"
#include "NetworkCommands.h"
#include "HandScore.h"
#include "PlayerAction.h"
#include "PlayerState.h"
#include "TableState.h"
#include "PublicPlayerInfo.h"
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

void ClientNetworkManager::handleRenderTable(const nlohmann::json& jReceived)
{
	try
	{
		std::vector<PublicPlayerInfo> playersInfo = jReceived["data"]["publicPlayersInfo"].get<std::vector<PublicPlayerInfo>>();
		TableState state = jReceived["data"]["tableState"].get<TableState>();

		this->pOutputHandler->renderTable(state, playersInfo);
	}
	catch (const std::exception& e)
	{

	}
}

void ClientNetworkManager::handleOnPlayerAction(const nlohmann::json& jReceived)
{
	try
	{
		std::string playerName = jReceived["data"]["playerName"];
		PlayerAction playerAction = jReceived["data"]["playerAction"].get<PlayerAction>();

		this->pOutputHandler->onPlayerAction(playerName, playerAction);
	}
	catch (const std::exception& e)
	{

	}
}

void ClientNetworkManager::handleOnCommunityCardDealt(const nlohmann::json& jReceived)
{
	try
	{
		Card card = jReceived["data"]["card"].get<Card>();
		this->pOutputHandler->onCommunityCardDealt(card);
	}
	catch (const std::exception& e)
	{

	}

}

void ClientNetworkManager::handleRequestAction(const nlohmann::json& jReceived)
{
	try
	{
		TableState state = jReceived["data"]["tableState"].get<TableState>();
		PlayerState playerState = jReceived["data"]["playerState"].get<PlayerState>();

		PlayerAction actionToSend = this->pInputHandler->requestAction(state, playerState);


		nlohmann::json jRespond = actionToSend;

		std::string message = jRespond.dump() + '\n';

		boost::asio::write(this->socket, boost::asio::buffer(message));
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR: " << e.what() << "\n";
	}
}

void ClientNetworkManager::handleOnShowdown(const nlohmann::json& jReceived)
{
	try
	{
		std::vector<std::string> winnerNames = jReceived["data"]["winnerNames"].get<std::vector<std::string>>();
		HandScore winningHand = jReceived["data"]["winningHand"].get<HandScore>();
		unsigned int pot = jReceived["data"]["pot"].get<unsigned int>();

		this->pOutputHandler->onShowdown(winnerNames, winningHand, pot);
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR: " << e.what() << "\n";
	}
}


void ClientNetworkManager::runLoop()
{

	while (this->isConnected)
	{
		boost::system::error_code error;
		boost::asio::streambuf receiveBuffer;
		boost::asio::read_until(this->socket, receiveBuffer, '\n', error);

		if (error) break;

		std::istream is(&receiveBuffer);
		std::string message;

		std::getline(is, message);
		try
		{
			nlohmann::json jReceived = nlohmann::json::parse(message);

			NetworkCommand methodName = jReceived["method"].get<NetworkCommand>();

			// TODO: finish cases handlers
			switch (methodName)
			{
			case NetworkCommand::RENDER_TABLE:
				handleRenderTable(jReceived);
				break;
			case NetworkCommand::ON_PLAYER_ACTION:
				handleOnPlayerAction(jReceived);
				break;
			case NetworkCommand::ON_COMMUNITY_CARD_DEALT:
				handleOnCommunityCardDealt(jReceived);
				break;
			case NetworkCommand::REQUEST_ACTION:
				handleRequestAction(jReceived);
				break;
			case NetworkCommand::ON_SHOWDOWN:
				handleOnShowdown(jReceived);
				break;
			case NetworkCommand::UNKNOWN:
			default:
				break;
			}
		}
		catch (const std::exception& e)
		{
			std::cout << "ERROR: " << e.what() << "\n";
		}


	}
}

void ClientNetworkManager::tryToConnectToServer(const std::string& ipAddress, const int& port)
{
	boost::system::error_code error;

	this->socket.connect(boost::asio::ip::tcp::endpoint
	(boost::asio::ip::make_address(ipAddress), port), error);

	if (error)
	{
		std::cout << "ERROR: " << error.message() << "\n";
	}
	else
	{
		this->isConnected = true;
		
		PublicPlayerInfo playerInfo;
		playerInfo.name = "TEST";
		try
		{
			nlohmann::json jSend;

			jSend = playerInfo;
			std::string message = jSend.dump() + '\n';

			boost::asio::write(this->socket, boost::asio::buffer(message), error);
		}
		catch (const std::exception& e)
		{
			std::cout << "ERROR: " << e.what() << "\n";
		}
	}
}

