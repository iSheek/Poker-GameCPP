
/**
 * @file NetworkPlayerChannel.cpp
 * @brief File containing definition of NetworkPlayerChannel's methods
 */


#include "NetworkPlayerChannel.h"
#include "NetworkCommands.h"
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>


PlayerAction NetworkPlayerChannel::requestAction(const TableState& tableState, const PlayerState& playerState)
{

    nlohmann::json jSend;

    jSend["method"] = NetworkCommand::REQUEST_ACTION;
    jSend["data"]["tableState"] = tableState;
    jSend["data"]["playerState"] = playerState;

    std::string serializedData = jSend.dump() + "\n";
    boost::system::error_code error;
    boost::asio::write(*this->pSocket, boost::asio::buffer(serializedData), error);

    if (error)
    {
        std::cout << "ERROR: " << error.message() << "\n";
        return PlayerAction();
    }

    boost::asio::streambuf receiveBuffer;
    boost::asio::read_until(*this->pSocket, receiveBuffer, '\n', error);

    if (error)
    {
        std::cout << "ERROR: " << error.message() << "\n";
        return PlayerAction();
    }

    std::istream is(&receiveBuffer);

    std::string message;
    std::getline(is, message);

    try
    {
        nlohmann::json jReceived = nlohmann::json::parse(message);
        PlayerAction actionToReturn = jReceived.get<PlayerAction>();
        return actionToReturn;
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << "\n";
        return PlayerAction();
    }



}

void NetworkPlayerChannel::onPlayersCardDealt(const Card& card)
{

}

using nlohmann::json;

void NetworkPlayerChannel::sendStringToSocket(std::string_view serializedData)
{
    boost::system::error_code error;
    boost::asio::write(*pSocket, boost::asio::buffer(serializedData), error);
    if (error) std::cout << "ERROR: " << error.message() << "\n";
}

void NetworkPlayerChannel::onCommunityCardDealt(const Card& card)
{
    json jSend{};

    jSend["method"] = NetworkCommand::ON_COMMUNITY_CARD_DEALT;
    jSend["data"]["card"] = card;

    std::string serializedData = jSend.dump() + "\n";
    sendStringToSocket(serializedData);
}

void NetworkPlayerChannel::onPlayerAction(const std::string& playerName, const PlayerAction& action)
{
    json jSend{};

    jSend["method"] = NetworkCommand::ON_PLAYER_ACTION;
    jSend["data"]["playerName"] = playerName;
    jSend["data"]["playerAction"] = action;

    std::string serializedData = jSend.dump() + "\n";
    sendStringToSocket(serializedData);
}

void NetworkPlayerChannel::onShowdown(const std::vector<std::string>& winnerNames, const HandScore& winningHand, const int& pot)
{
    json jSend{};

    jSend["method"] = NetworkCommand::ON_SHOWDOWN;
    jSend["data"]["winnerNames"] = winnerNames;
    jSend["data"]["winningHand"] = winningHand;
    jSend["data"]["pot"] = pot;

    std::string serializedData = jSend.dump() + "\n";
    sendStringToSocket(serializedData);
}

void NetworkPlayerChannel::renderTable(const TableState& tableState, const std::vector<PublicPlayerInfo>& publicPlayersInfo)
{
    json jSend{};

    jSend["method"] = NetworkCommand::RENDER_TABLE;
    jSend["data"]["tableState"] = tableState;
    jSend["data"]["publicPlayersInfo"] = publicPlayersInfo;

    std::string serializedData = jSend.dump() + "\n";
    sendStringToSocket(serializedData);
}

