/**
 * @file utils.hpp
 * @author tomo-uchiyama@moegi.waseda.jp
 * @date 2024-01-05
 * @copyright Copyright (c) 2024
 * @brief Utility class.
 */

#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include <cmath>
#include <cstdint>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace utils {

/**
 * @brief Map for terminal output colors.
 *
 * Mapping of color names to corresponding integer values used in terminal output.
 */
inline std::map<std::string, int> color_map = {
    {"red", 31}, {"green", 32}, {"yellow", 33}, {"blue", 34}, {"magenta", 35}, {"cyan", 36}, {"white", 37}, {"black", 30}, {"bright_red", 91}, {"bright_green", 92}, {"bright_yellow", 93}, {"bright_blue", 94}, {"bright_magenta", 95}, {"bright_cyan", 96}, {"bright_white", 97}};

/**
 * @brief Get the Current Date Time As String object
 *
 * @return std::string The current date time as string
 */
std::string GetCurrentDateTimeAsString();

/**
 * @brief Gets the current working directory.
 *
 * This function retrieves the current working directory path
 * and returns it as a string.
 *
 * @return A string containing the current directory path.
 */
std::string GetCurrentDirectory();

/**
 * @brief Creates a sequence of numbers within a given range.
 *
 * Generates a sequence of unsigned 64-bit integers within the specified range.
 * The sequence starts from 'start' (inclusive) and ends at 'end' (exclusive).
 *
 * @param start The starting value of the sequence (inclusive).
 * @param end The ending value of the sequence (exclusive).
 * @return A vector containing the sequence of numbers.
 */
std::vector<uint32_t> CreateSequence(const uint32_t start, const uint32_t end);

/**
 * @brief Creates a vector filled with a specified value.
 *
 * Generates a vector containing 'size' number of elements, all initialized with 'value'.
 *
 * @param value The value used to fill the vector.
 * @param size The number of elements in the vector.
 * @return A vector containing 'size' elements, all initialized with 'value'.
 */
std::vector<uint32_t> CreateVectorWithSameValue(const uint32_t value, const uint32_t size);

/**
 * @brief Converts a std::array to a string with specified delimiter.
 *
 * Converts the elements of the std::array 'array' to a string representation
 * with the specified delimiter 'del' between elements.
 *
 * @tparam T The type of elements in the array. Default is uint32_t.
 * @tparam N The size of the array.
 * @param array The std::array to be converted to a string.
 * @param del The delimiter string used to separate elements in the output string.
 * @return A string representation of the std::array elements separated by 'del'.
 */
template <typename T = uint32_t, std::size_t N>
std::string ArrayToStr(const std::array<T, N> &array, const std::string &del = " ") {
    std::stringstream ss;
    for (std::size_t i = 0; i < array.size(); i++) {
        ss << array[i];
        if (i != array.size() - 1) {
            ss << del;
        }
    }
    return ss.str();
}

/**
 * @brief Converts a std::vector to a string with specified delimiter.
 *
 * Converts the elements of the std::vector 'vec' to a string representation
 * with the specified delimiter 'delimiter' between elements.
 *
 * @tparam T The type of elements in the vector. Default is uint32_t.
 * @param vec The std::vector to be converted to a string.
 * @param del The delimiter string used to separate elements in the output string.
 * @return A string representation of the std::vector elements separated by 'delimiter'.
 */
template <typename T = uint32_t>
std::string VectorToStr(const std::vector<T> &vec, const std::string &del = " ") {
    std::stringstream ss;
    for (std::size_t i = 0; i < vec.size(); i++) {
        ss << vec[i];
        if (i != vec.size() - 1) {
            ss << del;
        }
    }
    return ss.str();
}

/**
 * @brief Converts a boolean vector to a string representation.
 *
 * Converts a vector of boolean values into a string where each boolean value
 * is represented as its corresponding numerical (0 or 1) character.
 *
 * @param bool_vector The input boolean vector to be converted.
 * @return A string representation of the boolean vector.
 */
std::string BoolVectorToStr(const std::vector<bool> &bool_vector);

/**
 * @brief Converts a double value to a string representation with specified precision.
 *
 * Converts the given double value 'val' to a string with the specified number of 'digits' after
 * the decimal point. The resulting string will represent the double value with the specified precision.
 *
 * @param val The double value to be converted to a string.
 * @param digits The number of digits after the decimal point in the resulting string.
 * @return A string representation of the double value with the specified precision.
 */
