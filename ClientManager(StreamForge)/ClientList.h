#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <utility>

class ClientsList
{
private:
	std::vector<std::string> clients;

	std::vector<std::pair<std::string, bool>> loadTasks(const std::string& clientName) const;
	void saveTasks(const std::string& clientName, const std::vector<std::pair<std::string, bool>>& tasks) const;

public:
	void addClient(const std::string& clientName);
	void removeClient(const std::string& clientName);
	void listClients() const;

	void viewClient(const std::string& clientName);

	void createTaskList(const std::string& clientName);

	void listClientTasks(const std::string& clientName) const;
	void addTaskToClient(const std::string& clientName, const std::string& task);
	void markTaskCompleted(const std::string& clientName, size_t taskNumber); // taskNumber is 1-based
	void removeTaskFromClient(const std::string& clientName, size_t taskNumber); // taskNumber is 1-based

	void promptAI() const;
};

