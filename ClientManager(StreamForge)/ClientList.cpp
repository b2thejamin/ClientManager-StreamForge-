#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <cstdio>
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

static std::string taskFileName(const std::string& clientName)
{
	return "client-tasks-" + clientName + ".csv";
}

void ClientsList::addClient(const std::string& clientName)
{
	// append client to client-list.csv if not already present
	bool exists = false;
	{
		std::ifstream in("client-list.csv");
		std::string line;
		while (std::getline(in, line)) {
			if (line == clientName) { exists = true; break; }
		}
	}

	if (!exists) {
		std::ofstream out("client-list.csv", std::ios::out | std::ios::app);
		if (out.is_open()) {
			out << clientName << "\n";
		}
	}

	// ensure client has a task file (only create if missing/empty)
	createTaskList(clientName);
}

void ClientsList::removeClient(const std::string& clientName)
{
	std::ifstream myFile("client-list.csv");
	if (!myFile.is_open()) return;

	std::string line;
	std::vector<std::string> remaining;
	while (std::getline(myFile, line)) {
		if (line != clientName && !line.empty()) remaining.push_back(line);
	}
	myFile.close();

	std::ofstream outFile("client-list.csv", std::ios::out | std::ios::trunc);
	for (const auto& c : remaining) outFile << c << "\n";
	outFile.close();

	// also remove the client's task file if present
	std::remove(taskFileName(clientName).c_str());
	std::cout << "Client " << clientName << " removed.\n";
}

void ClientsList::listClients() const
{
	std::ifstream myFile("client-list.csv");
	if (!myFile.is_open()) {
		std::cout << "No clients found.\n";
		return;
	}
	std::string line;
	std::cout << "Client List:\n";
	while (std::getline(myFile, line)) {
		if (!line.empty()) std::cout << "- " << line << "\n";
	}
	myFile.close();
}

void ClientsList::createTaskList(const std::string& clientName)
{
	const auto filename = taskFileName(clientName);

	// If file exists and is non-empty, do nothing.
	std::ifstream check(filename);
	if (check.is_open()) {
		check.seekg(0, std::ios::end);
		if (check.tellg() > 0) {
			// file exists and has content -> don't overwrite
			check.close();
			return;
		}
		check.close();
	}

	// create default task list with status 0 (incomplete)
	std::ofstream myFile(filename, std::ios::out | std::ios::trunc);
	if (myFile.is_open()) {
		for (const auto& task : tasks) {
			myFile << task << "\t0\n";
		}
		myFile.close();
	}
}

// interactive viewer/manager for a client's tasks
void ClientsList::viewClient(const std::string& clientName)
{
	std::cout << "\nViewing tasks for client: " << clientName << "\n";

	for (;;) {
		listClientTasks(clientName);
		std::cout << "\nActions for " << clientName << ":\n";
		std::cout << " 1) Mark task completed\n";
		std::cout << " 2) Remove a task\n";
		std::cout << " 3) Add a task\n";
		std::cout << " 4) Back to main menu\n";
		std::cout << "Choose an action: ";

		int action = 0;
		if (!(std::cin >> action)) {
			std::cin.clear();
			std::string dummy;
			std::getline(std::cin, dummy);
			continue;
		}

		if (action == 4) {
			// consume trailing newline before returning
			std::string dummy;
			std::getline(std::cin, dummy);
			return;
		}

		if (action == 1) {
			std::cout << "Task number to mark completed: ";
			size_t n;
			if (std::cin >> n) {
				markTaskCompleted(clientName, n);
			} else {
				std::cin.clear();
				std::string dum; std::getline(std::cin, dum);
			}
		} else if (action == 2) {
			std::cout << "Task number to remove: ";
			size_t n;
			if (std::cin >> n) {
				removeTaskFromClient(clientName, n);
			} else {
				std::cin.clear();
				std::string dum; std::getline(std::cin, dum);
			}
		} else if (action == 3) {
			std::cout << "Enter new task text (single line): ";
			std::string dum; std::getline(std::cin, dum); // consume trailing newline
			std::string newTask;
			std::getline(std::cin, newTask);
			if (!newTask.empty()) addTaskToClient(clientName, newTask);
		} else {
			std::cout << "Invalid action.\n";
		}

		// consume trailing newline before next loop iteration
		std::string dummy;
		std::getline(std::cin, dummy);
	}
}