std::string DoubleToStr(const double val, const size_t digits = 0);

/**
 * @brief Converts an array of bytes to a hexadecimal string representation.
 *
 * Converts the given array of bytes 'data' into a hexadecimal string.
 *
 * @param data Pointer to the array of bytes.
 * @param length The length of the array 'data'.
 * @return A string representing the hexadecimal conversion of the byte array.
 */
std::string ConvertToHex(unsigned char *data, size_t length);

/**
 * @brief Gets a string representation of validity status.
 *
 * Returns a string representation of the validity status based on the boolean value.
 * If 'is_valid' is true, returns "[VALID]"; otherwise, returns "[INVALID]".
 *
 * @param is_valid The boolean representing the validity status.
 * @return A string indicating the validity status ("[VALID]" or "[INVALID]").
 */
std::string GetValidity(const bool is_valid);

// #######################
// ######## Print ########
// #######################

/**
 * @brief Prints text to the console.
 *
 * Prints the provided 'text' to the console output.
 *
 * @param text The text to be displayed.
 */
void PrintText(const std::string &text);

/**
 * @brief Prints colored text to the console.
 *
 * Changes the text color in the console output based on the provided 'color_code' value
 * using ANSI escape codes. The 'text' parameter represents the text to be displayed in color.
 *
 * @param text The text to be displayed in the specified color.
 * @param color_code The ANSI color code to set the console color.
 *                   Refer to ANSI color codes for supported colors.
 *                   For instance, 31 represents red, 32 represents green, and so on.
 */
void PrintColoredText(const std::string &text, const int color_code);

/**
 * @brief Prints bold text to the console.
 *
 * Prints the provided 'text' in bold format to the console output.
 *
 * @param text The text to be displayed in bold format.
 */
void PrintBoldText(const std::string &text);

/**
 * @brief Prints the validity status to the console.
 *
 * Prints the validity status based on the boolean value 'is_valid'.
 * If 'is_valid' is true, prints "[VALID]" in bright green color;
 * otherwise, prints "[INVALID]" in red color.
 *
 * @param is_valid The boolean representing the validity status.
 */
void PrintValidity(const std::string &info_msg, const std::string &msg_body, const bool is_valid, const bool debug);

/**
 * @brief Prints the validity of an equality check to the console.
 *
 * Compares two uint32_t values 'x' and 'y' for equality and prints the result
 * along with function name information to the console.
 *
 * @param info_msg The information message associated with the equality check.
 * @param x The first uint32_t value to compare.
 * @param y The second uint32_t value to compare.
 */
void PrintValidity(const std::string &info_msg, const uint32_t x, const uint32_t y, const bool debug);

/**
 * @brief Print test result.
 *
 * @param test_name  Test name.
 * @param result   Test result.
 */
void PrintTestResult(const std::string &test_name, const bool result);

/**
 * @brief Print an trace message to the console.
 *
 * This function prints a trace message with the specified message body.
 *
 * @param info_msg The information message to be displayed.
 * @param msg_body The message body to be displayed.
 * @param debug If true, the message is printed; if false, the message is not printed.
 */
void PrintTraceMessage(const std::string &info_msg, const std::string &msg_body, const bool debug);

/**
 * @brief Print an debug message to the console.
 *
 *  This function prints an debug message with the specified message body.
 *
 * @param info_msg  The information message to be displayed.
 * @param msg_body  The message body to be displayed.
 * @param debug     If true, the message is printed; if false, the message is not printed.
 */
void PrintDebugMessage(const std::string &info_msg, const std::string &msg_body, const bool debug);

/**
 * @brief Print an information message to the console.
 *
 *  This function prints an information message with the specified message body.
 *
 * @param info_msg  The information message to be displayed.
 * @param msg_body  The message body to be displayed.
 */
void PrintInfoMessage(const std::string &info_msg, const std::string &msg_body);

/**
 * @brief Print a warning message to the console.
 *
 *  This function prints a warning message with the specified message body.
 *
 * @param info_msg  The information message to be displayed.
 * @param msg_body  The message body to be displayed.
 */
void PrintWarningMessage(const std::string &info_msg, const std::string &msg_body);

/**
 * @brief Print an error message to the console.
 *
 *  This function prints an error message with the specified message body.
 *
 * @param info_msg  The information message to be displayed.
 * @param msg_body  The message body to be displayed.
 */
void PrintErrorMessage(const std::string &info_msg, const std::string &msg_body);

