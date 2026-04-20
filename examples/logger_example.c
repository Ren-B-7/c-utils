#include <stdio.h>
#include <stdlib.h>

#include "logger.h"
#include "minunit.h"

/* --- Logger Example --- */

// This example demonstrates the basic usage of the logger.
// It shows how to set the log level and output messages at different levels.

char *test_logger_levels() {
    // Default log level is LOG_INFO.
    // Messages with level below LOG_INFO will not be displayed.

    log_info("This is an informational message."); // Should be displayed
    log_warn("This is a warning message.");     // Should be displayed
    log_error("This is an error message.");     // Should be displayed
    log_debug("This is a debug message.");     // Should NOT be displayed

    // Change log level to LOG_DEBUG
    set_log_level(LOG_DEBUG);
    log_debug("This is now a debug message (level changed)."); // Should be displayed

    // Change log level back to LOG_INFO for subsequent tests
    set_log_level(LOG_INFO);

    return NULL;
}

char *test_logger_custom_output() {
    // You can redirect log output to a file.
    // For this example, we'll just demonstrate it conceptually.
    // In a real test, you'd capture stdout/stderr or redirect to a file.

    FILE *log_file = fopen("test_log.txt", "w");
    if (log_file == NULL) {
        // In a real test, this would be an error. For this example, we'll just note it.
        fprintf(stderr, "Warning: Could not open test_log.txt for writing.
");
        return NULL; // Skip this part of the test if file cannot be opened.
    }

    set_log_output(log_file); // Redirect output

    log_info("This message should go to the file.");

    set_log_output(stdout); // Reset output to stdout
    fclose(log_file);
    remove("test_log.txt"); // Clean up the test file

    return NULL;
}

// Minunit runner for logger tests
char *(*all_tests[])() = {
    test_logger_levels,
    test_logger_custom_output,
    NULL
};

int main() {
    return run_all_tests(all_tests);
}
