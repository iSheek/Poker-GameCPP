#pragma once

/**
 * @file GameApplication.h
 * @brief File containing declaration of GameApplication class
 */


#include "IPlayerChannel.h"
#include "GameSettings.h"
#include "GameEndStatus.h"
#include <stop_token>
#include <string>
#include <memory>
#include <thread>


/**
 * @brief Class that handles starting and managing the game session based on desired settings.
 *
 * @details Responsible for initializing the core game managers, setting up the local player,
 * generating bots (for single-player), and handling server/client setup (for multiplayer).
 */
class GameApplication
{
private:
	std::string playerName{};									///< The chosen nickname for the main player
	std::shared_ptr<IPlayerChannel> pHandler{};					///< Pointer to the handler responsible for rendering output and capturing input
	std::unique_ptr<std::thread> pServerThread{};				///< Pointer to the thread running the server (used if this application is hosting)
	int startingChips{};										///< The initial amount of chips every player starts with
	int playerCount{};											///< Total number of players (humans + bots) in the game
	int port{};													///< Network port used for the multiplayer connection
	std::string ipAddress{};									///< Target IPv4 address for the multiplayer connection
	bool isHost{ false };										///< Indicates whether the local application is also hosting the server
	std::stop_token stopToken{};								///< stop token

public:

	
	/**
	 * @brief Constructs a GameApplication using GameSettings and custom I/O handlers.
	 * @details Useful for dependency injection, allowing custom logic for input/output (e.g., for GUI or testing).
	 * @param gameSettings A structure containing all setup parameters.
	 * @param pHandler Shared pointer to an initialized Input/Output Handler.
	 */
	GameApplication(GameSettings gameSettings, std::shared_ptr<IPlayerChannel> pHandler, std::stop_token stopToken = {}) :
		playerName(gameSettings.nickname), 
		pHandler(pHandler),
		startingChips(gameSettings.startingChips), 
		playerCount(gameSettings.playerCount), 
		port(gameSettings.port),
		ipAddress(gameSettings.ipAddress),
		isHost(gameSettings.isHost),
		stopToken(stopToken)
	{}

	/**
	 * @brief Starts a local single-player game.
	 * @details Initializes a local TexasHoldemManager, creates a human player and the requested
	 * number of bot players, and runs the local game loop until the player wins or runs out of chips.
	 */
	GameEndStatus startSingleplayer();

	/**
	 * @brief Starts a multiplayer game session.
	 * @details If the user chose to host, it spins up a ServerManager in a background thread.
	 * Afterward, it initializes a ClientNetworkManager to connect to the specified IP and port
	 * (either locally hosted or remote) and enters the network event loop.
	 */
	void startMultiplayer();

};