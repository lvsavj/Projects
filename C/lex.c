#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 20

char line[100],label[MAX][10],opcode[MAX][10],op1[MAX][10],op2[MAX][10],symbol[MAX][10],literal[MAX][10],rel[MAX];
int lno=0,lc[MAX],lab_lc[MAX],lins=15,i,j=0,length=4,b_loc,sno=0;

void main()
{
	FILE *file;
	char *token;
	file=fopen("tassem.txt","r");
	printf("\n");
	while(fgets(line,sizeof(line),file)!=NULL)
	{
		printf("\nline: %s",line);
		if(line[0]==' ' || line[0]==(char)9)
		{
			printf("label: NULL\n");
			label[lno][0]=(char)32;
			token=strtok(line," \t");
			while(token!=NULL)
			{
				printf("opcode: %s\n",token);
				strcpy(opcode[lno],token);
				token=strtok(NULL," \t\n");
				printf("operand1: %s\n",token);
				if(token!=NULL)
					strcpy(op1[lno],token);
				token=strtok(NULL," ,\t\n");
				printf("operand2: %s\n",token);
				if(token!=NULL)
					strcpy(op2[lno],token);
				token=strtok(NULL," \t");
			}
		}
		else
		{
			token=strtok(line," ");
			while(token!=NULL)
			{
				printf("label: %s\n",token);
				strcpy(label[lno],token);
				token=strtok(NULL," \t");
				printf("opcode: %s\n",token);
				strcpy(opcode[lno],token);
				token=strtok(NULL," \t\n");
				printf("operand1: %s\n",token);
				if(token!=NULL)
					strcpy(op1[lno],token);
				token=strtok(NULL," ,\t\n");
				printf("operand2: %s\n",token);
				if(token!=NULL)
					strcpy(op2[lno],token);
				token=strtok(NULL," \t");
			}
		}
		lno++;
	}
	printf("\nLABEL\tOPCODE\tOP1\tOP2\n");
	for(i=0;i<lno;i++)
		printf("\n%s\t%s\t%s\t%s",label[i],opcode[i],op1[i],op2[i]);

	symbol_table();
	literal_table();
	base_table();
	for_ref();
}
int symbol_table()
{
	int k;
	char pot[MAX][10]={"START","USING","END"};
	char op[MAX];
	printf("\nSymbol Table\n");
	printf("\nLABEL\t\tLC\t\tLENGTH\t\tRELOCATION\n");
	for(i=0;i<lno;i++)
	{
		strcpy(op,opcode[i]);
		if(strcmp(opcode[i],pot[0])!=0 && strcmp(opcode[i],pot[1])!=0 && strcmp(opcode[i],pot[2])!=0)
		{
				lc[i]=lins;
				lins=lins+4;		
		}
		if(label[i][0]!=(char)32 && label[i][0]!=' ')
		{
			strcpy(symbol[sno],label[i]);
			if(strcmp(opcode[i],"EQU")==0 && op1[i][0]!='*')
				rel[sno]='A';
			else
				rel[sno]='R';

			lab_lc[sno]=lc[i];
			printf("%s\t\t%d\t\t%d\t\t%c\n",symbol[sno],lab_lc[sno],length,rel[sno]);
			sno++;
		}
		if(strcmp(opcode[i],"END")==0)
			return 1;
	}
	return 1;
}
void literal_table()
{
	j=0;
	int flag=0,k=0;
	printf("\nLiteral Table\n");
	printf("\nLITERAL\t\tLC\t\tLENGTH\t\tRELOCATION");
	for(i=0;i<lno;i++)
	{
		if(strcmp(opcode[i],"EQU")==0 && op1[i][0]!='*')
				rel[j]='A';
			else
				rel[j]='R';
		if(op1[i][0]=='F' && op1[i][1]==(char)39)
		{
			strcpy(literal[j],op1[i]);
			printf("\n%s\t\t%d\t\t%d\t\t%c",literal[j],lc[i],length,rel[j]);
			j++;
		}
		if(op2[i][0]=='=')
		{
			for(k=1;k<sizeof(op2[i]);k++)
				literal[j][k-1]=op2[i][k];

			printf("\n%s\t\t%d\t\t%d\t\t%c",literal[j],lc[i],length,rel[j]);
			j++;
		}
	}
	printf("\n");
}
void base_table()
{
	int k,flag=0;
	for(k=0;k<MAX;k++ && flag!=1)
	{
		if(strcmp(opcode[k],"USING")==0)
		{
			b_loc=atoi(op2[k]);
			flag=1;
		}
	}
	printf("\n\n****Pass 2***\n\n");
	printf("\nBase Table\n\nRegister no\tAvailability\tContents");
	for(k=0;k<16;k++)
	{
		if(k==b_loc)
			printf("\n%d\t\tY\t\t%d",k,k);
		else
			printf("\n%d\t\tN\t\t0",k);
	}
	printf("\n");
}
void for_ref()
{

	int flag=0,offset[MAX];
	j=0;
	printf("\nForward Reference\n");
	for(i=0;i<=sno;i++)
	{
		for(j=0;j<lno;j++)
		{
			offset[j]=0;
				
			if(strcmp(symbol[i],op1[j])==0 || strcmp(symbol[i],op2[j])==0)
			{
				offset[j]=lab_lc[i];
				if(offset[j]!=0)
				printf("\n%s\t1,%d(0,%d)",opcode[j],offset[j],b_loc);
			}
		}
	}
	printf("\n");
}