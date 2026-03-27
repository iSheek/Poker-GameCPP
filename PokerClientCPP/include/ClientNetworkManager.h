#pragma once

#include "IInputHandler.h"
#include "IOutputHandler.h"
#include "NetworkCommands.h"
#include "HandScore.h"
#include "PlayerAction.h"
#include "PlayerState.h"
#include "TableState.h"
#include "PublicPlayerInfo.h"
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

//TODO : IMPLEMENT BETTER EXCEPTION HANDLING

class ClientNetworkManager
{
private:
	boost::asio::ip::tcp::socket socket;

	std::shared_ptr<IOutputHandler> pOutputHandler;
	std::shared_ptr<IInputHandler> pInputHandler;

	boost::asio::streambuf receiveBuffer;

	bool isConnected = false;

public:
	ClientNetworkManager(
		boost::asio::io_context& io_context,
		std::shared_ptr<IOutputHandler> output,
		std::shared_ptr<IInputHandler> input) : socket(io_context), pOutputHandler(output),
		pInputHandler(input)
	{}

	void handleRenderTable(const nlohmann::json& jReceived);

	void handleOnPlayerAction(const nlohmann::json& jReceived);

	void handleOnCommunityCardDealt(const nlohmann::json& jReceived);

	void handleRequestAction(const nlohmann::json& jReceived);

	void handleOnShowdown(const nlohmann::json& jReceived);

	void runLoop();

	void tryToConnectToServer(std::string_view ipAddress, const int& port);

	


};