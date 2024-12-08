/**
 * @file file_io.hpp
 * @author tomo-uchiyama@moegi.waseda.jp
 * @date 2024-01-05
 * @copyright Copyright (c) 2024
 * @brief File I/O class.
 */

#ifndef UTILS_FILE_IO_H_
#define UTILS_FILE_IO_H_

#include <cstdint>
#include <string>
#include <vector>

namespace utils {

/**
 * @class FileIo
 * @brief A class providing file I/O operations.
 */
class FileIo {
public:
    /**
     * @brief Constructs a FileIo object with optional parameters.
     *
     * Constructs a FileIo object with the provided settings.
     *
     * @param debug Determines if debug mode is enabled. Defaults to false.
     * @param ext Specifies the file extension. Defaults to ".dat".
     */
    FileIo(const bool debug = false, const std::string ext = ".dat");

    /**
     * @brief Writes a uint32_t value to a file.
     *
     * Writes the provided 'data' value of type uint32_t to the specified 'file_path'.
     * If 'append' is true, the value will be appended to the file; otherwise, the file will be overwritten.
     *
     * @param file_path The path to the file where the value will be written.
     * @param data The uint32_t value to be written to the file.
     * @param append If true, appends the value to the file; otherwise, overwrites the file. Defaults to false.
     */
    void WriteValueToFile(const std::string &file_path, const uint32_t data, const bool append = false);

    /**
     * @brief Writes a vector of uint32_t values to a file.
     *
     * Writes the contents of the provided 'data' vector of uint32_t values to the specified 'file_path'.
     * If 'append' is true, the vector contents will be appended to the file; otherwise, the file will be overwritten.
     *
     * @param file_path The path to the file where the vector contents will be written.
     * @param data The vector of uint32_t values to be written to the file.
     * @param append If true, appends the vector contents to the file; otherwise, overwrites the file. Defaults to false.
     */
    void WriteVectorToFile(const std::string &file_path, const std::vector<uint32_t> &data, const bool append = false);

    /**
     * @brief Writes a string to a file.
     *
     * Writes the provided 'data' string to the specified 'file_path'.
     * If 'append' is true, the string will be appended to the file; otherwise, the file will be overwritten.
     *
     * @param file_path The path to the file where the string will be written.
     * @param data The string to be written to the file.
     * @param append If true, appends the string to the file; otherwise, overwrites the file. Defaults to false.
     */
    void WriteStringToFile(const std::string &file_path, const std::string &data, const bool append = false);

    /**
     * @brief Writes a vector of strings to a file.
     *
     * Writes the contents of the provided 'data' vector of strings to the specified 'file_path'.
     * Each string is written as a separate line in the file.
     * If 'append' is true, the vector contents will be appended to the file; otherwise, the file will be overwritten.
     *
     * @param file_path The path to the file where the vector contents will be written.
     * @param data The vector of strings to be written to the file.
     * @param append If true, appends the vector contents to the file; otherwise, overwrites the file. Defaults to false.
     */
    void WriteStringVectorToFile(const std::string &file_path, const std::vector<std::string> &data, const bool append = false);

    /**
     * @brief Reads a uint32_t value from a file.
     *
     * Reads a uint32_t value from the specified 'file_path'.
     * The read value is stored in the 'data' variable.
     *
     * @param file_path The path to the file from which the value will be read.
     * @param data The reference to a uint32_t variable where the read value will be stored.
     */
    void ReadValueFromFile(const std::string &file_path, uint32_t &data);

    /**
     * @brief Reads a vector of uint32_t values from a file.
     *
     * Reads a vector of uint32_t values from the specified 'file_path'.
     * The read values are stored in the provided 'data' vector.
     *
     * @param file_path The path to the file from which the vector will be read.
     * @param data The reference to a vector of uint32_t values where the read values will be stored.
     */
    void ReadVectorFromFile(const std::string &file_path, std::vector<uint32_t> &data);

    /**
     * @brief Reads a string from a file.
     *
     * Reads a string from the specified 'file_path' and stores it in the 'data' string variable.
     *
     * @param file_path The path to the file from which the string will be read.
     * @param data The reference to a string variable where the read string will be stored.
     */
    void ReadStringFromFile(const std::string &file_path, std::string &data);

    /**
     * @brief Clears the contents of a file.
     *
     * Opens the specified file at 'file_path' and clears its contents, effectively making the file empty.
     *
     * @param file_path The path to the file whose contents will be cleared.
     */
    void ClearFileContents(const std::string &file_path);

    /**
     * @brief Opens a file for writing.
     *
     * Opens the specified file at 'file_path' for writing based on the provided 'append' mode.
     * If 'append' is true, the file is opened in append mode; otherwise, it's opened in truncation mode.
     * The opened file is associated with the provided 'file' stream object.
     *
     * @param file The reference to the ofstream object to associate with the opened file.
     * @param file_path The path to the file to be opened for writing.
     * @param file_name The name of the function calling this method for error messages.
     * @param line_num The line number of the function calling this method for error messages.
     * @param append If true, opens the file in append mode; otherwise, opens it in truncation mode.
     * @return Returns true if the file was successfully opened; otherwise, false.
     */
    bool OpenFile(std::ofstream &file, const std::string &file_path, const std::string &location, const bool append = false);

    /**
     * @brief Opens a file for reading.
     *
     * Opens the specified file at 'file_path' for reading and associates it with the provided 'file' ifstream object.
     *
     * @param file The reference to the ifstream object to associate with the opened file.
     * @param file_path The path to the file to be opened for reading.
     * @param file_name The name of the function calling this method for error messages.
     * @param line_num The line number of the function calling this method for error messages.
     * @return Returns true if the file was successfully opened; otherwise, false.
     */
    bool OpenFile(std::ifstream &file, const std::string &file_path, const std::string &location);

    /**
     * @brief Reads the number of elements from the first line of a file.
     *
     * Reads the number of elements from the first line of the provided 'file' ifstream object
     * and returns the count of elements read as a uint32_t value.
     *
     * @param file The reference to the ifstream object from which the number of elements will be read.
     * @param file_name The name of the function calling this method for error messages.
     * @param line_num The line number of the function calling this method for error messages.
     * @return Returns the count of elements read from the file. If the format is invalid or unable to read,
     * it returns zero (0).
     */
    uint32_t ReadNumCountFromFile(std::ifstream &file, const std::string &location);

    /**
     * @brief Splits a string into uint32_t values and stores them in a vector.
     *
     * Parses the provided 'str' string using the ',' delimiter and extracts uint32_t values.
     * It stores these values in the 'data' vector<uint32_t>.
     *
     * @param str The input string to be split into uint32_t values.
     * @param data The vector<uint32_t> to store the extracted uint32_t values.
     */
    void SplitStringToUint32(const std::string &str, std::vector<uint32_t> &data);

private:
    const bool        debug_; /**< Flag indicating debug mode. */
    const std::string ext_;   /**< File extension for file operations. */
};

}    // namespace utils

#endif    // UTILS_FILE_IO_H_
