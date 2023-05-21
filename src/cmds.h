// Command list
// cmdList must have the exact same amount of entries as funcList!!!
#ifndef _Tobias_CMDS_
#define _Tobias_CMDS_

#define AMOUNT_OF_COMMANDS      20

char *cmdList[] = {
                   "help",
                   "zero",
                   "one",
                   "two",
                   "three",
                   "four",
                   "five",
                   "six",
                   "seven",
                   "turnredon",
                   "turnredoff",
                   "togglered",
                   "turnyellowon",
                   "turnyellowoff",
                   "toggleyellow",
                   "turngreenon",
                   "turngreenoff",
                   "togglegreen",
                   "exit",
                   "quit"
};

void (*funcList[])() = {
                        cli_help,
                        leds_zero,
                        leds_one,
                        leds_two,
                        leds_three,
                        leds_four,
                        leds_five,
                        leds_six,
                        leds_seven,
                        leds_onRed,
                        leds_offRed,
                        leds_toggleRed,
                        leds_onYellow,
                        leds_offYellow,
                        leds_toggleYellow,
                        leds_onGreen,
                        leds_offGreen,
                        leds_toggleGreen,
                        uart_end,
                        uart_end
};

#endif
