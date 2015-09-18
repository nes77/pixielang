#include <iostream>
#include <string>
#include <boost/program_options/options_description.hpp>
#include "pixie_config.hpp"
#include "common.hpp"

namespace po = boost::program_options;

int main(int argc, const char **argv) {

    bool print_ast = false;
    
    po::options_description desc("Compiler options");
    desc.add_options()
            ("help", "Print this message")
            ("version,v", "Print the version number")
            ("ast", "Print the AST during compile")
            ;
    
    po::positional_options_description pdesc;
    pdesc.add("FILE", -1);
    
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv)
            .options(desc)
            .positional(pdesc)
            .run(), vm);
    
    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 0;
    }
    
    if (vm.count("version")) {
        std::cout << "Pixie Compiler version " 
                << PIXIE_VERSION_MAJOR << "." 
                << PIXIE_VERSION_MINOR << "\n";
        
        return 0;
    }
    
    if (vm.count("ast")) {
        print_ast = true;
    }

    return 0;
}