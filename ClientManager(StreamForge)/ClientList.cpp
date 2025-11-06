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




void ClientsList::createTaskList(const std::string& clientName) const
{
	std::fstream myFile;
	myFile.open("client-tasks-" + clientName + ".csv", std::ios::out | std::ios::app);
	if (myFile.is_open()) {
		for (const auto& task : tasks) {
			myFile << task << "\n";
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
		myFile.open("client-tasks-" + clientName + ".csv", std::ios::out | std::ios::app);
	}
}




//thumbmnail need a better prompt
//description is too lengthy
void ClientsList::promptAI() const
{
	std::string game, topic;
	std::cout << "\nGame: ";
	std::getline(std::cin, game);
	if (game.empty()) {
		std::getline(std::cin, game);
	}
	std::cout << "\nVideo topic: ";
	std::getline(std::cin, topic);
	std::cout << "\nv =====BEGIN PROMPT===== v\n";
	std::cout << "\nOptimize YouTube gaming video for " + game + ":\n"
		"Use Google Trends → search " + game + " (last 90 days, YouTube, worldwide)\n"
		"Video is about: " + topic + "\n"
		"Give me:\n"
		"TITLE (3 lines, <60 chars)\n"
		"THUMB (GENERATE 3 THUMBNAIL IMAGES relating to " + game + " and " + topic + ")\n"
		"DESC (150-word template, no timestamps + 8 tags)\n"
		"TAGS (25, comma list)\n"
		"POST (3 dates/times next 10 days, e.g. Fri 7pm EST)\n"
		"Max 12 total lines output. No fluff.\n";
	std::cout << "\n^ =====END OF PROMPT===== ^\n";
}

