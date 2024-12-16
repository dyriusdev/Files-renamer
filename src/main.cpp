#include <iostream>
#include <string>
#include <filesystem>

using namespace std;

string changeFileName(string& currentFileName, string& newName, string& extension, int number) {
	cout << "Current file name : " << currentFileName << "\n";

	string newFileName {newName + to_string(number) + extension};
	cout << "File name after renaming : " << newFileName << "\n";
	return newFileName;
}

int main() {
	std::cout << "Starting file re-namer\nPaste the directory and type a base name to subscribe all files\n";
	bool isValid = false;

	do {
		string path;
		string replaceToName;
		cout << "Directory : ";
		cin >> path;
		cout << "New name : ";
		cin >> replaceToName;

		isValid = std::filesystem::exists(path);
		if (isValid) {

			filesystem::path directory = path;
			int number = 0;

			for (auto& entry : filesystem::directory_iterator(directory)) {
				if (filesystem::is_regular_file(entry)) {
					string currentName { entry.path().filename() };
					string extension { entry.path().extension() };
					string newName { changeFileName(currentName, replaceToName, extension, number++) };

					try {
						filesystem::rename(directory / currentName, directory / newName);
					} catch (std::filesystem::filesystem_error &err) {
						cout << err.code() << "\n" << err.what() << "\n";
					}
				}
			}
		} else {
			cout << "Invalid directory try again";
		}
	} while(!isValid);
}
