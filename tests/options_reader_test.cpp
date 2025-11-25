//
// Created by mshamrai on 11/25/25.
//
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>

#include "options_reader.h"

class OptionsReaderTest : public ::testing::Test
{
protected:
    std::string inFile;
    std::string outFile;
    std::string algType;
    int k;

    void SetUp() override {
        inFile = "";
        outFile = "";
        algType = "";
        k = -1;
    }

    void callGetAllParameters(const std::vector<std::string>& args) {
        std::vector<char*> argv;

        argv.push_back(const_cast<char*>("program_name"));
        for (const auto& arg : args) {
            argv.push_back(const_cast<char*>(arg.data()));
        }
        argv.push_back(nullptr);

        int argc = static_cast<int>(argv.size()) - 1;

        getAllParameters(inFile, outFile, algType, k, argc, argv.data());
    }
};

TEST_F(OptionsReaderTest, throws_exception_when_input_file_missing)
{
    // No -input-file provided
    std::vector<std::string> args = {
        "-output-file", "out.txt",
        "-k", "5"
    };

    EXPECT_THROW(callGetAllParameters(args), std::invalid_argument);
}

TEST_F(OptionsReaderTest, check_default_values)
{
    // Only input file provided
    std::vector<std::string> args = {
        "-input-file", "data.in"
    };

    callGetAllParameters(args);

    EXPECT_EQ(inFile, "data.in");
    EXPECT_EQ(outFile, "result.txt"); // Default output
    EXPECT_EQ(algType, "exact");               // Default type
    EXPECT_EQ(k, 1);                  // Default k
}

TEST_F(OptionsReaderTest, check_all_parameters_approximation)
{
    // Providing all arguments, setting type to approximation
    std::vector<std::string> args = {
        "-input-file", "graph.txt",
        "-output-file", "output.txt",
        "-type", "approximation",
        "-k", "10"
    };

    callGetAllParameters(args);

    EXPECT_EQ(inFile, "graph.txt");
    EXPECT_EQ(outFile, "output.txt");
    EXPECT_EQ(algType, "approximation");
    EXPECT_EQ(k, 10);
}

TEST_F(OptionsReaderTest, check_all_parameters_exact_explicit)
{
    // Explicitly setting exact type
    std::vector<std::string> args = {
        "-input-file", "graph.txt",
        "-type", "exact",
        "-k", "3"
    };

    callGetAllParameters(args);

    EXPECT_EQ(algType, "exact");
    EXPECT_EQ(k, 3);
}

TEST_F(OptionsReaderTest, check_invalid_type_defaults_to_exact)
{
    // Passing garbage type
    std::vector<std::string> args = {
        "-input-file", "test.in",
        "-type", "super_fast_algo" // Invalid
    };

    callGetAllParameters(args);

    // Should log a warning and default to exact=true
    EXPECT_EQ(algType, "exact");
}

TEST_F(OptionsReaderTest, check_invalid_k_defaults_to_one)
{
    // Passing k <= 0
    std::vector<std::string> args = {
        "-input-file", "test.in",
        "-k", "0"
    };

    callGetAllParameters(args);

    // Should log a warning and default k to 1
    EXPECT_EQ(k, 1);
}

TEST_F(OptionsReaderTest, check_negative_k_defaults_to_one)
{
    // Passing negative k
    std::vector<std::string> args = {
        "-input-file", "test.in",
        "-k", "-5"
    };

    callGetAllParameters(args);

    EXPECT_EQ(k, 1);
}

TEST_F(OptionsReaderTest, check_case_insensitivity_for_type)
{
    // "APPROXIMATION" in caps
    std::vector<std::string> args = {
        "-input-file", "test.in",
        "-type", "APPROXIMATION"
    };

    callGetAllParameters(args);

    // The function transforms input to lower, so this should work
    EXPECT_EQ(algType, "approximation");
}