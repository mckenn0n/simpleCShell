#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define MAX_LINE 80 

typedef struct{
	int N;
	char *cmd;
}CMD;

int main(void){

	char *args[MAX_LINE/2 + 1]; 
	int should_run = 1; 

	while (should_run) {
		// sleep(1);
		int w = 1;
		printf("osh> ");
		fflush(stdout);

	    char input[50];

	    fgets(input,sizeof(input),stdin);
	    input[strlen(input)-1] = '\0';

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
		/**
		* After reading user input, the steps are:
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		* (3) if command not included &, parent will invoke wait()
		*/
	}
	return 0;
}