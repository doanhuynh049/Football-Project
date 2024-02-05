#include <gtest/gtest.h>
#include "Logger.h"   // Include the header file with logging functions
#include <filesystem> // feature in C++17
#include <iostream>
#include <fstream>     // Include the necessary header for std::ofstream

// #include <ofstream>
// Define a fixture for logging tests
class LoggerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Create any necessary setup for your tests
    }

    void TearDown() override
    {
        // Clean up after your tests if needed
    }
};
TEST_F(LoggerTest, ensureDirectoryExists)
{
    std::string directoryPath = "directoryTesting";
    std::filesystem::create_directory(directoryPath);
    bool result = ensureDirectoryExists(directoryPath);
    EXPECT_TRUE(result);
    std::filesystem::remove_all(directoryPath);
}   
TEST_F(LoggerTest, ensureDirectoryExists_1)
{
    std::string directoryPath = "directoryTesting";
    std::ofstream file(directoryPath); // Fix: Include necessary header for std::ofstream
    if (file.is_open())
    {
        file << "Hello, this is a sample file content.";
        file.close();
    }
    bool result = ensureDirectoryExists(directoryPath);
    EXPECT_FALSE(result);
    std::filesystem::remove(directoryPath);
}