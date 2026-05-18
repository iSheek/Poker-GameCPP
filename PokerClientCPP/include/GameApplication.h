#pragma once

/**
 * @file GameApplication.h
 * @brief File containing declaration of GameApplication class
 */


#include "IOutputHandler.h"
#include "IInputHandler.h"
#include "GameSettings.h"
#include "ConsoleOutputHandler.h"
#include "ConsoleInputHandler.h"

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
	std::string playerName{};						///< The chosen nickname for the main player
	std::shared_ptr<IOutputHandler> pOutput{};		///< Pointer to the handler responsible for rendering output
	std::shared_ptr<IInputHandler> pInput{};		///< Pointer to the handler responsible for capturing input
	std::unique_ptr<std::thread> pServerThread{};	///< Pointer to the thread running the server (used if this application is hosting)
	int startingChips{};							///< The initial amount of chips every player starts with
	int playerCount{};								///< Total number of players (humans + bots) in the game
	int port{};										///< Network port used for the multiplayer connection
	std::string ipAddress{};						///< Target IPv4 address for the multiplayer connection
	bool isHost{ false };							///< Indicates whether the local application is also hosting the server

public:
	/**
	 * @brief Default constructor for GameApplication.
	 */
	GameApplication() = default;

	/**
	 * @brief Constructs a GameApplication using the provided GameSettings.
	 * @details Automatically initializes the input and output handlers with standard console implementations.
	 * @param gameSettings A structure containing all setup parameters (nickname, ip, port, chips, etc.).
	 */
	GameApplication(GameSettings gameSettings) : 
		playerName(gameSettings.nickname), 
		ipAddress(gameSettings.ipAddress), 
		startingChips(gameSettings.startingChips), 
		playerCount(gameSettings.playerCount), 
		port(gameSettings.port), 
		isHost(gameSettings.isHost),
		pOutput(std::make_shared<ConsoleOutputHandler>()), 
		pInput(std::make_shared<ConsoleInputHandler>()) 
	{}
	
	/**
	 * @brief Constructs a GameApplication using GameSettings and custom I/O handlers.
	 * @details Useful for dependency injection, allowing custom logic for input/output (e.g., for GUI or testing).
	 * @param gameSettings A structure containing all setup parameters.
	 * @param pOutput Shared pointer to an initialized Output Handler.
	 * @param pInput Shared pointer to an initialized Input Handler.
	 */
	GameApplication(GameSettings gameSettings, std::shared_ptr<IOutputHandler> pOutput, std::shared_ptr<IInputHandler> pInput) : 
		playerName(gameSettings.nickname), 
		isHost(gameSettings.isHost), 
		ipAddress(gameSettings.ipAddress),
		startingChips(gameSettings.startingChips), 
		playerCount(gameSettings.playerCount), 
		port(gameSettings.port),
		pOutput(pOutput), 
		pInput(pInput) 
	{}

	/**
	 * @brief Starts a local single-player game.
	 * @details Initializes a local TexasHoldemManager, creates a human player and the requested
	 * number of bot players, and runs the local game loop until the player wins or runs out of chips.
	 */
	void startSingleplayer();

	/**
	 * @brief Starts a multiplayer game session.
	 * @details If the user chose to host, it spins up a ServerManager in a detached background thread.
	 * Afterward, it initializes a ClientNetworkManager to connect to the specified IP and port
	 * (either locally hosted or remote) and enters the network event loop.
	 */
	void startMultiplayer();

};