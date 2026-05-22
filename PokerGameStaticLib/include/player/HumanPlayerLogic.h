/**
 * @file HumanPlayerLogic.h
 * @brief File containing declaration of HumanPlayerLogic class
 */
#pragma once

#include "PlayerLogicParent.h"
#include "IInputHandler.h"
#include <memory>

/**
 * @brief Class representing a human player's logic
 */
class HumanPlayerLogic : public PlayerLogicParent
{
private:
	std::shared_ptr<IInputHandler> pInputHandler{};
	
public:
	/**
	 * @brief Constructor with starting chips
	 * @param startingChips The initial amount of chips
	 */
	HumanPlayerLogic(int startingChips);
	
	/**
	 * @brief Constructor with starting chips and input handler
	 * @param startingChips The initial amount of chips
	 * @param inputHandlerPointer Shared pointer to an input handler
	 */
	HumanPlayerLogic(int startingChips, std::shared_ptr<IInputHandler> inputHandlerPointer);

	/**
	 * @brief Prompts the human player to make a decision based on the current table state
	 * @param state The current table state
	 * @return The action chosen by the player
	 */
	PlayerAction makeDecision(const TableState& state) override;

};