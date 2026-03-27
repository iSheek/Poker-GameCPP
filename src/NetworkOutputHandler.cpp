#include "NetworkOutputHandler.h"
#include "NetworkCommands.h"
#include <nlohmann/json.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string_view>

using nlohmann::json;

void NetworkOutputHandler::sendStringToAllSockets(std::string_view serializedData)
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

	jSend["method"] = NetworkCommand::ON_COMMUNITY_CARD_DEALT;
	jSend["data"]["card"] = card;

	std::string serializedData = jSend.dump() + "\n";
	sendStringToAllSockets(serializedData);
}

void NetworkOutputHandler::onPlayerAction(std::string_view playerName, const PlayerAction& action)
{
	json jSend{};

	jSend["method"] = NetworkCommand::ON_PLAYER_ACTION;
	jSend["data"]["playerName"] = playerName;
	jSend["data"]["playerAction"] = action;

	std::string serializedData = jSend.dump() + "\n";
	sendStringToAllSockets(serializedData);
}

void NetworkOutputHandler::onShowdown(const std::vector<std::string>& winnerNames, const HandScore& winningHand, const unsigned int& pot)
{
	json jSend{};

	jSend["method"] = NetworkCommand::ON_SHOWDOWN;
	jSend["data"]["winnerNames"] = winnerNames;
	jSend["data"]["winningHand"] = winningHand;
	jSend["data"]["pot"] = pot;

	std::string serializedData = jSend.dump() + "\n";
	sendStringToAllSockets(serializedData);
}

void NetworkOutputHandler::renderTable(const TableState& tableState, const std::vector<PublicPlayerInfo>& publicPlayersInfo)
{
	json jSend{};

	jSend["method"] = NetworkCommand::RENDER_TABLE;
	jSend["data"]["tableState"] = tableState;
	jSend["data"]["publicPlayersInfo"] = publicPlayersInfo;

	std::string serializedData = jSend.dump() + "\n";
	sendStringToAllSockets(serializedData);
}
