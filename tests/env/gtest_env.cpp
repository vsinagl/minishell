#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <filesystem>
#include <ostream>

extern "C" {
	#include "../../libft/libft.h"
	#include "../../includes/minishell.h"
}

TEST(msh_env_list, env_add)
{
	t_env *head = NULL;
	int len = 6;

	env_add(&head, "test", "24");
	env_add(&head, "something", "32");
	env_add(&head, "neco", "84");
	env_add(&head, "neco2", "76");
	env_add(&head, "neco81", "81");
	env_add(&head, "neco71", "71");

	t_env *ptr = head;
	int calculated_len = 0;
	while(ptr != NULL)
	{
		calculated_len++;
		ptr = ptr->next;
	}
	EXPECT_EQ(len, calculated_len);
	env_free(head);

	//declaring test variables
	//test body
	/*
	testing::internal::CaptureStdout();
	msh_echo(5, argv);
	free(argv);
 	std::string function_output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(function_output, expected_result);
	*/
}

TEST(msh_env_list, env_print)
{
	std::string expected_result = "name: test1\nvalue: 1\nname: test2\nvalue: 2\nname: test3\nvalue: 3\nname: test4\nvalue: 4\nname: test5\nvalue: 5\n";
	t_env *head = NULL;

	env_add(&head, "test5", "5");
	env_add(&head, "test4", "4");
	env_add(&head, "test3", "3");
	env_add(&head, "test2", "2");
	env_add(&head, "test1", "1");
	testing::internal::CaptureStdout();
	env_print(head);
	std::string env_print_output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(expected_result, env_print_output);
	env_free(head);
}


TEST(msh_env_list, env_getvalue)
{
	std::string expected_result = "16";

	t_env *head = NULL;
	env_add(&head, "test", "24");
	env_add(&head, "something", "32");
	env_add(&head, "neco", "84");
	env_add(&head, "neco", "24");
	env_add(&head, "something", "32");
	env_add(&head, "neco", "16");


	std::string result = env_getvalue(head, (char *)"neco");
	char *result2;
	char *expected_result2;
	result2 = env_getvalue(head, (char *)"notexisting");
	expected_result2 = NULL;
	env_free(head);
	EXPECT_EQ(result, expected_result);
	EXPECT_EQ(result2, expected_result2);
}

TEST(msh_export, adding_variable_emptylist)
{
	char **argv;
	argv = ft_split("export test=30", ' ');
	t_env *env = NULL;
	//env_add(&env, "something", "32");
	std::string result_value = "30";

	msh_export(2, argv, &env);
	t_env *ptr;
	ptr = env;
	while (ptr != NULL)
	{
		printf("variable <%s> = <%s>\n", ptr->name, ptr->value);
		ptr = ptr->next;
	}
	std::string value = env_getvalue(env, (char *)"test");
	//printf("	TEST VALUE =======\nValue: %s\n", value);
	EXPECT_EQ(value, result_value);
	env_free(env);
}
