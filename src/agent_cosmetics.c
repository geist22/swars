/******************************************************************************/
// Syndicate Wars Port, source port of the classic strategy game from Bullfrog.
/******************************************************************************/
/** @file agent_cosmetics.c
 *     Ingame appearance of player agents loading from file.
 * @par Purpose:
 *     Implement functions for reading file with in-game appearance.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     20 May 2024 - 4 Jun 2024
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include "agent_cosmetics.h"

#include "bffile.h"
#include "bfini.h"
#include "bfmemory.h"
#include "swlog.h"
/******************************************************************************/

enum AgentCosmeticsAgentConfigCmd {
    ACAgentCmd_Agent1=1,
    ACAgentCmd_Agent2,
    ACAgentCmd_Agent3,
    ACAgentCmd_Agent4,
};

const struct TbNamedEnum agent_cosmetics_agent_cmnds[] = {
  {"Agent1",	ACAgentCmd_Agent1},
  {"Agent2",	ACAgentCmd_Agent2},
  {"Agent3",	ACAgentCmd_Agent3},
  {"Agent4",	ACAgentCmd_Agent4},
  {NULL,		0},
};

/* TODO find location where player zealot sprites are drawn
enum AgentCosmeticsZealotConfigCmd {
    ACZealotCmd_Zealot1 = 1,
    ACZealotCmd_Zealot2,
    ACZealotCmd_Zealot3,
    ACZealotCmd_Zealot4,
};

const struct TbNamedEnum agent_cosmetics_zealot_cmnds[] = {
  {"Zealot1",	ACZealotCmd_Zealot1},
  {"Zealot2",	ACZealotCmd_Zealot2},
  {"Zealot3",	ACZealotCmd_Zealot3},
  {"Zealot4",	ACZealotCmd_Zealot4},
  {NULL,		0},
};
*/

short PlayerAgentHeads[] = {0,0,0,0};

