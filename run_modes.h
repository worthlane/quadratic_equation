/*! \file
* \brief contains funtions declaration, that needed for test mode
*/

#define TEST

static const char TEST_FILE[] = "test.txt";     ///< contains test file name

/************************************************************//**
 * @brief Runs tests from TEST_FILE
 ************************************************************/

void RunTest();

/************************************************************//**
 * @brief Prints help information about flags
 *
 * @param[in] FlagInfo list of information about flags
 *************************************************************/

void PrintHelp(struct FlagInfo* FlagInfo[]);

/************************************************************//**
 * @brief Runs program in solving mode
 *
 * @param[in] FlagInfo information about flags
 * @param[in] pointers mode of program
 * @return error from ErrorList
 ************************************************************/

ErrorList RunSolve(struct FlagInfo* FlagInfo[], struct ProgramCondition* pointers);

/************************************************************//**
 * @brief Runs one test and checks answers
 *
 * @param[in] a coefficient
 * @param[in] b coefficient
 * @param[in] c coefficient
 * @param[in] test test answers
 * @param[in] test_number test number
 *************************************************************/

void OneTest(const double a, const double b, const double c,
             const struct QuadSolutions* test, int* test_number);

/************************************************************//**
 * @brief Contains information about one flag
 ************************************************************/

struct FlagInfo
{
  const char* LONG_FLAG;                                    ///< long flag name
  const char* SHORT_FLAG;                                   ///< short flag name
  char* argument;                                           ///< space for flag argument
  ErrorList (*FlagFunc) (void* params);                     ///< function, that flag is doing
  const char* help_info;                                    ///< help info about this flag
};

/************************************************************//**
 * @brief Contains information about mode of program
 ************************************************************/

struct ProgramCondition
{
    int input_ptr;      ///< pointer to input mode
    int output_ptr;     ///< pointer to output mode
    int mode_ptr;       ///< pointer to mode
};

/************************************************************//**
 * @brief Stdin input flag function
 *
 * @param[in] params parameters storage
 * @return error from ErrorList (0 if no error)
 ************************************************************/

ErrorList StdinInput(void* params);

/************************************************************//**
 * @brief Flag function for input from file
 *
 * @param[in] params parameters storage
 * @return error from ErrorList (0 if no error)
 ************************************************************/

ErrorList FileInput(void* params);

/************************************************************//**
 * @brief Flag function for input from console
 *
 * @param[in] params parameters storage
 * @return error from ErrorList (0 if no error)
 ************************************************************/

ErrorList ConsoleInput(void* params);

/************************************************************//**
 * @brief Flag function for output to stdout
 *
 * @param[in] params parameters storage
 * @return error from ErrorList (0 if no error)
 ************************************************************/

ErrorList StdoutOutput(void* params);

/************************************************************//**
 * @brief Flag function for output to file
 *
 * @param[in] params parameters storage
 * @return error from ErrorList (0 if no error)
 ************************************************************/

ErrorList FileOutput(void* params);


static char STDIN_ARGUMENT[LEN]      = "";  ///< stdin input argument initialization

static char FILEINPUT_ARGUMENT[LEN]  = "";  ///< file input argument initialization

static char CONSOLE_ARGUMENT[LEN]    = "";  ///< console input argument initialization

static char STDOUT_ARGUMENT[LEN]     = "";  ///< stdout output argument initialization

static char FILEOUTPUT_ARGUMENT[LEN] = "";  ///< file output argument initialization

static char SOLVE_ARGUMENT[LEN]      = "";  ///< solve mode argument initialization

static char HELP_ARGUMENT[LEN]       = "";  ///< help mode argument initialization

#ifdef TEST
static char TEST_ARGUMENT[LEN]       = "";  ///< test mode argument initialization
#endif

///@brief stdin input flag info
static struct FlagInfo STD_INPUT     = {LONG_STDIN_FLAG,     SHORT_STDIN_FLAG,
                                        STDIN_ARGUMENT,      StdinInput,           STDIN_HELP};

///@brief file input flag info
static struct FlagInfo FILE_INPUT    = {LONG_FROMFILE_FLAG,  SHORT_FROMFILE_FLAG,
                                        FILEINPUT_ARGUMENT,  FileInput,            FROMFILE_HELP};

///@brief console input flag info
static struct FlagInfo CONSOLE_INPUT = {LONG_CONSOLE_FLAG,   SHORT_CONSOLE_FLAG,
                                        CONSOLE_ARGUMENT,    ConsoleInput,         CONSOLE_HELP};

///@brief stdout output flag info
static struct FlagInfo STD_OUTPUT    = {LONG_STDOUT_FLAG,    SHORT_STDOUT_FLAG,
                                        STDOUT_ARGUMENT,     StdoutOutput,         STDOUT_HELP};

