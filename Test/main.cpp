#include <iostream>
#include <SFML/Network.hpp>

int main(void)
{
	std::cout << "Start" << std::endl;

	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("93.201.163.184", 30000);
	std::cout << "Verbindunsaufbau..." << std::endl;
	if (status != sf::Socket::Done) {
		std::cout << "Error while trying to connect to IP" << std::endl;
		return 0;
	}

	std::cout << "Bereit Verbindung aufzubauen" << std::endl;
	char data[20];
	std::size_t received;

	if (socket.receive(data, 20, received) != sf::Socket::Done) {
		std::cout << "Failed to receive package" << std::endl;
		return 0;
	}

	std::cout << data << std::endl;
	getchar();

	return 0;
}