TbBool read_agent_cosmetics_file(void)
{
    TbFileHandle conf_fh;
    TbBool done;
    int i;
    long k;
    char *conf_buf;
    struct TbIniParser parser;
    //char locbuf[320];
    char conf_fname[80];
    int conf_len;

    sprintf(conf_fname, "%s" FS_SEP_STR "agent_cosmetics.ini", "conf");
    conf_fh = LbFileOpen(conf_fname, Lb_FILE_MODE_READ_ONLY);
    if (conf_fh != INVALID_FILE) {
        conf_len = LbFileLengthHandle(conf_fh);
        if (conf_len > 1024*1024)
            conf_len = 1024*1024;
        conf_buf = LbMemoryAlloc(conf_len+16);
        conf_len = LbFileRead(conf_fh, conf_buf, conf_len);
        LOGSYNC("Processing '%s' file, %d bytes", conf_fname, conf_len);
        LbFileClose(conf_fh);
    } else {
        LOGERR("Could not open '%s' file, agent appearance left at default.", conf_fname);
        conf_buf = LbMemoryAlloc(16);
        conf_len = 0;
    }
    conf_buf[conf_len] = '\0';
    LbIniParseStart(&parser, conf_buf, conf_len);
#define CONFWRNLOG(format,args...) LOGWARN("%s(line %lu): " format, conf_fname, parser.line_num, ## args)
#define CONFDBGLOG(format,args...) LOGDBG("%s(line %lu): " format, conf_fname, parser.line_num, ## args)

    // Parse the [EuroCorp] section of loaded file
    done = false;
    if (LbIniFindSection(&parser, "EuroCorp") != Lb_SUCCESS) {
        CONFWRNLOG("Could not find \"[%s]\" section.", "EuroCorp");
        done = true;
    }
#define COMMAND_TEXT(cmd_num) LbNamedEnumGetName(agent_cosmetics_agent_cmnds,cmd_num)
    while (!done)
    {
        int cmd_num;

        // Finding command number in this line
        i = 0;
        cmd_num = LbIniRecognizeKey(&parser, agent_cosmetics_agent_cmnds);
        // Now store the config item in correct place
        switch (cmd_num)
        {
        case ACAgentCmd_Agent1:
            i = LbIniValueGetLongInt(&parser, &k);
            if (i <= 0) {
                CONFWRNLOG("Could not read \"%s\" command parameter.", COMMAND_TEXT(cmd_num));
                break;
            }
	    if ((k >=0) && (k<= 3)) {
		PlayerAgentHeads[0] = k;
	    }
	    else {
		CONFWRNLOG("Invalid entry, appearance left at default.");
	    }
            CONFDBGLOG("%s %d", COMMAND_TEXT(cmd_num), (int)PlayerAgentHeads[0]);
            break;
        case ACAgentCmd_Agent2:
            i = LbIniValueGetLongInt(&parser, &k);
            if (i <= 0) {
                CONFWRNLOG("Could not read \"%s\" command parameter.", COMMAND_TEXT(cmd_num));
                break;
            }
	    if ((k >=0) && (k<= 3)) {
		PlayerAgentHeads[1] = k;
	    }
	    else {
		CONFWRNLOG("Invalid entry, appearance left at default.");
	    }
            CONFDBGLOG("%s %d", COMMAND_TEXT(cmd_num), (int)PlayerAgentHeads[1]);
            break;
		case ACAgentCmd_Agent3:
            i = LbIniValueGetLongInt(&parser, &k);
            if (i <= 0) {
                CONFWRNLOG("Could not read \"%s\" command parameter.", COMMAND_TEXT(cmd_num));
                break;
            }
	    if ((k >=0) && (k<= 3)) {
		PlayerAgentHeads[2] = k;
	    }
	    else {
		CONFWRNLOG("Invalid entry, appearance left at default.");
	    }
            CONFDBGLOG("%s %d", COMMAND_TEXT(cmd_num), (int)PlayerAgentHeads[2]);
            break;
        case ACAgentCmd_Agent4:
            i = LbIniValueGetLongInt(&parser, &k);
            if (i <= 0) {
                CONFWRNLOG("Could not read \"%s\" command parameter.", COMMAND_TEXT(cmd_num));
                break;
            }
	    if ((k >=0) && (k<= 3)) {
		PlayerAgentHeads[3] = k;
	    }
	    else {
		CONFWRNLOG("Invalid entry, appearance left at default.");
	    }
            CONFDBGLOG("%s %d", COMMAND_TEXT(cmd_num), (int)PlayerAgentHeads[3]);
            break;
        case 0: // comment
            break;
        case -1: // end of buffer
        case -3: // end of section
            done = true;
            break;
        default:
            CONFWRNLOG("Unrecognized command.");
            break;
        }
        LbIniSkipToNextLine(&parser);
    }
#undef COMMAND_TEXT

/* church section, disabled until a way to replace their sprites is found
    // Parse the [Church] section of loaded file
    done = false;
    if (LbIniFindSection(&parser, "Church") != Lb_SUCCESS) {
        CONFWRNLOG("Could not find \"[%s]\" section.", "Church");
        done = true;
    }
#define COMMAND_TEXT(cmd_num) LbNamedEnumGetName(agent_cosmetics_zealot_cmnds,cmd_num)
    while (!done)
    {
        int cmd_num;

        // Finding command number in this line
        i = 0;
        cmd_num = LbIniRecognizeKey(&parser, agent_cosmetics_zealot_cmnds);
        // Now store the config item in correct place
        switch (cmd_num)
        {
        case ACZealotCmd_Zealot1:
            i = LbIniValueGetLongInt(&parser, &k);
            if (i <= 0) {
                CONFWRNLOG("Could not read \"%s\" command parameter.", COMMAND_TEXT(cmd_num));
                break;
            }
            zealot1cosmetics = k;
            CONFDBGLOG("%s %d", COMMAND_TEXT(cmd_num), (int)zealot1cosmetics);
            break;
        case ACZealotCmd_Zealot2:
            i = LbIniValueGetLongInt(&parser, &k);
            if (i <= 0) {
                CONFWRNLOG("Could not read \"%s\" command parameter.", COMMAND_TEXT(cmd_num));
                break;
            }
            zealot2cosmetics = k;
            CONFDBGLOG("%s %d", COMMAND_TEXT(cmd_num), (int)zealot2cosmetics);
            break;
		case ACZealotCmd_Zealot3:
            i = LbIniValueGetLongInt(&parser, &k);
            if (i <= 0) {
                CONFWRNLOG("Could not read \"%s\" command parameter.", COMMAND_TEXT(cmd_num));
                break;
            }
            zealot3cosmetics = k;
            CONFDBGLOG("%s %d", COMMAND_TEXT(cmd_num), (int)zealot3cosmetics);
            break;
        case ACZealotCmd_Zealot4:
            i = LbIniValueGetLongInt(&parser, &k);
            if (i <= 0) {
                CONFWRNLOG("Could not read \"%s\" command parameter.", COMMAND_TEXT(cmd_num));
                break;
            }
            zealot4cosmetics = k;
            CONFDBGLOG("%s %d", COMMAND_TEXT(cmd_num), (int)zealot4cosmetics);
            break;
        case 0: // comment
            break;
        case -1: // end of buffer
        case -3: // end of section
            done = true;
            break;
        default:
            CONFWRNLOG("Unrecognized command.");
            break;
        }
        LbIniSkipToNextLine(&parser);
    }
#undef COMMAND_TEXT
*/

    LbIniParseEnd(&parser);
    LbMemoryFree(conf_buf);
    return true;
}
/******************************************************************************/
