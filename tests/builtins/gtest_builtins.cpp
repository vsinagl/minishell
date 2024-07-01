#include <gtest/gtest.h>
#include <filesystem>
#include <ostream>

extern "C" {
	#include "../../libft/libft.h"
	#include "../../includes/minishell.h"
}


TEST(msh_echo, string_input)
{
	//expected result
	std::string expected_result = "Hello World From Echo\n";

	//creating argv argument
	char	**argv; 
	argv = ft_split("echo Hello World From Echo", ' ');

	//test body
	testing::internal::CaptureStdout();
	msh_echo(5, argv);
	free(argv);
 	std::string function_output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(function_output, expected_result);
}

TEST(msh_echo2, string_input_without_newline)
{
	//expected result
	std::string expected_result = "Hello World From Echo Again Without Newline";

	//creating argv argument
	char	**argv; 
	argv = ft_split("echo -n Hello World From Echo Again Without Newline", ' ');

	//test body
	testing::internal::CaptureStdout();
	msh_echo(9, argv);
	free(argv);
 	std::string function_output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(function_output, expected_result);
}

TEST(msh_echo3, string_with_dash)
{
	//expected result

	std::string expected_result = "n - should not be printed\n";
	std::string expected_result2 = "s something";

	//creating argv argument
	char	**argv; 
	char	**argv2;
	argv = ft_split("echo - n - should not be printed", ' ');
	argv2 = ft_split("echo -n - s something", ' ');

	//test body 1
	testing::internal::CaptureStdout();
	msh_echo(8, argv);
	free(argv);
 	std::string function_output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(function_output, expected_result);

	//test body 2
	testing::internal::CaptureStdout();
	msh_echo(5, argv2);
	free(argv2);
 	std::string function_output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(function_output2, expected_result2);
}

TEST(msh_pwd, get_actual_directory)
{
	std::string cwd_cpp = std::filesystem::current_path().string();
	testing::internal::CaptureStdout();
	msh_pwd();
	std::string msh_pwd_output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(msh_pwd_output, cwd_cpp);
}

TEST(msh_cd, change_to_upper_dirrectory)
{
	std::filesystem::path current_dir = std::filesystem::current_path();
	std::string upper_dir_path = current_dir.parent_path().string();

	//creating function arguments and obtaining results:
	char **argv = ft_split("cd ../", ' ');
	testing::internal::CaptureStdout();
	msh_cd(2, argv);
	std::string terminal_output = testing::internal::GetCapturedStdout();
	free(argv);
	//getting current workind directory after calling msh_cd
	std::string msh_cd_cwd = std::filesystem::current_path().string();
	EXPECT_EQ(msh_cd_cwd, upper_dir_path);
	EXPECT_EQ("", terminal_output);
}

TEST(msh_cd, change_to_sources)
{
	std::filesystem::path project_root = std::filesystem::current_path().parent_path().parent_path();
	std::string srcs_path = project_root.string() + "/srcs";

	//creating function arguments and obtaining results:
	char **argv = ft_split("cd ../../srcs/", ' ');
	msh_cd(2, argv);
	free(argv);
	//getting current workind directory after calling msh_cd
	std::string msh_cd_cwd = std::filesystem::current_path().string();
	EXPECT_EQ(msh_cd_cwd, srcs_path);
}

TEST(msh_cd, no_argument)
{
	std::string no_argument_result = "";
	std::string cwd = std::filesystem::current_path().string();
	//creating function arguments and obtaining results:
	char **argv = ft_split("cd ", ' ');
	testing::internal::CaptureStdout();
	msh_cd(1, argv);
	std::string terminal_output = testing::internal::GetCapturedStdout();
	free(argv);
	//getting current workind directory after calling msh_cd
	std::string msh_cd_cwd = std::filesystem::current_path().string();
	EXPECT_EQ(msh_cd_cwd, cwd);
	EXPECT_EQ(terminal_output, no_argument_result);

}

TEST(msh_cd, more_than_2_arguments)
{
	std::string more_than_2_stdout = "cd: string not in pwd: ../\n";
	std::string cwd = std::filesystem::current_path().string();
	//creating function arguments and obtaining results:
	char **argv = ft_split("cd ../ error", ' ');
	testing::internal::CaptureStdout();
	msh_cd(3, argv);
	std::string terminal_output = testing::internal::GetCapturedStdout();
	free(argv);
	//getting current workind directory after calling msh_cd
	std::string msh_cd_cwd = std::filesystem::current_path().string();
	EXPECT_EQ(msh_cd_cwd, cwd);
	EXPECT_EQ(terminal_output, more_than_2_stdout);
}

TEST(msh_cd, wrong_directory)
{
	std::string wrong_directory_stdout = "cd: no such file or directory: error\n";
	std::string cwd = std::filesystem::current_path().string();
	//creating function arguments and obtaining results:
	char **argv = ft_split("cd error", ' ');
	testing::internal::CaptureStdout();
	msh_cd(2, argv);
	std::string terminal_output = testing::internal::GetCapturedStdout();
	free(argv);
	//getting current workind directory after calling msh_cd
	std::string msh_cd_cwd = std::filesystem::current_path().string();
	EXPECT_EQ(msh_cd_cwd, cwd);
	EXPECT_EQ(terminal_output, wrong_directory_stdout);
}
