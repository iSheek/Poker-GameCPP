#include "ClientNetworkManager.h"
#include "TexasHoldemManager.h"
#include "IOutputHandler.h"
#include "IInputHandler.h"
#include "ConsoleInputHandler.h"
#include "ConsoleOutputHandler.h"
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <memory>

using asiotcp = boost::asio::ip::tcp;
using json = nlohmann::json;

int main()
{
	/*
	try
	{


		boost::asio::io_context io_context;

		asiotcp::socket socket(io_context);

		socket.connect(asiotcp::tcp::endpoint(boost::asio::ip::make_address("127.0.0.1"), 1234));

		std::string receivedMessage;

		boost::asio::streambuf receiveBuffer;

		std::string message;

		std::cin >> message;

		boost::system::error_code error;

		message += '\n';

		boost::asio::write(socket, boost::asio::buffer(message), error);

		boost::asio::read_until(socket, receiveBuffer, '\n');

		std::istream is(&receiveBuffer);
		std::getline(is, receivedMessage);

		json jReceived = json::parse(receivedMessage);

		Card receivedCard = jReceived.get<Card>();

		std::cout << "RECEIVED: " << CardFormatter::getCardName(receivedCard).wholeCardString() << std::endl;

		int value;

		std::cin >> value;

	}
	catch (std::exception& e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
	}
	*/

	boost::asio::io_context ioContext;
	std::shared_ptr pOutputHandler = std::make_shared<ConsoleOutputHandler>();
	std::shared_ptr pInputHandler = std::make_shared<ConsoleInputHandler>();

	ClientNetworkManager gameManager{ ioContext, pOutputHandler, pInputHandler };

	gameManager.tryToConnectToServer("127.0.0.1", 1234);

	gameManager.runLoop();

	return 0;
}