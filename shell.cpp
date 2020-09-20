#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <bits/stdc++.h>
#include <string>
#include <cctype>
#include <fcntl.h>
using namespace std;

// trim function reference to Geeks for Geeks
 void trim(string &str) 
{ 
    str += " ";  
    int n = str.length(); 
    int i = 0, j = -1; 
    bool spaceFound = false;

    while (++j < n && str[j] == ' ');

    while (j < n) 
    { 
        if (str[j] != ' ') 
        { 
            str[i++] = str[j++];
            spaceFound = false; 
        } 
      
        else if (str[j++] == ' ') 
        {  
            if (!spaceFound) 
            { 
                str[i++] = ' '; 
                spaceFound = true; 
            } 
        } 
    } 
  
    if (i <= 1)
    {
        str.erase(str.begin() + i, str.end());
    }  
    else
    {
        str.erase(str.begin() + i - 1, str.end()); 
    }
       
}


vector<string> split(string str, int& pipe_count, char sep, bool& IOper)
{
    vector<string> bgs;
    string command = "";

    for(int i=0;i < str.length(); i++)
    {
       // checks to see if there is quotes and pipe, then simply adds eeything till delimeter.
        if((str.at(i) == '\"' || str.at(i) == '\'') && pipe_count>1)
        {   
            while(str.at(i) != sep)
            {
                command += str.at(i);
                i++;
            }
            
            bgs.push_back(command);
            command="";
            continue;
        }
        else if((str.at(i) == '\"' || str.at(i) == '\'')) //if normal quotes, then keep string between quotes and remove quotes
        {
            i++;
            while(str.at(i)!='\"' && str.at(i) != '\'')
            {
                command += str.at(i);
                i++;
            }
            bgs.push_back(command);
            command="";
            continue;
        }

        if(str.at(i) == '<' || str.at(i) == '>') // if IO operation
        {
            IOper = true;
            string temp;
            if(str.at(i-1) != ' ' && str.at(i+1) != ' ') //if no space before or after add spaces and the character, and incrememnt
            {
                temp = command.substr(0, i);
                temp += " ";
                temp += str.at(i);
                temp += " ";
                command = temp;
                i++;
            }
            else if(str.at(i-1) != ' ')
            {
                temp = command.substr(0, i);
                temp += " " + str.at(i);
                command = temp;
                i++;
            }
            else if(str.at(i+1) != ' ')
            {
                temp = command.substr(0, i+1) + " ";
                command = temp; 
                i++;
            }

        }
        
        if(str.at(i) == sep) // if current character  is delimiter, then commmand is full, and can be pushed to the vector
        {
        
            if(command!= " " && command!="")
            {
                bgs.push_back(command);
            }
           
            command="";
            continue;
        }
        
        command+= str.at(i);
        
    }
    if(command!="") //last command will not be recognized some times as space after it does not exist.  
    {                // thus if command still have value then push it back to vector.
        bgs.push_back(command);
    }
    
    return bgs;
}

void find_values(string str, int& pipe_count, bool& dir)
{
    //checks to see if pipe symbol exists outisde of quotes, and increments pipe count based on number of pipe commands.
    // also checks to see if there is a "cd" for change directory outside of quotes
    for(int i=0;i < str.length(); i++)
    {
        if(str.at(i) == '|')
        {
            pipe_count++;
        }
        if(str.at(i) == 'c' && str.at(i+1) == 'd')
        {
            dir = true;
        }
        if((str.at(i) == '\"' || str.at(i) == '\''))
        {
            i++;
            while(str.at(i)!='\"' && str.at(i) != '\'')
            {
                i++;
            }
            i++;
        }
  
    }
  
}

