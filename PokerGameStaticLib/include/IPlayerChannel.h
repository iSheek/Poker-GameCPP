/**
 * @file IPlayerChannel.h
 * @brief File containing declaration of IPlayerChannel interface
 */
#pragma once

#include "IInputHandler.h"
#include "IOutputHandler.h"

 /**
  * @brief Interface for handling user input and output during the game 
  */
class IPlayerChannel : public IInputHandler, public IOutputHandler
{
public:
	virtual ~IPlayerChannel() = default;
};
