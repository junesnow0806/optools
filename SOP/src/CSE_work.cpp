#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *fp, *fpt;

int strcmp_num(char *a, char *b, int n)
{
    int i;
    for(i = 0; a[i] && b[i] && i < n; i++)
    {
        if(a[i]>b[i]) return 1;
        if(a[i]<b[i]) return -1;
    }
    return 0;
}


void LP_TO_SOP(FILE *fp, FILE *fpt){
	int i;
	int st_sig = 0, sig = 0; 
	char ob;
	char *td = (char *)malloc(500 * sizeof(char));
	fprintf(fpt, "Probtype lp\n\n");
	while(feof(fp)==0){
		fgets(td, 500, fp);
		printf("%s",td);
		i = 0;
		while(td[i] == ' ')
			i++;
		if(td[i] == '\\' || td[i] == '\n' || td[i] == 0)
			continue;
		
		if(td[i] == 'M'){
			if(strcmp_num(&td[i], "Max", 3) == 0 || strcmp_num(&td[i], "MAX", 3) == 0 || strcmp_num(&td[i], "Maximize", 8) == 0 || strcmp_num(&td[i], "MAXIMIZE", 8) == 0)
				fprintf(fpt, "Objective:\nmax ");
			else if(strcmp_num(&td[i], "Min", 3) == 0 || strcmp_num(&td[i], "MIN", 3) == 0 || strcmp_num(&td[i], "Minimum", 7) == 0 || strcmp_num(&td[i], "MINIMUN", 7) == 0)
				fprintf(fpt, "Objective:\nmin ");
			else{
				fprintf(fpt, "Please input correctly\n");
				exit(1);
			}
			continue;
		}
		if(strcmp_num(&td[i], "obj:", 4) == 0){
			fprintf(fpt, "obj =");
			i=i+4;
			while(td[i] != '\n' && td[i] != 0){
				fprintf(fpt, "%c", td[i]);
				i++;
			}	
			fprintf(fpt, "\n\n");
		}
		
		if(st_sig == 1 && strcmp_num(&td[i], "Bounds", 6) != 0 && strcmp_num(&td[i], "GENERAL", 7) != 0 && strcmp_num(&td[i], "GEN", 3) != 0 
		&& strcmp_num(&td[i], "BINARY", 6) != 0 && strcmp_num(&td[i], "SEMI-CONTINUOUS", 15) != 0 && strcmp_num(&td[i], "SEMI", 4) != 0 && strcmp_num(&td[i], "SEMIS", 5) != 0){
			while(td[i] != ':')
				i++;
			i++;
			while(td[i] != '\n' && td[i] != 0){
				fprintf(fpt, "%c", td[i]);
				i++;
			}	
			fprintf(fpt, "\n");
			continue;
		}
		
		if(strcmp_num(&td[i], "Subject To", 10) == 0){
			if(sig == 1)
				fprintf(fpt, "\n");
			fprintf(fpt, "Subject To:\n");
			st_sig = 1;
			sig = 0;
			continue;
		}
		 
		if(strcmp_num(&td[i], "Bounds", 6) == 0){
			fprintf(fpt, "\n");
			st_sig = 0;
			sig = 1;
			fprintf(fpt, "Bounds:\n");
			continue;
		}
		
		if(strcmp_num(&td[i], "GENERAL", 7) == 0 || strcmp_num(&td[i], "GEN", 3) == 0){
			fprintf(fpt, "\n");
			st_sig = 0;
			sig = 1;
			fprintf(fpt, "General:\n");
			continue;
		}
		
		if(strcmp_num(&td[i], "BINARY", 6) == 0){
			fprintf(fpt, "\n");
			st_sig = 0;
			sig = 1;
			fprintf(fpt, "Binary:\n");
			continue;
		}
		
		if(strcmp_num(&td[i], "SEMI-CONTINUOUS", 15) == 0 || strcmp_num(&td[i], "SEMI", 4) == 0 || strcmp_num(&td[i], "SEMIS", 5) == 0){
			fprintf(fpt, "\n");
			st_sig = 0;
			sig = 1;
			fprintf(fpt, "Semis:\n");
			continue;
		}
		
		if(strcmp_num(&td[i], "End", 3) == 0){
			fprintf(fpt, "\nEnd");
			break;
		}
		
		if(sig == 1){
			while(td[i] != '\n' && td[i] != 0){
				fprintf(fpt, "%c", td[i]);
				i++;
			}	
			fprintf(fpt, "\n");
			continue;
		}	
	}
}

