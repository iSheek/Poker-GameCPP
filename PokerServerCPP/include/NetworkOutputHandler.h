#pragma once

#include "IOutputHandler.h"
#include "PlayerNode.h"
#include <nlohmann/json.hpp>
#include <string>
#include <string_view>



class NetworkOutputHandler : public IOutputHandler
{
private:
	const std::vector<PlayerNode>& playersNodesRef;

	void sendStringToAllSockets(std::string_view serializedData);

public:
	NetworkOutputHandler(const std::vector<PlayerNode>& players) : 
		playersNodesRef(players) {}

	void onCommunityCardDealt(const Card& card) override;
	void onPlayerAction(std::string_view playerName, const PlayerAction& action) override;
	void onShowdown(const std::vector<std::string>& winnerNames, const HandScore& winningHand, const unsigned int& pot) override;
	void renderTable(const TableState& tableState, const std::vector<PublicPlayerInfo>& publicPlayersInfo) override;
	~NetworkOutputHandler() = default;
};