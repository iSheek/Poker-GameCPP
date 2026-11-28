#pragma once
/**
* @file GUIPlayerChannel.h
* @brief File containing declaration of GUIPlayerChannel class
*/

#include "IPlayerChannel.h"
#include "EventQueue.h"
#include "PlayerAction.h"
#include <stdexcept>
#include <stop_token>
#include <string>

/**
 * @brief Class that handles pushing events to the eventQueue
 * @details All methods work in game's thread but they don't touch scene or OpenGL, only puts copies of arguments of the event into the queue
 */
class GUIPlayerChannel : public IPlayerChannel
{
private:
	EventQueue& eventQueue;
	std::stop_token stopToken{};

public:
	GUIPlayerChannel(EventQueue& queue, std::stop_token stopToken) : eventQueue(queue), stopToken(stopToken) {}

	/**
	* @name Copying and moving
	* Only one channel per game
	*/
	///@{
	GUIPlayerChannel(const GUIPlayerChannel& other) = delete;
	GUIPlayerChannel(GUIPlayerChannel&& other) = delete;
	GUIPlayerChannel& operator=(const GUIPlayerChannel& other) = delete;
	GUIPlayerChannel& operator=(GUIPlayerChannel&& other) = delete;
	///@}

	void onCommunityCardDealt(const Card& card) override;
	void onPlayerAction(const std::string& playerName, const PlayerAction& action) override;
	void onShowdown(const ShowdownResult& showdownResult) override;
	void renderTable(const TableState& tableState, const std::vector<PublicPlayerInfo>& publicPlayersInfo) override;

	/**
	* @copydoc IInputHandler::requestAction
	* @details Puts request with promise, waits for PlayerAction and checks stop_token
	* @throws GameTerminationException if there is a request to stop or if broken promise from std::future @ref GameTerminationException
	*/
	PlayerAction requestAction(const TableState& tableState, const PlayerState& playerState) override;
	void onPlayersCardDealt(const Card& card) override;
};

/**
* @brief Custom exception class
* @details It's thrown when there is a request to stop or if there is a broken promise, it should be caught only on top of the function of game's thread
*/
class GameTerminationException : public std::runtime_error 
{
public:
	GameTerminationException(const char* const message) : runtime_error(message) {}
};