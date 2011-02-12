#ifndef _Aa_Object__
#define _Aa_Object__

#include <AaIncludes.h>
#include <AaUtil.h>
#include <AaRoot.h>
#include <AaScope.h>
#include <AaType.h>
#include <AaValue.h>
#include <AaExpression.h>


/*****************************************  OBJECT  ****************************/
// base object
// Each object has a type, a name, a value and a parent

class AaObject: public AaRoot
{

 protected:
  string _name;
  AaConstantLiteralReference* _value;
  AaType* _type;
  AaScope* _scope;

 public:

  AaType* Get_Type() {return(this->_type);}

  AaConstantLiteralReference* Get_Value() {return(this->_value);}
  void Set_Value(AaConstantLiteralReference* v) {this->_value = v;}
  virtual string Get_Name() {return(this->_name);}
  virtual string Get_VC_Name() {return(this->_name);}

  virtual AaScope* Get_Scope() {return(this->_scope);}
  virtual string Tab();

  AaObject(AaScope* scope_tpr, string oname, AaType* object_type);
  ~AaObject();

  virtual void Print(ostream& ofile);  
  virtual string Kind() {return("AaObject");}
  virtual bool Is_Object() {return(true); }

  virtual void PrintC(ofstream& ofile, string tab_string)
  {
    ofile << tab_string << this->Get_Type()->CName() 
	  << " " 
	  <<  this->Get_Name()
	  << this->Get_Type()->CDim();
    ofile << ";" << endl;
  }

  virtual string CRef()
  {
    if(this->Get_Scope())
      return(this->Get_Scope()->Get_Struct_Dereference() + this->Get_Name() + ".__val");
    else
      return(this->Get_Name() + ".__val");
  }

  virtual void Write_Initialization(ofstream& ofile)
  {
    if(this->_value)
      {
	ofile << this->CRef() << " = ";
	this->_value->PrintC(ofile,"");
	ofile << ";" << endl;
      }
  }

  // \todo
  virtual void Write_VC_Model(ostream& ofile);

  virtual bool Is_Constant() {return(false);}
};

// interface object: function arguments
class AaInterfaceObject: public AaObject
{
  // arguments can be input or output
  string _mode; // "in" or "out"

 public:
  string Get_Mode() {return(this->_mode);}

  AaInterfaceObject(AaScope* scope_tpr, string oname, AaType* otype, string mode);
  ~AaInterfaceObject();
  virtual string Kind() {return("AaInterfaceObject");}
  // uses AaObject::Print method

};

class AaConstantObject: public AaObject
{
  // 
 // constants are visible only in pure ancestors
  // or pure descendants.
  //
 public:
  AaConstantObject(AaScope* scope_tpr, string oname, AaType* otype, AaConstantLiteralReference* value);
  ~AaConstantObject();

  virtual void Print(ostream& ofile); 
  virtual string Kind() {return("AaConstantObject");}

  virtual bool Is_Constant() {return(true);}

  // todo: this is different from the base Object..
  virtual void Write_VC_Model(ostream& ofile);
};

class AaStorageObject: public AaObject
{
  // objects will be stored in memory
  //
  int _base_address;    // location of "base" of object.
  int _word_size;       // minimum addressable unit
  
 public:

  AaStorageObject(AaScope* scope_tpr, string oname, AaType* otype, AaConstantLiteralReference* initial_value);
  ~AaStorageObject();

  virtual void Print(ostream& ofile); 
  virtual string Kind() {return("AaStorageObject");}

  // todo: this is the same as object, but keep it here
  //      because the initial value needs to be 
  //      updated..
  virtual void Write_VC_Model(ostream& ofile);
};

class AaPipeObject: public AaObject
{
  
 public:
  AaPipeObject(AaScope* scope_tpr,string oname, AaType* otype);
  ~AaPipeObject();

  virtual void Print(ostream& ofile);
  virtual string Kind() {return("AaPipeObject");}
  virtual string Get_Valid_Flag_Name() { return(this->Get_Name() + "_valid__");}
  virtual string Get_Valid_Flag_Name_Ref() 
  {
    if(this->Get_Scope() == NULL)
      return(this->Get_Valid_Flag_Name());
    else
      return(this->Get_Scope()->Get_Struct_Dereference() + this->Get_Valid_Flag_Name());
  }

  virtual void PrintC(ofstream& ofile, string tab_string)
  {
    this->AaObject::PrintC(ofile,tab_string);
    ofile << tab_string 
	  << "unsigned int " 
	  << this->Get_Valid_Flag_Name() 
	  << " : 1; " 
	  << endl;
  }

   virtual void Write_VC_Model(ostream& ofile);
   virtual string Get_VC_Name();

};

#endif