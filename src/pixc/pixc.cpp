#include <iostream>
#include <string>
#include <vector>
#include <cerrno>
#include <boost/program_options.hpp>
#include <boost/foreach.hpp>
#include "pixie_config.hpp"
#include "lexer.hpp"
#include "common.hpp"

namespace po = boost::program_options;
using namespace std;

int main(int argc, const char **argv) {

    bool print_ast = false;
    
    po::options_description desc("Compiler options");
    desc.add_options()
            ("help", "Print this message")
            ("version,v", "Print the version number")
            ("ast", "Print the AST during compile")
            ("FILE", po::value<vector<string> >()->required(), "Pixie source files")
            ;
    
    po::positional_options_description pdesc;
    pdesc.add("FILE", -1);
    
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv)
            .options(desc)
            .positional(pdesc)
            .run(), vm);

    if (vm.count("help")) {
        cout << desc << "\n";
        return 0;
    }
    
    po::notify(vm);
    
    if (vm.count("version")) {
        cout << "Pixie Compiler version " 
                << PIXIE_VERSION_MAJOR << "." 
                << PIXIE_VERSION_MINOR << "\n";
        
        return 0;
    }
    
    if (vm.count("ast")) {
        print_ast = true;
    }
    
    if (!vm.count("FILE")) {
        cerr << "Must supply at least one source file." << "\n";
    }
    
    cout << "Gonna print out AST? " 
            << string(print_ast ? "true" : "false") << "\n";
    
    cout << "Source files:\n";
    
    vector<string> files = vm["FILE"].as<vector<string> >();
    
    BOOST_FOREACH(string file, files) {
        
        cout << "    " << file << "\n";
        
        pixie::compile::_test_tokenizer(file);
        
        cout << endl;
    }

    return 0;
}