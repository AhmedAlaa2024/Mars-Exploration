#include "Formulation.h"

Formulation::Formulation(char typ,int ed, int id, double tloc, int mdur, int sig)
	:Event(ed,id){
	TYP = typ;
	
	TLOC = tloc;
	MDUR = mdur;
	SIG = sig;
}

void Formulation::Execute()
{
}
