#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>

using namespace std;

void displayHex(ifstream &fileStream) {
    unsigned char dataBlock[16];
    size_t addressCounter = 0;

    while (fileStream.read(reinterpret_cast<char*>(dataBlock), sizeof(dataBlock)) || fileStream.gcount()) {
        size_t bytesRead = fileStream.gcount();

        cout << hex << setw(7) << setfill('0') << addressCounter << ": ";
        
        for (size_t i = 0; i < bytesRead; i++) {
            cout << setw(2) << setfill('0') << static_cast<int>(dataBlock[i]) << " ";
            if (i == 7) cout << " ";
        }

        if (bytesRead < 16) {
            for (size_t i = bytesRead; i < 16; i++) {
                cout << "   ";
                if (i == 7) cout << " ";
            }
        }

        cout << " ";
        for (size_t i = 0; i < bytesRead; i++) {
            cout << (isprint(dataBlock[i]) ? static_cast<char>(dataBlock[i]) : '.');
        }

        cout << endl;
        addressCounter += 16;
    }
}

void displayBinary(ifstream &fileStream) {
    unsigned char dataBlock[6];
    size_t addressCounter = 0;

    while (fileStream.read(reinterpret_cast<char*>(dataBlock), sizeof(dataBlock)) || fileStream.gcount()) {
        size_t bytesRead = fileStream.gcount();

        cout << hex << setw(7) << setfill('0') << addressCounter << ": ";

        for (size_t i = 0; i < bytesRead; i++) {
            for (int bit = 7; bit >= 0; bit--) {
                cout << ((dataBlock[i] >> bit) & 1);
            }
            cout << " ";
        }

        if (bytesRead < 6) {
            for (size_t i = bytesRead; i < 6; i++) {
                cout << "         ";
            }
        }

        cout << " ";
        for (size_t i = 0; i < bytesRead; i++) {
            cout << (isprint(dataBlock[i]) ? static_cast<char>(dataBlock[i]) : '.');
        }

        cout << endl;
        addressCounter += 6;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        cerr << "Usage: xed [-b] <filename>" << endl;
        return 1;
    }

    bool binaryOutput = false;
    string inputFilename;

    if (argc == 3 && string(argv[1]) == "-b") {
        binaryOutput = true;
        inputFilename = argv[2];
    } else {
        inputFilename = argv[1];
    }

    ifstream inputFile(inputFilename, ios::binary);
    if (!inputFile) {
        cerr << "Error: Unable to open file " << inputFilename << endl;
        return 1;
    }

    if (binaryOutput) {
        displayBinary(inputFile);
    } else {
        displayHex(inputFile);
    }

    return 0;
}