// reference to Dr. Tanzirs video demo.
char** vec_to_char_array(vector<string>& parts)
{
    //cout << "first element in parts is"<<parts[0] <<endl;
    char** result = new char* [parts.size()+1];
    //string val =" ";
    for(int i=0; i<parts.size(); i++)
    {   
        //cout << parts[i] << endl;
        result[i] = (char*) parts[i].c_str();
        
        //printf(result[i]);

    }
    result [parts.size()]=NULL;
    //cout  << "result is: " <<  **result <<endl;;
    return result;
}

int main ()
{

    int pipe_count = 1;
    vector<int> bgs;
    char* prev;
    prev = (char*) malloc( PATH_MAX * sizeof(char) ); //pointer to last directory location
    int backup = dup (0); //back up for standard input.
    int backup1 = dup(1); //back up for standard output.
    while (true)
    {
        time_t now = time(0);
        char* dt = ctime(&now);
        string time(dt);
        time = time.substr(0, time.length()-1); // get current time
        dt = NULL;
        char *p = getenv("USER"); //get user name
        if(p==NULL)
        {
            return EXIT_FAILURE;
        }
        // set std input and output back to default.
        dup2(backup, 0);
        dup2(backup1, 1);
        bool IOper = false; //if IO operation exists
        bool bg = false; // if background processes exist
        bool dir = false; // if change directory function is needed
        int pipe_count = 1; //number of piping commands.
        string filename = ""; //filename for IO operation

        // check on background processes before getting next;
        for(int k=0; k<bgs.size(); k++)
        {
            if(waitpid(bgs[k], 0, WNOHANG) == bgs[k])
            {
                //cout is slightely delayed.
                cout << "Process: " << bgs[k] << " ended" << endl;
                bgs.erase(bgs.begin() + k);
                k--;
            }
        }

        cout << time << " " << p << "$ " ; //print a prompt
        string inputline;
        getline (cin, inputline); //get a line from standard input
        trim(inputline);
        if (inputline == string("exit"))
        {
            cout << "Bye!! End of shell" << endl;
            free(prev);
            prev = NULL;
            break;
        }
        // check to see if pipe and how many, as well as if change directory
        find_values(inputline, pipe_count, dir);

        //adjust string if background process is needed
        int pos = inputline.find('&');
        if( pos == inputline.length()-1)
        {
            inputline = inputline.substr(0, pos);
            bg = true;
        }      
        // if change directory is needed.
        if(inputline.find("cd") != string::npos && dir)
        {  
            //cout << inputline.find("-") << endl;
            if(inputline.find("-") != string::npos)
            {   
                char* cwd;
                cwd = (char*) malloc( PATH_MAX * sizeof(char) );
                getcwd(cwd,PATH_MAX);
                if (chdir(prev) != 0)
                {
                    perror("operation failed");
                }
                else
                {
                    getcwd(prev, PATH_MAX);
                    cout << "Current path is: " << prev << endl;
                }
                free(prev);
                prev = cwd;
                cwd = NULL;
            }
            else
            {
                
                vector<string> dir_parts = split(inputline, pipe_count, ' ', IOper);
                char** path_args = vec_to_char_array(dir_parts);
                *path_args++;
                getcwd(prev, PATH_MAX);

                if(chdir(*path_args) != 0)
                {
                    perror("operation failed");
                }
                else
                {
                    char* cwd;
                    cwd = (char*) malloc( PATH_MAX * sizeof(char) );
                    getcwd(cwd,PATH_MAX);
                    cout << "Current path is: " << cwd <<endl;
                    free(cwd);
                    cwd = NULL;
                    
                }
                
                
            }
            continue;
        }

        // keep a copy of pipe_count
        int temp = pipe_count;
        vector<string> pparts = split(inputline, pipe_count, '|', IOper);
        //if piping operation
        if(pipe_count >1)
        {
            int pid;
            int start_pos = 0;
            int fds[2];
            for(int i=0; i<pparts.size(); i++)
            {
                IOper = false;
                string curr_command = pparts[i];
                trim(curr_command);
                curr_command += " "; //space is added, as split needs a space at the end to split accurately
                pipe_count = 0; // pipe count is made zero so normal quote functionality for strings is processed, and quotes are removed.
                                // refer to split function to understand more
                vector<string> commands = split(curr_command, pipe_count, ' ', IOper);
                if(IOper)
                {
                    int pos_read = curr_command.find('<');
                    int pos_write = curr_command.find('>');
                    if(pos_write>0)
                    {  
                        
                        string command = "";
                        string filename = "";
                        command = curr_command.substr(0, pos_write);
                        trim(command);
                        filename = curr_command.substr(pos_write + 1);
                        trim(filename);
                        curr_command = command;
                        int fd = open(filename.c_str(), O_WRONLY|O_CREAT|O_RDONLY, S_IWUSR| S_IRUSR);
                        dup2(fd, 1);
                        close(fd);
                    }
                    if(pos_read>0)
                    {   
                   
                        string command = "";
                        string filename = "";
                        command = curr_command.substr(0, pos_read);
                        trim(command);
                        filename = curr_command.substr(pos_read + 1);
                        trim(filename);
                        curr_command = command;
                        int fd = open(filename.c_str(), O_RDONLY, S_IWUSR|S_IRUSR);
                        dup2(fd, 0);
                        close(fd); 
                    }
                    curr_command += " ";
                    commands = split(curr_command, pipe_count, ' ', IOper);
                }
                pipe_count = temp;
                
                char** pipe_args = vec_to_char_array(commands);
                
                
                pipe(fds);
                pid = fork();
                if(pid == 0)
                {
                    if(i< pparts.size() -1)
                    {
                        dup2(fds[1], 1);

                    }

                    if(execvp (pipe_args[0], pipe_args))
                    {
                        
                    cout << "invalid command try again" << endl;
              
                    }
                }
                else
                {
                    if(i==pparts.size()-1) //only wait for last child.
                    {
                        waitpid(pid, 0,0);
                    }
                    else
                    {  // add pids to background processes vector so as to reap zombie processes of child pipe commands
                        bgs.push_back(pid);
                    }
                    dup2(fds[0], 0);
                    close(fds[1]);
                }
               
            }
           bgs.push_back(pid);
           waitpid(pid, 0, 0);
           continue;
        }
    
        // if it is simply a single command it will run this code below
        int pid = fork();
        if (pid == 0)
        {
            
           if(IOper)
           {
                int pos_read = inputline.find('<');
                int pos_write = inputline.find('>');
                if(pos_write>0)
                {  
            
                    string command = "";
                    string filename = "";
                    command = inputline.substr(0, pos_write);
                    trim(command);
                    filename = inputline.substr(pos_write + 1);
                    trim(filename);
                    inputline = command;
                    int fd = open(filename.c_str(), O_WRONLY|O_CREAT|O_RDONLY, S_IWUSR| S_IRUSR);
                    dup2(fd, 1);
                    close(fd);
                }
                if(pos_read>0)
                {   
                
                    string command = "";
                    string filename = "";
                    command = inputline.substr(0, pos_read);
                    trim(command);
                    filename = inputline.substr(pos_read + 1);
                    trim(filename);
                    inputline = command;
                    int fd = open(filename.c_str(), O_RDONLY, S_IWUSR|S_IRUSR);
                    dup2(fd, 0);
                    close(fd); 
                }
                
           }
            
            vector<string> parts = split(inputline, pipe_count, ' ', IOper); 
            char** args = vec_to_char_array(parts);

            if(execvp (args[0], args) == -1) //check for execvp, so as to not pass in an incorrect command
            {
                cout << "invalid command try again" << endl;
                break;
            }
        }
        else
        { 
            if(!bg)
            {
                
                waitpid (pid, 0, 0); //parent waits for child process
            }
            else
            {
                bgs.push_back(pid); //background processes are added to vector of PIDS, to be reaped before next command.
            }

           
        }
    }
}