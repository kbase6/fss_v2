#include <functional>
#include <getopt.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../comm/comm.hpp"
#include "../tools/secret_sharing.hpp"
#include "../tools/tools.hpp"
#include "../utils/file_io.hpp"
#include "../utils/utils.hpp"

int main(int argc, char *argv[]) {
    int           port         = comm::kDefaultPort;
    std::string   host_address = comm::kDefaultAddress;
    int           party_id     = -1;
    std::string   exec_mode;
    std::string   function_name;
    int           function_mode = 0;
    std::string   output_file;
    int           iteration = 1;
    utils::FileIo io(false, ".log");

    const char *const short_opts  = "p:s:n:m:o:i:h";
    const option      long_opts[] = {
        {"port", required_argument, nullptr, 'p'},
        {"server", required_argument, nullptr, 's'},
        {"name", required_argument, nullptr, 'n'},
        {"mode", required_argument, nullptr, 'm'},
        {"output", required_argument, nullptr, 'o'},
        {"iteration", required_argument, nullptr, 'i'},
        {"help", no_argument, nullptr, 'h'},
        {nullptr, no_argument, nullptr, 0}};

    while (true) {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);
        if (opt == -1)
            break;

        try {
            switch (opt) {
                case 'p':
                    port = std::stoi(optarg);
                    break;
                case 's':
                    host_address = optarg;
                    break;
                case 'n':
                    function_name = optarg;
                    break;
                case 'm':
                    function_mode = std::stoi(optarg);
                    break;
                case 'o':
                    output_file = optarg;
                    break;
                case 'i':
                    iteration = std::stoi(optarg);
                    break;
                case 'h':
                    DisplayHelp();
                    return EXIT_SUCCESS;
                default:
                    std::cerr << "Invalid option\n\n";
                    DisplayHelp();
                    return EXIT_FAILURE;
            }
        } catch (const std::invalid_argument &e) {
            std::cerr << "Invalid argument for option -" << static_cast<char>(opt) << ": " << optarg << " is not a number.\n";
            return EXIT_FAILURE;
        } catch (const std::out_of_range &e) {
            std::cerr << "Argument out of range for option -" << static_cast<char>(opt) << ": " << optarg << " is too large.\n";
            return EXIT_FAILURE;
        } catch (...) {
            std::cerr << "Unexpected error occurred while processing option -" << static_cast<char>(opt) << ": " << optarg << ".\n";
            return EXIT_FAILURE;
        }
    }

    if (optind + 1 < argc) {
        party_id  = std::stoi(argv[optind]);
        exec_mode = argv[optind + 1];
        if (party_id != 0 && party_id != 1) {
            std::cerr << "Invalid party_id. It must be 0 or 1.\n";
            return 1;
        }
        if (exec_mode != "test" && exec_mode != "bench") {
            std::cerr << "Invalid mode. It must be 'test' or 'bench'.\n";
            return 1;
        }
    } else {
        std::cerr << "Party ID and mode are required. Use -h, --help for usage.\n";
        return 1;
    }

    comm::CommInfo               comm_info(party_id, port, host_address);
    tools::secret_sharing::Party party(comm_info);
    fss::DebugInfo               dbg_info;


    // ########################################
    // ############ TEST FUNCTIONS ############
    if (exec_mode == "test") {
        utils::Logger::InfoLog(LOCATION, "Mode: Test");
        fss::TestInfo test_info;
        test_info.domain_size = utils::CreateSequence(8, 9);
        test_info.dbg_info    = dbg_info;
        test_info.mode        = function_mode;

        SetupTestFuncMap(party, comm_info, test_info);
        if (test_func_map.find(function_name) != test_func_map.end()) {
            test_func_map[function_name]();    // Run the function associated with the function_name key
            if (!output_file.empty()) {
                const std::string log_file = utils::GetCurrentDirectory() + "/log/test/" + output_file + std::to_string(party_id);
                utils::Logger::SaveLogsToFile(log_file, false);
                utils::Logger::InfoLog(LOCATION, "Log file saved: " + log_file + ".log");
            }
        } else {
            utils::Logger::FatalLog(LOCATION, "Invalid function name: '" + function_name + "'. Please set the correct function name from the list below by using -n (--name) option.");
            utils::Logger::InfoLog(LOCATION, "Available functions list: [" + utils::VectorToStr<std::string>(test_names, ", ") + "]");
            return EXIT_FAILURE;
        }
    }

    return 0;
}
