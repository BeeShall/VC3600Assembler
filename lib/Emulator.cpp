#include "stdafx.h"
#include "Emulator.h"

bool emulator::insertMemory(int a_location, int a_contents){
	// If the location to be stored in is greater than 10000, then, return false
	if (a_location >= MEMSZ) {
		return false;
	}

	m_memory[a_location] = a_contents;		// Add the data to the location

	return true;
}

bool emulator::runProgram(){

	for (int i = 0; i < MEMSZ; ++i){
		if (m_memory[i] != 0){
			int opCode = m_memory[i] / 10000;
			int address = m_memory[i] % 10000;
			switch (opCode) {
			case 1:
				// Adds the content of accumulator and memory location provided 
				accumulator += m_memory[address];
				break;
			case 2:
				// Substracts the contents of accumulator and memory location provided
				accumulator -= m_memory[address];
				break;
			case 3:
				// Multiplies the contents of accumulator and memory location provided
				accumulator *= m_memory[address];
				break;
			case 4:
				// Divides the contents of accumulator and memory location provided
				accumulator = accumulator / m_memory[address];
				break;
			case 5:
				// Loads the content of the address into the accumulator
				accumulator = m_memory[address];
				break;
			case 6:
				// The contents of accumulator is stored in the address provided
				m_memory[address] = accumulator;
				break;
			case 7:
				// A line is read and its first 6 digits are placed in the specified address
				cout << "?";
				int userInput;
				cin >> userInput;
				userInput = userInput % 1000000;
				m_memory[address] = userInput;

				break;
			case 8:
				// Contents of the address is displayed
				cout << m_memory[address] << endl;
				break;
			case 9:
				// Goes to the provided address for next instruction i.e. changes the index to the location
				i = address;
				break;
			case 10:
				// Goes to the address if content of accumulator is less than 0
				if (accumulator < 0) i = address - 1;
				break;
			case 11:
				// Goes to the address if c(ACC) = 0
				if (accumulator == 0) i = address - 1;
				break;
			case 12:
				// Goes to the address if c(ACC) > 0
				if (accumulator > 0) i = address-1;
				break;
			case 13:
				// terminates the execution
				i = 10000;
				break;
			}
		}
	}

	return true;
}