#pragma once

/**
 * @file MenuChoice.h
 * @brief File containing declaration of MenuChoice structure
 */

/**
 * @enum MenuChoice
 * @brief Represents the available options in the game's main menu.
 * @details Used by the menu controllers and views to handle user navigation
 * and determine which game setup flow to initiate.
 */
enum class MenuChoice
{
	START_SINGLEPLAYER,	///< Option to start a local single-player game against AI bots.
	START_MULTIPLAYER,	///< Option to host a new multiplayer game server.
	JOIN_MULTIPLAYER,	///< Option to connect to an existing multiplayer game as a client.
	EXIT,				///< Option to exit the application.
	numberofchoices		///< Utility value representing the total number of valid menu options. Used for input bounds checking.
};