/**
 * @brief Print a fatal message to the console.
 *
 *  This function prints a fatal message with the specified message body.
 *
 * @param info_msg  The information message to be displayed.
 * @param msg_body  The message body to be displayed.
 */
void PrintFatalMessage(const std::string &info_msg, const std::string &msg_body);

/**
 * @brief Adds a new line to the console output if debugging is enabled.
 *
 * Adds a new line to the console output if 'debug' is set to true and LOG_LEVEL_DEBUG is defined.
 *
 * @param debug If true, adds a new line; if false, does nothing.
 */
void AddNewLine(bool debug);

/**
 * @brief Prints the help message for the available options.
 *
 * @param func_name The name of the function or context associated with the options.
 * @param line_num The line number where the options are printed.
 * @param options The list of available options.
 */
void OptionHelpMessage(const std::string &location, const std::vector<std::string> &options);

// #############################
// ######## Calculation ########
// #############################

/**
 * @brief Calculates the power of an integer to another integer exponent.
 *
 * Calculates the value of 'base' raised to the power of 'exponent'.
 *
 * @param base The base value.
 * @param exponent The exponent value.
 * @return The result of 'base' raised to the power of 'exponent'.
 */
inline uint32_t Pow(const uint32_t base, const uint32_t exponent) {
    return static_cast<uint32_t>(std::pow(base, exponent));
}

/**
 * @brief Performs modular arithmetic on a value using a specified bit size.
 *
 * Computes the modulo of 'value' using the specified 'bitsize' by performing
 * a bitwise AND operation with a bitmask derived from 'bitsize'.
 *
 * @param value The value on which modulo operation is performed.
 * @param bitsize The bit size used for computing the modulo.
 * @return The result of 'value' modulo (2^bitsize).
 */
inline uint32_t Mod(const uint32_t value, const uint32_t bitsize) {
    return value & ((1UL << bitsize) - 1UL);
}

/**
 * @brief Excludes bits above a specified bit position in a given value.
 *
 * Constructs a mask to exclude bits at positions higher than the 'bit_position'
 * by performing a bitwise AND operation with the 'value'.
 *
 * @param value The value from which bits are to be excluded.
 * @param bit_position The bit position above which bits are to be excluded.
 * @return The result of 'value' after excluding bits above 'bit_position'.
 */
uint32_t ExcludeBitsAbove(const uint32_t value, const uint32_t bit_position);

/**
 * @brief Gets the bit value at a specified position in a given value.
 *
 * Retrieves the bit at the 'bit_position' by constructing a mask
 * and performing a bitwise AND operation with the 'value'.
 *
 * @param value The value from which the bit value is obtained.
 * @param bit_position The position of the bit to be retrieved.
 * @return The boolean value representing the bit at 'bit_position'.
 */
bool GetBitAtPosition(const uint32_t value, const uint32_t bit_position);

/**
 * @brief Gets the lower 'n' bits of a given value.
 *
 * Retrieves the lower 'n' bits of the 'value' by constructing a mask
 * and performing a bitwise AND operation with the 'value'.
 *
 * @param value The value from which the lower bits are obtained.
 * @param n The number of lower bits to be retrieved.
 * @return The lower 'n' bits of the input value.
 */
uint32_t GetLowerNBits(const uint32_t value, const uint32_t n);

/**
 * @brief Converts an unsigned integer to its two's complement representation.
 *
 * Converts the given unsigned integer 'x' to its two's complement representation
 * considering the specified number of bits 'bitsize'.
 *
 * @param x The unsigned integer to be converted.
 * @param bitsize The number of bits representing the integer (including the sign bit).
 * @return The two's complement representation of the unsigned integer.
 */
inline int32_t To2Complement(uint32_t x, const uint32_t bitsize) {
    if (x & (1U << (bitsize - 1))) {    // If the sign bit is 1, indicating a negative number
        x = x - (1U << bitsize);        // Convert to two's complement
    }
    return static_cast<int32_t>(x);
}

/**
 * @brief Calculates the absolute value of an integer.
 *
 * Calculates and returns the absolute value of the given integer 'value'.
 *
 * @param value The integer for which the absolute value is calculated.
 * @return The absolute value of the input integer.
 */
inline uint32_t Abs(int32_t value) {
    // Calculate the absolute value
    uint32_t result = static_cast<uint32_t>(std::abs(value));
    return result;
}

namespace test {

void Test_FileIo(const uint32_t mode, bool debug);

}    // namespace test

}    // namespace utils

#endif    // UTILS_UTILS_H_
