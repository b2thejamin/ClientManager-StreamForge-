#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "ClientList.h"

void ClientsList::addClient(const std::string& clientName)
{
	std::fstream myFile;
	myFile.open("client-list.csv", std::ios::out | std::ios::app);
	if (myFile.is_open()) {
		myFile << clientName << "\n";
	}
	myFile.close();




	/*clients.push_back(clientName);
	std::cout << "Client " << clientName << " added.\n";*/
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




	/*auto it = std::find(clients.begin(), clients.end(), clientName);
	if (it != clients.end())
	{
		clients.erase(it);
		std::cout << "Client " << clientName << " removed.\n";
	}
	else
	{
		std::cout << "Client " << clientName << " not found.\n";
	}*/
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


// each client needs to be assigned a task list and it needsa to keep track of what tasks are finished and what arent
void ClientsList::taskList() const
{
	bool finished = false;
	std::cout << "1. Clips created: \n" << finished;
	std::cout << "2. Video edited: \n" << finished;
	std::cout << "3. Thumbnails created: \n" << finished;
	std::cout << "4. Descriptions written: \n" << finished;
	std::cout << "5. Tags researched: \n" << finished;
	std::cout << "6. Titles created: \n" << finished;
	std::cout << "7. Schedule posts: \n" << finished;

}
