#include <stdio.h>
#include <stdlib.h>
#include <string.h> // For demonstration purposes, though not strictly needed by logger API itself

#include "../src/logger.h" // Include the logger header

/* --- Logger Example --- */
// This example demonstrates the usage of the logger library.
// It shows how to initialize the logger with different levels,
// log messages at various levels, and how filtering works.

int main()
{
	printf("--- Logger Example ---\n");

	// 1. Initialize logger to stderr with DEBUG level
	printf("Initializing logger to stderr with LOG_DEBUG level...\n");

	log_init(LOG_DEBUG, NULL); // NULL filepath means log only to stderr

	printf("Logging messages at LOG_DEBUG level:\n");

	LOG_DEBUG("This is a debug message.");
	LOG_INFO("This is an info message.");
	LOG_WARN("This is a warning message.");
	LOG_ERROR("This is an error message.");

	printf("----------------------\n");

	printf("Re-initializing logger to stderr with LOG_INFO level...\n");

	log_init(LOG_INFO, NULL); // Set level to INFO, debug messages should be
	                          // filtered out

	printf("Logging messages at LOG_INFO level (debug should be filtered):\n");
	LOG_DEBUG("This is a debug message (should NOT appear).");
	LOG_INFO("This is an info message.");
	LOG_WARN("This is a warning message.");
	LOG_ERROR("This is an error message.");

	printf("----------------------\n");

	const char* log_filepath = "logger_example.log";
	printf("Initializing logger to stderr AND file '%s' with LOG_WARN "
	       "level...\n",
	 log_filepath);

	log_init(LOG_WARN, log_filepath); // Set level to WARN, log to stderr and
	                                  // file
	printf("Logging messages at LOG_WARN level (debug, info should be "
	       "filtered):\n");

	LOG_DEBUG("This is a debug message (should NOT appear).");
	LOG_INFO("This is an info message (should NOT appear).");
	LOG_WARN("This is a warning message.");
	LOG_ERROR("This is an error message.");

	printf("----------------------\n");
	// Close the log file

	printf("Closing logger file...\n");
	log_close();

	printf("Logger file closed.\n");

	printf("\n--- Logger Example Finished ---\n");
	// Note: On successful run, logger_example.log should contain WARN and
	// ERROR messages.
	return 0;
}
