#pragma once

/**
 * @file GameSettings.h
 * @brief File containing declaration of GameSettings struct
 */

#include <string>

/**
 * @brief A structure holding all the configuration data required to initialize a game session.
 * @details This struct is populated by the menu settings based on user input and passed
 * to the GameApplication to set up a local single-player game, host a multiplayer server,
 * or connect as a client.
 */
struct GameSettings
{
	bool isMultiplayer{false};	///< True if the game is a multiplayer session, false for single-player.
	bool isHost{ false };		///< True if the local application is acting as the host/server.
	std::string nickname{};		///< The chosen display name of the local player.
	std::string ipAddress{};	///< The target IPv4 address for joining a multiplayer game.
	int port{};					///< The network port used for hosting or connecting to a game.
	int startingChips{};		///< The initial amount of chips every player receives at the start.
	int playerCount{};			///< The total number of players (humans and bots) in the session.

	/**
	 * @brief Overloaded equality operator to compare two GameSettings instances.
	 * @param a The first GameSettings object to compare.
	 * @param b The second GameSettings object to compare.
	 * @return True if all member variables of both objects are strictly equal, false otherwise.
	 */
	friend bool operator==(const GameSettings& a, const GameSettings& b) {
		if (a.isMultiplayer == b.isMultiplayer
			&& a.isHost == b.isHost
			&& a.nickname == b.nickname
			&& a.ipAddress == b.ipAddress
			&& a.port == b.port
			&& a.startingChips == b.startingChips
			&& a.playerCount == b.playerCount)
		{
			return true;
		}
		return false;
	}
};