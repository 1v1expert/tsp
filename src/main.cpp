#include <iostream>
#include <map>
#include <fstream>

#include "Tests/TestExecutor.hpp"
#include "ElasticNet/ElasticNet.hpp"

using std::map;
using std::string;
using std::ostream;
using std::fstream;

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::move;

enum class WorkingMode
{
    Help, InputPath, OutputPath, Test
};

struct ParametersProcessor
{
    static bool ProcessInput(int argc, char ** argv)
    {
        if (argc == 1) return false;

        for (auto i = 0; i < argc; ++i)
        {
            if (strcmp(argv[i], "--help") == 0)
            {
                input_map[WorkingMode::Help] = "";
            }
            else if (strcmp(argv[i], "--input") == 0 && i + 1 < argc)
            {
                input_map[WorkingMode::InputPath] = { argv[i + 1] };
            }
            else if (strcmp(argv[i], "--output") == 0 && i + 1 < argc)
            {
                input_map[WorkingMode::OutputPath] = { argv[i + 1] };
            }
            else if (strcmp(argv[i], "--test") == 0)
            {
                input_map[WorkingMode::Test] = "";
            }
        }

        return true;
    }

    static ostream& Help(ostream& stream)
    {
        stream << "Available options:\n"
               << "--help (Print available options)\n"
               << "--input [path] (Input path for csv file with adjacency matrix)\n"
               << "--output [path] (Output path for hamiltonial path (task solution))\n"
               << "--test (Run unit tests)\n";
        return stream;
    }

    static map<WorkingMode, string> input_map;
};

map<WorkingMode, string> ParametersProcessor::input_map;

int main(int argc, char ** argv)
{
    if (!ParametersProcessor::ProcessInput(argc, argv))
    {
        cerr << "No input parameters. Type --help to see available input parameters" 
             << endl;
        return -1;
    }
    if (ParametersProcessor::input_map.count(WorkingMode::Help))
    {
        cout << ParametersProcessor::Help;
        return 0;
    }
    if (ParametersProcessor::input_map.count(WorkingMode::Test))
    {
        tsp_tests::TestExecutor::ExecuteAllTests();
        tsp_tests::TestExecutor::PrintStat(cout);
        return 0;
    }
    if (ParametersProcessor::input_map.count(WorkingMode::InputPath) 
        && ParametersProcessor::input_map.count(WorkingMode::OutputPath))
    {
        fstream input_file(ParametersProcessor::input_map[WorkingMode::InputPath], 
            std::ios::in);
        fstream output_file(ParametersProcessor::input_map[WorkingMode::OutputPath],
            std::ios::out | std::ios::trunc);

        if (input_file.is_open() && output_file.is_open())
        {
            if (input_file.peek() == fstream::traits_type::eof())
            {
                cerr << "Input file is empty:\n"
                     << ParametersProcessor::input_map[WorkingMode::InputPath]
                     << endl;
                return -1;
            }

            auto nodes = tsp::NodeFactory<float>::Create(input_file);
            auto ham_path = tsp::ElasticNet<float>::Run(move(nodes));

            cout << *ham_path << endl;
            output_file << *ham_path << endl;
        }
        else
        {
            cerr << "Unable to open file in one of given paths:\n"
                 << ParametersProcessor::input_map[WorkingMode::InputPath]
                 << endl
                 << ParametersProcessor::input_map[WorkingMode::OutputPath]
                 << endl;
            return -1;
        }
    }
    else
    {
        cerr << "No such parameters. Maybe you forget input or output path?\n"
                "Type --help to see available input parameters"
             << endl;
        return -1;
    }
    return 0;
}