void ClientsList::listClientTasks(const std::string& clientName) const
{
	auto clientTasks = loadTasks(clientName);
	if (clientTasks.empty()) {
		std::cout << "No tasks found for client: " << clientName << "\n";
		return;
	}

	std::cout << "Tasks for " << clientName << ":\n";
	for (size_t i = 0; i < clientTasks.size(); ++i) {
		std::cout << (i + 1) << ". [" << (clientTasks[i].second ? "x" : " ") << "] " << clientTasks[i].first << "\n";
	}
}

void ClientsList::addTaskToClient(const std::string& clientName, const std::string& task)
{
	auto clientTasks = loadTasks(clientName);
	clientTasks.emplace_back(task, false);
	saveTasks(clientName, clientTasks);
	std::cout << "Added task to " << clientName << ": " << task << "\n";
}

void ClientsList::markTaskCompleted(const std::string& clientName, size_t taskNumber)
{
	auto clientTasks = loadTasks(clientName);
	if (taskNumber == 0 || taskNumber > clientTasks.size()) {
		std::cout << "Invalid task number.\n";
		return;
	}
	size_t idx = taskNumber - 1;
	clientTasks[idx].second = true;
	saveTasks(clientName, clientTasks);
	std::cout << "Marked task " << taskNumber << " completed for " << clientName << ".\n";
}

void ClientsList::removeTaskFromClient(const std::string& clientName, size_t taskNumber)
{
	auto clientTasks = loadTasks(clientName);
	if (taskNumber == 0 || taskNumber > clientTasks.size()) {
		std::cout << "Invalid task number.\n";
		return;
	}
	size_t idx = taskNumber - 1;
	std::cout << "Removing task \"" << clientTasks[idx].first << "\" from " << clientName << ".\n";
	clientTasks.erase(clientTasks.begin() + idx);
	saveTasks(clientName, clientTasks);
}

std::vector<std::pair<std::string, bool>> ClientsList::loadTasks(const std::string& clientName) const
{
	std::vector<std::pair<std::string, bool>> result;
	std::ifstream inFile(taskFileName(clientName));
	if (!inFile.is_open()) {
		return result;
	}

	std::string line;
	while (std::getline(inFile, line)) {
		if (line.empty()) continue;

		// Preferred format: <task>\t<0|1>
		auto tabPos = line.rfind('\t');
		if (tabPos != std::string::npos) {
			std::string taskText = line.substr(0, tabPos);
			std::string status = line.substr(tabPos + 1);
			bool completed = (status == "1");
			result.emplace_back(taskText, completed);
			continue;
		}

		// Fallback: handle legacy "task,incomplete" or "task,complete"
		auto commaPos = line.rfind(',');
		if (commaPos != std::string::npos) {
			std::string taskText = line.substr(0, commaPos);
			std::string status = line.substr(commaPos + 1);
			// trim whitespace from status
			status.erase(std::remove_if(status.begin(), status.end(), ::isspace), status.end());
			bool completed = (status == "complete" || status == "1" || status == "done");
			result.emplace_back(taskText, completed);
			continue;
		}

		// Otherwise treat whole line as task (incomplete)
		result.emplace_back(line, false);
	}
	inFile.close();
	return result;
}

void ClientsList::saveTasks(const std::string& clientName, const std::vector<std::pair<std::string, bool>>& tasks) const
{
	std::ofstream outFile(taskFileName(clientName), std::ios::out | std::ios::trunc);
	if (!outFile.is_open()) {
		std::cout << "Failed to open task file for " << clientName << "\n";
		return;
	}
	for (const auto& t : tasks) {
		outFile << t.first << "\t" << (t.second ? "1" : "0") << "\n";
	}
	outFile.close();
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

