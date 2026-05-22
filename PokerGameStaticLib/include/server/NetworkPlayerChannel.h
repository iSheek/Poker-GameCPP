/**
 * @file NetworkPlayerChannel.h
 * @brief File containing declaration of NetworkPlayerChannel class
 */
#pragma once


#include "IPlayerChannel.h"
#include "PlayerNode.h"
#include "TableState.h"
#include "PlayerAction.h"
#include "PlayerState.h"
#include "Cards.h"
#include <boost/asio.hpp>
#include <memory>

 /**
  * @brief Class handling input and output from and to server
  *
  * @details This class uses tcp sockets from Boost.Asio for sending informations from the users to the server
  */

class NetworkPlayerChannel : public IPlayerChannel
{
private:
	std::shared_ptr<boost::asio::ip::tcp::socket> pSocket{};	///< tcp socket from Boost.Asio

	/**
	* @brief Private method that sends data to player
	*
	* @param[in] serializedData serialized data from nlohmann::json
	*/
	void sendStringToSocket(std::string_view serializedData);

public:

	/**
	* @brief Constructor for NetworkPlayerChannel
	* @param[in] pSocket shared_ptr to tcp socket
	*/
	NetworkPlayerChannel(std::shared_ptr<boost::asio::ip::tcp::socket> pSocket) : pSocket(pSocket) {}

	/**
	 * @copydoc IInputHandler::requestAction(const TableState& tableState, const PlayerState& playerState)
	 *
	 */
	PlayerAction requestAction(const TableState& tableState, const PlayerState& playerState) override;

	/**
	 * @copydoc IInputHandler::onPlayersCardDealt(const Card& card)
	 *
	 */
	void onPlayersCardDealt(const Card& card) override;



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