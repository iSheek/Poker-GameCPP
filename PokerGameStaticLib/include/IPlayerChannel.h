/**
 * @file IPlayerChannel.h
 * @brief File containing declaration of IPlayerChannel interface
 */
#pragma once

#include "IInputHandler.h"
#include "IOutputHandler.h"

 /**
  * @brief Interface for handling user input and output during the game 
  * @details it is only a connection of input and output handlers so it is not needed to implement them separately
  */
class IPlayerChannel : public IInputHandler, public IOutputHandler
{
public:
	virtual ~IPlayerChannel() = default;
};
