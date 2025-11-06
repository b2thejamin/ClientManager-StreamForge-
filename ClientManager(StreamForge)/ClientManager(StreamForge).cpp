#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "ClientList.h"


//Need to add TODO list
//Need to add ability to save clients to file a long as TODO list progress
//add a 24 hour timer for when the client is added and how long until the tasks are due

// fix console formatting
// create fall backs if user does not type in correct responses


ClientsList clientList;

int main()
{
    bool running = true;
    while (running)
    {
        std::cout << "\nStreamForge - CLIENT MANAGER\n";
        int choice;
		std::cout << "1. Add Client\n" << "2. Remove Client\n" << "3. Client List\n" << "4. View Client\n" << "5. Suggested AIs\n" << "6. Exit\n" << "\nChoose an option: ";
        std::cin >> choice;
        std::string clientName;
        switch (choice)
        {
            case 1:
				std::cout << "\nADD CLIENT\n";
                std::cout << "Client Name? ";
                std::cin >> clientName;
                clientList.addClient(clientName);
				clientList.createTaskList(clientName);
                break;
            case 2:
				std::cout << "\nREMOVE CLIENT\n";
				clientList.listClients();
                std::cout << "Client Name? ";
                std::cin >> clientName;
                clientList.removeClient(clientName);
                break;
            case 3:
                std::cout << "\nCURRENT CLIENTS:\n";
                clientList.listClients();
                break;
			case 4:
                std::cout << "\nVIEW CLIENT\n";
                std::cout << "Client Name? ";
				std::cin >> clientName;
				clientList.viewClient(clientName);
                break;
            case 5:
				std::cout << "\nSUGGESTED AIs FOR CONTENT CREATION TASKS:\n";
				std::cout << "\nGrok or ChatGPT:\n";
				std::cout << "\t -Thumbnails\n" << "\t -Descriptions\n" << "\t -Tags\n" << "\t -Titles\n" << "\t -Schedule\n";
				std::cout << "Powder.gg or eklipse.gg:\n";
				std::cout << "\t -Videos\n" << "\t -Clips\n";
				std::cout << "\nWould you like a prompt for Grok or ChatGPT? (y/n): ";
				char yn;
                std::cin >> yn;
                if (yn == 'y') {
                    clientList.promptAI();
                    break;
                }
                else {
                    break;
                }
            case 6:
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}
