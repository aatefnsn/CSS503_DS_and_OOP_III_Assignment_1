#ifndef DIVIDE_AND_CONQUER_CC
#define DIVIDE_AND_CONQUER_CC
	int pipefd[2]; /* Array for the pipe file descriptor [0] reading end [1] writing end */
	Points hull1; /* first hull set of points resulting from the child forked process divide and conquer */
	Points hull2; /* second hull set of points resulting from the parent divide and conquer */ 
	pid_t cpid; /* child pid */
	int status; /* wait process *int */ 
	if (pipe(pipefd) == -1) /* An error has occurred while trying to pipe(). */
	{
		fprintf(stderr, "%s", "The call to pipe() has failed.\n");           
		exit(EXIT_FAILURE);
	}
	cpid = fork(); /* fork() returns the child process's PID  */
	if (cpid == -1) /* An error has occurred. */
	{
		fprintf(stderr, "%s", "The call to fork() has failed.\n");
		exit(EXIT_FAILURE); /*Exit if failure occurs */
	}
	if (cpid == 0) /* Child process block */  
	{
		//fprintf(stderr,"I am the child.\n");
		Slice slice1{points, (size + 1) / 2}; /* Creating the first slice of points */
		slice1.divide_and_conquer((n_processors + 1) / 2, hull1);  /* Applying D&C to Slice1 and resultant will be hull1*/
		//fprintf(stderr, "child writes to parent\n");
		close(pipefd[0]); /* Close reading end of pipe to start writing */
		hull1.write_raw(pipefd[1]); /* Use the pre-defined write_raw method to write hull1 points into fd */
		//fprintf(stderr, "child write complete\n");
		close(pipefd[1]);    /* Closing creates the EOF marker. */
		//fprintf(stderr, "child exit success\n");
		exit(EXIT_SUCCESS); /* Child will exit after finishing its D&C part*/
	}
	else /* Parent process block */
	{ 
		//fprintf(stderr,"I am the parent.\n");
		close(pipefd[1]);              /* Close unused write end */
		Slice slice2{points + (size + 1) / 2, size / 2};
		slice2.divide_and_conquer(n_processors / 2, hull2);    
		////     fprintf(stderr, "The parent will read results from child.\n");
		hull1.read_raw(pipefd[0]); /* Read the FD into hull1 in parent process */
		close(pipefd[0]); /* Close the reading end of pipe */
		////     fprintf(stderr, "The parent will read results from child.\n");
		//pid_t pid = wait(NULL);                    /* Parent waits for the child to terminate */
		pid_t pid = wait(&status);
		if (pid > 0){
		////     fprintf(stderr, "parent: child %d exited with status ???\n", pid);
		}
		else{
			exit(EXIT_FAILURE);
		}
	}
#endif     
