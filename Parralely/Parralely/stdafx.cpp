#include "stdafx.h"



DictWord::DictWord(short n, CString DictChar)
{
	const char ZeroChar=DictChar.GetAt(0);
	Current= new StructWord;
	Head=Current; Tale=Current;
	Current->c=ZeroChar;

	for(int i=1;i<n;i++)
	{
		Current->next= new StructWord;
		Current->next->c=ZeroChar;
		Current->next->prev=Current; Tale=Current->next;
		Current=Current->next;		
	}
	CharBase=DictChar;
}

DictWord::~DictWord()
{
	while(Current!=Head)
	{
		Current=Tale;
		Current=Current->prev;
		Tale=Current;
		delete Current->next;
	}
	delete Tale;
	delete Head;

}

CString DictWord::GetString(bool Heading)
{
	CString TempString="";
	if(Heading)
	{
		Current=Tale;
		while (true)
		{
			TempString+=Current->c;
			if(Current==Head) break;
			Current=Current->prev;
			
		}
	}
	else
	{
		Current=Head;
		while(true)
		{
			TempString+=Current->c;
			if(Current==Tale) break;
			Current=Current->next;
			
		}
	}
    return TempString;
}

int DictWord::Add()
{
	int Now;
	bool E=true;
	
	char Max=CharBase.GetAt(CharBase.GetLength()-1);
	char Min=CharBase.GetAt(0);

	if(PureAdd)Current=Tale;
	Now=CharBase.Find(Current->c,0);	
	Now++;	
	
	if((Now>=CharBase.GetLength())||(Now<0))
	{
		Current->c=Min;
		if(Current!=Head)
		{
			Current=Current->prev;
			PureAdd=false;
			if(-2==Add()) return -2;
			return -1;

		}
		else 
			return -2;		
	}
	else
	{
		Current->c=CharBase.GetAt(Now);
		PureAdd=true;
		return Now;
	}
}


DictCreator::DictCreator(periods* range)
{
	periods *run;
	int ii=0;	
	
	for(int i=0;i<=255;i++)
		BaseDict[i]=i;

	run=range;
	while(run!=NULL)
	{
		
		for(int i=run->start;i<=run->end;i++)
		{
			Dict+=char(BaseDict[i]);
			ii++;
		}
		run=run->next;

	}	
}

bool DictCreator::Open(const char* DictName)
{
	
	if(DictName!=NULL)
		DictFile=fopen(DictName,"w+t");
	if(DictFile!=NULL) return true;
	else return false;
	
}

void DictCreator::Close()
{
	if(DictFile!=NULL) fclose(DictFile);
}


void DictCreator::Work(int n, int nn)
{
	int a;
	DictWord *DCW;	
	
	for(int i=n;i<=nn;i++)
	{
		a=0;
		DCW = new DictWord(i, Dict);
		while(a!=-2)
		{		
			fprintf(DictFile,"%s \n",DCW->GetString(false));
			printf("%s \n",DCW->GetString(false));
			a=DCW->Add();
		}
		
		free(DCW);
	}
	
}




