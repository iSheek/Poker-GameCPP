/**
 * @file ServerManager.cpp
 * @brief File containing definition of ServerManager methods
 */
#include "ServerManager.h"
#include "HumanPlayerLogic.h"
#include "NetworkPlayerChannel.h"

void ServerManager::acceptPlayers()
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

			PublicPlayerInfo playerInfo = jReceived.get<PublicPlayerInfo>();
			playerNode.playerInfo = playerInfo;
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

void ServerManager::startGame(int startingChips)
{

	for (const auto& node : this->playerNodes)
	{
		auto pNetworkPlayerChannel = std::make_shared<NetworkPlayerChannel>(node.socket);
		auto pPlayer = std::make_shared<HumanPlayerLogic>(startingChips, pNetworkPlayerChannel);

		pPlayer->setPlayerName(node.playerInfo.name);

		this->manager.addPlayer(pPlayer);
		this->manager.addOutputHandler(pNetworkPlayerChannel);
	}

	while (true)
	{
		this->manager.playRound();
	}
}
