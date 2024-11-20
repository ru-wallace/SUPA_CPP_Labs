#include "CustomFunctions.h"

/**
 * * Main function to run the program
 *  Reads data from a file, and allows the user to select from a list of options
 */

int main(int argc, char* argv[]) {

    std::string input_file = INPUT_FILE;
    InputData data = readData(input_file);
    int exit = 0;
    int savedMag = 0;
    int savedFit = 0;
    int savedXtoY = 0;
    do 
    {

        int option = getOption();
        std::vector<float> results;
        FitLine fitLine;

        switch (option)
        {
        case 1:
            printData(data);
            break;
        case 2:
            results = getMagnitudes(data);
            std::cout << "Magnitudes: " << std::endl;
            save(results, "magnitudes.txt");
            savedMag = 1;
            printData(results);
            break;
        case 3:
            fitLine = calcFitLine(data, INPUT_ERR_FILE);
            std::cout << "y=" << fitLine.gradient << "x+" << fitLine.intercept << std::endl;
            std::cout << "Chi2/NDF: " << fitLine.chi2/2 << "\n" << std::endl;
            save(fitLine, "fitLine.txt");
            savedFit = 1;
            std::cout << "Press enter to continue" << "\n" << std::endl;
            std::cin.ignore();
            
            break;
        case 4:
            results = xToY(data);
            std::cout << "x^y Results: " << std::endl;
            save(results, "xToY.txt");
            savedXtoY = 1;
            printData(results);
            break;
        default:
            exit = 1;
            break;
        }
    } while (!exit);

    int saved = savedMag + savedFit + savedXtoY;
    if (saved > 0) {
        std::cout << "Saved " << saved << " files to " << OUTPUT_DIR << std::endl;
    }

}

