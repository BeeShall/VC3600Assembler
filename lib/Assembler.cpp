//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"

// Constructor for the assembler.  Note: we are passing argc and argv to the file access constructor.
// See main program.
Assembler::Assembler( int argc, char *argv[] )
: m_facc( argc, argv )
{
    // Nothing else to do here at this point.
}
// Destructor currently does nothing.  You might need to add something as you develope this project.
Assembler::~Assembler( )
{
	
}
// Pass I establishes the location of the labels.  You will write better function comments according to the coding standards.
void Assembler::PassI( ) 
{
	Errors::InitErrorReporting();
    int loc = 0;        // Tracks the location of the instructions to be generated.

    // Successively process each line of source code.
    for( ; ; ) {

        // Read the next line from the source file.
        string buff; 
        if( ! m_facc.GetNextLine( buff ) ) {

            // If there are no more lines, we are missing an end statement.
            // We will let this error be reported by Pass II.
            return;
        }
        // Parse the line and get the instruction type.
        Instruction::InstructionType st =  m_inst.ParseInstruction( buff );

        // If this is an end statement, there is nothing left to do in pass I.
        // Pass II will determine if the end is the last statement.
        if( st == Instruction::ST_End ) return;

        // Labels can only be on machine language and assembler language
        // instructions.  So, skip other instruction types.
        if( st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr ) 
        {
        	continue;
	  }
        // If the instruction has a label, record it and its location in the
        // symbol table.
        if( m_inst.isLabel( ) ) {
			int tempLoc;
			//if any label is defined twice, report the error and ignore the new one
			if (!m_symtab.LookupSymbol(m_inst.GetLabel(), tempLoc)){
				m_symtab.AddSymbol(m_inst.GetLabel(), loc);
			}
			else{
				Errors::RecordError("Label already exists! :: " + m_inst.GetLabel());
			}
        }
        // Compute the location of the next instruction.
        loc = m_inst.LocationNextInstruction( loc );
    }
}

void Assembler::PassII(){
	m_facc.rewind();
	cout << "Translation of Program:" << endl;
	cout << left << setw(10) << "Location" << setw(10) << "Contents" << setw(10) << "Original Statement" << endl;
	int location = 0;
	string lineBuff;
	while (m_facc.GetNextLine(lineBuff)){
		Instruction::InstructionType st = m_inst.ParseInstruction(lineBuff);
		if (st == Instruction::ST_Blank) continue;
		//if (st == Instruction::ST_Illegal) Errors::RecordError("Unknown Syntax in: " + m_inst.GetInstruction()); continue;
		if (st == Instruction::ST_End || st == Instruction::ST_Comment){
			cout << left << setw(10) << "" << setw(10) << "" << setw(10) << m_inst.GetInstruction() << endl;
			if (st == Instruction::ST_End) break;
			continue;
		}
		if (m_inst.GetLabel() != ""){
			string label = m_inst.GetLabel();
			if (label.length() > 10){
				Errors::RecordError("Label size is longer than 10 characters for \"" + m_inst.GetLabel() + "\""); continue;
			}
			if (isdigit(label[0])){
				Errors::RecordError("Label cannot start with a number for \"" + m_inst.GetLabel() + "\"");	continue;
			}
		}

		if (m_inst.getOpCode() == "org" || m_inst.getOpCode() == "ds"){
			cout << left << setw(10) << location << setw(10) << "" << setw(10) << m_inst.GetInstruction() << endl;
		}
		else{
			int contents = m_inst.getOpCodeValue() * 10000;
			int operandValue;
			if (m_inst.isNumericOperand()) operandValue = m_inst.getNumericOperand();
			else m_symtab.LookupSymbol(m_inst.getStringOperand(), operandValue);
			contents += operandValue;
			cout << left << setw(10) << location <<right << setfill('0')<<setw(6) << contents << setw(4) << setfill(' ')<<""<<left<<setw(10)<< m_inst.GetInstruction() << endl;
		}
		location = m_inst.LocationNextInstruction(location);
	}

	system("pause");


	Errors::DisplayErrors();
}

void Assembler::DisplaySymbolTable(){
	m_symtab.DisplaySymbolTable();
}

void Assembler::RunEmulator(){


}
