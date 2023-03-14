#include "../../include/minishell.h"

void    help_handler(char **instruct, t_data *data)
{
    if (ft_cmp_builtin(instruct[0], "help", 4) == 0)
	{
        data->cmd_lst->is_builtin = true;
        ft_putstr_fd("Read the fu**ing manual\n", 0);
        ft_putstr_fd("man bash\n", 0);
        ft_putstr_fd("man 2 pipe\n", 0);
        ft_putstr_fd("man Yo-Yo Ma\n", 0);
    }
}

void    man_yoyo_ma(char **instruct, t_data *data)
{
    if (ft_cmp_builtin(instruct[0], "man" ,3) == 0 && ft_cmp_builtin(instruct[1], "yoyoma", 6) == 0)
	{
        data->cmd_lst->is_builtin = true;
        ft_putendl_fd("                                                   .~?Y5P57^.", 0);
        ft_putendl_fd("                                            .!G#&@@@@@@@&G!            :7PJ^", 0);
        ft_putendl_fd("                                           :G#&&&&&&&@@@@@@#^         ?P#@&#~", 0);
        ft_putendl_fd("                                           .?B&&##&&@@@@@@@@@~        :YP@&G7", 0);
        ft_putendl_fd("                                            .:!J5P#&@@@@@@@@@?    ~?7YYP#@&&#?", 0);
        ft_putendl_fd("                                            ..:~7J5B&@@@@&&@@.    G@#&@&&#?..", 0);
        ft_putendl_fd("                                           ...^~!7?P&@@&PP5&P:JBBG&@B&Y.", 0);
        ft_putendl_fd("                                           .:^77JYYYPPG5JG5P5B@&5GPP&5", 0);
        ft_putendl_fd("                                             .!!!JYY5PPGGGBGGBP~:^~7J.", 0);
        ft_putendl_fd("                                             .?7?:7YPGB####&@B~!~?JJJJ5GJ~.", 0);
        ft_putendl_fd("                                           .7&@P??7YGB&&&&@@#G###Y!JJ?75@@@&G?.", 0);
        ft_putendl_fd("                                       .?G#@@@@@BY5G&&&&#G&&B555PY7???7!Y@@@@@&!", 0);
        ft_putendl_fd("                                     :5&@@@@@@@@@@@@@@BJ7?B&@&@@@@G!!777!?B@@@@@J", 0);
        ft_putendl_fd("                                   :P&@@@@@@@@@@@@@@@@@&J5#&&@@@@@@&5?7!!~~?B@@@@Y", 0);
        ft_putendl_fd("                                .^Y&@@@@@@@@@@@@@@@@@@@&G#&#&@@@@@@@@@&#?!!~~?G@@@G.", 0);
        ft_putendl_fd("                             .!5&@@@@@@@@@@@@@@@@@@@@@&PB&&B@@@@@@@@@@@@@5!!!!!75#@&^", 0);
        ft_putendl_fd("                           :?#@@@@@@@@@@@@@@@@@@@@@&&GP#&@@&&#&@@@@@@@@@@@G777!!!!75&7", 0);
        ft_putendl_fd("                     .:!JG#@@@@@@@@@@@@@@#@@@@@@&PJ7!5#&@@@@PJJ?P@@@@@@@@@@&Y?7!!!~~Y@&?", 0);
        ft_putendl_fd("                    !J5G&@@@@@@@@@@@&PJ?: ^&@@#J^^^~P#&@@@&5?JJJ7J&@@@@@@@@G#GJ?!!!!P@@@Y", 0);
        ft_putendl_fd("                   7?^~7?5&@@@@@@&G?:      ^&Y!^^^!P#&@@@&Y?JJJ??7P#&@@@@@Y .JBPJ7!?@@@@@!", 0);
        ft_putendl_fd("                  .J~~?5PPG@@&5^..         .7~^^^!G#&@@@&Y?JYYY??JGGBB#&@Y    ^B&B#@@@@@@#", 0);
        ft_putendl_fd("                 :^^^~75Y5##Y:            .!~~~^7B&@@@@&5YYYYYYJ?PGGGBBB&P .    7#@@@@@@@?", 0);
        ft_putendl_fd("               .~!~!^J?J!~^.              ~~~~^7B#@@@@@G55555JJJPGGPPPPG&@7..::.  .!GBG5~", 0);
        ft_putendl_fd("             ..^?!Y7Y5J!                 .!!~~?B&@&&@@#GGPP55JYPBBGBGGPB@@#    .::  ^", 0);
        ft_putendl_fd("             .~?Y?J?J!~...               ~J: 7B&@&B@@&BBBGG5JJB#BGBBBBG&@@@P     ^.:^", 0);
        ft_putendl_fd("               ....:.:.  .............. ^Y7.?#&@&P@@&####BPYJBBBB###BB&@@@@@~    :~!.", 0);
        ft_putendl_fd("                                     ...:^~~7?Y575##GGBBBPPB#&BBGB#B#@@@@@@@#    77.", 0);
        ft_putendl_fd("                                         :YJY!?7JP5?????7JY55PBBGYB#@@@@@@@@@.  ~Y:", 0);
        ft_putendl_fd("                                        .?~Y#P55B&&&##BPBBBGGPGG##&&@@@@@@@@@&:.P~", 0);
        ft_putendl_fd("                                        ^!?BG5PPPB&&&BG5BBBBBBG&@@@@@@@@@@@@@@&PJ.", 0);
        ft_putendl_fd("                                     ^7~^~!7J5555PG&&J?GBBBBG5B@@@@@@@@@@@@@@@@&^", 0);
    }
}