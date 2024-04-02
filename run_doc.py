import os
import subprocess
import platform
import webbrowser

def is_doxygen_installed():
    try:
        subprocess.run(["doxygen", "--version"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, check=True)
        return True
    except subprocess.CalledProcessError:
        return False

def run_doxygen():
    if not is_doxygen_installed():
        raise Exception("Doxygen is not installed. Please install Doxygen and try again.")

    if platform.system() == "Windows":
        path_separator = "\\"
        index_file = "index.html"
    else:
        path_separator = "/"
        index_file = "index.html"

    doc_dir = os.path.join(os.getcwd(), "doc")
    doxyfile = os.path.join(doc_dir, "../Doxyfile.in")

    if os.path.exists(doxyfile):
        os.chdir(doc_dir)
        subprocess.run(["doxygen", doxyfile], shell=True)
        print("Doxygen documentation generated successfully.")

        # Open the index.html file in the default web browser
        index_path = os.path.join(doc_dir, "html", index_file)
        webbrowser.open("file://" + index_path)
    else:
        print("Doxyfile not found in the doc directory.")

if __name__ == "__main__":
    run_doxygen()