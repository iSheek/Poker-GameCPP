#include "ServerManager.h"
#include "HumanPlayerLogic.h"
#include "NetworkInputHandler.h"

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
	auto pOutputHandler = std::make_shared<NetworkOutputHandler>(this->playerNodes);

	this->manager.setPOutputHandler(pOutputHandler);

	for (const auto& node : this->playerNodes)
	{
		auto pInputHandler = std::make_shared<NetworkInputHandler>(node.socket);
		auto pPlayer = std::make_shared<HumanPlayerLogic>(startingChips, pInputHandler);

		pPlayer->setPlayerName(node.playerInfo.name);

		this->manager.addPlayer(pPlayer);
	}

	while (true)
	{
		this->manager.playRound();
	}
}
