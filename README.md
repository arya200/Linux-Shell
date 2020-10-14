**Features of Shell**

Environment

The shell maintains many variables which allow the user to maintain some settings and information visible throughout the system. This is analogous to a collection of global variables in a C program. The difference is that all programs running from the shell can use environment variables. For instance, the current working directory and the PATH are two of many important variables. As its name implies, the current working directory variable keeps track of the user&#39;s current directory. The PATH variable on the other hand consists of a colon separated directory list that is searched wherever you type a command in the terminal. If an executable file by the same name does not exist in any of these directories or the current directory, the shell says &quot;command not found&quot;, which is something we experience when trying to run a program before installing it. One may modify the PATH at any time to add and remove directories to search for executables. The following shows the commands for printing the current directory and the content of the PATH variable:

**shell\&gt;** pwd

/home/tanzir

**shell\&gt;** echo $PATH

/usr/local/bin:/usr/bin:/usr/local/games:..

Command Pipelining

While the individual linux commands are useful for doing specific tasks (e.g., **grep** for searching, **ls** for listing files, **echo** for printing), sometimes the problems at hand are more complicated as they require multiple commands together and feeding the output of one to the input of the next. The linux shell lets you combine commands by putting the character | between then. A pipe in between two commands causes the standard output of one to be redirected into the standard input of another. An example of this is provided below, using the pipe operation to search for all processes with the name &quot;bash&quot;.

**shell\&gt;** ps -elf | grep bash | awk &#39;{print $10}&#39; | sort

3701

4197

Input/Output Redirection

Many times, the output of a program is not intended for immediate human consumption (if at all). Even if someone isn&#39;t intending to look at the output of your program, it is still immensely helpful to have it print out status/logging messages during execution. If something goes wrong, those messages can be reviewed to help pinpoint bugs. Since it is impractical to have all messages from all system programs print out to a screen to be reviewed at a later date, sending that data to a file as it is printed is desired.

Other times, a program might require an extensive list of input commands. It would be an unnecessary waste of programmer time to have to sit and type them out individually. Instead, pre-written text in a file can be redirected to serve as the input of the program as if it were entered in the terminal window.

In short, the shell implements input redirection by redirecting the standard input of a program to an file opened for reading. Similarly, output redirection is implemented by changing the standard output (and sometimes also standard error) to point to a file opened for writing.

**shell\&gt;** echo &quot;This text will go to a file&quot; \&gt; temp.txt

**shell\&gt;** cat temp.text

This text will go to a file

**shell\&gt;** cat \&lt; temp1.txt

This text came from a file

Background Processes

When you run a command in the shell, it suspends until the command finishes. We often do not notice this effect because many commonly used commands finish soon after they start. However, if the command takes a while to finish, the shell stays inactive for that duration and you cannot use it. For instance, typing **sleep 5** in the shell causes the shell to suspend for 5 seconds. Only after that the prompt comes back and you can type the next command. You can change this behavior by sending the program to the background and continue using the shell. If you type **sleep 5 &amp;** in the shell for example, it will return the shell immediately because the corresponding process for the sleep runs in the background instead of in the foreground where regular programs run.

Implementation Hint: First of all, remove the &#39;&amp;&#39; symbol from the command before passing it to exec(). But use the symbol to set a boolean that tells you that it is supposed to run in the background. After that, from the parent process do not call **waitpid()**, which you have been doing for the regular processes. Rather put the pid into a list/vector of background processes that are currently running and periodically check on the list to make sure that they do not become Zombies or do not stay in that state for too long. A good frequency of check is before scanning the next input from the user inside the main loop. Keep in mind that waitpid() function suspends when called on a running process. Therefore, calling it as it is on background processes may cause your whole program to get suspended. However, there is an option in waitpid() that makes it non-blocking, which is the desired way of calling it on background processes. You can find this option from the man pages.

Use of Single/Double Quotes

White-spaces are usually treated as argument separators except when they are used inside quotes. For example, notice the difference between the following two commands:

**shell\&gt;** echo -e &quot;cat\ta.txt&quot;

cat a.txt

**shell\&gt;** echo &quot;-e cat\ta.txt&quot;

-e cat\ta.txt

Note that the &quot;-e&quot; option for the **echo** command prints the string with interpretation of some symbols. Now, in the first command, the string is put inside quotes to make sure that it is interpreted as a single string. As a result of using the -e option, the string is printed after interpreting the &quot;\t&quot; as a tab. In the second example, &quot;-e&quot; is part of the string which masks &#39;\t&#39; interpretation and prints a multi-word sentence which is impossible without putting quotes around. Also note the following example:

**shell\&gt;** echo -e `\&lt;\&lt;\&lt;\&lt;\&lt; This message contains a |||line feed \&gt;\&gt;\&gt;\&gt;\&gt;\n&#39;

\&lt;\&lt;\&lt;\&lt;\&lt; This message contains a |||line feed \&gt;\&gt;\&gt;\&gt;\&gt;

**shell\&gt;**

Which does not consider the above command to have redirections or pipes because the corresponding symbols are inside quotation marks.
