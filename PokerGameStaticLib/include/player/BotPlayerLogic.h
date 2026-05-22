#pragma once
/**
 * @file BotPlayerLogic.h
 * @brief File containing declaration of BotPlayerLogic class
 */


#include "PlayerLogicParent.h"
#include <random>
#include <string>

/**
 * @brief Class representing Bot Player
 *
 */
class BotPlayerLogic : public PlayerLogicParent
{
private:
	int aggressiveLevel{};					///< factor that is used in bot's decision making (between 1 and 10)
	std::random_device rd{};				///< used for generating random value
	std::mt19937 gen{};						///< generator for random numbers

	/**
	* @brief Private method that gets a random name for bot from file
	* 
	* @details It opens bot_names.txt from 'data' directory, reads all names and randomly chooses one
	* 
	* @returns random name from the file
	*/
	std::string getRandomNameFromFile();	

public:
	/**
	* @brief Public constructor without specifying aggressiveLevel
	* 
	* @details Instead of manually putting aggressive level, the constructor will randomly choose aggressiveLevel between 1 and 10
	* 
	* @param[in] startingChips amount of chips that bot will start with
	*/
	BotPlayerLogic(int startingChips);
	
	/**
	* @brief Public constructor with specifying aggressiveLevel
	*
	* @details If the value inside of argument for aggressiveLevel is outside of range [1,10] 
	then it will be randomly generated between those values
	*
	* @param[in] startingChips amount of chips that bot will start with
	* @param[in] aggressiveLevel aggressive factor of the bot player
	*/
	BotPlayerLogic(int startingChips, int aggressiveLevel);


	/**
	 * @copydoc PlayerLogicParent::makeDecision(const TableState& state)
	 *
	 */
	PlayerAction makeDecision(const TableState& state) override;


};
