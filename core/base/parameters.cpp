
#include <string>
#include <iostream> 

#include "parameters.hpp"
#include "application.hpp"
#include "log.hpp"

using namespace Bx::Base;

namespace po = boost::program_options;

Parameters::Parameters():
_basicParams("Basic")
{
  _basicParams.add_options()
              //("version,v", "application version information")
              ("help,h", "help information")
             // ("file,f", po::value<std::string>(), "configuration file in INI format")
              //("log-level,ll", po::value<std::string>()->default_value("inf"),
               // "log level: dbg, inf (default), wrn, err, ftl")
             // ("log-file,lf", po::value<std::string>(), "log file name")
              ;
}

int 
Parameters::getParams(int argc, const char* pArgv[])
{
  BX_ASSERT((argc && pArgv), "Missing arguments");

  int ret(0);

  for(int i = 0; i < argc; i++)
  {
    std::cout << pArgv[i] << std::endl;
  }
  
  po::options_description all_parameters;

  all_parameters.add(_basicParams).add(_specificParams);
  
  po::store(po::parse_command_line(argc, pArgv, _basicParams), _parameter_map);

  //po::notify(_parameter_map);
    for (po::variables_map::iterator it=_parameter_map.begin(); it!=_parameter_map.end(); ++it)
    std::cout << it->first; //  << " => " << it->second << '\n';


  if(_parameter_map.count("help"))
  {
    // Help message requested
    std::cout << pArgv[0] << std::endl;
    
    if(_helpMessage.size())
    {
      std::cout << _helpMessage << std::endl;
    }
      
    std::cout << all_parameters << std::endl;

    ret = 1;
  }
  else if(_parameter_map.count("version"))
  {
    // Help message requested
    std::cout << "Application version information:"
      << Application::appInfo() << std::endl;
  }
  else
  {
    // Read the parameters from file if file was specified
    if(_parameter_map.count("file"))
    {
      BX_LOG(LOG_INF, "Reading parameters from file '%s'",
        _parameter_map["file"].as<std::string>().c_str())
      
      // Need to load the configuration from the file
      std::ifstream fileName(_parameter_map["file"].as<std::string>().c_str());
      po::store(po::parse_config_file(fileName, all_parameters),
        _parameter_map);
      
      po::notify(_parameter_map);
    }
  }

  // Extract some parameters if available
  if( _parameter_map.count("log-level") )
  {
    _logLevel = _parameter_map["log-level"].as<std::string>();
  }

  if(_parameter_map.count("log-file"))
  {
    _logFile = _parameter_map["log-file"].as<std::string>();
  }
 
  return ret;
}

