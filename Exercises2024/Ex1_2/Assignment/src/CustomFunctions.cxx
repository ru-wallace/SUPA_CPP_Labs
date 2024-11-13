#include "CustomFunctions.h"

const std::string OUTPUT_DIR = "/workspaces/SUPA_CPP_Labs/Exercises2024/Ex1_2/Outputs/ex1/";
const std::string INPUT_FILE = "/workspaces/SUPA_CPP_Labs/Exercises2024/Ex1_2/input2D_float.txt";
const std::string INPUT_ERR_FILE = "/workspaces/SUPA_CPP_Labs/Exercises2024/Ex1_2/error2D_float.txt";


InputData readData(std::string filename) {
    
    std::cout << "Reading data from file: " << filename << std::endl;
    std::ifstream input_file(filename);

    if (!input_file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    std::vector<float> xValues = {};
    std::vector<float> yValues = {};
    int lineCount = 0;
    while (std::getline(input_file, line)) {
        if (lineCount == 0) {
            lineCount++;
            continue;
        }

        float x, y;
        sscanf(line.c_str(), "%f,%f", &x, &y); // c_str returns ptr to array of characters ending in null rather than a string
        lineCount++;
        xValues.push_back(x);
        yValues.push_back(y);
    }
    input_file.close();
    return {xValues, yValues};
}

int getOption() {

    std::string RED_ASCII = "\033[1;31m";
    std::string RESET_ASCII = "\033[0m";

    int loopCount = 0;
    do {
        std::cout << std::endl << "What would you like to do?" << std::endl;
        std::cout << "  [p] Print input values" << std::endl;
        std::cout << "  [m] Calculate magnitudes" << std::endl;
        std::cout << "  [f] Calculate fit line" << std::endl;
        std::cout << "  [r] Calculate x^y" << std::endl;
        std::cout << "  [x] Exit" << std::endl;
        std::string input;
        std::getline(std::cin, input);

        std::cout << std::endl;

        char input_char;
        if (input.size() != 1) {
            input_char = ' ';
        } else {
            input_char = std::tolower(input[0]);
        }
        
        switch (input_char)
        {
        case 'x':
            return 0;
        case 'p':
            return 1;
        case 'm':
            return 2;
        case 'f':
            return 3;
        case 'r':
            return 4;

        default:
            if (loopCount < 3) {
                std::cout << RED_ASCII << "Invalid input '" << input_char << "'. Please try again." << RESET_ASCII << std::endl;
                loopCount++;
            } else {
                std::cout << RED_ASCII << "Too many invalid inputs. Exiting program." << RESET_ASCII << std::endl;
                return 0;
            }
        }
    } while (true);
    return 0;
}

std::vector<float> getMagnitudes(InputData data) {


    std::vector<float> magnitudes = {};
    for (int i = 0; i < data.xValues.size(); i++) {
        float x = data.xValues[i];
        float y = data.yValues[i];
        float magnitude = sqrt(x*x + y*y);
        magnitudes.push_back(magnitude);
    }
    return magnitudes;
}

static int getNLines(int nDefault, int max) {

    int nLines = nDefault;
    std::string input;
    std::cout << "Enter number of datapoints to print (Default " << nDefault << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        nLines = std::stoi(input);
    }

    if (nLines > max) {
        std::cout << "Warning: Data contains " << max << " datapoints - fewer than " << nLines << " datapoints." << std::endl;
        std::cout << "Printing first " << nDefault << " datapoints:" << std::endl;
        nLines = nDefault;
    }
    return nLines;
}

int printData(InputData data) {

    int nLines = getNLines(5, data.xValues.size());

    for (int i = 0; i < nLines; i++) {
        std::cout << i << " | x: " << data.xValues[i] << " y: " << data.yValues[i] << std::endl;
    }
    std::cout << std::endl << "Press enter to continue...";
    std::cin.ignore();
    std::cout << "\r" << std::string(100, '*') << std::endl << std::endl;

    return 0;
}

