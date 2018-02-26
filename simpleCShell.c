#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define MAX_LINE 80 

// typedef struct{
// 	int n;
// 	char *cmd;
// }CMD;

int main(void){

	char *args[MAX_LINE/2 + 1]; 
	int should_run = 1; 
	// CMD *hist[10];
	int n[10];
	char cmd[10][MAX_LINE];
	int histC = 0;
	int c = 0;
	int count = 1;

	while (should_run) {
		// sleep(1);
		int w = 1;
		printf("osh> ");
		fflush(stdout);

	    char input[50];

	    fgets(input,sizeof(input),stdin);
	    input[strlen(input)-1] = '\0';
	    if(input[0]=='!'){
	    	if(input[1]=='!'){
	    		if(c==0){
	    			printf("%s\n", "No commands in history");
	    			strcpy(input,"history"); 
	    			count--;
	    		}else{
		    		int index = (count % 10) - 2;
		    		count--;
		    		printf("%s\n", cmd[index]);
		    		strcpy(input,cmd[index]); 
		    	}
	    	}else{
	    		int num = input[1] - '0';
	    		int index = (num % 10) - 1;
	    		// input = cmd[index];
	    		printf("%s\n",cmd[index]);
	    		strcpy(input,cmd[index]); 
	    		count--;
	    	}
	    	count++;
	    }
	    if(strcmp(input,"history")){
		    if(histC == 10){
		    	histC = 0;
		    }
		    n[histC] = count;
		    count++;
		    strcpy(cmd[histC], input);
		    histC++;
		    if(c != 10){
		    	c++;
		    }
		}
	    const char d[2] = " ";
	    char *token;

	    token = strtok(input, d);
	    int i = 0;
	    while(token != NULL){
	    	args[i] = token;
	    	i++;
	    	token = strtok(NULL, d);
	    }
	    args[i] = NULL;

	    int j = 0;
	    for(; j != i; j++){
	    	if (*args[j] == '&'){
	    		w = 0;
	    		args[j] = NULL;
	    	}
	    	//printf("%s\n", args[j]);
	    }

	    if(!strcmp(args[0],"exit")){
	    	should_run = 0;
	    }
	    if(!strcmp(args[0],"history")){
	    	int x = c;
	    	for(;x >= 0; x--){
	    		if(n[x] != 0){
		    		printf("%d  %s\n",n[x], cmd[x]);
	    		}
		    }
	    }

	    int counter = 0;
	    pid_t pid = fork();

	    if (pid == 0){
	    	execvp(args[0],args);
	    }
	    else if (pid > 0){
	    	if (w){
	    		wait(NULL);
	    	}else{
	    		printf("%s\n", "Executed Concurrently");
	    		sleep(1);
	    	}
	    }
	    else{
	        printf("fork() failed!\n");
	        return 1;
	    }
	}
	return 0;
}