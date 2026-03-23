#include "NetworkInputHandler.h"
#include "NetworkCommands.h"
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>


PlayerAction NetworkInputHandler::requestAction(const TableState& tableState, const PlayerState& playerState)
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

void NetworkInputHandler::onPlayersCardDealt(const Card& card)
{

}
