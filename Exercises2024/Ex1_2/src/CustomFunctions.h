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

/**
 * Reads data from a file and returns it as a struct containing two vectors of floats
 * 
 * @param filename The path of the file to read from
 */
InputData readData(std::string filename);

/**
 * Prompts the user to select an option from a list of options
 * 
 * @return The selected option as an integer
 */
int getOption();

/**
 * Calculates the magnitudes of the x and y values in the input data
 * using the formula sqrt(x^2 + y^2)
 * 
 * @param data The input data
 * @return A vector of floats containing the magnitudes
 */
std::vector<float> getMagnitudes(InputData data);

/**
 * Prints the x and y values from the input data
 * 
 * @param data The input data
 */
int printData(InputData data);

/**
 * Prints a vector of floats
 * 
 * @param data The vector of floats to print
 */
int printData(std::vector<float> data);

/**
 * Calculates the gradient and intercept of a fit line for the input data
 * 
 * @param data The input data
 * @param expectedErrFilename The path of the file containing the expected error data
 * @return A FitLine struct containing the gradient, intercept and chi squared value
 */
FitLine calcFitLine(InputData data, std::string expectedErrFilename);

/**
 * Saves the gradient, intercept and chi squared value of a fit line to a file
 * 
 * @param fitLine The fit line to save
 * @param filename The path of the file to save to
 */
int save(FitLine fitLine, std::string filename);

/**
 * Saves a vector of floats to a file
 * 
 * @param data The vector of floats to save
 * @param filename The path of the file to save to
 */
int save(std::vector<float> data, std::string filename);

/** 
 * Saves the x and y values from the input data to a file
 * 
 * @param data The input data
 * @param filename The path of the file to save to
 */
int save(InputData data, std::string filename);

/**
 * Calculates x to the power of y for each pair of x and y values in the input data
 * 
 * @param data The input data
 * @return A vector of floats containing the results of x^y
 */
std::vector<float> xToY(InputData data);

