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
	json j_send{};

	j_send["method"] = "onCommunityCardDealt";
	j_send["data"]["card"] = card;

	std::string serializedData = j_send.dump() + "\n";
	sendStringToAllSockets(serializedData);
}

void NetworkOutputHandler::onPlayerAction(const std::string& playerName, const PlayerAction& action)
{
	json j_send{};

	j_send["method"] = "onPlayerAction";
	j_send["data"]["playerName"] = playerName;
	j_send["data"]["playerAction"] = action;

	std::string serializedData = j_send.dump() + "\n";
	sendStringToAllSockets(serializedData);
}

void NetworkOutputHandler::onShowdown(const std::vector<std::string>& winnerNames, const HandScore& winningHand, const unsigned int& pot)
{
	json j_send{};

	j_send["method"] = "onShowdown";
	j_send["data"]["winnerNames"] = winnerNames;
	j_send["data"]["winningHand"] = winningHand;
	j_send["data"]["pot"] = pot;

	std::string serializedData = j_send.dump() + "\n";
	sendStringToAllSockets(serializedData);
}

void NetworkOutputHandler::renderTable(const TableState& tableState, const std::vector<PublicPlayerInfo>& publicPlayersInfo)
{
	json j_send{};

	j_send["method"] = "renderTable";
	j_send["data"]["tableState"] = tableState;
	j_send["data"]["publicPlayersInfo"] = publicPlayersInfo;

	std::string serializedData = j_send.dump() + "\n";
	sendStringToAllSockets(serializedData);
}
