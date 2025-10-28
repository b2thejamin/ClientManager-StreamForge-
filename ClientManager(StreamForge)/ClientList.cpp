#include "ClientList.h"

void ClientsList::addClient(const std::string& clientName)
{
	clients.push_back(clientName);
	std::cout << "Client " << clientName << " added.\n";
}
void ClientsList::removeClient(const std::string& clientName)
{
	auto it = std::find(clients.begin(), clients.end(), clientName);
	if (it != clients.end())
	{
		clients.erase(it);
		std::cout << "Client " << clientName << " removed.\n";
	}
	else
	{
		std::cout << "Client " << clientName << " not found.\n";
	}
}
void ClientsList::listClients() const
{
	std::cout << "Client List:\n";
	for (const auto& client : clients)
	{
		std::cout << "- " << client << "\n";
	}
}
void ClientsList::todo(const std::string& task)
{
	bool finished = false;
	std::cout << "TODO: " << task << "\n";
}
