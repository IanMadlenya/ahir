#include <signal.h>
#include <getopt.h>
#include <vcSystem.hpp>
#include <vcParser.hpp>
#include <vcLexer.hpp>

using namespace std;
struct option long_options[] = {
    {"relaxed-component-visibility", 0, 0, 0},
    {"depend", required_argument, 0, 0},
    {0, 0, 0, 0}
};

void Handle_Segfault(int signal)
{
  vcSystem::Error("in vc2vhdl: segmentation fault! giving up!!");
  exit(-1);
}

void Usage_Vc2VHDL()
{
  cerr << "Usage: " << endl;
  cerr << "vc2vhdl [-O] [-C] [-s <ghdl/modelsim>] -f <vc-file> [-f <vc-file>...] -t <top-module> [-t <top-module>...] " << endl << endl;
  cerr << "specify vc-files using -f, top-modules in system using -t.. for example" << endl
       << "    vc2vhdl -O -t foo -f file1.vc -f file2.vc -t bar" << endl;
  cerr << "file1.vc and file2.vc will be parsed in order, and the instantiated " << endl
       << "system will have modules foo and bar as top-modules. " << endl;
  cerr << "-O option will lead to smaller VHDL files due to some compaction" << endl
       << "-C option will produce testbench which listens on socket for foreign TB. " << endl;
  cerr << "-s ghdl will produce a testbench which uses VHPI and can link to GHDL" << endl
       << "-s modelsim will produce a testbench which uses Modelsim-FLI and can link to Modelsim. " << endl;
}


int main(int argc, char* argv[])
{


  string sys_name = "test_system";
  vcSystem test_system(sys_name);
  
  vector<string> file_list;
  set<string> file_set;
  set<string> top_modules;

  // command-line parsing
  extern int optind;
  extern char *optarg;
  int opt;
  int option_index = 0;

  signal(SIGSEGV, Handle_Segfault);

  if(argc < 3)
    {
      Usage_Vc2VHDL();
      exit(1);
    }



  string fname;
  string mod_name;
  string opt_string;
  string sim_id;

  vcSystem::_opt_flag = false;
  while ((opt = 
	  getopt_long(argc, 
		      argv, 
		      "t:f:OCs:",
		      long_options, &option_index)) != -1)
    {
      switch (opt)
	{
	case 'f':
	  fname = string(optarg);	
	  if(file_set.find(fname) != file_set.end())
	    {
	      cerr << "Error: multiple occurences of VC file " << fname << " in argument list" << endl;
	    }
	  else
	    {
	      file_set.insert(fname);
	      file_list.push_back(fname);
	    }
	  break;
	case 't':
	  mod_name = string(optarg);	
	  top_modules.insert(mod_name);
	  break;
	case 'O':
	  vcSystem::_opt_flag = true;
	  cerr << "Info: -O option selected: will flatten and reduce control path" << endl;
	  break;
	case 'C':
	  vcSystem::_vhpi_tb_flag = true;
	  cerr << "Info: -C option selected: will generate testbench which connects to foreign link" << endl;
	  break;
	case 's':
	  sim_id = string(optarg);
	  if(sim_id == "ghdl")
	  {
	     cerr << "Info: -s ghdl option selected: will generate testbench with VHPI link" << endl;
	     vcSystem::_simulator_prefix = "Vhpi_";
	  }
	  else 
          {
	     cerr << "Info: -s modelsim option selected: will generate testbench with VHPI link" << endl;
          }
	  break;
	case '?':		  // incorrect option
	  opt_string = opt;
	  cerr << (string("Error: ") + " illegal option " + opt_string);
	  Usage_Vc2VHDL();
	  break;
	default:
	  break;
	}
    }



  for(int idx = 0; idx < file_list.size(); idx++)
    {

      string filename = file_list[idx];
      
      test_system.Parse(filename);
      
      if(vcSystem::Get_Error_Flag())
	{
	  cerr << "Error: there were errors during parsing, check the log" << endl;
	  return(1);
	}
    }

  if(!vcSystem::Get_Error_Flag())
    {
      for(set<string>::iterator iter = top_modules.begin();
	  iter != top_modules.end();
	  iter++)
	{
	  test_system.Set_As_Top_Module(*iter);
	}

      test_system.Elaborate();
      cout << "-- VHDL produced by vc2vhdl from virtual circuit (vc) description " << endl;
      test_system.Print_VHDL(cout);

      if(vcSystem::_vhpi_tb_flag)
	test_system.Print_VHDL_Vhpi_Test_Bench(cout);
      else
	test_system.Print_VHDL_Test_Bench(cout);
    }

  return(0);
}


