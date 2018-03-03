//#ifndef divide_and_conquer.cc
//#define divide_and_conquer.cc
#ifndef DIVIDE_AND_CONQUER_CC
#define DIVIDE_AND_CONQUER_CC	
//#include "divide_and_conquer.cc"
int pipefd[2];
Points hull1;
Points hull2;
pid_t cpid;
  if (pipe(pipefd) == -1)          /* An error has occurred. */
    {
      fprintf(stderr, "%s", "The call to pipe() has failed.\n");           
          exit(EXIT_FAILURE);
    }
  cpid = fork();                   /* fork() returns the child process's PID  */
  if (cpid == -1)                  /* An error has occurred. */
  {
  fprintf(stderr, "%s", "The call to fork() has failed.\n");
  exit(EXIT_FAILURE);
   }
   if (cpid == 0) 
     {
////     fprintf(stderr,"I am the child.\n");

     Slice slice1{points, (size + 1) / 2};
////     cout << "Slice1 dump" << endl;
////     slice1.dump(cout);
////     cout << "Slice1 dump end" << endl;
     //Points hull1;
     slice1.divide_and_conquer((n_processors + 1) / 2, hull1);

     // close pipe for writing and start writing hull1 points into buffer/fd/
     // close fd after writing 
////     fprintf(stderr, "child writes to parent\n");
     close(pipefd[0]);
////     cout << "Hull1 points in child process" << endl;
////     hull1.dump(cout);
////     cout << "Hull1 points dump end" << endl;
     hull1.write_raw(pipefd[1]);
////     fprintf(stderr, "child write complete\n");
     close(pipefd[1]);
////     fprintf(stderr, "child exit success\n");
     exit(EXIT_SUCCESS);
  }
  else 
    { 
////     fprintf(stderr,"I am the parent.\n");

     close(pipefd[1]);              /* Close unused write end */
     Slice slice2{points + (size + 1) / 2, size / 2};
     slice2.divide_and_conquer(n_processors / 2, hull2);  
       
     //close(pipefd[1]);              /* Closing creates the EOF marker. */
////     fprintf(stderr, "The parent will read results from child.\n");
     hull1.read_raw(pipefd[0]);
     // read fd into another Points vector called hull1
////     fprintf(stderr, "The parent will read results from child.\n");
     pid_t pid = wait(NULL);                    /* Parent waits for the child to terminate */
     if (pid > 0){
////     fprintf(stderr, "parent: child %d exited with status ???\n", pid);
}
     else{
       exit(EXIT_FAILURE);
      }
     }
#endif     
