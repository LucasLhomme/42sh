#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

// Ajustez le chemin vers votre binaire mysh
#define MYSH_PATH "./mysh"

// Implémentation de execute_command qui lance réellement votre shell
int execute_command(const char *command) {
    FILE *fp;
    char cmd[1024];
    int status;

    // Créer une commande qui exécute mysh avec la commande donnée
    // echo "command" | ./mysh
    snprintf(cmd, sizeof(cmd), "echo \"%s\" | %s", command, MYSH_PATH);
    
    // Exécuter la commande et capturer le statut de sortie
    fp = popen(cmd, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        return -1;
    }
    
    // Lire la sortie pour vider le buffer (optionnel)
    char output[1024];
    while (fgets(output, sizeof(output), fp) != NULL) {
        // Vous pouvez traiter la sortie si nécessaire
    }
    
    // Récupérer le code de retour
    status = pclose(fp);
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    
    return -1;
}

// Helper function to set up environment
static void setup_env(const char *path_value, const char *term_value) {
    if (path_value)
        setenv("PATH", path_value, 1);
    if (term_value)
        setenv("TERM", term_value, 1);
}

// Redirect stdout and stderr for all tests
static void redirect_all_std(void) {
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// Vérifier que mysh existe avant de lancer les tests
static void check_mysh_exists(void) {
    if (access(MYSH_PATH, X_OK) != 0) {
        cr_log_error("mysh executable not found at: %s\n", MYSH_PATH);
        cr_assert_fail("mysh executable not found");
    }
}

// Helper function to clean environment variables
static void clean_env_variables(void) {
    // Réinitialiser les variables d'environnement essentielles
    char *path = getenv("PATH_BACKUP");
    if (path)
        setenv("PATH", path, 1);
}

// Test setup qui vérifie l'existence du binaire
static void test_setup(void) {
    check_mysh_exists();
    // Sauvegarder PATH original
    char *path = getenv("PATH");
    if (path)
        setenv("PATH_BACKUP", path, 1);
    redirect_all_std();
}

// Test teardown qui nettoie l'environnement
static void test_teardown(void) {
    clean_env_variables();
}

/* 
 * Minishell 1 Tests
 */

// Test empty command
Test(minishell1, empty_command, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result = execute_command("");
    
    cr_assert_eq(result, 0, "Empty command should return 0");
}

// Test basic commands
Test(minishell1, basic_commands, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result1 = execute_command("ls /etc");
    cr_assert_eq(result1, 0, "ls /etc should succeed");
    
    int result2 = execute_command("cat /etc/resolv.conf");
    cr_assert_eq(result2, 0, "cat /etc/resolv.conf should succeed");
}

// Test with different PATH settings
Test(minishell1, different_path, .init = test_setup, .fini = test_teardown) {
    setup_env("/usr/bin", "xterm");
    int result1 = execute_command("pwd");
    cr_assert_eq(result1, 0, "pwd should succeed with PATH=/usr/bin");
    
    setup_env("/bin", "xterm");
    int result2 = execute_command("pwd");
    cr_assert_eq(result2, 0, "pwd should succeed with PATH=/bin");
}

// Test multiple commands in sequence
Test(minishell1, multiple_commands, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result1 = execute_command("cat /etc/resolv.conf");
    cr_assert_eq(result1, 0, "First command should succeed");
    
    int result2 = execute_command("ls -l /etc");
    cr_assert_eq(result2, 0, "Second command should succeed");
    
    int result3 = execute_command("pwd");
    cr_assert_eq(result3, 0, "Third command should succeed");
}

// Test environment variable operations
Test(minishell1, env_operations, .init = test_setup, .fini = test_teardown) {
    clean_env_variables();
    setup_env("/bin:/usr/bin", "xterm");
    setenv("HOSTTYPE", "value", 1);
    setenv("_", "ls", 1);
    setenv("LS_COLORS", "RID", 1);
    setenv("MYBG", "4", 1);
    setenv("LVL", "4", 1);
    setenv("NOTE", "2", 1);
    
    int result1 = execute_command("unsetenv HOSTTYPE");
    cr_assert_eq(result1, 0, "unsetenv should succeed");
    cr_assert_null(getenv("HOSTTYPE"), "HOSTTYPE should be unset");
    
    int result2 = execute_command("setenv var1 val1");
    cr_assert_eq(result2, 0, "setenv should succeed");
    cr_assert_str_eq(getenv("var1"), "val1", "var1 should be set to val1");
    
    int result3 = execute_command("setenv var2 val2");
    cr_assert_eq(result3, 0, "setenv should succeed");
    cr_assert_str_eq(getenv("var2"), "val2", "var2 should be set to val2");
}

// Test cd built-in
Test(minishell1, cd_builtin, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    char original_dir[1024];
    getcwd(original_dir, sizeof(original_dir));
    
    int result1 = execute_command("cd ..");
    cr_assert_eq(result1, 0, "cd .. should succeed");
    
    char new_dir[1024];
    getcwd(new_dir, sizeof(new_dir));
    cr_assert_neq(strcmp(original_dir, new_dir), 0, "Directory should have changed");
    
    int result2 = execute_command("cd /usr");
    cr_assert_eq(result2, 0, "cd /usr should succeed");
    
    getcwd(new_dir, sizeof(new_dir));
    cr_assert_str_eq(new_dir, "/usr", "Current directory should be /usr");
}

// Test with many tabs and spaces
Test(minishell1, tabs_and_spaces, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result = execute_command("\t\t    ls\t     \t-l    \t\t  \t -a /usr   \t\t");
    cr_assert_eq(result, 0, "Command with tabs and spaces should succeed");
}

// Test error handling for non-existent directory
Test(minishell1, cd_nonexistent, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result = execute_command("cd caca");
    cr_assert_neq(result, 0, "cd to non-existent directory should fail");
    
    int result2 = execute_command("ls -l");
    cr_assert_eq(result2, 0, "Shell should continue working after error");
}

// Test error handling for non-existent file
Test(minishell1, ls_nonexistent, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result = execute_command("ls nofile");
    cr_assert_neq(result, 0, "ls non-existent file should return error");
}

// Test cd - (previous directory)
Test(minishell1, cd_previous, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    char original_dir[1024];
    getcwd(original_dir, sizeof(original_dir));
    
    execute_command("cd ..");
    char parent_dir[1024];
    getcwd(parent_dir, sizeof(parent_dir));
    
    int result1 = execute_command("cd -");
    cr_assert_eq(result1, 0, "cd - should succeed");
    
    char new_dir[1024];
    getcwd(new_dir, sizeof(new_dir));
    cr_assert_str_eq(new_dir, original_dir, "cd - should return to original directory");
    
    int result2 = execute_command("cd -");
    cr_assert_eq(result2, 0, "second cd - should succeed");
    
    getcwd(new_dir, sizeof(new_dir));
    cr_assert_str_eq(new_dir, parent_dir, "second cd - should return to parent directory");
}

// Test invalid setenv (starting with number)
Test(minishell1, invalid_setenv_number, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result = execute_command("setenv 4coucou coucou");
    cr_assert_neq(result, 0, "setenv with name starting with number should fail");
}

// Test invalid setenv (non-alphanumeric character)
Test(minishell1, invalid_setenv_special_char, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result = execute_command("setenv coucou: coucou");
    cr_assert_neq(result, 0, "setenv with non-alphanumeric character should fail");
}

// Test setenv with one argument
Test(minishell1, setenv_one_arg, .init = test_setup, .fini = test_teardown) {
    clean_env_variables();
    setup_env("/bin:/usr/bin", "xterm");
    
    int result = execute_command("setenv coucou");
    cr_assert_eq(result, 0, "setenv with one argument should succeed");
    cr_assert_not_null(getenv("coucou"), "coucou should be set");
    cr_assert_str_eq(getenv("coucou"), "", "coucou should be set to empty string");
}

// Test cd home directory
Test(minishell1, cd_home, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    char *home = getenv("HOME");
    if (!home) {
        cr_skip("HOME environment variable not set");
    }
    
    int result = execute_command("cd ~");
    cr_assert_eq(result, 0, "cd ~ should succeed");
    
    char current_dir[1024];
    getcwd(current_dir, sizeof(current_dir));
    cr_assert_str_eq(current_dir, home, "Current directory should be HOME");
}

// Test cd with no argument (should go to HOME)
Test(minishell1, cd_no_arg, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    char *home = getenv("HOME");
    if (!home) {
        cr_skip("HOME environment variable not set");
    }
    
    int result = execute_command("cd");
    cr_assert_eq(result, 0, "cd without argument should succeed");
    
    char current_dir[1024];
    getcwd(current_dir, sizeof(current_dir));
    cr_assert_str_eq(current_dir, home, "Current directory should be HOME");
}

// Test creating, displaying and deleting files
Test(minishell1, file_operations, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result1 = execute_command("touch test");
    cr_assert_eq(result1, 0, "touch should succeed");
    
    FILE *f = fopen("test", "r");
    cr_assert_not_null(f, "File should exist");
    if (f) fclose(f);
    
    int result2 = execute_command("cat test");
    cr_assert_eq(result2, 0, "cat should succeed");
    
    int result3 = execute_command("rm test");
    cr_assert_eq(result3, 0, "rm should succeed");
    
    f = fopen("test", "r");
    cr_assert_null(f, "File should not exist after rm");
}

// Test setting environment variable with valid underscore
Test(minishell1, setenv_underscore, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result = execute_command("setenv _test value");
    cr_assert_eq(result, 0, "setenv with underscore should succeed");
    cr_assert_str_eq(getenv("_test"), "value", "_test should be set to value");
}

// Test unsetenv without parameters
Test(minishell1, unsetenv_no_params, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result = execute_command("unsetenv");
    cr_assert_neq(result, 0, "unsetenv without parameters should fail");
}

/*
 * Minishell 2 Tests
 */

// Test simple pipe
Test(minishell2, simple_pipe, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result = execute_command("ls -l /etc | grep sh");
    cr_assert_eq(result, 0, "Simple pipe should succeed");
}

// Test pipe with builtin
Test(minishell2, pipe_with_builtin, .init = test_setup, .fini = test_teardown) {
    setenv("VAR1", "VALEUR1", 1);
    setup_env("/random", "xterm");
    
    int result1 = execute_command("setenv | /bin/grep VAR1");
    cr_assert_eq(result1, 0, "Pipe with setenv should succeed");
    
    int result2 = execute_command("/bin/ls | cd /usr");
    cr_assert_eq(result2, 0, "Pipe with cd should succeed");
    
    char current_dir[1024];
    getcwd(current_dir, sizeof(current_dir));
    cr_assert_str_eq(current_dir, "/usr", "Current directory should be /usr");
    
    int result3 = execute_command("ls -l");
    cr_assert_eq(result3, 0, "ls after cd should succeed");
    
    int result4 = execute_command("exit 45 | cat /etc/resolv.conf");
    cr_assert_eq(result4, 0, "Pipe with exit should succeed");
}

// Test simple pipe with grep
Test(minishell2, simple_pipe_grep, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result = execute_command("echo nicolas des small bytes | grep y");
    cr_assert_eq(result, 0, "Simple pipe with grep should succeed");
}

// Test multiple commands with semicolon
Test(minishell2, multiple_commands_semicolon, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result = execute_command("ls ; ls -l");
    cr_assert_eq(result, 0, "Multiple commands with semicolon should succeed");
}

// Test multiple commands with arguments
Test(minishell2, multiple_commands_with_args, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result = execute_command("ls -l ; ls -a");
    cr_assert_eq(result, 0, "Multiple commands with arguments should succeed");
}

// Test multiple pipes
Test(minishell2, multiple_pipes, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result = execute_command("ls -l | grep a | grep o");
    cr_assert_eq(result, 0, "Multiple pipes should succeed");
}

// Test multiple commands with pipes
Test(minishell2, multiple_commands_with_pipes, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result = execute_command("ls -l | grep a | grep o ; ls -a | grep .");
    cr_assert_eq(result, 0, "Multiple commands with pipes should succeed");
}

// Test simple redirection
Test(minishell2, simple_redirection, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result1 = execute_command("ls -l > coucou");
    cr_assert_eq(result1, 0, "Redirection should succeed");
    
    FILE *f = fopen("coucou", "r");
    cr_assert_not_null(f, "Output file should exist");
    if (f) fclose(f);
    
    int result2 = execute_command("cat coucou");
    cr_assert_eq(result2, 0, "Reading redirected output should succeed");
    
    remove("coucou");
}

// Test multiple redirections
Test(minishell2, multiple_redirections, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result1 = execute_command("ls -l > coucou");
    cr_assert_eq(result1, 0, "First redirection should succeed");
    
    int result2 = execute_command("ls -l >> coucou");
    cr_assert_eq(result2, 0, "Append redirection should succeed");
    
    int result3 = execute_command("cat < coucou");
    cr_assert_eq(result3, 0, "Input redirection should succeed");
    
    remove("coucou");
}

// Test void redirection
Test(minishell2, void_redirection, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result = execute_command("<");
    cr_assert_neq(result, 0, "Void redirection should fail");
}

// Test invalid pipe syntax
Test(minishell2, invalid_pipe_syntax, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result = execute_command("ls |||||||||");
    cr_assert_neq(result, 0, "Invalid pipe syntax should fail");
}

// Test redirection with pipe
Test(minishell2, redirection_with_pipe, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result1 = execute_command("ls -l > coucou");
    cr_assert_eq(result1, 0, "Redirection should succeed");
    
    int result2 = execute_command("cat < coucou | grep a");
    cr_assert_eq(result2, 0, "Redirection with pipe should succeed");
    
    remove("coucou");
}

// Test heredoc
Test(minishell2, heredoc, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    cr_skip("Heredoc test needs special handling");
}

// Test pipe with cd
Test(minishell2, pipe_with_cd, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    char original_dir[1024];
    getcwd(original_dir, sizeof(original_dir));
    
    int result1 = execute_command("ls -l | grep nicolas | cd ../");
    cr_assert_eq(result1, 0, "Pipe with cd should succeed");
    
    char new_dir[1024];
    getcwd(new_dir, sizeof(new_dir));
    cr_assert_neq(strcmp(original_dir, new_dir), 0, "Directory should have changed");
    
    int result2 = execute_command("ls");
    cr_assert_eq(result2, 0, "ls after cd should succeed");
}

// Test exit command with pipe
Test(minishell2, exit_with_pipe, .init = test_setup, .fini = test_teardown) {
    setup_env("/bin:/usr/bin", "xterm");
    
    int result = execute_command("exit | ls");
    cr_assert_eq(result, 0, "exit with pipe should succeed");
}

// Main function to run all tests
int main(int argc, char *argv[]) {
    if (access(MYSH_PATH, X_OK) != 0) {
        fprintf(stderr, "Erreur: l'exécutable mysh n'a pas été trouvé à l'emplacement: %s\n", MYSH_PATH);
        return 1;
    }
    
    struct criterion_test_set *tests = criterion_initialize();
    
    int result = 0;
    if (criterion_handle_args(argc, argv, true))
        result = !criterion_run_all_tests(tests);
    
    criterion_finalize(tests);
    return result;
}