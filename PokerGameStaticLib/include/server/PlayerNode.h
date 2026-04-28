#pragma once

#include <boost/asio.hpp>
#include <memory>
#include "PublicPlayerInfo.h"

using boost::asio::ip::tcp;


struct PlayerNode
{
	std::shared_ptr<tcp::socket> socket{};
	PublicPlayerInfo playerInfo{};
};
