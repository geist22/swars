/******************************************************************************/
// Syndicate Wars Port, source port of the classic strategy game from Bullfrog.
/******************************************************************************/
/** @file felogin.c
 *     Front-end desktop and menu system, login screen.
 * @par Purpose:
 *     Implement functions for login screen in front-end desktop.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     22 Apr 2023 - 22 Oct 2023
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include "felogin.h"

#include "bfkeybd.h"
#include "bftext.h"
#include "bfutility.h"
#include "guiboxes.h"
#include "campaign.h"
#include "display.h"
#include "feoptions.h"
#include "game.h"
#include "sound.h"
#include "util.h"
#include "swlog.h"
/******************************************************************************/
extern struct ScreenBox login_campaigns_box;
extern struct ScreenBox login_name_box;
extern struct ScreenButton login_continue_button;
extern struct ScreenButton login_abort_button;

ubyte ac_do_abort_2(ubyte click);
ubyte ac_do_login_2(ubyte click);
ubyte ac_show_campaigns_list(struct ScreenBox *box);
ubyte ac_show_login_name(struct ScreenBox *box);

ubyte do_login_2(ubyte click)
{
#if 0
    ubyte ret;
    asm volatile ("call ASM_do_login_2\n"
        : "=r" (ret) : "a" (click));
    return ret;
#else
    if (strlen(login_name) == 0)
        return 0;
    strtocapwords(login_name);

    read_user_settings();

    update_options_screen_state();

    if (in_network_game)
    {
        screentype = 7;
        game_system_screen = 3;
        reload_background_flag = 1;
        edit_flag = 0;
        return 1;
    }

    if ((ingame.Flags & GamF_Unkn0010) != 0)
    {
        sysmnu_button_enable(1,2);
        ingame.Flags &= ~GamF_Unkn0010;
    }

    campaign_new_game_prepare();

    if (new_mail)
        play_sample_using_heap(0, 119 + (LbRandomAnyShort() % 3), 127, 64, 100, 0, 3u);

    return 1;
#endif
}

ubyte do_abort_2(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_abort_2\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte show_campaigns_list(struct ScreenBox *box)
{
#if 0
    ubyte ret;
    asm volatile ("call ASM_show_campaigns_list\n"
        : "=r" (ret) : "a" (box));
    return ret;
#else
    int campgn, ncampgns;
    struct Campaign *p_campgn;
    const char *text;
    int campgn_height, line_height, nlines;
    int box_width, box_height;
    int cy;

    lbFontPtr = small_med_font;
    box_width = box->Width - 8;
    box_height = box->Height - 8;
    my_set_text_window(box->X + 4, box->Y + 4, box_width, box_height);
    byte_197160 = 4;
    ncampgns = selectable_campaigns_count();
    campgn_height = box_height / (ncampgns + 1);
    cy = box_height / (ncampgns + 1);
    line_height = font_height('A');
    lbDisplay.DrawColour = 87;

    for (campgn = 0; campgn < ncampgns; campgn++)
    {
        int hbeg;

        p_campgn = &campaigns[campgn];
        text = gui_strings[p_campgn->TextId];
        nlines = my_count_lines(text);
        if (background_type == campgn)
            lbDisplay.DrawFlags = 0x140;
        else
            lbDisplay.DrawFlags = 0x100;
        hbeg = cy - (4 * nlines - 4 + nlines * line_height) / 2;
        lbDisplay.DrawFlags |= 0x8000;
        text = gui_strings[642 + campgn];
        draw_text_purple_list2(0, hbeg, text, 0);
        lbDisplay.DrawFlags &= ~0x8000;
        cy += campgn_height;
    }

    cy = box_height / (ncampgns + 1);
    for (campgn = 0; campgn < ncampgns; campgn++)
    {
        int hbeg, hend;

        p_campgn = &campaigns[campgn];
        text = gui_strings[p_campgn->TextId];
        nlines = my_count_lines(text);
        hbeg = cy - (4 * nlines - 4 + nlines * line_height) / 2;
        hend = hbeg + (line_height + 4) * (nlines - 1) + line_height;
        if (lbDisplay.LeftButton)
        {
            short msy, msx;
            short y1, y2;
            msy = lbDisplay.ScreenMode == 1 ? 2 * lbDisplay.MouseY : lbDisplay.MouseY;
            msx = lbDisplay.ScreenMode == 1 ? 2 * lbDisplay.MouseX : lbDisplay.MouseX;

            y1 = text_window_y1 + hbeg;
            y2 = text_window_y1 + hend;
            if (in_box_coords(msx, msy, text_window_x1, y1, text_window_x2, y2))
            {
                lbDisplay.LeftButton = 0;
                background_type = campgn;
            }
        }
        cy += campgn_height;
    }
    return 0;
#endif
}

ubyte show_login_name(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_login_name\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

void show_login_screen(void)
{
    if ((game_projector_speed && (login_name_box.Flags & 0x01)) ||
      (lbKeyOn[KC_SPACE] && !edit_flag))
    {
        lbKeyOn[KC_SPACE] = 0;
        login_campaigns_box.Flags |= 0x0002;
        login_name_box.Flags |= 0x0002;
        login_abort_button.Flags |= 0x0002;
        login_continue_button.Flags |= 0x0002;
    }
    //login_name_box.DrawFn(&login_name_box); -- incompatible calling convention
    asm volatile ("call *%1\n"
        : : "a" (&login_name_box), "g" (login_name_box.DrawFn));
    //login_campaigns_box.DrawFn(&login_campaigns_box); -- incompatible calling convention
    asm volatile ("call *%1\n"
        : : "a" (&login_campaigns_box), "g" (login_campaigns_box.DrawFn));
    //login_continue_button.DrawFn(&login_continue_button); -- incompatible calling convention
    asm volatile ("call *%1\n"
        : : "a" (&login_continue_button), "g" (login_continue_button.DrawFn));
    //login_abort_button.DrawFn(&login_abort_button); -- incompatible calling convention
    asm volatile ("call *%1\n"
        : : "a" (&login_abort_button), "g" (login_abort_button.DrawFn));
}

void init_login_screen_boxes(void)
{
    init_screen_box(&login_campaigns_box, 219u, 159u, 200u, 100, 6);
    init_screen_box(&login_name_box, 150u, 128u, 337u, 22, 6);
    init_screen_button(&login_continue_button, 260u, 300u,
      gui_strings[455], 6, med2_font, 1, 0);
    init_screen_button(&login_abort_button, 260u, 329u,
      gui_strings[388], 6, med2_font, 1, 0);
    login_continue_button.X = 319 - (login_continue_button.Width >> 1);
    login_abort_button.X = 319 - (login_abort_button.Width >> 1);
    login_abort_button.Border = 3;
    login_continue_button.Border = 3;
    login_continue_button.AccelKey = 28;
    login_abort_button.AccelKey = 1;
    login_continue_button.CallBackFn = ac_do_login_2;
    login_abort_button.CallBackFn = ac_do_abort_2;
    login_campaigns_box.SpecialDrawFn = ac_show_campaigns_list;
    login_name_box.SpecialDrawFn = ac_show_login_name;
    lbFontPtr = med2_font;
    login_name_box.Width = my_string_width(gui_strings[454]) + 254;
    login_name_box.X = 319 - (login_name_box.Width >> 1);
}

void reset_login_screen_boxes_flags(void)
{
    login_name_box.Flags = 0x0001;
    login_campaigns_box.Flags = 0x0001;
}

void set_flag01_login_screen_boxes(void)
{
    login_continue_button.Flags |= 0x0001;
    login_abort_button.Flags |= 0x0001;
}

/******************************************************************************/