
# Discrete Process Control Course
## Single-machine problems

The exercises performed processed basic single-machine problems. As the name suggests
a single machine was available, as well as sets of tasks with different numbers of tasks. Each set was distinguished by unique relationships
values of rj , qj and pj , thus making it possible to check the correctness of the implemented algorithms for serialization of
tasks.

## Prerequisites

Before you begin, ensure you have met the following requirements:
- Python 3.9 (min)
- CMake
- A build system (Make or Ninja)

### Linux & macOS

- Install Python 3, CMake, and build tools (Make is usually pre-installed; Ninja is optional):
  ```bash
  sudo apt-get update
  sudo apt-get install python3 cmake make  # For Ubuntu/Debian
  brew install python cmake make                 # For macOS
  ```

### Windows

- Install Python 3 from the [official Python website](https://www.python.org/downloads/).
- Install CMake and Ninja using [Scoop](https://scoop.sh/) or [Chocolatey](https://chocolatey.org/), or download from the official websites.

## Automated Build and Run

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd <repository-name>
   ```

2. Run the Python script with the path to your data file as an argument:
   ```bash
   python3 run.py ./data/test_1.txt
   ```

## Manual Build and Run Instructions

1. **Clone the repository:**
   ```bash
   git clone <repository-url>
   cd <repository-name>
   ```

2. **Create and enter the build directory:**
   ```bash
   mkdir build && cd build
   ```

3. **Configure the project with CMake:**
   ```bash
   cmake ..
   ```

4. **Build the project:**
    - Using Make:
      ```bash
      make
      ```
    - Or, using Ninja (if installed):
      ```bash
      ninja
      ```

5. **Run the executable with the data file:**
   ```bash
   ./main ../data/test_1.txt
   ```
   Replace `main` with the name of your project's executable and adjust the path to your data file as necessary.
## Generating Documentation

This project's documentation is generated using Doxygen. Follow the steps below to generate and view the documentation:

### Prerequisites

Before generating the documentation, ensure you have the following prerequisites installed on your system:

- **Doxygen**: You can install Doxygen from the [official Doxygen website](https://www.doxygen.nl/download.html).

### Generating Documentation

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd <repository-name>
   ```

2. Run the Python script with the path to your data file as an argument:
   ```bash
   python3 run_doc.py
   ```
   
After generation, the documentation will be opened in default browser.

