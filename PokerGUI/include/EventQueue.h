#pragma once

/**
* @file EventQueue.h
* @brief File containing declaration and definition of the EventQueue class
*/

#include "GameEvents.h"
#include <queue>
#include <variant>
#include <mutex>
#include <optional>

/**
* @brief Class representing a thread-safe queue of the game events
*/
class EventQueue
{
private:
	std::queue<GameEvent> events{};		///< queue containing @ref GameEvent
	std::mutex queueMutex{};			///< mutex for locking resources between threads

public:
	/**
	* @brief Main default constructor explicitly declared since we deleted copying and moving
	*/
	EventQueue() = default;

	/**
	* @name Copying and moving
	* Class already can't be copied due to mutex, so we explicitly declare it for visibility
	*/
	///@{
	EventQueue(const EventQueue& other) = delete;
	EventQueue(EventQueue&& other) = delete;
	EventQueue& operator=(const EventQueue& other) = delete;
	EventQueue& operator=(EventQueue&& other) = delete;
	///@}

	/**
	* @brief Thread-safe method that pushes event to the queue
	* @details It should be used only in thread responsible for receiving info about event
	* @param event event that will be pushed @ref GameEvent
	*/
	void push(GameEvent event)
	{
		std::lock_guard<std::mutex> guard(queueMutex);
		events.push(std::move(event));
	}


	/**
	* @brief Thread-safe method that tries to retrieve event from the queue
	* @details It should be used only in thread responsible for GUI/Drawing, it doesn't wait for queue to have any element
	* @return nullopt if queue is empty or front GameEvent of the queue @ref GameEvent
	*/
	std::optional<GameEvent> tryRetrieve()
	{
		std::lock_guard<std::mutex> guard(queueMutex);
		if (events.empty())
		{
			return std::nullopt;
		}
		GameEvent retrievedVariant{ std::move(events.front()) };
		events.pop();
		return retrievedVariant;
	}
};