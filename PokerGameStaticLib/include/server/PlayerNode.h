#pragma once


/**
 * @file PlayerNode.h
 * @brief File containing PlayerNode struct declaration
 */


#include <boost/asio.hpp>
#include <memory>
#include "PublicPlayerInfo.h"

using boost::asio::ip::tcp;


/**
 * @brief Struct representing player in the server
 *
 * @details This struct has public information about player as well as socket used for connection
 */
struct PlayerNode
{
	std::shared_ptr<tcp::socket> socket{}; ///< socket from Boost.Asio
	PublicPlayerInfo playerInfo{};		   ///< struct containing public info about player
};
