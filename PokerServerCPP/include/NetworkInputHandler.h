#pragma once

#include "IInputHandler.h"
#include "TableState.h"
#include "PlayerAction.h"
#include "PlayerState.h"
#include "Cards.h"
#include <boost/asio.hpp>
#include <memory>

class NetworkInputHandler : public IInputHandler
{
private:
	std::shared_ptr<boost::asio::ip::tcp::socket> pSocket;

public:
	NetworkInputHandler(std::shared_ptr<boost::asio::ip::tcp::socket> pSocket) : pSocket(pSocket) {}
	PlayerAction requestAction(const TableState& tableState, const PlayerState& playerState) override;
	void onPlayersCardDealt(const Card& card) override;
};