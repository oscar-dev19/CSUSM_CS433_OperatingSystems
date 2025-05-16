/**
 * Assignment 2: Simple UNIX Shell
 * @file prog.cpp
 * @brief This is the main function of a simple UNIX Shell that supports command execution, history, I/O redirection, and pipes
 * @version 1.1
 */

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <string>
#include <array>
#include <signal.h>

using namespace std;

#define MAX_LINE 80 // The maximum length command
#define HISTORY_SIZE 10 // Size of history buffer

// Global variables for history
vector<string> history;
int history_count = 0;

// Forward declaration
bool execute_command(char *args[], int num_args);

/**
 * @brief parse out the command and arguments from the input command separated by spaces
 * @param command Input command string
 * @param args Array to store parsed arguments
 * @return Number of arguments
 */
int parse_command(char command[], char *args[])
{
    int count = 0;
    char *token = strtok(command, " \n\t");
    bool is_background = false;
    
    while (token != NULL && count < MAX_LINE/2) {
        size_t len = strlen(token);
        
        // Check if this token ends with &
        if (len > 0 && token[len-1] == '&') {
            // Remove the & from the token
            token[len-1] = '\0';
            is_background = true;
            
            // Only add token if it's not empty after removing &
            if (strlen(token) > 0) {
                args[count++] = token;
            }
        } else {
            args[count++] = token;
        }
        
        token = strtok(NULL, " \n\t");
    }
    
    // Add & as a separate argument if command is to run in background
    if (is_background) {
        args[count++] = strdup("&");
    }
    
    args[count] = NULL;
    return count;
}

/**
 * @brief Get the last command from history
 * @return Last command or empty string if history is empty
 */
string get_last_command() {
    if (history.empty()) {
        printf("No command history\n");
        return "";
    }
    return history.back();
}

/**
 * @brief Add command to history
 * @param command Command to add
 */
void add_to_history(const string& command) {
    if (command.empty() || command == "!!" || command[0] == '!') return;
    
    if (history.size() >= HISTORY_SIZE) {
        history.erase(history.begin());
    }
    history.push_back(command);
    history_count++;
}

/**
 * @brief Execute a single pipe command (cmd1 | cmd2)
 * @param cmd1 First command and its arguments
 * @param cmd2 Second command and its arguments
 * @return true if successful
 */
bool execute_pipe(char* cmd1[], char* cmd2[]) {
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        return false;
    }

    // Create first child (cmd1)
    pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed");
        return false;
    }

    if (pid1 == 0) {  // First child process
        close(pipefd[0]);  // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO);  // Redirect stdout to pipe
        close(pipefd[1]);

        execvp(cmd1[0], cmd1);
        perror("Command not found");
        exit(1);
    }

    // Create second child (cmd2)
    pid2 = fork();
    if (pid2 < 0) {
        perror("Fork failed");
        return false;
    }

    if (pid2 == 0) {  // Second child process
        close(pipefd[1]);  // Close unused write end
        dup2(pipefd[0], STDIN_FILENO);  // Redirect stdin to pipe
        close(pipefd[0]);

        execvp(cmd2[0], cmd2);
        perror("Command not found");
        exit(1);
    }

    // Parent process
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return true;
}

/**
 * @brief Execute the command with I/O redirection and pipe support
 * @param args Command arguments
 * @param num_args Number of arguments
 * @return true if command executed successfully
 */
bool execute_command(char *args[], int num_args) {
    if (num_args == 0) return true;
    
    // Check for background execution
    bool is_background = false;
    if (num_args > 0 && strcmp(args[num_args-1], "&") == 0) {
        is_background = true;
        args[--num_args] = NULL;  // Remove & from arguments
    }

    // Check for pipe
    int pipe_pos = -1;
    for (int i = 0; i < num_args; i++) {
        if (strcmp(args[i], "|") == 0) {
            pipe_pos = i;
            break;
        }
    }

    // Handle pipe command
    if (pipe_pos != -1) {
        args[pipe_pos] = NULL;  // Split commands at pipe
        char **cmd2 = &args[pipe_pos + 1];
        
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            return false;
        }
        if (pid == 0) {  // Child process
            execute_pipe(args, cmd2);
            exit(0);
        }
        if (!is_background) {
            waitpid(pid, NULL, 0);
        }
        return true;
    }

    // Check for redirection
    int input_fd = -1, output_fd = -1;
    char *input_file = NULL, *output_file = NULL;
    int cmd_end = num_args;

    for (int i = 0; i < num_args; i++) {
        if (strcmp(args[i], "<") == 0 && i + 1 < num_args) {
            input_file = args[i + 1];
            cmd_end = i;
            i++;
        } else if (strcmp(args[i], ">") == 0 && i + 1 < num_args) {
            output_file = args[i + 1];
            cmd_end = i;
            i++;
        }
    }
    args[cmd_end] = NULL;

    // Execute command
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return false;
    }
    
    if (pid == 0) {  // Child process
        // Handle input redirection
        if (input_file) {
            input_fd = open(input_file, O_RDONLY);
            if (input_fd < 0) {
                perror("Failed to open input file");
                exit(1);
            }
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }

        // Handle output redirection
        if (output_file) {
            output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (output_fd < 0) {
                perror("Failed to open output file");
                exit(1);
            }
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        // Execute command
        if (execvp(args[0], args) < 0) {
            perror("Command not found");
            exit(1);
        }
    }

    // Parent process
    if (!is_background) {
        waitpid(pid, NULL, 0);
    }
    
    return true;
}

int main(void)
{
    char command[MAX_LINE];       // the command that was entered
    char *args[MAX_LINE / 2 + 1]; // hold parsed out command line arguments
    int should_run = 1;           // flag to determine when to exit program
    string cmd_str;

    while (should_run)
    {
        printf("osh>");
        fflush(stdout);
        
        // Read the input command
        if (!fgets(command, MAX_LINE, stdin)) break;
        
        // Save original command
        cmd_str = string(command);
        cmd_str = cmd_str.substr(0, cmd_str.length()-1); // Remove newline
        
        // Handle history commands
        if (cmd_str == "!!") {
            string last_cmd = get_last_command();
            if (last_cmd.empty()) {
                continue;
            }
            printf("%s\n", last_cmd.c_str());
            strcpy(command, last_cmd.c_str());
            strcat(command, "\n");  // Add newline back for parsing
        }
        
        // Parse the input command
        int num_args = parse_command(command, args);
        
        // Handle built-in commands
        if (num_args > 0) {
            if (strcmp(args[0], "exit") == 0) {
                should_run = 0;
                continue;
            }
        }
        
        // Execute the command and add to history if successful
        if (execute_command(args, num_args)) {
            add_to_history(cmd_str);
        }
    }
    return 0;
}

