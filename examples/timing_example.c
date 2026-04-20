#include <stdio.h>
#include <stdlib.h>
#include <time.h> // For basic time operations if needed for comparison
#include <unistd.h> // For sleep()

#include "timing.h"
#include "minunit.h"

/* --- Timing Example --- */

// This example demonstrates the timing utility.
// It shows how to start, stop, and get elapsed time.

char *test_timing_basic() {
    timing_t *t = timing_create();
    mu_assert("timing_create failed", t != NULL);

    // Start the timer
    mu_assert("timing_start failed", timing_start(t) == SUCCESS);

    // Simulate some work (e.g., sleeping for a short duration)
    printf("Timing: Sleeping for 100ms...
");
    // Note: sleep() takes seconds, usleep() takes microseconds.
    // For more precise timing, one might need to use platform-specific functions or a library like `nanosleep`.
    // Assuming timing_stop will measure the actual elapsed time.
    usleep(100 * 1000); // 100 milliseconds

    // Stop the timer
    mu_assert("timing_stop failed", timing_stop(t) == SUCCESS);

    // Get elapsed time
    double elapsed_ms = timing_elapsed_ms(t);
    double elapsed_s = timing_elapsed_s(t);

    printf("Timing: Elapsed time (ms): %.3f
", elapsed_ms);
    printf("Timing: Elapsed time (s): %.6f
", elapsed_s);

    // Assert that the elapsed time is reasonable (e.g., greater than 90ms and less than 200ms)
    mu_assert("Elapsed time (ms) is too short", elapsed_ms >= 90.0);
    mu_assert("Elapsed time (ms) is too long", elapsed_ms < 200.0); // Allows for some overhead

    mu_assert("Elapsed time (s) is too short", elapsed_s >= 0.09);
    mu_assert("Elapsed time (s) is too long", elapsed_s < 0.2);

    // Test resuming and stopping again
    printf("Timing: Restarting timer and sleeping for 50ms...
");
    mu_assert("timing_start failed (resume)", timing_start(t) == SUCCESS);
    usleep(50 * 1000);
    mu_assert("timing_stop failed (second stop)", timing_stop(t) == SUCCESS);

    double elapsed_total_ms = timing_elapsed_ms(t);
    printf("Timing: Total elapsed time after resume/stop (ms): %.3f
", elapsed_total_ms);
    // This should be roughly 100ms + 50ms = 150ms
    mu_assert("Total elapsed time after resume/stop is incorrect", elapsed_total_ms >= 140.0);
    mu_assert("Total elapsed time after resume/stop is too long", elapsed_total_ms < 250.0);

    timing_destroy(t); // Clean up
    return NULL;
}

char *test_timing_pause_resume() {
    timing_t *t = timing_create();
    mu_assert("timing_create failed", t != NULL);

    printf("Timing: Starting timer, sleeping 100ms, pausing...
");
    timing_start(t);
    usleep(100 * 1000);
    mu_assert("timing_pause failed", timing_pause(t) == SUCCESS);

    // Check elapsed time while paused (should be ~100ms)
    double elapsed_before_resume = timing_elapsed_ms(t);
    printf("Timing: Elapsed time while paused (ms): %.3f
", elapsed_before_resume);
    mu_assert("Elapsed time while paused is incorrect", elapsed_before_resume >= 90.0);
    mu_assert("Elapsed time while paused is too long", elapsed_before_resume < 200.0);

    // Sleep again while paused (should not increase elapsed time)
    printf("Timing: Sleeping another 50ms while paused (should not count)...
");
    usleep(50 * 1000);
    double elapsed_while_paused = timing_elapsed_ms(t);
    printf("Timing: Elapsed time after sleeping while paused (ms): %.3f
", elapsed_while_paused);
    mu_assert("Elapsed time changed while paused", elapsed_while_paused == elapsed_before_resume);

    // Resume and stop
    printf("Timing: Resuming timer, sleeping 50ms, stopping...
");
    mu_assert("timing_resume failed", timing_resume(t) == SUCCESS);
    usleep(50 * 1000);
    mu_assert("timing_stop failed (final stop)", timing_stop(t) == SUCCESS);

    double elapsed_total = timing_elapsed_ms(t);
    printf("Timing: Total elapsed time after resume/stop (ms): %.3f
", elapsed_total);
    // Total should be ~100ms (before pause) + ~50ms (after resume) = ~150ms
    mu_assert("Total elapsed time after resume/stop is incorrect", elapsed_total >= 140.0);
    mu_assert("Total elapsed time after resume/stop is too long", elapsed_total < 250.0);

    timing_destroy(t);
    return NULL;
}


// Minunit runner for timing tests
char *(*all_tests[])() = {
    test_timing_basic,
    test_timing_pause_resume,
    NULL
};

int main() {
    return run_all_tests(all_tests);
}
