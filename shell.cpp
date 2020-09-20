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
        str.erase(str.begin() + i, str.end()); 
    else
        str.erase(str.begin() + i - 1, str.end()); 
}

vector<string> split(string str, int& pipe_count, char sep, bool& IOper)
{
    vector<string> bgs;
    //istringstream ss(str);
    string token;
    string command = "";
    //str+= " ";
    for(int i=0;i < str.length(); i++)
    {

        if(str.at(i) == '|')
        {
            pipe_count ++;
        }
        if(str.at(i) == '<' || str.at(i) == '>')
        {
            IOper = true;
        }
       
        if((str.at(i) == '\"' || str.at(i) == '\'') && pipe_count>1)
        {   
            command += str.at(i);
            i++;
            while(str.at(i)!='\"' && str.at(i) != '\'')
            {
                command += str.at(i);
                i++;
            }
            command += str.at(i);
            //cout << "The command should return with quotes: " << command << endl;
            bgs.push_back(command);
            command="";
            continue;
        }
        else if((str.at(i) == '\"' || str.at(i) == '\''))
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
        
        if(str.at(i) == sep)
        {
            //cout << "command is: " << command << endl;
            if(command!= " ")
            {
                bgs.push_back(command);
            }
           
            command="";
            continue;
        }
        
        command+= str.at(i);
        
    }
    if(command!="")
    {
        bgs.push_back(command);
    }
    

    // Traverse through all words
    //cout << str.length();
    
    // do { 
    //     // Read a word 
    //     string word;
    //     ss >> word;
  
    //     // Print the read word
    //     bgs.push_back(word);
    //     //i++;
    //     // While there is more to read 
    // } while (ss);
    // bgs.resize(bgs.size()-1);
    // return bgs;
    // if(str.find("|")!= -1)
    // {
    //     while(getline(ss, token, '|')) 
    //     {
    //         //cout << token <<endl;
    //         pipe = true;
    //         bgs.push_back(token);
    //     }
    // }
    // else
    // {
        // while(getline(ss, token, sep)) 
        // {

        //     if(token == "|")
        //     {
        //         pipe_count++;
        //     }
        //     //cout << "token is: " <<   token <<endl;
        //     bgs.push_back(token);
        // }
    //}
    return bgs;
}

