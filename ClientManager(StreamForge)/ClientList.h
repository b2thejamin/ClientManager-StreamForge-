#pragma once
#include <vector>
#include <string>
#include <iostream>

class ClientsList
{
private:
	std::vector<std::string> clients;
	std::vector<std::string> tasks;
public:
	void addClient(const std::string& clientName);
	void removeClient(const std::string& clientName);
	void todo(const std::string& task);
	void listClients() const;
};