void CNF_TO_SOP(FILE *fp, FILE *fpt){
	int i;
	int sig_mul = 0, sig_plus = 0; 
	char ob;
	char *td = (char *)malloc(500 * sizeof(char));
	fprintf(fpt, "Probtype cnf\n\n");
	while(feof(fp)==0){
		fgets(td, 500, fp);
		printf("%s",td);
		i = 0;
		while(td[i] == ' ')
			i++;
		if(td[i] == 'c' || td[i] == '\n' || td[i] == 0 || td[i] == 'p')
			continue;
		if((td[i] >= '0' && td[i] <= '9') || td[i] == '-'){
			if(sig_mul == 1)
				fprintf(fpt, " * ");
			sig_mul = 1;
			fprintf(fpt, "(", td[i]);
			if(td[i] == '-'){
				fprintf(fpt, "~x");
				i++;
			}	
			else fprintf(fpt, "x");
			while(td[i] != '\n' && td[i] != 0 && !(td[i] == '0' && (td[i+1] == '\n' || td[i+1] == 0))){
				if(td[i] == '-')
					fprintf(fpt, " + ~x");
				else if(td[i] == ' ' && td[i+1] > '0' && td[i+1] <= '9')
					fprintf(fpt, " + x");
				else if(td[i] >= '0' && td[i] <= '9')
					fprintf(fpt, "%c", td[i]);
				i++;
			}
			fprintf(fpt, ")", td[i]);
		}
	}
	fprintf(fpt, "\n\nEnd");
} 

void OPB_TO_SOP(FILE *fp, FILE *fpt){
	int i;
	int sig = 0; 
	char ob;
	char *td = (char *)malloc(500 * sizeof(char));
	fprintf(fpt, "Probtype opb\n\n");
	while(feof(fp)==0){
		fgets(td, 500, fp);
		printf("%s",td);
		i = 0;
		while(td[i] == ' ')
			i++;
		if(td[i] == '*' || td[i] == '\n' || td[i] == 0)
			continue;
		
		if(td[i] == 'm'){
			if(strcmp_num(&td[i], "max", 3) == 0)
				fprintf(fpt, "Objective:\nmax ");
			else if(strcmp_num(&td[i], "min", 3) == 0)
				fprintf(fpt, "Objective:\nmin ");
			else{
				fprintf(fpt, "Please input correctly\n");
				exit(1);
			}
			i = i + 4;
			while(td[i] != '\n' && td[i] != 0 && td[i] != ';'){
				fprintf(fpt, "%c", td[i]);
				i++;
			}	
			fprintf(fpt, "\n\n");
			continue;
		}
		
		if((td[i] >= '0' && td[i] <= '9') || td[i] == '-'){
			if(sig == 0)
				fprintf(fpt, "Subject To:\n");
			sig = 1;
			while(td[i] != '\n' && td[i] != 0 && td[i] != ';'){
				fprintf(fpt, "%c", td[i]);
				i++;
			}	
			fprintf(fpt, "\n");
			continue;
		}
		 
	}
	fprintf(fpt, "\nEnd");
}

int main(){
	char filename[100];
	fp=fopen("example.opb","r");
	fpt=fopen("result.sop","w+");
	OPB_TO_SOP(fp, fpt);
	return 0;
}
