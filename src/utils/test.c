#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Global variable to capture the signal number.
// Must be volatile sig_atomic_t for safe access from a signal handler.
volatile sig_atomic_t g_last_signal = 0;

// This is the extended signal handler function.
// It receives a siginfo_t struct, from which we can extract more information.
static void handler(int sig_num, siginfo_t *info, void *context) {
    // The signal number is available in the siginfo_t structure.
    g_last_signal = info->si_signo;
	(void)sig_num;
    // In a real application, a signal handler should only set a flag and exit.
    // Avoid calling non-async-signal-safe functions like printf() inside a handler,
    // as it can lead to undefined behavior or deadlocks.
    // We are only using printf() here for a simple, clear demonstration.
    (void)context; // To suppress unused variable warning.
}

void setup_signal_handler(int sig_num) {
    struct sigaction sa;

    // Clear the struct to avoid garbage values.
    sigemptyset(&sa.sa_mask);

    // Set the handler function to be the extended version.
    sa.sa_sigaction = handler;

    // Use SA_SIGINFO to tell sigaction() to use sa_sigaction.
    sa.sa_flags = SA_SIGINFO;

    // Register the signal handler for the specified signal.
    if (sigaction(sig_num, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

int main(void) {
    // Register the signal handler for SIGINT (Ctrl-C).
    setup_signal_handler(SIGINT);
    
    printf("Signal handler for SIGINT is set. Try pressing Ctrl-C.\n");
    printf("The program will run until a signal is received.\n\n");

    // Main loop that waits for a signal.
    while (g_last_signal == 0) {
        pause(); // Wait for any signal to arrive.
    }

    // Now, g_last_signal holds the number of the signal that was delivered.
    printf("Received signal number: %d\n", g_last_signal);

    return 0;
}
