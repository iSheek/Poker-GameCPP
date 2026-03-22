#include "NetworkOutputHandler.h"
#include <nlohmann/json.hpp>
#include <boost/asio.hpp>
#include <iostream>

using nlohmann::json;

void NetworkOutputHandler::sendStringToAllSockets(const std::string& serializedData)
{
	for (auto const& playerNode : this->playersNodesRef)
	{
		boost::system::error_code error;
		boost::asio::write(*playerNode.socket, boost::asio::buffer(serializedData), error);
		if (error) std::cout << "ERROR: " << error.message() << "\n";
	}
}

void NetworkOutputHandler::onCommunityCardDealt(const Card& card)
{
	json jSend{};

	jSend["method"] = "onCommunityCardDealt";
	jSend["data"]["card"] = card;

	std::string serializedData = jSend.dump() + "\n";
	sendStringToAllSockets(serializedData);
}

void NetworkOutputHandler::onPlayerAction(const std::string& playerName, const PlayerAction& action)
{
	json jSend{};

	jSend["method"] = "onPlayerAction";
	jSend["data"]["playerName"] = playerName;
	jSend["data"]["playerAction"] = action;

	std::string serializedData = jSend.dump() + "\n";
	sendStringToAllSockets(serializedData);
}

void NetworkOutputHandler::onShowdown(const std::vector<std::string>& winnerNames, const HandScore& winningHand, const unsigned int& pot)
{
	json jSend{};

	jSend["method"] = "onShowdown";
	jSend["data"]["winnerNames"] = winnerNames;
	jSend["data"]["winningHand"] = winningHand;
	jSend["data"]["pot"] = pot;

	std::string serializedData = jSend.dump() + "\n";
	sendStringToAllSockets(serializedData);
}

void NetworkOutputHandler::renderTable(const TableState& tableState, const std::vector<PublicPlayerInfo>& publicPlayersInfo)
{
	json jSend{};

	jSend["method"] = "renderTable";
	jSend["data"]["tableState"] = tableState;
	jSend["data"]["publicPlayersInfo"] = publicPlayersInfo;

	std::string serializedData = jSend.dump() + "\n";
	sendStringToAllSockets(serializedData);
}
