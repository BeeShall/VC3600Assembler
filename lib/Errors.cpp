#include "stdafx.h"
#include "Errors.h"



vector<string> Errors::m_ErrorMsgs;

void Errors::InitErrorReporting(){
	m_ErrorMsgs.clear();
}

void Errors::RecordError(string &a_emsg){
	m_ErrorMsgs.push_back(a_emsg);
}

void Errors::DisplayErrors(){
	if (m_ErrorMsgs.empty()) cout << "Wohooo! No Errors!" << endl; return;
	for (int i = 0; i < m_ErrorMsgs.size(); i++){
		cout << m_ErrorMsgs[i] << endl;
	}
}