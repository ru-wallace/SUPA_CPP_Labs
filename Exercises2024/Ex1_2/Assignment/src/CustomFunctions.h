#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#pragma once

extern const std::string OUTPUT_DIR;
extern const std::string INPUT_FILE;
extern const std::string INPUT_ERR_FILE;



struct InputData {
    std::vector<float> xValues;
    std::vector<float> yValues;
};

// gradient and intercept are p and q respectively in the equation y = px + q
struct FitLine { 
    float gradient; 
    float intercept;
    float chi2;
};

InputData readData(std::string filename);
int getOption();
std::vector<float> getMagnitudes(InputData data);

int printData(InputData data);
int printData(std::vector<float> data);

FitLine calcFitLine(InputData data, std::string expectedErrFilename);

int save(FitLine fitLine, std::string filename);
int save(std::vector<float> data, std::string filename);
int save(InputData data, std::string filename);

std::vector<float> xToY(InputData data);

