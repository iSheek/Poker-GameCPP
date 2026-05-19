#pragma once

/**
 * @file ClientNetworkManager.h
 * @brief File containing declaration of ClientNetworkManager class
 */


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
#include <string_view>
#include <vector>

//TODO : IMPLEMENT BETTER EXCEPTION HANDLING



/**
* @brief Class managing connection from client to the server.
*
* @details This class is used to connect to the server, send and receive jsons to/from server
* and handling connection using socket from Boost.Asio.
*/
class ClientNetworkManager
{
private:
	boost::asio::ip::tcp::socket socket;	///< socket from Boost.Asio for connecting to the server

	std::shared_ptr<IOutputHandler> pOutputHandler{};	///< pointer to the handler responsible for outputting
	std::shared_ptr<IInputHandler> pInputHandler{};		///< pointer to the handler responsible for inputting

	boost::asio::streambuf receiveBuffer{};				///< buffer responsible for receiving data from the server

	bool isConnected{ false };							///< boolean for checking whether we are successfully connected to the server

public:

	/**
	 * @brief Constructs the ClientNetworkManager.
	 *
	 * @param io_context Reference to the Boost Asio IO context
	 * @param output Pointer to the handler managing UI/console output
	 * @param input Pointer to the handler managing user input
	 */
	ClientNetworkManager(
		boost::asio::io_context& io_context,
		std::shared_ptr<IOutputHandler> output,
		std::shared_ptr<IInputHandler> input) : socket(io_context), pOutputHandler(output),
		pInputHandler(input)
	{}

	/**
	 * @brief Handles the incoming command to render the current table state.
	 *
	 * @details Extracts public player information and table state from the received json
	 * JSON payload, then passes it to the output handler for rendering.
	 *
	 * @param jReceived The JSON object containing the "data" payload with "publicPlayersInfo" and "tableState".
	 */
	void handleRenderTable(const nlohmann::json& jReceived);

	/**
	 * @brief Processes a notification about a specific player's action.
	 *
	 * @details Extracts the player's name and their corresponding action from the
	 * JSON payload, and updates the output handler.
	 *
	 * @param jReceived The JSON object containing "playerName" and "playerAction".
	 */
	void handleOnPlayerAction(const nlohmann::json& jReceived);


	/**
	 * @brief Handles the event when a new community card is dealt on the table.
	 *
	 * @param jReceived The JSON object containing the newly dealt "card".
	 */
	void handleOnCommunityCardDealt(const nlohmann::json& jReceived);

	/**
	 * @brief Handles the server's request for the local player to make an action.
	 *
	 * @details Extracts the current table and player state, prompts the input handler
	 * for the player's decision, and sends the serialized action back to the server.
	 *
	 * @param jReceived The JSON object containing "tableState" and "playerState".
	 */
	void handleRequestAction(const nlohmann::json& jReceived);

	/**
	 * @brief Processes the showdown phase at the end of a round.
	 *
	 * @details Extracts the winners, the winning hand evaluation, and the total pot
	 * amount, then passes this data to the output handler to display the results.
	 *
	 * @param jReceived The JSON object containing "winnerNames", "winningHand", and "pot".
	 */
	void handleOnShowdown(const nlohmann::json& jReceived);

	/**
	 * @brief The main network listening loop for the client.
	 *
	 * @details Continuously waits for and reads incoming messages from the server over
	 * the socket. It parses each message as JSON, determines the NetworkCommand method,
	 * and routes the payload to the appropriate handler function.
	 */
	void runLoop();

	/**
	 * @brief Attempts to establish a connection to the remote poker server.
	 *
	 * @details Uses Boost.Asio to connect to the specified IP address and port.
	 * Upon a successful connection, it serializes and sends the player's initial
	 * public information (such as their nickname) to the server.
	 *
	 * @param ipAddress The IP address of the target server.
	 * @param port The port number of the target server.
	 * @param nickname The chosen display name for the local player.
	 */
	void tryToConnectToServer(std::string_view ipAddress, const int& port, std::string_view nickname);

};