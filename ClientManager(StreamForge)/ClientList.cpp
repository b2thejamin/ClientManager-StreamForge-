#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <array>
#include "ClientList.h"




std::array<std::string, 7> tasks = {
	"Clips created",
	"Video edited",
	"Thumbnails created",
	"Descriptions written",
	"Tags researched",
	"Titles created",
	"Schedule posts"
};




void ClientsList::addClient(const std::string& clientName)
{
	std::fstream myFile;
	myFile.open("client-list.csv", std::ios::out | std::ios::app);
	if (myFile.is_open()) {
		myFile << clientName << "\n";
	}
	myFile.close();
}




void ClientsList::removeClient(const std::string& clientName)
{
	std::fstream myFile;
	myFile.open("client-list.csv", std::ios::in);
	if (myFile.is_open()) {
		std::string line;
		std::vector<std::string> clients;
		while (std::getline(myFile, line)) {
			if (line != clientName) {
				clients.push_back(line);
			}
		}
		std::cout << "Client " << clientName << " removed.\n";
		myFile.close();

		std::ofstream outFile("client-list.csv", std::ios::out | std::ios::trunc);
		for (const auto& client : clients) {
			outFile << client << "\n";
		}
		outFile.close();
	}
}




void ClientsList::listClients() const
{
	std::fstream myFile;
	myFile.open("client-list.csv", std::ios::in);
	if (myFile.is_open()) {
		std::string line;
		std::cout << "Client List:\n";
		while (std::getline(myFile, line)) {
			std::cout << "- " << line << "\n";
		}
		myFile.close();
	}
}



// each client needs to be assigned a task list and it needs to keep track of what tasks are finished and what arent
void ClientsList::viewClient(const std::string& clientName) const
{
	std::fstream myFile;
	myFile.open("client-list.csv", std::ios::in);
	if (myFile.is_open()) {
		std::string line;
		std::vector<std::string> clients;
		while (std::getline(myFile, line)) {
			if (line != clientName) {
				clients.push_back(line);
			}
		}
		std::cout << "\nViewing tasks for client: " << clientName << "\n";
		for (const auto& task : tasks) {
			std::cout << "- " << task << "\n";
		}
	}
}

