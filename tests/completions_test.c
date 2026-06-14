#include <stdio.h>

#include "../src/minicli.h"

int dummy_callback(int argc, char** argv, void* user_data)
{
	(void) argc;
	(void) argv;
	(void) user_data;
	printf("Callback executed\n");
	return 0;
}

int main(int argc, char** argv)
{
	CliParser parser;
	CliInitParams params = {"test-app", "A test application"};
	cli_init(&parser, params);

	CliArgument arg1 = {
	    "--version", "-v", "Print version", dummy_callback, NULL};
	CliArgument arg2 = {
	    "--config", "-c", "Set config path", dummy_callback, NULL};
	cli_add_argument(&parser, arg1);
	cli_add_argument(&parser, arg2);

	cli_parse(&parser, argc, argv);

	cli_destroy(&parser);
	return 0;
}
