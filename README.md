# Features of Shell

### Environment

The shell maintains many variables which allow the user to maintain some settings and information visible throughout the system. This is analogous to a collection of global variables in a C program. The difference is that all programs running from the shell can use environment variables. For instance, the current working directory and the PATH are two of many important variables. As its name implies, the current working directory variable keeps track of the user&#39;s current directory. The PATH variable on the other hand consists of a colon separated directory list that is searched wherever you type a command in the terminal. If an executable file by the same name does not exist in any of these directories or the current directory, the shell says &quot;command not found&quot;, which is something we experience when trying to run a program before installing it. One may modify the PATH at any time to add and remove directories to search for executables. The following shows the commands for printing the current directory and the content of the PATH variable:

![pwd](https://user-images.githubusercontent.com/59649759/95981886-05523680-0e3d-11eb-847a-6e9256281ef3.PNG)

### Command Pipelining

While the individual linux commands are useful for doing specific tasks (e.g., **grep** for searching, **ls** for listing files, **echo** for printing), sometimes the problems at hand are more complicated as they require multiple commands together and feeding the output of one to the input of the next. The linux shell lets you combine commands by putting the character | between then. A pipe in between two commands causes the standard output of one to be redirected into the standard input of another. An example of this is provided below, using the pipe operation to search for all processes with the name &quot;bash&quot;.

![piping](https://user-images.githubusercontent.com/59649759/95982181-6ed24500-0e3d-11eb-8a9b-f3a39a66b28d.PNG)

### Input/Output Redirection

Many times, the output of a program is not intended for immediate human consumption (if at all). Even if someone isn&#39;t intending to look at the output of your program, it is still immensely helpful to have it print out status/logging messages during execution. If something goes wrong, those messages can be reviewed to help pinpoint bugs. Since it is impractical to have all messages from all system programs print out to a screen to be reviewed at a later date, sending that data to a file as it is printed is desired.

Other times, a program might require an extensive list of input commands. It would be an unnecessary waste of programmer time to have to sit and type them out individually. Instead, pre-written text in a file can be redirected to serve as the input of the program as if it were entered in the terminal window.

In short, the shell implements input redirection by redirecting the standard input of a program to an file opened for reading. Similarly, output redirection is implemented by changing the standard output (and sometimes also standard error) to point to a file opened for writing.


![IO redirection](https://user-images.githubusercontent.com/59649759/95982573-df796180-0e3d-11eb-8000-02d3a0ea10a9.PNG)


### Background Processes

When you run a command in the shell, it suspends until the command finishes. We often do not notice this effect because many commonly used commands finish soon after they start. However, if the command takes a while to finish, the shell stays inactive for that duration and you cannot use it. For instance, typing **sleep 5** in the shell causes the shell to suspend for 5 seconds. Only after that the prompt comes back and you can type the next command. You can change this behavior by sending the program to the background and continue using the shell. If you type **sleep 5 &amp;** in the shell for example, it will return the shell immediately because the corresponding process for the sleep runs in the background instead of in the foreground where regular programs run.

![sleep20](https://user-images.githubusercontent.com/59649759/95982751-236c6680-0e3e-11eb-89a7-65693c895a19.PNG)

![bgprocess](https://user-images.githubusercontent.com/59649759/95982758-25cec080-0e3e-11eb-8484-02e97a486132.PNG)


### Use of Single/Double Quotes

Note that the &quot;-e&quot; option for the **echo** command prints the string with interpretation of some symbols. In the example below, &quot;-e&quot; is part of the string which masks &#39;\t&#39; interpretation and prints a multi-word sentence which is impossible without putting quotes around. Also note the following example:

![echo](https://user-images.githubusercontent.com/59649759/95983106-b5746f00-0e3e-11eb-9d03-7a22720e691f.PNG)

Which does not consider the above command to have redirections or pipes because the corresponding symbols are inside quotation marks.


### For an extensive demo please watch this video tutorial here:
https://youtu.be/S7_FnzQtkJM
