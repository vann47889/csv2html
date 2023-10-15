#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include<sstream>
#include <algorithm>
using namespace std;
int hCheck = 0;
int rCheck = 0;
int nCheck = 0;
int qCheck = 0;
int bgCheck = 0;
int fgCheck = 0;
int border = 1;
string bg = "";
string fg = "";
int lineCount = 0;

int main(int argc, char* argv[]) {
    vector<string> switches;
	string fileName;
	string htmlFname;

	for (int i = 1; i < argc; ++i) {
		string arg = argv[i];
		if (arg.ends_with(".csv")) {
			fileName = arg;
			htmlFname = arg.substr(0, arg.size() - 4) + ".html";
		}
		if (arg == "-bg") {
			bgCheck = 1;
			bg = argv[i + 1];
		}
		if (arg == "-fg") {
			fgCheck = 1;
			fg = argv[i + 1];
		}
		else {
			switches.emplace_back(arg);
		}
	}

	

    for (const string& arg : switches) {
        if (arg == "--help") {
            cout << "--help: display the help text for the program" << endl;
            cout << "-h: first line is the table header" << endl;
            cout << "-r: report conversion metrics" << endl;
            cout << "-n: no border" << endl;
            cout << "-q: strip quotes, commas inside quotes are not delimiters" << endl;
            cout << "--bg: background-colors for rows (first is header, then cycle)" << endl;
            cout << "--background: where the colors are HTML/CSS compatible encoding" << endl;
            cout << "--fg: foreground-colors for row (first is header, then cycle)" << endl;
            cout << "--foreground: where the colors are HTML/CSS compatible encoding" << endl;
            return 0;
        }
		else if (arg == "-h") {
			hCheck = 1;
		}

        else if (arg == "-r") {
			rCheck = 1;
        }
        else if (arg == "-n") {
			nCheck = 1;
        }
        else if (arg == "-q") {
			qCheck = 1;
        }
		
        
    }

	ifstream inputFile(fileName);
	ofstream outputFile(htmlFname);
	if (inputFile.is_open())
	{
		outputFile << "<!DOCTYPE html>" << endl;
		outputFile << "<html>" << endl;
		if (hCheck == 1)
		{
			outputFile << "<head><title>" << htmlFname << "</title></head>" << endl;
		}
		if (bgCheck == 1 && fgCheck == 0)
		{
			outputFile << "<style>\n th {background-color:" << bg << "; } \n</style>";
		}
		if (fgCheck == 1 && bgCheck == 0)
		{
			outputFile << "<style>\n th {color:" << fg << "; } \n</style>";
		}
		if (bgCheck == 1 && fgCheck == 1)
		{
			outputFile << "<style>\n th {background-color:" << bg << "; color:" << fg << ";} \n</style>";
		}

		outputFile << "<body>" << endl;
		if (nCheck == 1)
		{
			border = 0;
			outputFile << "<table border='" << border << "'>" << endl;
		}
		if (nCheck == 0)
		{
			border = 1;
			outputFile << "<table border='" << border << "'>" << endl;
		}

		string line;

		if (qCheck == 0)
		{
			while (getline(inputFile, line)) {
				stringstream ss(line);
				string cell;
				outputFile << "<tr>" << endl;
				while (getline(ss, cell, ',')) {
					outputFile << "  <td>" << cell << "</td>" << endl;
				}
				outputFile << "</tr>" << endl;
				lineCount++;
			}
		}

		if (qCheck == 1)
		{
			while (getline(inputFile, line)) {
				stringstream ss(line);
				string cell;
				outputFile << "<tr>" << endl;
				while (getline(ss, cell)) {
					outputFile << "  <td>" << cell << "</td>" << endl;
				}
				outputFile << "</tr>" << endl;
				lineCount++;
			}
		}

		cout << "HTML table generated successfully." << endl;


	}
	else {
		cout << "Error opening file";
	}

    return 0;
}
