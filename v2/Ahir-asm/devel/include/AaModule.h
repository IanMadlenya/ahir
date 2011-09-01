#ifndef _Aa_Module__
#define _Aa_Module__

#include <AaIncludes.h>
#include <AaUtil.h>
#include <AaRoot.h>
#include <AaScope.h>
#include <AaType.h>
#include <AaValue.h>
#include <AaExpression.h>
#include <AaObject.h>
#include <AaStatement.h>


// *******************************************  MODULE ************************************
// compilation unit: a module is basically a block
// statement, but with arguments
class AaMemorySpace;
class AaModule: public AaSeriesBlockStatement
{
  vector<AaInterfaceObject*>  _input_args;
  vector<AaInterfaceObject*>  _output_args;

  bool _foreign_flag;
  bool _inline_flag;
  bool _pipeline_flag;

  bool _writes_to_shared_pipe;
  bool _reads_from_shared_pipe;

  // memory spaces and pipes accessed by
  // this module.
  vector<AaMemorySpace*> _memory_spaces;

  set<AaPipeObject*> _write_pipes;
  set<AaPipeObject*> _read_pipes;
  set<AaMemorySpace*> _shared_memory_spaces;

  int _number_of_times_called;

  map<string,string> _attribute_map;

 public:
  AaModule(string fname); // Modules have NULL parent (parent is the program)
  ~AaModule();

  void Increment_Number_Of_Times_Called()
  {
    _number_of_times_called++;
  }
  int Get_Number_Of_Times_Called()
  {
    return(_number_of_times_called);
  }

  bool Has_No_Side_Effects();

  void Set_Foreign_Flag(bool ff) { this->_foreign_flag = ff; }
  bool Get_Foreign_Flag() {return(this->_foreign_flag);}

  void Set_Pipeline_Flag(bool ff) { this->_pipeline_flag = ff; }
  bool Get_Pipeline_Flag() {return(this->_pipeline_flag);}
  virtual bool Is_Pipelined() {return(_pipeline_flag);}

  void Set_Inline_Flag(bool ff) { this->_inline_flag = ff; }
  bool Get_Inline_Flag() {return(this->_inline_flag);}

  void Add_Argument(AaInterfaceObject* obj);

  void Add_Attribute(string name, string val)
  {
    _attribute_map[name] = val;
  }
  void Print_Attributes(ostream& ofile);

  unsigned int Get_Number_Of_Input_Arguments() {return(this->_input_args.size());}
  AaInterfaceObject* Get_Input_Argument(unsigned int index)
  {
    return(this->_input_args[index]);
  }

  unsigned int Get_Number_Of_Output_Arguments() {return(this->_output_args.size());}
  AaInterfaceObject* Get_Output_Argument(unsigned int index)
  {
    return(this->_output_args[index]);
  }

  virtual string Get_C_Name()
  {
    return(this->Get_Label());
  }

  void Print(ostream& ofile);
  virtual string Kind() {return("AaModule");}

  virtual AaRoot* Find_Child(string tag);
  virtual void Map_Source_References();

  void Set_Foreign_Object_Representatives();
  string Get_Structure_Name() { return(this->Get_Label() + "_State"); }
  void Write_Header(ofstream& ofile);
  void Write_Source(ofstream& ofile);

  void Write_VC_Model(ostream& ofile);
  void Write_VC_Model(bool opt_flag, ostream& ofile);


  void Write_VC_Control_Path(bool opt_flag, ostream& ofile);


  void Write_VC_Data_Path(ostream& ofile);
  void Write_VC_Memory_Spaces(ostream& ofile);
  void Write_VC_Links(bool opt_flag, ostream& ofile);

  void Write_VC_Model_Optimized(ostream& ofile);

  void Propagate_Constants();
  void Add_Memory_Space(AaMemorySpace* ms)
  {
    _memory_spaces.push_back(ms);
  }

  void Add_Shared_Memory_Space(AaMemorySpace* ms)
  {
    _shared_memory_spaces.insert(ms);
  }

  void Add_Write_Pipe(AaPipeObject* obj)
  {
    if((obj->Get_Scope() == NULL) || 
       (obj->Get_Scope()->Get_Root_Scope() != (AaScope*)this))
      {
	_writes_to_shared_pipe = true;
      }
    _write_pipes.insert(obj);
  }

  void Add_Read_Pipe(AaPipeObject* obj)
  {
    if((obj->Get_Scope() == NULL) || 
       (obj->Get_Scope()->Get_Root_Scope() != (AaScope*)this))
      {
	_reads_from_shared_pipe = true;
      }
    _read_pipes.insert(obj);
  }

  void Write_VHDL_C_Stub_Prefix(ostream& ofile);
  void Write_VHDL_C_Stub_Header(ostream& ofile);
  void Write_VHDL_C_Stub_Source(ostream& ofile);

};

#endif
