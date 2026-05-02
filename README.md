# Log Analyzer (C++)

A fast command-line tool for analyzing log files and extracting useful insights such as log level counts and most frequent error messages.

## 🚀 Features

- Parses large log files efficiently (line-by-line streaming)
- Counts log levels:
  - INFO
  - WARNING
  - ERROR
- Identifies top repeated error messages
- Clean, readable console output
- Lightweight and fast
## 🛠 Tech Stack

- C++
- STL (fstream, unordered_map, vector, algorithm)
- Command-line interface (CLI)

## 📦 Project Structure
log-analyzer/
- ├── src/
- │ └── main.cpp # Core log analyzer
- │
- ├── sample_logs/
- │ └── test.log # log file for testing
- │
- ├── README.md # Project documentation
- └── .gitignore

## Example output
<img width="779" height="677" alt="image" src="https://github.com/user-attachments/assets/546897cf-2898-4231-96b3-1401ab74c427" />
