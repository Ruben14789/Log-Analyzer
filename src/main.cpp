/// build and compile as g++ -std=c++17 src/main.cpp -o log-analyzer
/// bash as ./log-analyzer sample_logs/app.log


#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main(int argc, char* argv[]) {
    // file path is provided as a command-line argument
    if (argc < 2) {
        std::cout << "Usage: log-analyzer <log_file>\n";
        return 1;
    }
    // Get the file path from arguments
    std::string filePath = argv[1];

    // Open file
    std::ifstream file(filePath);

    // file open failure
    if (!file) {
        std::cerr << "Error: Could not open file: " << filePath << '\n';
        return 1;
    }

    //variables for the statistics
    int totalLines = 0;
    int infoCount = 0;
    int warningCount = 0;
    int errorCount = 0;


    // Stores frequency of each unique error message
    // Key = error message, Value = count
    std::unordered_map<std::string, int> errorMessages;

    std::string line;

    // Read the file line-by-line
    while (std::getline(file, line)) {
        totalLines++;

        // Check log level and update counts
        if (line.find("INFO") != std::string::npos) {
            infoCount++;
        } else if (line.find("WARNING") != std::string::npos) {
            warningCount++;
        } else if (line.find("ERROR") != std::string::npos) {
            errorCount++;

            // Find where "error" starts in the line
            std::size_t errorPos = line.find("ERROR");

            if (errorPos != std::string::npos) {
                // Extract everything AFTER "error"
                std::string message = line.substr(errorPos + 5);

                while (!message.empty() && message[0] == ' ') {
                    message.erase(0, 1);
                }
                
                // Increment occurrence count for this error message
                errorMessages[message]++;
            }
        }
    }


    // Move map data into a vector for sorting
    std::vector<std::pair<std::string, int>> sortedErrors(
        errorMessages.begin(),
        errorMessages.end()
    );

    // Sort errors by frequency
    std::sort(sortedErrors.begin(), sortedErrors.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        }
    );


    // Print statistics
    std::cout << "Log Summary\n";
    std::cout << "-----------\n";
    std::cout << "Total lines: " << totalLines << '\n';
    std::cout << "INFO: " << infoCount << '\n';
    std::cout << "WARNING: " << warningCount << '\n';
    std::cout << "ERROR: " << errorCount << '\n';


    // Print at top the most frequent error messages
    std::cout << "\nTop Error Messages\n";
    std::cout << "------------------\n";

    int limit = 3;  // var to show top 3 errors 
    int shown = 0;

    for (const auto& error : sortedErrors) {
        if (shown >= limit) {
            break;
        }

        std::cout << shown + 1 << ". " << error.first
                  << " - " << error.second << " times\n";

        shown++;
    }

    return 0;
}