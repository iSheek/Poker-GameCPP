#pragma once

/**
 * @file NetworkOutputHandler.h
 * @brief File containing declaration of NetworkOutputHandler class
 */

#include "IOutputHandler.h"
#include "PlayerNode.h"
#include <nlohmann/json.hpp>
#include <string>
#include <string_view>

 /**
  * @brief Class handling output from the server to the client
  *
  * @details This class uses information from the server to output informations to the client
  */
class NetworkOutputHandler : public IOutputHandler
{
private:
	const std::vector<PlayerNode>& playersNodesRef{};	///< reference to vector containing public info about all players and their tcp::socket


	/**
	* @brief Private method that sends data to all connected players
	* 
	* @param[in] serializedData serialized data from using nlohmann::json to send to all players
	*/
	void sendStringToAllSockets(std::string_view serializedData);

public:
	/**
	* @brief Public constructor for NetworkOutputHandler
	*
	* @param[in] players reference to vector containing PlayerNode objects
	*/
	NetworkOutputHandler(const std::vector<PlayerNode>& players) : 
		playersNodesRef(players) {}

	/**
	 * @copydoc IOutputHandler::onCommunityCardDealt(const Card& card)
	 *
	 */
	void onCommunityCardDealt(const Card& card) override;
	
	/**
	 * @copydoc IOutputHandler::onPlayerAction(const std::string& playerName, const PlayerAction& action)
	 *
	 */
	void onPlayerAction(const std::string& playerName, const PlayerAction& action) override;
	
	/**
	 * @copydoc IOutputHandler::onShowdown(const std::vector<std::string>& winnerNames, const HandScore& winningHand, const int& pot)
	 *
	 */
	void onShowdown(const std::vector<std::string>& winnerNames, const HandScore& winningHand, const int& pot) override;
	
	/**
	 * @copydoc IOutputHandler::renderTable(const TableState& tableState, const std::vector<PublicPlayerInfo>& publicPlayersInfo)
	 *
	 */
	void renderTable(const TableState& tableState, const std::vector<PublicPlayerInfo>& publicPlayersInfo) override;
	
};