#pragma once

/**
 * @file ServerManager.h
 * @brief File containing declaration of ServerManager class
 */

#include "PlayerNode.h"
#include "TexasHoldemManager.h"
#include "NetworkOutputHandler.h"
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>
#include <string>


using json = nlohmann::json;

/**
 * @brief Class representing the main manager of the game for server
 * 
 * @details This class' role is to prepare for the connection of the player and after everyone are connected, 
 *	letting the TexasHoldemManager object to handle the game
 */
class ServerManager
{
private:
	TexasHoldemManager manager;					///< manager of the game 
	std::vector<PlayerNode> playerNodes{};		///< vector containing socket and info from every player
	int playerCount{};							///< number of players
	std::string ipAddress{};					///< ip address used for connecting to the server
	int port{};									///< port used for connecting to the server
	boost::asio::io_context io_context;			///< context from Boost.Asio that allows for I/O operations
	boost::asio::ip::tcp::acceptor acceptor;	///< acceptor for TCP connection
public:

	/**
	* @brief Public constructor of ServerManager
	* 
	* @param[in] playerCount amount of players that will be connected
	* @param[in] ipAddress ipv4 address of the server
	* @param[in] port server's port
	*/
	ServerManager(int playerCount, std::string ipAddress, int port) :
		playerCount(playerCount),
		ipAddress(ipAddress),
		port(port),
		acceptor(io_context, tcp::endpoint(tcp::v4(), port)),
		manager(nullptr) {}

	/**
	* @brief Method that starts accepting players to the server
	* 
	* @details After invoking it accepts players sockets and keeps doing it as long 
	* as amount of players connected equals to playerCount variable
	* 
	*/
	void acceptPlayers();

	/**
	* @brief Method that sets everything up for game manager
	* 
	* @details It prepares every node for each player and adds every player to the TexasHoldemManager object
	* after that is done, the game starts and game manager is controlling the flow of the game
	* 
	*/
	void startGame(int startingChips);

};