///@brief file output flag info
static struct FlagInfo FILE_OUTPUT   = {LONG_TOFILE_FLAG,    SHORT_TOFILE_FLAG,
                                        FILEOUTPUT_ARGUMENT, FileOutput,           TOFILE_HELP};

///@brief solving mode flag info
static struct FlagInfo SOLVE_MODE    = {LONG_SOLVE_FLAG,    SHORT_SOLVE_FLAG,
                                        SOLVE_ARGUMENT,     nullptr,               SOLVE_HELP};

///@brief help mode flag info
static struct FlagInfo HELP_MODE     = {LONG_HELP_FLAG,     SHORT_HELP_FLAG,
                                        HELP_ARGUMENT,      nullptr,               HELP_HELP};
#ifdef TEST
static struct FlagInfo TEST_MODE     = {LONG_TEST_FLAG,     SHORT_TEST_FLAG,
                                        TEST_ARGUMENT,      nullptr,               nullptr};
static const int flag_amount = 8;
#else
static struct FlagInfo TEST_MODE     = {nullptr,            nullptr,
                                        nullptr,            nullptr,               nullptr};
static const int flag_amount = 7;
#endif

/************************************************************//**
 * @brief Enums flags
 ************************************************************/

enum Flags
{
    unknown_flag       = -1,        ///< unknown flag

    stdin_flag         =  0,        ///< stdin input flag
    file_input_flag    =  1,        ///< file input flag
    console_input_flag =  2,        ///< console input flag

    stdout_flag        =  3,        ///< stdout output flag
    file_output_flag   =  4,        ///< file output flag

    solve_flag         =  5,        ///< solve mode flag
    help_flag          =  6,        ///< help mode flag
    #ifdef TEST
    test_flag          =  7         ///< test mode flag
    #endif
};

static struct FlagInfo* FlagList[] = {&STD_INPUT,   &FILE_INPUT, &CONSOLE_INPUT, &STD_OUTPUT,
                                      &FILE_OUTPUT, &SOLVE_MODE, &HELP_MODE,     &TEST_MODE};

/************************************************************//**
 * @brief Gets flags from console
 *
 * @param[in] argc amount of console arguments
 * @param[in] argv console arguments
 * @param[out] FlagInfo info about flags + place for argument
 * @param[out] pointers container of program working mode
 *************************************************************/

void FlagParse(const int argc, const char* argv[], struct FlagInfo* FlagInfo[],
               struct ProgramCondition* pointers);

/************************************************************//**
 * @brief Compares command line argument with long flag list
 *
 * @param[in] argc amount of console arguments
 * @param[in] argv console argument
 * @param[in] FlagInfo list with info about flags
 * @param[in] pointers pointers to program mode
 * @param[in] i pointer to console argument
 ************************************************************/

void LongFlagCheck(const int argc, const char* argv[], struct FlagInfo* FlagInfo[],
                   struct ProgramCondition* pointers, int* i);

/************************************************************//**
 * @brief Compares command line argument with short flag list
 *
 * @param[in] argc amount of console arguments
 * @param[in] argv console argument
 * @param[in] FlagInfo list with info about flags
 * @param[in] pointers pointers to program mode
 * @param[in] i pointer to console argument
 ************************************************************/

void ShortFlagCheck(const int argc, const char* argv[], struct FlagInfo* FlagInfo[],
                   struct ProgramCondition* pointers, int* i);

/************************************************************//**
 * @brief Reads flag argument from console
 *
 * @param[in] argc amount of console arguments
 * @param[in] argv console argument
 * @param[in] FlagInfo list with info about flags
 * @param[in] i pointer to console argument
 ************************************************************/

void ReadArgument(const int argc, const char* argv[], struct FlagInfo* FlagInfo[], int* i, int flag_ptr);

/************************************************************//**
 * @brief Calls for menu
 *
 * @param[out] pointers pointers to program mode
 * @return true if user wants to continue
 * @return false if user want to quit
 ************************************************************/

bool Menu(struct ProgramCondition* pointers);

/************************************************************//**
 * @brief Defines flag from flag list
 *
 * @param[in] flag_name name of flag
 * @param[in] FlagInfo list with info about flags
 * @return enumerated flag number
 ************************************************************/

int FindFlag(const char* flag_name, struct FlagInfo* FlagInfo[]);

/************************************************************//**
 * @brief Makes one big string from three strings
 *
 * @param[in] string1 first string
 * @param[in] string2 second string
 * @param[in] string3 third string
 * @param[out] outstring string1 + string2 + string3
 ************************************************************/

inline ErrorList TripleString(char* string1, char* string2, char* string3, char* outstring);

/************************************************************//**
 * @brief Skips line in file
 *
 * @param[in] fp file
 ************************************************************/

void SkipHeader(FILE* fp);