vector<string> pipe_split(string str, int& pipe_count)
{
    vector<string> bgs;
    //istringstream ss(str);
    //string token;
    string command = "";
    //str+= " ";
    for(int i=0;i < str.length(); i++)
    {
        if(str.at(i) == '|')
        {
            pipe_count++;
            //cout << "command is: " << command << endl;
            if(command!= " ")
            {
                bgs.push_back(command);
            }
           
            command="";
            continue;
        }
        
        command+= str.at(i);
        
    }
    if(command!="")
    {
        bgs.push_back(command);
    }
    return bgs;
}

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
    // bool IOper = false;
    // int pipe_count = 1;
    // vector<string> test = split("ps aux | awk '{print $1$11}' | sort -r | grep root", pipe_count, '|', IOper);
    // for(int i=0; i<test.size(); i++)
    // {
    //     cout << "command " << i << " " << test[i] << endl;
    // }
    vector<int> bgs;
    char* prev;
    prev = (char*) malloc( PATH_MAX * sizeof(char) );
    int backup = dup (0);
    while (true)
    {
        // time_t now = time(0);
        // char* dt = ctime(&now);
        time_t my_time = time(NULL); 
        dup2(backup, 0);
        bool IOper = false;
        bool bg = false;
        bool dir = false;
        int pipe_count = 1;
        string filename = "";

        // check on background processes before getting next;
        for(int k=0; k<bgs.size(); k++)
        {
            if(waitpid(bgs[k], 0, WNOHANG) == bgs[k])
            {
                cout << "Process: " << bgs[k] << " ended" << endl;
                bgs.erase(bgs.begin() + k);
                k--;
            }
        }

        cout << "AryaRamchandani" << "$ " ; //print a prompt
        string inputline;
        getline (cin, inputline); //get a line from standard input
        trim(inputline);
        // if(inputline.find('|') > 0)
        // {
        //     ispipe = true;
        // }
        if (inputline == string("exit"))
        {
            cout << "Bye!! End of shell" << endl;
            free(prev);
            prev = NULL;
            break;
        }
        
        //adjust string if background process is needed
        int pos = inputline.find('&');
        if( pos == inputline.length()-1)
        {
            inputline = inputline.substr(0, pos);
            bg = true;
        }      

        // if change directory is needed.
        if(inputline.find("cd") != string::npos)
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

    
        // vector<string> pparts = split(inputline, '|');
        // for(int i=0; i<pparts.size(); i++)
        // {
            
        //     int fds[2];
        //     pipe(fds);

        //     int pid = fork();
        //     if (pid == 0)
        //     {   
        //         //cout <<" I enter here " << endl;
        //         int pos_write = inputline.find('>');
        //         int pos_read = inputline.find('<');
        //         if(pos_write>0)
        //         {   

        //             string command = "";
        //             string filename = "";
        //             command = inputline.substr(0, pos_write);
        //             trim(command);
        //             filename = inputline.substr(pos_write + 1);
        //             trim(filename);
        //             inputline = command;
        //             int fd = open(filename.c_str(), O_WRONLY|O_CREAT|O_RDONLY, S_IWUSR| S_IRUSR);
        //             dup2(fd, 1);
        //             close(fd);
        //         }
        //         if(pos_read>0)
        //         {   

        //             string command = "";
        //             string filename = "";
        //             command = inputline.substr(0, pos_read);
        //             trim(command);
        //             filename = inputline.substr(pos_read + 1);
        //             trim(filename);
        //             inputline = command;
        //             int fd = open(filename.c_str(), O_RDONLY, S_IWUSR|S_IRUSR);
        //             dup2(fd, 0);
        //             close(fd); 
        //         }
        //         if(i < pparts.size() -1)
        //         {
        //             dup2(fds[1], 1);
        //             close(fds[1]);
            
        //         }

        //         string command = pparts[i];
        //         //cout << inputline << endl;
        //         vector<string> parts = split(command, ' ');
        //         char** args = vec_to_char_array(parts);
        //         execvp (args[0], args);
        //     }
        //     else
        //     { 
        //         if(!bg)
        //         {
        //             //cout << "enter here" <<endl;
        //             waitpid (pid, 0, 0); //parent waits for child process
        //             dup2(fds[0], 0);
        //             close(fds[1]);
        //         }
        //         else
        //         {
        //             bgs.push_back(pid);
        //         }

            
        //     }
        // }

        //pipe_count =2;
        vector<string> pparts = split(inputline, pipe_count, '|', IOper);
        int temp = pipe_count;
        //cout << " parts 0 is at line 351: " << parts[0] << endl;
        //if piping operation
        
        if(pipe_count >1)
        {
            int pid;
            int start_pos = 0;
            for(int i=0; i<pparts.size(); i++)
            {
                IOper = false;
                string curr_command = pparts[i];
                trim(curr_command);
                curr_command += " ";
                pipe_count = 0;
                
                vector<string> commands = split(curr_command, pipe_count, ' ', IOper);
                if(IOper)
                {
                    int pos_read = curr_command.find('<');
                    int pos_write = curr_command.find('>');
                    if(pos_write>0)
                    {  
                        //cout <<"I am in the first if" << endl;
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
                    //s cout << "I am in the second if " << endl;
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
                    //commands = split(curr_command, pipe_count, ' ', IOper);
                }
                pipe_count = temp;
                
                char** pipe_args = vec_to_char_array(commands);
                
                int fds[2];
                pipe(fds);
                pid = fork();
                if(pid == 0)
                {
                    if(i< pipe_count -1)
                    {
                        dup2(fds[1], 1);
                
                    }

                    execvp (pipe_args[0], pipe_args);
                }
                else
                {
                    //waitpid(pid, 0, 0);
                    dup2(fds[0], 0);
                    close(fds[1]);
                }
               
            }

           waitpid(pid, 0, 0);
           continue;
        }
        
        //if not change directory operation fork and proceed.
        
        int pid = fork();
        //int pid = 1;
        if (pid == 0)
        {   //cout <<"I make it here" << endl;
            vector<string> parts;
           if(IOper)
           {
                int pos_read = inputline.find('<');
                int pos_write = inputline.find('>');
                if(pos_write>0)
                {  
                    //cout <<"I am in the first if" << endl;
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
                   //s cout << "I am in the second if " << endl;
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
                parts = split(inputline, pipe_count, ' ', IOper);
           }
            
           
            //cout << "parts is: " << parts[0] << "    " << parts[1] << endl; 
            char** args = vec_to_char_array(parts);
            execvp (args[0], args);
        }
        else
        { 
            if(!bg)
            {
                //cout << "enter here" <<endl;
                waitpid (pid, 0, 0); //parent waits for child process
            }
            else
            {
                bgs.push_back(pid);
            }

           
        }
    }
}

// for(int i=start_pos; i<pparts.size(); i++)
                // {
                //     if(pparts[i] == "|")
                //     {
                //         start_pos = i +1;
                //         break;
                //     } 
                //     curr_command += pparts[i] + " ";
                // }