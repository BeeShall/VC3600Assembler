#include "stdafx.h"
#include "Instruction.h"

Instruction::Instruction(){
	sym_opcodes.insert({{ "add", 1 }, { "sub", 2 }, { "mult", 3 }, { "div", 4 }, { "load", 5 }, { "store", 6 }, { "read", 7 }, { "write", 8 }, { "b", 9 }, { "bm", 10 }, { "bz", 11 }, { "bp", 12 },{"halt", 13} });
	mach_opcodes.insert({ "dc", "ds", "org", "end" });
}

int Instruction::LocationNextInstruction(int a_loc){
	if (m_OpCode == "org" || m_OpCode == "ds") return a_loc + parseToInt(m_Operand);
	return ++a_loc;


}

void Instruction::setElements(string opcode, string operand){
	m_OpCode = opcode;
	m_Operand = operand;

	int temp = parseToInt(operand);
	if (temp == -1){
		m_IsNumericOperand = false;
	}
	else{
		m_IsNumericOperand = true;
		m_OperandValue = temp;
	}
}

int Instruction::parseToInt(string number){
	try{
		return stoi(number);
	}
	catch (exception e){
		return -1;
	}
	//needs error checking
}


bool Instruction::checkForComments(string &buff){
	int index = buff.find(';');
	if (index == string::npos) return false;
	else{
		buff = buff.substr(0, index);
		return true;
	} 
}

Instruction::InstructionType Instruction::ParseInstruction(string &a_buff){
	m_instruction = a_buff;
	m_Label = "";
	istringstream is(a_buff);
	string lineBuff;
	vector<string> buff;
	bool inlineComment = false;
	while (is >> lineBuff){
		if (lineBuff == ""){
			return ST_Blank;
		}
		if (lineBuff[0] == ';' && !inlineComment){
			return ST_Comment;
		}
		if (lineBuff == "end"){
			m_OpCode = lineBuff;
			return ST_End;
		}
		if (checkForComments(lineBuff)){
			buff.push_back(lineBuff);
			break;
		}
		buff.push_back(lineBuff);
		inlineComment = true;
	}

	string opcode;
	string operand;
	if(buff.size() > 2){
		m_Label = buff[0];
		opcode = buff[1];
		operand = buff[2];
	}
	else if (buff.size() <= 2){
		opcode = buff[0];
		if (buff.size()==2) operand = buff[1];
		else operand = "";
	}

	if (mach_opcodes.find(opcode) != mach_opcodes.end()){
		setElements(opcode, operand);
		return ST_MachineLanguage;
	}

	if (sym_opcodes.find(opcode) != sym_opcodes.end()){
		setElements(opcode, operand);
		return ST_AssemblerInstr;
	}
	return ST_Illegal;
}






