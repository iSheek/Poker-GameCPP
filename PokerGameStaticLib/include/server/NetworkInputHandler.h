#pragma once

/**
 * @file NetworkInputHandler.h
 * @brief File containing declaration of NetworkInputHandler class
 */


#include "IInputHandler.h"
#include "TableState.h"
#include "PlayerAction.h"
#include "PlayerState.h"
#include "Cards.h"
#include <boost/asio.hpp>
#include <memory>

/**
 * @brief Class handling input from the clients to the server
 * 
 * @details This class uses tcp sockets from Boost.Asio for sending informations from the users to the server
 */

class NetworkInputHandler : public IInputHandler
{
private:
	std::shared_ptr<boost::asio::ip::tcp::socket> pSocket{};	///< tcp socket from Boost.Asio

public:

	/**
	* @brief Constructor for NetworkInputHandler
	* @param[in] pSocket shared_ptr to tcp socket
	*/
	NetworkInputHandler(std::shared_ptr<boost::asio::ip::tcp::socket> pSocket) : pSocket(pSocket) {}
	
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
};