#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

class ClientsList
{
private:
	std::vector<std::string> clients;
public:
	void addClient(const std::string& clientName);
	void removeClient(const std::string& clientName);
	void taskList() const;
	void listClients() const;
};

