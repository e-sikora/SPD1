import os
import subprocess
import sys
import argparse

# Parse command-line arguments
parser = argparse.ArgumentParser(description="Build and run a CMake project, passing a data file to the executable.")
parser.add_argument('data_file', type=str, help="The path to the data file to pass to the program.")
args = parser.parse_args()

# Function to run a command and optionally return its exit code
def run_command(command, check=True):
    try:
        subprocess.check_call(command, shell=True)
    except subprocess.CalledProcessError as e:
        if check:
            print(f"Command failed with {e.returncode}, {e.output}")
            sys.exit(e.returncode)
        else:
            return e.returncode
    return 0

# Check OS and set command for opening directory
is_windows = sys.platform.startswith('win')

# Step 1: Check and create the build directory
build_dir = "build"
if not os.path.isdir(build_dir):
    os.makedirs(build_dir)
os.chdir(build_dir)

# Step 2: Determine the available build system (make or ninja)
build_system = ""
if run_command("ninja --version", check=False) == 0:
    build_system = "Ninja"
elif run_command("make --version", check=False) == 0:
    build_system = "Unix Makefiles"
else:
    print("Neither make nor ninja build system found. Please install one of them.")
    sys.exit(1)

# Step 3: Configure the project with CMake
if run_command(f'cmake -G "{build_system}" ..') != 0:
    print("CMake configuration failed.")
    sys.exit(1)

# Step 4: Build the project
build_command = "ninja" if build_system == "Ninja" else "make"
if run_command(build_command) != 0:
    print("Build failed.")
    sys.exit(1)

# Step 5: Run the program with the data file
# Replace 'your_program_name' with the actual path to your executable
run_program_command = f".{os.sep}main {args.data_file}"
if run_command(run_program_command) != 0:
    print("Running program failed.")
    sys.exit(1)