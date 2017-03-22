#include "stdafx.h"
#include "Instruction.h"
#include "Errors.h"

Instruction::Instruction(){
	sym_opcodes.insert({{ "add", 1 }, { "sub", 2 }, { "mult", 3 }, { "div", 4 }, { "load", 5 }, { "store", 6 }, { "read", 7 }, { "write", 8 }, { "b", 9 }, { "bm", 10 }, { "bz", 11 }, { "bp", 12 },{"halt", 13} });
	mach_opcodes.insert({ "dc", "ds", "org", "end" });
}

int Instruction::LocationNextInstruction(int a_loc){
	return 0;
}

void Instruction::setElements(string opcode, string operand){
	m_OpCode = opcode;
	m_Operand = operand;
	cout << "operand:: " << m_Operand;
}

bool Instruction::checkMachineCodes(string buff, istringstream &is){
	if (mach_opcodes.find(buff) != mach_opcodes.end()){
		string opcode = buff;
		is >> buff;
		setElements(opcode, checkForComments(buff));
		return true;
	}
	return false;
}
bool Instruction::checkSymbolicCodes(string buff, istringstream &is){
	if (sym_opcodes.find(buff) != sym_opcodes.end()){
		string opcode = buff;
		is >> buff;
		setElements( opcode, checkForComments(buff));
		return true;
	}
	return false;
}

string Instruction::checkForComments(string buff){
	int index = buff.find(';');
	if (index == string::npos) return buff;
	else return buff.substr(0, index);
}

Instruction::InstructionType Instruction::ParseInstruction(string &a_buff){
	m_instruction = a_buff;
	m_Label = "";
	istringstream is(a_buff);
	string lineBuff;
	while (is >> lineBuff){
		if (lineBuff[0] == ';'){
			return ST_Comment;
		}
		if (lineBuff == "end"){
			m_OpCode = lineBuff;
			return ST_End;
		}
		if (checkMachineCodes(lineBuff,is)) return ST_MachineLanguage;
		if (checkSymbolicCodes(lineBuff,is)) return ST_AssemblerInstr;
		m_Label = lineBuff;
	}
	return ST_Blank;
}