int printData(std::vector<float> data) {
    int nLines =  getNLines(5, data.size());

    for (int i = 0; i < nLines; i++) {
        std::cout << i << " | " << data[i] << std::endl;
    }

    std::cout << std::endl << "Press enter to continue..." << std::endl << std::endl;
    std::cin.ignore();


    return 0;
}

static float calcChi2(InputData data, InputData expectedErrData, float gradient, float intercept) {
    if (data.xValues.size() != expectedErrData.xValues.size()) {
        throw std::runtime_error("Data and expected error data have different sizes");
    }

    std::vector<float> xValues = {};
    std::vector<float> yValues = {};
    float chi2 = 0;
    for (int i = 0; i < data.xValues.size(); i++) {
        float x = data.xValues[i];
        float y = data.yValues[i];
        float predictedY = gradient * x + intercept;
        float expectedErr = expectedErrData.yValues[i];
        float error = y - predictedY;
        chi2 += (error * error) / (expectedErr * expectedErr);
    }

    return chi2;
}


FitLine calcFitLine(InputData data, std::string expectedErrFilename) {

    InputData errData;
    errData = readData(expectedErrFilename);

    float sumX = 0;
    float sumY = 0;
    float sumXY = 0;
    float sumX2 = 0;
    for (int i = 0; i < data.xValues.size(); i++) {
        sumX += data.xValues[i];
        sumY += data.yValues[i];
        sumXY += data.xValues[i] * data.yValues[i];
        sumX2 += data.xValues[i] * data.xValues[i];
    }

    float n = data.xValues.size();
    float gradient = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    float intercept = (sumX2*sumY - sumXY*sumX) / (n*sumX2 - sumX*sumX);

    float chi2 = calcChi2(data, errData, gradient, intercept);
    return {gradient, intercept, chi2};
}

int save(FitLine fitLine, std::string filename) {
    std::string filepath = OUTPUT_DIR + filename;
    std::ofstream output_file(filepath);
    if (!output_file.is_open()) {
        std::cout << "Could not open file '" << filepath << "'" << std::endl;
        return 1;
    }
    output_file << "y=" << fitLine.gradient << "x+" << fitLine.intercept << std::endl;
    output_file << "Chi2/NDF: " << fitLine.chi2/2 << std::endl;
    output_file.close();
    return 0;
}

int save(std::vector<float> data, std::string filename) {
    std::string filepath = OUTPUT_DIR + filename;
    std::ofstream output_file(filepath);
    if (!output_file.is_open()) {
        std::cout << "Could not open file '" << filepath << "'" << std::endl;
        return 1;
    }
    for (int i = 0; i < data.size(); i++) {
        output_file << data[i] << std::endl;
    }
    output_file.close();
    return 0;
}

int save(InputData data, std::string filename) {
    std::string filepath = OUTPUT_DIR + filename;
    std::ofstream output_file(filepath);
    if (!output_file.is_open()) {
        std::cout << "Could not open file '" << filepath << "'" << std::endl;
        return 1;
    }
    output_file << "x,y" << std::endl;
    for (int i = 0; i < data.xValues.size(); i++) {
        output_file << data.xValues[i] << "," << data.yValues[i] << std::endl;
    }
    output_file.close();
    return 0;
}


static void calcXtoY(float* result, float x, int yRounded) {
    
    if (yRounded == 0) {
        return;
    } else {
        *result = *result * x;
        calcXtoY(result, x, yRounded - 1);
    }
}

std::vector<float> xToY(InputData data) {
    std::vector<float> results = {};
    for (int i = 0; i < data.xValues.size(); i++) {
        float x = data.xValues[i];
        int y = std::round(data.yValues[i]);
        float result = 1;
        calcXtoY(&result, x, y);
        results.push_back(result);
    }
    
    return results;

}



