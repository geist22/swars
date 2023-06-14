#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "bfdata.h"
#include "bfsprite.h"
#include "bfscreen.h"
#include "bfkeybd.h"
#include "bfmouse.h"
#include "bftext.h"
#include "bfpalette.h"
#include "bfmemory.h"
#include "bfmemut.h"
#include "bffile.h"
#include "bfgentab.h"
#include "bfwindows.h"
#include "bfpng.h"
#include "bfutility.h"
#include "bfsvaribl.h"
#include "poly.h"
#include "svesa.h"
#include "swlog.h"
#include "bflib_fmvids.h"
#include "bflib_snd_sys.h"
#include "bflib_snd_cda.h"
#include "bflib_joyst.h"
#include "game_data.h"
#include "display.h"
#include "dos.h"
#include "game.h"
#include "keyboard.h"
#include "mouse.h"
#include "network.h"
#include "sound.h"
#include "unix.h"
#include "util.h"
#include "windows.h"
#include "command.h"
#include "research.h"
#include "thing.h"
#include "packet.h"
#include "player.h"

#include "timer.h"

#define SAVEGAME_PATH "qdata/savegame/"

#pragma pack(1)

struct UnkStruct7
{
  char field_0;
  char field_1;
  char field_2;
  char field_3;
  char field_4;
  char field_5;
  char field_6;
  char field_7;
  char field_8;
  char field_9;
  char field_A;
  char field_B;
  char field_C;
  char field_D;
  char field_E;
  char field_F;
};

struct Element;
struct Frame;

#pragma pack()

extern unsigned char *fade_data;
extern char *fadedat_fname;
extern char *pop_dat_fname_fmt;
extern char *pop_tab_fname_fmt;
extern unsigned long unkn_buffer_04;

extern ubyte *small_font_data;
extern ubyte *pointer_data;
extern struct TbSprite *pop1_sprites;
extern struct TbSprite *pop1_sprites_end;
extern ubyte *pop1_data;

extern struct TbSprite *unk2_sprites;
extern struct TbSprite *unk2_sprites_end;
extern ubyte *m_spr_data;
extern ubyte *m_spr_data_end;
extern struct TbSprite *m_sprites;
extern struct TbSprite *m_sprites_end;

extern struct Element *melement_ani;
extern struct Element *mele_ani_end;
extern ushort *nstart_ani;
extern ushort *nstart_ani_end;
extern struct Frame *frame;
extern struct Frame *frame_end;

extern struct MyMapElement *game_my_big_map;
extern struct SingleFloorTexture *game_textures;
extern struct SingleTexture *game_face_textures;
extern struct SinglePoint *game_object_points;
extern struct SingleObjectFace3 *game_object_faces;
extern struct SingleObject *game_objects;
extern struct QuickLight *game_quick_lights;
extern struct FullLight *game_full_lights;
extern struct Normal *game_normals;
extern struct SingleObjectFace4 *game_object_faces4;
extern struct AnimTmap *game_anim_tmaps;
extern struct TrafficNode *game_traffic_nodes;
extern struct LightCommand *game_light_commands;
extern struct ColVectList *game_col_vects_list;
extern struct ColVect *game_col_vects;
extern struct WalkHeader *game_walk_headers;
extern short *game_walk_items;
extern struct ColColumn *game_col_columns;
extern struct SingleObjectFace3 *game_special_object_faces;
extern struct SingleObjectFace4 *game_special_object_faces4;
extern struct FloorTile *game_floor_tiles;
extern struct Objective *game_used_objectives;
extern struct Objective *game_objectives;
extern ubyte *game_user_heap;
extern struct SpecialPoint *game_screen_point_pool;
extern struct DrawItem *game_draw_list;
extern struct SortSprite *game_sort_sprites;
extern struct SortLine *game_sort_lines;
extern struct Command *game_game_commands;
extern struct UnknBezEdit *bez_edit;
extern ubyte *spare_map_buffer;
extern struct Objective *game_used_lvl_objectives;
extern struct LevelMisc *game_level_miscs;

extern unsigned char *display_palette;
extern unsigned short unkn2_pos_x;
extern unsigned short unkn2_pos_y;
extern unsigned short unkn2_pos_z;
extern int data_1c8428;
extern const char *primvehobj_fname;
extern unsigned char textwalk_data[640];

extern PrimObjectPoint *prim_object_points;
extern PrimObjectFace *prim_object_faces;
extern PrimObjectFace4 *prim_object_faces4;
extern PrimObject *prim_objects;
extern Prim4Texture *prim4_textures;
extern PrimFaceTexture *prim_face_textures;

extern ushort prim_object_points_count;
extern ushort prim_object_faces_count;
extern ushort prim_object_faces4_count;
extern ushort prim_objects_count;
extern ushort prim4_textures_count;
extern ushort prim_face_textures_count;
extern ushort prim_unknprop01;
extern struct UnkStruct7 *game_panel;
extern struct UnkStruct7 game_panel_lo[];
extern struct UnkStruct7 unknstrct7_arr2[];

extern ubyte execute_commands;
extern long gamep_unknval_10;
extern long gamep_unknval_11;
extern long gamep_unknval_12;
extern long gamep_unknval_13;
extern long gamep_unknval_14;
extern long gamep_unknval_15;
extern long gamep_unknval_16;

extern ubyte player_unkn0C9[8];
extern char player_unknCC9[8][128];
extern long scanner_unkn370;
extern long scanner_unkn3CC;

extern ushort netgame_agent_pos_x[8][4];
extern ushort netgame_agent_pos_y[8][4];

extern long engn_xc;
extern long engn_yc;
extern long engn_zc;
extern ubyte byte_153198;

extern short brightness;
extern long game_speed;

struct TbLoadFiles unk02_load_files[] =
{
  { "*VESA",			(void **)&lbVesaData,		(void **)NULL,LB_VESA_DATA_SIZE, 1, 0 },
#if 1 // !defined(BFLIB_WSCREEN_CONTROL)
  { "*W_SCREEN",		(void **)&lbDisplay.WScreen,(void **)NULL,MAX_SUPPORTED_SCREEN_WIDTH*(MAX_SUPPORTED_SCREEN_HEIGHT+1), 0, 0 },
#endif
  { "data/pop2-1.dat",	(void **)&pop1_data,		(void **)NULL,			0, 0, 0 },
  { "data/pop2-1.tab",	(void **)&pop1_sprites,		(void **)&pop1_sprites_end, 0, 0, 0 },
  { "data/mspr-0.dat",	(void **)&m_spr_data,		(void **)&m_spr_data_end,0, 0, 0 },
  { "data/mspr-0.tab",	(void **)&m_sprites,		(void **)&m_sprites_end,0, 0, 0 },
  { "data/mele-0.ani",	(void **)&melement_ani,		(void **)&mele_ani_end,	0, 0, 0 },
  { "data/nsta-0.ani",	(void **)&nstart_ani,		(void **)&nstart_ani_end,0, 0, 0 },
  { "data/nfra-0.ani",	(void **)&frame,			(void **)&frame_end,	0, 0, 0 },
  { "data/font0-0.dat",	(void **)&small_font_data,	(void **)NULL,			0, 0, 0 },
  { "data/font0-0.tab",	(void **)&small_font,		(void **)&small_font_end, 0, 0, 0 },
  { "data/pointers.dat",(void **)&pointer_data,		(void **)NULL,			0, 0, 0 },
  { "data/pointers.tab",(void **)&pointer_sprites,	(void **)&pointer_sprites_end, 0, 0, 0 },
  { "qdata/pal.pal",	(void **)&display_palette,	(void **)NULL,			0, 0, 0 },
  { "",					(void **)NULL, 				(void **)NULL,			0, 0, 0 }
};

MemSystem mem_game[] = {
  { "my_big_map",		&game_my_big_map,		18u, 16513, 0, 0, 0 },
  { "textures",			&game_textures,			18u, 4512, 0, 0, 0 },
  { "face_textures",	&game_face_textures,	16u, 4000, 0, 0, 0 },
  { "object_points",	&game_object_points,	10u, 20000, 0, 0, 0 },
  { "object_faces",		&game_object_faces,		32u, 15000, 0, 0, 0 },
  { "objects",			&game_objects,			36u, 2000, 0, 0, 0 },
  { "quick_lights",		&game_quick_lights,		6u, 64000, 0, 0, 0 },
  { "full_lights",		&game_full_lights,		32u, 4000, 0, 0, 0 },
  { "normals",			&game_normals,			16u, 10000, 0, 0, 0 },
  { "object_faces4",	&game_object_faces4,	40u, 10000, 0, 0, 0 },
  { "anim_tmaps",		&game_anim_tmaps,		54u, 66, 0, 0, 0 },
  { "traffic_nodes",	&game_traffic_nodes,	36u, 500, 0, 0, 0 },
  { "light_commands",	&game_light_commands,	36u, 1000, 0, 0, 0 },
  { "col_vects_list",	&game_col_vects_list,	6u, 26000, 0, 0, 0 },
  { "col_vects",		&game_col_vects,		14u, 13000, 0, 0, 0 },
  { "walk_headers",		&game_walk_headers,		4u, 3000, 0, 0, 0 },
  { "walk_items",		&game_walk_items,		2u, 18000, 0, 0, 0 },
  { "col_columns",		&game_col_columns,		16u, 6000, 0, 0, 0 },
  { "prim4_textures",	&prim4_textures,		18u, 1200, 0, 0, 0 },
  { "prim_face_textures", &prim_face_textures,	16u, 500, 0, 0, 0 },
  { "prim_object_points", &prim_object_points,	10u, 2000, 0, 0, 0 },
  { "prim_object_faces", &prim_object_faces,	32u, 800, 0, 0, 0 },
  { "prim_object_faces4", &prim_object_faces4,	40u, 1300, 0, 0, 0 },
  { "prim_objects",		&prim_objects,			36u, 60, 0, 0, 0 },
  { "special_object_faces", &game_special_object_faces, 32u, 1400, 0, 0, 0 },
  { "special_object_faces4",&game_special_object_faces4, 40u, 1400, 0, 0, 0 },
  { "floor_tiles",		&game_floor_tiles,		39u, 18000, 0, 0, 0 },
  { "used_objectives",	&game_used_objectives,	32u, 1200, 0, 0, 0 },
  { "objectives",		&game_objectives,		32u, 1200, 0, 0, 0 },
  { "user_heap",		&game_user_heap,		1u, 292228, 0, 0, 0 },
  { "screen_point_pool",&game_screen_point_pool,8u, 45000, 0, 0, 0 },
  { "draw_list",		&game_draw_list,		5u, 45001, 0, 0, 0 },
  { "sort_sprites",		&game_sort_sprites,		16u, 4001, 0, 0, 0 },
  { "sort_lines",		&game_sort_lines,		11u, 4001, 0, 0, 0 },
  { "commands",			&game_commands,			32u, 1, 0, 0, 0 },
  { "bez edit",			&bez_edit,				28u, 2000, 0, 0, 0 },
  { "spare map buffer",	&spare_map_buffer,		1u, 101, 0, 0, 1 },
  { "used_lvl_objectives", &game_used_lvl_objectives,32u, 20, 0, 0, 0 },
  { "level_miscs",		&game_level_miscs,		22u, 200, 0, 0, 0 },
  { NULL,				NULL,					0u, 0, 0, 0, 0 }
};

extern TbFileHandle packet_rec_fh;

char unk_credits_text_s[] = "";
char unk_credits_text_z[] = "";
char unk_credits_text_p[] = "";

void PacketRecord_Close(void)
{
    if (in_network_game)
        return;
    LbFileClose(packet_rec_fh);
}

void PacketRecord_OpenWrite(void)
{
    asm volatile ("call ASM_PacketRecord_OpenWrite\n"
        :  :  : "eax" );
}

void debug_trace_place(int place)
{
    LOGDBG("reached place %d", place);
}

/** Decrease the size of some arrays to reduce memory usage.
 */
void adjust_memory_use(void)
{
    if (ingame.LowerMemoryUse == 1)
    {
        mem_game[35].N = 1; // bez_edit
        mem_game[28].N = 1; // objectives
        mem_game[36].N = 1; // spare_map_buffer
        mem_game[27].N = 1000; // used_objectives
        mem_game[26].N = 1124; // floor_tiles
        mem_game[31].N = 2500; // draw_list
        mem_game[32].N = 1000; // sort_sprites
        mem_game[33].N = 700; // sort_lines
        mem_game[30].N = 3000; // screen_point_pool
        if ( is_single_game || cmdln_param_bcg )
        {
            mem_game[20].N = 2000; // prim_object_points
            mem_game[21].N = 2000; // prim_object_faces increase(?)
            mem_game[22].N = 2000; // prim_object_faces4 increase(?)
        }
        mem_game[4].N = 11000; // object_faces
        mem_game[9].N = 11000; // object_faces4 increase(?)
        mem_game[5].N = 1500; // objects
        mem_game[7].N = 1000; // full_lights
        mem_game[13].N = 16000; // col_vects_list
        mem_game[14].N = 9000; // col_vects
        engine_mem_alloc_size = 2700000;
        game_perspective = (mem_game[5].N >> 8) & 0xff; // = 5
    }
}

bool game_initialise(void)
{
    TbResult ret;
    ret = LbBaseInitialise();
    if (ret != Lb_SUCCESS)
    {
        LOGERR("Bullfrog Library initialization failed");
        return false;
    }

#ifdef __unix__
    /* clean up after SDL messing around where it shouldn't */
    unix_restore_signal_handlers();
#endif

    LbSetUserResourceMapping(SWResourceMapping);
    LbSetTitle(PACKAGE_NAME);
    LbSetIcon(1);

    // Make sure file names are properly converted before opening
    setup_file_names();

    return true;
}

void
game_handle_sdl_events (void)
{
    TbBool contn;
    contn = LbWindowsControl();
    if (!contn) {
        game_quit();
    }
}

void *ASM_smack_malloc(int msize);
void ASM_smack_mfree(void *ptr);
void *(*smack_malloc)(int);
void (*smack_free)(void *);


void load_texturemaps(void)
{
    asm volatile ("call ASM_load_texturemaps\n"
        :  :  : "eax" );
}

void test_open(int num)
{
    // Empty for production version
}

void read_textwalk(void)
{
    TbFileHandle handle;
    handle = LbFileOpen("data/textwalk.dat", Lb_FILE_MODE_READ_ONLY);
    if ( handle != INVALID_FILE )
    {
        LbFileRead(handle, textwalk_data, 640);
        LbFileClose(handle);
    }
}

void read_primveh_obj(const char *fname, int a2)
{
    long firstval;
    TbFileHandle fh;

    fh = LbFileOpen(fname, Lb_FILE_MODE_READ_ONLY);
    if ( fh == INVALID_FILE )
        return;
    LbFileRead(fh, &firstval, sizeof(long));
    if ( firstval != 1 )
    {
      LbFileRead(fh, &prim_object_points_count, sizeof(ushort));
      LbFileRead(fh, &prim_object_faces_count, sizeof(ushort));
      LbFileRead(fh, &prim_object_faces4_count, sizeof(ushort));
      LbFileRead(fh, &prim_objects_count, sizeof(ushort));
      LbFileRead(fh, &prim4_textures_count, sizeof(ushort));
      LbFileRead(fh, &prim_face_textures_count, sizeof(ushort));
      LbFileRead(fh, &prim_unknprop01, sizeof(ushort));
      LbFileRead(fh, prim_object_points, sizeof(PrimObjectPoint) * prim_object_points_count);
      LbFileRead(fh, prim_object_faces, sizeof(PrimObjectFace) * prim_object_faces_count);
      LbFileRead(fh, prim_object_faces4, sizeof(PrimObjectFace4) * prim_object_faces4_count);
      LbFileRead(fh, prim_objects, sizeof(PrimObject) * prim_objects_count);
      LbFileRead(fh, prim4_textures, sizeof(Prim4Texture) * prim4_textures_count);
      LbFileRead(fh, prim_face_textures, sizeof(PrimFaceTexture) * prim_face_textures_count);
    }
    LbFileClose(fh);
}

void load_prim_quad(void)
{
    unkn2_pos_x = 64;
    unkn2_pos_y = 64;
    unkn2_pos_z = 64;
    data_1c8428 = 0;
    prim_unknprop01 = 1000;
    read_primveh_obj(primvehobj_fname, 1);
    read_textwalk();
    data_19ec6f = 1;
    ingame.DisplayMode = DpM_UNKN_37;
    if (cmdln_param_bcg == 99)
        test_open(99);
    if (cmdln_param_bcg == 100)
        test_open(100);
}

void game_setup_sub1(void)
{
    asm volatile ("call ASM_game_setup_sub1\n"
        :  :  : "eax" );
}

void init_arrays_1(void)
{
    asm volatile ("call ASM_init_arrays_1\n"
        :  :  : "eax" );
}

void bang_set_detail(int a1)
{
    asm volatile ("call ASM_bang_set_detail\n"
        : : "a" (a1));
}

void game_setup_sub3(void)
{
    asm volatile ("call ASM_game_setup_sub3\n"
        :  :  : "eax" );
}

/** Remains of some Bf debug stuff.
 */
void debug_trace_setup(int place)
{
    LOGDBG("reached place %d", place);
}

/** Remains of some Bf debug stuff.
 */
void debug_trace_turn_bound(ulong turn)
{
    LOGDBG("turn %lu", turn);
}

/** NOOP func which compiler merged from several functions.
 */
void merged_noop_unkn1(int a1)
{
}

void game_setup_stuff(void)
{
    asm volatile ("call ASM_game_setup_stuff\n"
        :  :  : "eax" );
}

void smack_malloc_free_all(void)
{
    smack_malloc_used_tot = 0;
}

void flic_unkn03(ubyte a1)
{
    asm volatile ("call ASM_flic_unkn03\n"
        : : "a" (a1));
}

void play_smacker(int vid_type)
{
    asm volatile ("call ASM_play_smacker\n"
        : : "a" (vid_type));
}

void play_intro(void)
{
    char fname[FILENAME_MAX];

    lbDisplay.LeftButton = 0;
    lbKeyOn[KC_ESCAPE] = 0;
    if ( (cmdln_param_bcg || is_single_game) && !(ingame.Flags & GamF_Unkn80000) )
    {
        setup_screen_mode(screen_mode_fmvid);
        LbMouseChangeSprite(NULL);
        if (game_dirs[DirPlace_Sound].use_cd == 1)
            sprintf(fname, "%slanguage/%s/intro.smk", cd_drive, language_3str);
        else
            sprintf(fname, "intro/intro.smk");
        play_smk(fname, 13, 0);
        LbMouseChangeSprite(&pointer_sprites[1]);
        smack_malloc_used_tot = 0;
    }
    if (cmdln_param_bcg)
        setup_screen_mode(screen_mode_menu);
    flic_unkn03(1u);
}

void replay_intro(void)
{
    char fname[FILENAME_MAX];
    TbScreenModeInfo *mdinfo;

    mdinfo = LbScreenGetModeInfo(screen_mode_fmvid);
    if (mdinfo->Width == 0) return;
    LbScreenSetup(screen_mode_fmvid, mdinfo->Width, mdinfo->Height, display_palette);
    LbMouseSetup(0, 2, 2);
    show_black_screen();
    stop_sample_using_heap(0, 122);
    stop_sample_using_heap(0, 122);
    if ( game_dirs[DirPlace_Sound].use_cd == 1 )
        sprintf(fname, "%slanguage/%s/intro.smk", cd_drive, language_3str);
    else
        sprintf(fname, "intro/intro.smk");
    play_smk(fname, 13, 0);
    smack_malloc_free_all();
    play_sample_using_heap(0, 122, 127, 64, 100, -1, 3);
    show_black_screen();
    play_sample_using_heap(0, 122, 127, 64, 100, -1, 3);
}

void reset_heaps(void)
{
}

size_t setup_heaps(int a1)
{
    size_t ret;
    asm volatile ("call ASM_setup_heaps\n"
        : "=r" (ret) : "a" (a1));
    return ret;
}

char func_cc638(const char *text, const char *fname)
{
    char ret;
    asm volatile ("call ASM_func_cc638\n"
        : "=r" (ret) : "a" (text), "d" (fname));
    return ret;
}

void screen_dark_curtain_down(void)
{
    asm volatile ("call ASM_screen_dark_curtain_down\n"
        :  :  : "eax" );
}

void load_outro_sprites(void)
{
    asm volatile ("call ASM_load_outro_sprites\n"
        :  :  : "eax" );
}

void fill_floor_textures(void)
{
    asm volatile ("call ASM_fill_floor_textures\n"
        :  :  : "eax" );
}

void load_mad_console(ushort mapno)
{
    asm volatile ("call ASM_load_mad_console\n"
        : : "a" (mapno));
}

void load_mad_0_console(ushort map, short level)
{
    asm volatile ("call ASM_load_mad_0_console\n"
        : : "a" (map), "d" (level));
}

TbBool is_unkn_current_player(void)
{
    TbBool ret;
    asm volatile ("call ASM_is_unkn_current_player\n"
        : "=r" (ret) : );
    return ret;
}

void change_current_map(ushort mapno)
{
    cmdln_param_current_map = mapno;
    init_things();
    load_mad_console(mapno);
    fill_floor_textures();
}

void change_brightness(ushort val)
{
    asm volatile ("call ASM_change_brightness\n"
        : : "a" (val));
}

void traffic_unkn_func_01(void)
{
    asm volatile ("call ASM_traffic_unkn_func_01\n"
        :  :  : "eax" );
}

void process_view_inputs(int thing)
{
    asm volatile ("call ASM_process_view_inputs\n"
        : : "a" (thing));
}

void process_engine_unk1(void)
{
    asm volatile ("call ASM_process_engine_unk1\n"
        :  :  : "eax" );
}

void process_engine_unk2(void)
{
    asm volatile ("call ASM_process_engine_unk2\n"
        :  :  : "eax" );
}

void draw_hud(int thing)
{
    asm volatile ("call ASM_draw_hud\n"
        : : "a" (thing));
}

void draw_new_panel(void)
{
    asm volatile ("call ASM_draw_new_panel\n"
        :  :  : "eax" );
}

void draw_screen(void)
{
    asm volatile ("call ASM_draw_screen\n"
        :  :  : "eax" );
}

void process_engine_unk3(void)
{
    asm volatile ("call ASM_process_engine_unk3\n"
        :  :  : "eax" );
}

void setup_engine_nullsub4(void)
{
}

void process_sound_heap(void)
{
    asm volatile ("call ASM_process_sound_heap\n"
        :  :  : "eax" );
}

void func_2e440(void)
{
    asm volatile ("call ASM_func_2e440\n"
        :  :  : "eax" );
}

void func_cc0d4(char **str)
{
    asm volatile ("call ASM_func_cc0d4\n"
        : : "a" (str));
}

void init_outro(void)
{
#if 0
    asm volatile ("call ASM_init_outro\n"
        : : );
    return;
#else
    TbClockMSec last_loop_time;
    const char *fname;
    const char *text;
    int fh;
    int i;

    gamep_unknval_01 = 0;
    StopAllSamples();
    StopCD();
    show_black_screen();
    swap_wscreen();
    setup_screen_mode(screen_mode_fmvid);
    LbMouseChangeSprite(0);
    lbKeyOn[KC_SPACE] = 0;
    lbKeyOn[KC_RETURN] = 0;
    lbKeyOn[KC_ESCAPE] = 0;
    if (background_type == 1)
        fname = "data/outro-z.smk";
    else
        fname = "data/outro-s.smk";
    play_smk(fname, 13, 0);
    data_155704 = -1;
    screen_buffer_fill_black();

    switch (background_type)
    {
    case 0:
    default:
        fname = "data/outro-s.raw";
        break;
    case 1:
        fname = "data/outro-z.raw";
        break;
    case 2:
        fname = "data/outro-p.raw";
        break;
    }
    fh = LbFileOpen(fname, Lb_FILE_MODE_READ_ONLY);
    if (fh != -1)
    {
        for (i = 24; i != 174; i++)
        {
            ubyte *buf;
            buf = &lbDisplay.WScreen[i*lbDisplay.GraphicsScreenWidth + 10];
            LbFileRead(fh, buf, 300);
        }
    }
    LbFileClose(fh);

    LbFileLoadAt("qdata/pal.pal", display_palette);
    LbScreenWaitVbi();
	game_hacky_update();

    {
        char str[FILENAME_MAX];
        sprintf(str, "qdata/pal%d.dat", 0);
        LbFileLoadAt(str, display_palette);
        LbPaletteSet(display_palette);
    }
    swap_wscreen();
    screen_dark_curtain_down();
    init_things();
    change_current_map(51);
    load_outro_sprites();

    switch (background_type)
    {
    case 0:
    default:
        text = unk_credits_text_s;
        fname = outro_text_s;
        break;
    case 1:
        text = unk_credits_text_z;
        fname = outro_text_z;
        break;
    case 2:
        text = unk_credits_text_p;
        fname = outro_text_z;
        break;
    }
    func_cc638(text, fname);

    // Sleep for up to 10 seconds
    last_loop_time = LbTimerClock();
    for (i = 10*GAME_FPS; i != 0; i--)
    {
        if ( lbKeyOn[KC_SPACE] )
          break;
        if ( lbKeyOn[KC_ESCAPE] )
          break;
        if ( lbKeyOn[KC_RETURN] )
          break;
        TbClockMSec sleep_end = last_loop_time + 1000/GAME_FPS;
        LbSleepUntil(sleep_end);
        last_loop_time = LbTimerClock();
    }
    lbKeyOn[KC_SPACE] = 0;
    lbKeyOn[KC_ESCAPE] = 0;
    lbKeyOn[KC_RETURN] = 0;

    LbPaletteFade(0, 0xC8u, 1);
    screen_buffer_fill_black();
    swap_wscreen();
    StopAllSamples();
    reset_heaps();
    setup_heaps(100);
    play_sample_using_heap(0, 1, 127, 64, 100, -1, 3u);

    data_197150 = 1;
    data_1dd91c = 0;
    unkn_flags_01 = 1;
    overall_scale = 40;
    palette_brightness = 0;
    change_brightness(-64);

    for (i = 0; i < 128; i++)
    {
        if (i & 1)
          change_brightness(1);
        traffic_unkn_func_01();
        process_engine_unk1();
        process_sound_heap();
        func_2e440();
        swap_wscreen();
        screen_buffer_fill_black();
    }

    while (1)
    {
        if ( lbKeyOn[KC_SPACE] )
          break;
        if ( lbKeyOn[KC_ESCAPE] )
          break;
        if ( lbKeyOn[KC_RETURN] )
          break;
        gameturn++;
        traffic_unkn_func_01();
        process_engine_unk1();
        if ( !(LbRandomAnyShort() & 0xF) && (data_155704 == -1 || !IsSamplePlaying(0, data_155704, NULL)) )
        {
            play_sample_using_heap(0, 7 + (LbRandomAnyShort() % 5), 127, 64, 100, 0, 3u);
        }
        process_sound_heap();
        func_2e440();
        if (outro_unkn01)
        {
            outro_unkn02++;
            func_cc0d4((char **)&people_credits_groups[2 * outro_unkn03]);
            if (data_1ddb68 + 50 < outro_unkn02)
            {
              outro_unkn02 = 0;
              if (++outro_unkn03 == people_groups_count)
                  outro_unkn03 = 0;
            }
          }
          swap_wscreen();
          screen_buffer_fill_black();
    }
    StopAllSamples();
    reset_heaps();
    setup_heaps(2);
#endif
}

int init_memory(MemSystem *a1)
{
    int ret;
    asm volatile ("call ASM_init_memory\n"
        : "=r" (ret) : "a" (a1));
    return ret;
}

int alt_at_point(ushort x, ushort z)
{
    int ret;
    asm volatile ("call ASM_alt_at_point\n"
        : "=r" (ret) : "a" (x), "d" (z));
    return ret;
}

void load_pop_sprites_lo(void)
{
    asm volatile ("call ASM_load_pop_sprites_lo\n"
        :  :  : "eax" );
}

void load_pop_sprites_hi(void)
{
    asm volatile ("call ASM_load_pop_sprites_hi\n"
        :  :  : "eax" );
}

void srm_scanner_set_size_at_bottom_left(int margin, int width, int height)
{
    int i;
    int cutout;

    cutout = 24;
    ingame.Scanner.X1 = 1;
    ingame.Scanner.Y1 = lbDisplay.GraphicsScreenHeight - margin - height;
    ingame.Scanner.X2 = ingame.Scanner.X1 + width;
    ingame.Scanner.Y2 = ingame.Scanner.Y1 + height;

    for (i = 0; i + ingame.Scanner.Y1 <= ingame.Scanner.Y2; i++) {
        ingame.Scanner.Width[i] = min(width - cutout + i, width);
    }
}

#define SCANNER_R0_WIDTH 64
#define SCANNER_R0_HEIGHT 62

#define SCANNER_R1_WIDTH 129
#define SCANNER_R1_HEIGHT 119

/**
 * Updates engine parameters for best display for current video mode within the tactical mission.
 */
void adjust_mission_engine_to_video_mode(void)
{
    int margin, width, height;

    game_high_resolution = (lbDisplay.ScreenMode == screen_mode_game_hi);
    if (lbDisplay.GraphicsScreenWidth >= 640)
    {
        overall_scale = 400;
        load_pop_sprites_hi();
        render_area_a = 30;
        render_area_b = 30;
    }
    else
    {
        overall_scale = 150;
        load_pop_sprites_lo();
        render_area_a = 24;
        render_area_b = 24;
    }
    width = lbDisplay.GraphicsScreenWidth * 20 / 100;
    height = lbDisplay.GraphicsScreenHeight * 25 / 100;
    if (lbDisplay.GraphicsScreenWidth >= 640) {
        margin = 20;
        width = width * 101 / 100;
        height = height * 99 / 100;
    } else {
        margin = 11;
        // width without change
        height = height * 124 / 100;
    }
    srm_scanner_set_size_at_bottom_left(margin, width, height);
}

void video_mode_switch_to_next(void)
{
    TbScreenMode nmode;

    if (lbDisplay.ScreenMode == screen_mode_game_lo)
        nmode = screen_mode_game_hi;
    else
        nmode = screen_mode_game_lo;

    StopCD();
    setup_screen_mode(nmode);
    adjust_mission_engine_to_video_mode();
}

void teleport_current_agent(PlayerInfo *p_locplayer)
{
    int dctrl_thing;
    dctrl_thing = p_locplayer->DirectControl[mouser];
    delete_node(&things[dctrl_thing]);
    things[dctrl_thing].X = mouse_map_x << 8;
    things[dctrl_thing].Z = mouse_map_z << 8;
    things[dctrl_thing].Y = alt_at_point(mouse_map_x, mouse_map_z);
    add_node_thing(dctrl_thing);
}

void person_resurrect(struct Thing *p_person)
{
    ulong person_anim;
    p_person->Flag &= ~0x0002;
    p_person->Flag &= ~0x02000000;
    p_person->State = 5;
    p_person->U.UPerson.AnimMode = 1;
    person_anim = people_frames[p_person->SubType][p_person->U.UPerson.AnimMode];
    p_person->StartFrame = person_anim - 1;
    p_person->Frame = nstart_ani[person_anim + p_person->U.UPerson.Angle];
}

void person_give_all_weapons(struct Thing *p_person)
{
    p_person->U.UPerson.WeaponsCarried = 0x3FFBDFFF;
    do_weapon_quantities1(p_person);
}

void person_give_best_mods(struct Thing *p_person)
{
    p_person->U.UPerson.UMod.Mods &= ~0x0007;
    p_person->U.UPerson.UMod.Mods |= 0x0003;
    p_person->U.UPerson.UMod.Mods &= ~0x0038;
    p_person->U.UPerson.UMod.Mods |= 0x0018;
    p_person->U.UPerson.UMod.Mods &= ~0x0E00;
    p_person->U.UPerson.UMod.Mods |= 0x0600;
    p_person->U.UPerson.UMod.Mods &= ~0x01C0;
    p_person->U.UPerson.UMod.Mods |= 0x00C0;
}

void beefup_all_agents(PlayerInfo *p_locplayer)
{
    int i;
    for (i = 0; i < playable_agents; i++)
    {
        struct Thing *p_agent;
        p_agent = p_locplayer->MyAgent[i];
        if (p_agent->Flag & 0x0002)
            person_resurrect(p_agent);
        person_give_all_weapons(p_agent);
        if (lbShift & KMod_SHIFT)
        {
            person_give_best_mods(p_agent);

            p_agent->Health = 32000;
            p_agent->U.UPerson.MaxHealth = 32000;
            p_agent->U.UPerson.Energy = 32000;
            p_agent->U.UPerson.MaxEnergy = 32000;
        }
    }
    research.WeaponsCompleted = 0x3FFFFFFF;
}

void game_graphics_inputs(void)
{
#if 0
    asm volatile ("call ASM_game_graphics_inputs\n"
        : : );
    return;
#else
    PlayerInfo *p_locplayer;

    p_locplayer = &players[local_player_no];
    if ((ingame.DisplayMode != DpM_UNKN_32) &&
        (ingame.DisplayMode != DpM_UNKN_3B))
        return;
    if (in_network_game && p_locplayer->PanelState[mouser] != 17)
        return;

    if (lbKeyOn[KC_F] && (lbShift == KMod_NONE))
    {
        lbKeyOn[KC_F] = 0;
        if (game_perspective == 5)
            game_perspective = 0;
        else
            game_perspective = 5;
    }

    if ((ingame.Cheats & 0x04) && lbKeyOn[KC_T] && (lbShift & KMod_ALT))
    {
        lbKeyOn[KC_T] = 0;
        teleport_current_agent(p_locplayer);
    }

    if ((ingame.Cheats & 0x04) && !in_network_game)
    {
        if (lbKeyOn[KC_Q] && (lbShift == KMod_SHIFT || lbShift == KMod_NONE))
        {
            lbKeyOn[KC_Q] = 0;
            beefup_all_agents(p_locplayer);
        }
    }

    if (lbKeyOn[KC_F8])
    {
        lbKeyOn[KC_F8] = 0;
        video_mode_switch_to_next();
    }
#endif
}

void init_syndwars(void)
{
#if 0
    asm volatile ("call ASM_init_syndwars\n"
        :  :  : "eax" );
#endif
    //char locstr[100];
    AudioInitOptions audOpts;

    //sprintf(locstr, "%sSound", cd_drive); -- unused
    sound_initialise();

    audOpts.SoundDataPath = "Sound";
    audOpts.SoundDriverPath = "Sound";
    audOpts.IniPath = "Sound";
    audOpts.AutoScan = 1;
    audOpts.StereoOption = 1;
    audOpts.DisableLoadSounds = 1;
    audOpts.InitRedbookAudio = 1;
    audOpts.UseCurrentAwe32Soundfont = 1;
    audOpts.AbleFlags = 3;
    audOpts.SoundType = 1622;
    audOpts.MaxSamples = 10;
    InitAudio(&audOpts);

    if (!GetCDAble())
        StopMusicIfActive();
    fill_ail_sample_ids();
    if (GetSoundInstalled() && GetSoundAble() && GetSoundActive())
        ingame.Flags |= 0x020000;
    setup_heaps(0);
}

void setup_host_sub6(void)
{
    asm volatile ("call ASM_setup_host_sub6\n"
        :  :  : "eax" );
}

void setup_debug_obj_trace(void)
{
    // Code for setting memory ranges was here
    // Removed, as we no longer have such tracking/profiling mechanism
    debug_trace_place(0);
}

void set_smack_malloc(void *(*cb)(int))
{
    smack_malloc = cb;
}

void set_smack_free(void (*cb)(void *ptr))
{
    smack_free = cb;
}

void BAT_unknsub_20(int a1, int a2, int a3, int a4, unsigned long a5)
{
    asm volatile (
      "push %4\n"
      "call ASM_BAT_unknsub_20\n"
        : : "a" (a1), "d" (a2), "b" (a3), "c" (a4), "g" (a5));
}

void setup_host(void)
{
    char fname[DISKPATH_SIZE];

    BAT_unknsub_20(0, 0, 0, 0, unkn_buffer_04 + 41024);
    set_smack_malloc(ASM_smack_malloc);
    set_smack_free(ASM_smack_mfree);
    LOGDBG("&setup_host() = 0x%lx", (ulong)setup_host);
    {
        TbScreenModeInfo *mdinfo;

        // TODO we could use more complex mode selection here
        lbDisplay.ScreenMode = screen_mode_game_lo;
        mdinfo = LbScreenGetModeInfo(lbDisplay.ScreenMode);
        LbScreenSetup(lbDisplay.ScreenMode, mdinfo->Width, mdinfo->Height, display_palette);
    }
    LbSpriteSetup(pointer_sprites, pointer_sprites_end, pointer_data);
    { // Make mouse pointer sprite 1 an empty (zero size) sprite
        struct TbSprite *spr;
        spr = &pointer_sprites[1];
        spr->SWidth = 0;
        spr->SHeight = 0;
    }
    if ( keyboard_mode_direct )
        LbKeyboardOpen();
    else
        LbIKeyboardOpen();
    init_buffered_keys();
    lbMouseAutoReset = false;
    LbMouseSetup(&pointer_sprites[1], 2, 2);

    setup_debug_obj_trace();
    LbSpriteSetup(m_sprites, m_sprites_end, m_spr_data);
    ingame.PanelPermutation = -2;
    {
        int file_len;
        sprintf(fname, pop_dat_fname_fmt, 1);
        LbFileLoadAt(fname, pop1_data);
        sprintf(fname, pop_tab_fname_fmt, -ingame.PanelPermutation - 1);
        file_len = LbFileLoadAt(fname, pop1_sprites);
        pop1_sprites_end = &pop1_sprites[file_len/sizeof(struct TbSprite)];
        LbSpriteSetup(pop1_sprites, pop1_sprites_end, pop1_data);
    }
    ingame.TrenchcoatPreference = 0;
    game_panel = game_panel_lo;
    LbGhostTableGenerate(display_palette, 50, "data/synghost.tab");
    init_memory(mem_game);

    init_syndwars();
    LoadSounds(0);
    LoadMusic(0);

    setup_host_sub6();
    if (pktrec_mode == PktR_RECORD)
    {
      if ( !in_network_game )
      {
          int file_no;
          file_no = get_new_packet_record_no(ingame.CurrentMission);
          get_packet_record_fname(fname, ingame.CurrentMission, file_no+1);
          LOGDBG("%s: Opening for packet save", fname);
          packet_rec_fh = LbFileOpen(fname, Lb_FILE_MODE_NEW);
          LbFileWrite(packet_rec_fh, &cmdln_param_current_map, 2);
      }
    }
    if (pktrec_mode == PktR_PLAYBACK)
    {
        ushort pktrec_head;
        get_packet_record_fname(fname, ingame.CurrentMission, cmdln_pr_num);
        LOGDBG("%s: Opening for packet input", fname);
        packet_rec_fh = LbFileOpen(fname, Lb_FILE_MODE_READ_ONLY);
        LbFileRead(packet_rec_fh, &pktrec_head, sizeof(pktrec_head));
    }
    play_intro();
    if ( cmdln_param_bcg )
    {
        TbScreenModeInfo *mdinfo;

        lbDisplay.ScreenMode = screen_mode_menu;
        mdinfo = LbScreenGetModeInfo(lbDisplay.ScreenMode);
        LbScreenSetup(lbDisplay.ScreenMode, mdinfo->Width, mdinfo->Height, display_palette);
    }
    LbMouseSetup(&pointer_sprites[1], 2, 2);
    if ( cmdln_param_bcg )
      LbMouseChangeSprite(NULL);
}

void read_user_settings(void)
{
    asm volatile ("call ASM_read_user_settings\n"
        :  :  : "eax" );
}

void setup_color_lookups(void)
{
    asm volatile ("call ASM_setup_color_lookups\n"
        :  :  : "eax" );
}

void game_setup_sub8(void)
{
    asm volatile ("call ASM_game_setup_sub8\n"
        :  :  : "eax" );
}

void load_missions(int num)
{
    asm volatile ("call ASM_load_missions\n"
        : : "a" (num));
}

void init_engine(void)
{
    asm volatile ("call ASM_init_engine\n"
        :  :  : "eax" );
}

void init_player(void)
{
    asm volatile ("call ASM_init_player\n"
        :  :  : "eax" );
}

ushort make_group_into_players(ushort group, ushort plyr, ushort max_agent, short new_type)
{
#if 0
    ushort ret;
    asm volatile ("call ASM_make_group_into_players\n"
        : "=r" (ret) : "a" (group), "d" (plyr), "b" (max_agent), "c" (new_type));
    return ret;
#endif
    ulong n, nframe;
    ushort nagents, high_tier;
    PlayerInfo *p_player;
    struct Thing *p_person;

    p_player = &players[plyr];
    p_person = NULL;
    nagents = 0;
    high_tier = 0;
    for (n = things_used_head; n != 0; n = p_person->LinkChild)
    {
        p_person = &things[n];
        if ((p_person->U.UPerson.Group != group) || (p_person->Type != TT_PERSON))
            continue;

        if (nagents > p_player->DoubleMode)
        {
            if (in_network_game && p_player->DoubleMode) {
                p_person->State = 13;
                p_person->Flag |= 0x2000002;
            }
            p_player->DirectControl[nagents] = 0;
        }
        else
        {
            p_player->DirectControl[nagents] = p_person->ThingOffset;
            p_person->Flag |= 0x1000;
            if ((plyr == local_player_no) && (nagents == 0)) {
                ingame.TrackX = p_person->X >> 8;
                ingame.TrackZ = p_person->Z >> 8;
            }
        }
        players[plyr].MyAgent[nagents] = p_person;
        p_person->Flag |= 0x2000;
        if ((p_person->SubType == SubTT_PERS_ZEALOT) && !cmdln_param_bcg)
            background_type = 1;
        if (in_network_game)
            set_person_stats_type(p_person, 1);

        if (ingame.GameMode != GamM_Unkn2)
        {
            if ((p_person->SubType == SubTT_PERS_AGENT) || (p_person->SubType == SubTT_PERS_ZEALOT))
            {
                p_person->U.UPerson.WeaponsCarried = p_player->Weapons[high_tier] | 0x400000;
                p_person->U.UPerson.UMod.Mods = p_player->Mods[high_tier].Mods;
            }
            p_person->U.UPerson.CurrentWeapon = 0;
        }

        if (game_commands[p_person->U.UPerson.ComHead].Type == PCmd_HARD_AS_AGENT)
        {
            set_person_stats_type(p_person, 1);
            p_person->U.UPerson.ComHead = game_commands[p_person->U.UPerson.ComHead].Next;
        }

        if (game_commands[p_person->U.UPerson.ComHead].Type == PCmd_90)
        {
            p_person->U.UPerson.Stamina = peep_type_stats[1].MaximumStamina;
            p_person->U.UPerson.MaxStamina = peep_type_stats[1].MaximumStamina;
            p_person->U.UPerson.ComCur = p_person->U.UPerson.ComHead;
            p_person->Flag |= 0x40;
        }

        if ((p_person->U.UPerson.ComHead != 0) &&
            (game_commands[p_person->U.UPerson.ComHead].Type == PCmd_EXECUTE_COMS))
        {
            p_person->Flag2 |= 0x0800;
            p_person->U.UPerson.ComCur = 4 * plyr + nagents;
            if (ingame.GameMode == GamM_Unkn3)
                do_weapon_quantities_proper1(p_person);
            else
                do_weapon_quantities1(p_person);
            p_person->Flag |= 0x40;
            p_person->U.UPerson.ComCur = p_person->U.UPerson.ComHead;
            ingame.Flags |= 0x0100;
        }
        else
        {
            p_person->U.UPerson.ComCur = 4 * plyr + nagents;
            p_person->U.UPerson.ComHead = 0;
            if (ingame.GameMode == GamM_Unkn3)
                do_weapon_quantities_proper1(p_person);
            else
                do_weapon_quantities1(p_person);
        }
        netgame_agent_pos_x[plyr][nagents] = p_person->X >> 8;
        netgame_agent_pos_y[plyr][nagents] = p_person->Z >> 8;
        p_person->State = 0;
        {
            ushort health;
            health = 3 * p_person->Health;
            p_person->Health = health;
            p_person->U.UPerson.MaxHealth = health;
        }

        switch (new_type)
        {
        case 0:
            p_person->SubType = SubTT_PERS_AGENT;
            nframe = people_frames[p_person->SubType][p_person->U.UPerson.AnimMode];
            p_person->StartFrame = nframe - 1;
            p_person->Frame = nstart_ani[nframe + p_person->U.UPerson.Angle];
            break;
        case 1:
            p_person->SubType = SubTT_PERS_ZEALOT;
            nframe = people_frames[p_person->SubType][p_person->U.UPerson.AnimMode];
            p_person->StartFrame = nframe - 1;
            p_person->Frame = nstart_ani[nframe + p_person->U.UPerson.Angle];
            break;
        case 2:
            p_person->SubType = SubTT_PERS_PUNK_M;
            nframe = people_frames[p_person->SubType][p_person->U.UPerson.AnimMode];
            p_person->StartFrame = nframe - 1;
            p_person->Frame = nstart_ani[nframe + p_person->U.UPerson.Angle];
            break;
        }
        p_person->U.UPerson.FrameId.Version[0] = 0;
        if (p_person->U.UPerson.CurrentWeapon == 0)
        {
            nframe = people_frames[p_person->SubType][p_person->U.UPerson.AnimMode];
            p_person->Frame -= nstart_ani[nframe + p_person->U.UPerson.Angle];
            p_person->U.UPerson.AnimMode = 0;
            nframe = people_frames[p_person->SubType][p_person->U.UPerson.AnimMode];
            p_person->Frame += nstart_ani[nframe + p_person->U.UPerson.Angle];
        }

        if ((p_person->SubType == SubTT_PERS_AGENT) || (p_person->SubType == SubTT_PERS_ZEALOT))
            high_tier++;

        if (++nagents == max_agent)
            break;
    }
    return nagents;
}

int place_default_player(ushort player_id, TbBool replace)
{
    int ret;
    asm volatile ("call ASM_place_default_player\n"
        : "=r" (ret) : "a" (player_id), "d" (replace));
    return ret;
}

void place_single_player(void)
{
#if 0
    asm volatile ("call ASM_place_single_player\n"
        :  :  : "eax" );
#endif
    PlayerInfo *p_locplayer;
    ulong n;
    ushort nagents, pl_agents, pl_group;

    p_locplayer = &players[local_player_no];

    // Figure out how many agents are attending the mission
    if (p_locplayer->DoubleMode)
        nagents = p_locplayer->DoubleMode + 1;
    else
        nagents = 4;
    if (p_locplayer->MissionAgents < (1 << nagents) - 1)
    {
        switch (p_locplayer->MissionAgents)
        {
        case 1:
            nagents = 1;
            break;
        case 3:
            nagents = 2;
            break;
        case 7:
            nagents = 3;
            break;
        }
    }

    pl_agents = make_group_into_players(level_def.PlayableGroups[0], local_player_no, nagents, -1);
    pl_group = level_def.PlayableGroups[0];

    n = things_used_head;
    while (n != 0)
    {
        struct Thing *p_thing;

        p_thing = &things[n];
        n = p_thing->LinkChild;
        if ((p_thing->U.UPerson.Group == pl_group) && (p_thing->Type == TT_PERSON) && !(p_thing->Flag & 0x2000))
        {
            remove_thing(p_thing->ThingOffset);
            delete_node(p_thing);
        }
    }
    playable_agents = pl_agents;
    if (pl_agents == 0)
      place_default_player(0, 1);
}

void init_game(ubyte reload)
{
#if 0
    asm volatile ("call ASM_init_game\n"
        : : "a" (reload));
#endif
    ushort mission_no, new_map_no;
    long new_level_no;

    mission_no = ingame.CurrentMission;
    new_map_no = mission_list[mission_no].MapNo;
    if (cmdln_param_current_map != new_map_no)
        change_current_map(new_map_no);
    debug_trace_setup(0);

    if ((reload) && (mission_list[mission_no].ReLevelNo != 0)) {
        new_level_no = mission_list[mission_no].ReLevelNo;
    } else {
        new_level_no = mission_list[mission_no].LevelNo;
    }

    load_mad_0_console(-new_level_no, mission_no);
    if (ingame.GameMode == GamM_None)
        ingame.GameMode = GamM_Unkn2;
    debug_trace_setup(1);
    init_player();
    debug_trace_setup(2);
    execute_commands = 1;
    ingame.DisplayMode = DpM_UNKN_32;
    debug_trace_setup(3);
}

void unkn_lights_func_11(void)
{
    asm volatile ("call ASM_unkn_lights_func_11\n"
        :  :  : "eax" );
}

void init_level_3d(ubyte flag)
{
    asm volatile ("call ASM_init_level_3d\n"
        : : "a" (flag));
}

short test_missions(ubyte flag)
{
    short ret;
    asm volatile ("call ASM_test_missions\n"
        : "=r" (ret) : "a" (flag));
    return ret;
}

ubyte show_settings_controls_list(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_settings_controls_list\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

char *gui_strings_data_end;

TbBool create_strings_list(char **strings, char *strings_data, char *strings_data_end)
{
  int text_idx;
  char *text_ptr;
  char **text_arr;
  text_arr = strings;
  text_idx = STRINGS_MAX;
  text_ptr = strings_data;
  while (text_idx >= 0)
  {
      if (text_ptr >= strings_data_end) {
          break;
      }
      *text_arr = text_ptr;
      text_arr++;
      char chr_prev;
      do {
          chr_prev = *text_ptr;
          text_ptr++;
      } while ((chr_prev != '\0') && (text_ptr < strings_data_end));
      text_idx--;
  }
  return (text_idx < STRINGS_MAX);
}

void create_tables_file_from_fade(void)
{
    long len;
    int i, k;
    unsigned char *curbuf;
    // Note that the input file is not normally available with the game
    len = LbFileLoadAt("data/fade.dat", fade_data);
    if (len == Lb_FAIL) {
        LOGERR("Cannot find input file for tables update");
        return;
    }
    curbuf = fade_data;
    for (i = 0; i < 256; i++) {
        for (k = 0; k < 64; k++) {
          pixmap.fade_table[256 * k + i] = *(curbuf + (256+64) * k + i);
        }
    }
    fade_data = curbuf;
    LbFileSaveAt("data/tables.dat", &pixmap, sizeof(pixmap));
}

/** Universal way to generate the colour tables.
 */
void create_tables_file_from_palette(void)
{
    LbColourTablesGenerate(display_palette, fade_unaffected_colours,
      "data/tables.dat");
}

void game_setup(void)
{
    engine_mem_alloc_ptr = LbMemoryAlloc(engine_mem_alloc_size);
    load_texturemaps();
    LbDataLoadAll(unk02_load_files);
    game_setup_sub1();
    init_arrays_1();
    bang_set_detail(0);
    game_setup_sub3();
    ingame.draw_unknprop_01 = 0;
    debug_trace_setup(-4);
    game_setup_stuff();
    create_strings_list(gui_strings, gui_strings_data, gui_strings_data_end);
    setup_host();
    read_user_settings();
    debug_trace_setup(-3);
    setup_color_lookups();
    init_things();
    debug_trace_setup(-2);
    LbSpriteSetup(small_font, small_font_end, small_font_data);
    game_setup_sub8();
    load_missions(0);
    players[local_player_no].MissionAgents = 0x0f;
    debug_trace_setup(-1);
    if ( is_single_game || cmdln_param_bcg )
    {
        load_prim_quad();
    }
    debug_trace_setup(0);
    init_engine();
    if ( !cmdln_param_bcg )
    {
        screen_buffer_fill_black();
        swap_wscreen();
        LbPaletteSet(display_palette);
    }
    test_open(15);
    debug_trace_setup(1);
    if (is_single_game && cmdln_param_current_map)
      init_game(0);
    if (in_network_game || cmdln_param_bcg)
      ingame.DisplayMode = DpM_UNKN_37;
    debug_trace_setup(2);
    switch (cmdln_colour_tables)
    {
    case 1:
        create_tables_file_from_palette();
        break;
    case 2:
        create_tables_file_from_fade();
        break;
    }
}

void game_process_sub01(void)
{
    unsigned long tick_time = clock();
    tick_time = tick_time / 100;
    curr_tick_time = tick_time;
    if (tick_time != prev_tick_time)
    {
        unsigned long tmp;
        tmp = gameturn - prev_gameturn;
        prev_gameturn = gameturn;
        turns_delta = tmp;
    }
    if ( turns_delta != 0 ) {
        fifties_per_gameturn = 800 / turns_delta;
    } else {
        fifties_per_gameturn = 50;
    }
    if ( in_network_game )
        fifties_per_gameturn = 80;
    if ( fifties_per_gameturn > 400 )
        fifties_per_gameturn = 400;
    prev_tick_time = curr_tick_time;
}

void game_process_sub08(void);

void game_process_sub09(void)
{
    int i;
    switch ( gamep_unknval_01 )
    {
    case 1:
        game_process_sub08();
        break;
    case 2:
        for (i = 0; i < 10; i++) {
            ushort pos;
            uint8_t *ptr;
            pos = LbRandomAnyShort() + (gameturn >> 2);
            ptr = &vec_tmap[pos];
            *ptr = pixmap.fade_table[40*PALETTE_8b_COLORS + *ptr];
        }
        break;
    }
}

void load_multicolor_sprites(void)
{
    ulong sz;
    char fname[100];

    sprintf(fname, "data/mspr-%d.dat", ingame.TrenchcoatPreference);
    LbFileLoadAt(fname, m_spr_data);
    sprintf(fname, "data/mspr-%d.tab", ingame.TrenchcoatPreference);
    sz = LbFileLoadAt(fname, m_sprites);
    m_sprites_end = (struct TbSprite *)((ubyte *)m_sprites + sz);
    LbSpriteSetup(m_sprites, m_sprites_end, m_spr_data);
    //unknown_unused(); -- nop function, not sure what was its purpose
}

int func_6edb8(ubyte a1)
{
    int ret;
    asm volatile ("call ASM_func_6edb8\n"
        : "=r" (ret) : "a" (a1));
    return ret;
}

void debug_m_sprite(int idx)
{
    int i;
    char strdata[100];
    char *str;
    struct TbSprite *spr;
    unsigned char *ptr;
    spr = &m_sprites[idx];
    str = strdata;
    sprintf(str, "spr %d width %d height %d ptr 0x%lx data",
      idx, (int)spr->SWidth, (int)spr->SHeight, (ulong)spr->Data);
    ptr = spr->Data;
    for (i = 0; i < 10; i++)
    {
        str = strdata + strlen(strdata);
        sprintf(str, " %02x", (int)*ptr);
        ptr++;
    }
    LOGDBG("m_sprites: %s", strdata);
}

void mapwho_unkn01(int a1, int a2)
{
    asm volatile ("call ASM_mapwho_unkn01\n"
        : : "a" (a1), "d" (a2));
}

void new_bang(int a1, int a2, int a3, int a4, int a5, int a6)
{
    asm volatile (
      "push %5\n"
      "push %4\n"
      "call ASM_new_bang\n"
        : : "a" (a1), "d" (a2), "b" (a3), "c" (a4), "g" (a5), "g" (a6));
}

void new_bang_3(int a1, int a2, int a3, int a4)
{
    new_bang(a1, a2, a3, a4, 0, 0);
}

void input(void)
{
    uint16_t n;
    n = lbShift;
    if ( lbKeyOn[KC_LSHIFT] || lbKeyOn[KC_RSHIFT] )
        n |= KMod_SHIFT;
    else
        n &= ~KMod_SHIFT;
    if ( lbKeyOn[KC_LCONTROL] || lbKeyOn[KC_RCONTROL] )
        n |= KMod_CONTROL;
    else
        n &= ~KMod_CONTROL;
    if ( lbKeyOn[KC_RALT] || lbKeyOn[KC_LALT] )
        n |= KMod_ALT;
    else
        n &= ~KMod_ALT;
    lbShift = n;
}

short PlayCDTrack(int a1)
{
    int ret;
    asm volatile ("call ASM_PlayCDTrack\n"
        : "=r" (ret) : "a" (a1));
    return ret;
}

void gproc3_unknsub3(int a1)
{
    // Empty
}

void ASM_show_game_engine(void);
void show_game_engine(void)
{
#if 0
    ASM_show_game_engine();
#endif
    int zoom;
    int dctrl_thing;

    dctrl_thing = players[local_player_no].DirectControl[0];
    process_view_inputs(dctrl_thing);// inlined call gengine_ctrl

    zoom = (900 - overall_scale) >> 1;
    if (zoom < 50)
        ingame.Scanner.Zoom = 50;
    else if (zoom > 556)
        ingame.Scanner.Zoom = 556;
    else
        ingame.Scanner.Zoom = zoom;
    process_engine_unk1();
    process_engine_unk2();
    process_engine_unk3();
    setup_engine_nullsub4();
}

void ASM_gproc3_unknsub2(void);
void gproc3_unknsub2(void)
{
    ASM_gproc3_unknsub2();
}

void ASM_BAT_play(void);
void BAT_play(void)
{
    ASM_BAT_play();
}

TbResult init_read_all_sprite_files(void)
{
    TbResult ret;
    asm volatile ("call ASM_init_read_all_sprite_files\n"
        : "=r" (ret) : );
    return ret;
}

#if 0
TbPixel LbPaletteFindColour(ubyte *pal, ubyte rval, ubyte gval, ubyte bval)
{
    TbResult ret;
    asm volatile ("call ASM_LbPaletteFindColour\n"
        : "=r" (ret) : "a" (pal), "d" (rval), "b" (gval), "c" (bval));
    return ret;
}
#endif

void init_screen_box(struct ScreenBox *box, ushort x, ushort y, ushort width, ushort height, int drawspeed)
{
    asm volatile (
      "push %5\n"
      "push %4\n"
      "call ASM_init_screen_box\n"
        : : "a" (box), "d" (x), "b" (y), "c" (width), "g" (height), "g" (drawspeed));
}

void init_screen_text_box(struct ScreenTextBox *box, ushort x, ushort y, ushort width, ushort height, int drawspeed, struct TbSprite *font, int textspeed)
{
    asm volatile (
      "push %7\n"
      "push %6\n"
      "push %5\n"
      "push %4\n"
      "call ASM_init_screen_text_box\n"
        : : "a" (box), "d" (x), "b" (y), "c" (width), "g" (height), "g" (drawspeed), "g" (font), "g" (textspeed));
}

void init_screen_button(struct ScreenButton *box, ushort x, ushort y, char *text, int drawspeed, struct TbSprite *font, int textspeed, int flags)
{
    asm volatile (
      "push %7\n"
      "push %6\n"
      "push %5\n"
      "push %4\n"
      "call ASM_init_screen_button\n"
        : : "a" (box), "d" (x), "b" (y), "c" (text), "g" (drawspeed), "g" (font), "g" (textspeed), "g" (flags));
}

void init_screen_info_box(struct ScreenInfoBox *box, ushort x, ushort y, ushort width, const char *text1, const char *text2, int drawspeed, struct TbSprite *font1, struct TbSprite *font2, int textspeed)
{
    asm volatile (
      "push %9\n"
      "push %8\n"
      "push %7\n"
      "push %6\n"
      "push %5\n"
      "push %4\n"
      "call ASM_init_screen_info_box\n"
        : : "a" (box), "d" (x), "b" (y), "c" (width), "g" (text1), "g" (text2), "g" (drawspeed), "g" (font1), "g" (font2), "g" (textspeed));
}

ubyte ASM_show_title_box(struct ScreenTextBox *box);
ubyte ASM_show_unkn38_box(struct ScreenTextBox *box);

ubyte ASM_select_all_agents(ubyte click);
ubyte ASM_do_net_protocol_option(ubyte click);
ubyte ASM_do_net_unkn40(ubyte click);
ubyte ASM_do_serial_speed_switch(ubyte click);
ubyte ASM_change_panel_permutation(ubyte click);
ubyte ASM_change_trenchcoat_preference(ubyte click);
ubyte ASM_do_unkn10_CALIBRATE(ubyte click);
ubyte ASM_do_unkn10_SAVE(ubyte click);
ubyte ASM_do_unkn10_CONTROLS(ubyte click);
ubyte ASM_alert_OK(ubyte click);
ubyte ASM_do_net_SET2(ubyte click);
ubyte ASM_do_net_SET(ubyte click);
ubyte ASM_do_net_INITIATE(ubyte click);
ubyte ASM_do_net_groups_LOGON(ubyte click);
ubyte ASM_do_unkn8_EJECT(ubyte click);
ubyte ASM_accept_mission(ubyte click);
ubyte ASM_do_unkn1_CANCEL(ubyte click);
ubyte ASM_do_unkn2_CANCEL(ubyte click);
ubyte ASM_do_unkn2_ACCEPT(ubyte click);
ubyte ASM_do_sysmnu_button(ubyte click);
ubyte ASM_do_storage_NEW_MORTAL(ubyte click);
ubyte ASM_load_game_slot(ubyte click);
ubyte ASM_save_game_slot(ubyte click);
ubyte ASM_main_do_my_quit(ubyte click);
ubyte ASM_main_do_login_1(ubyte click);
ubyte ASM_goto_savegame(ubyte click);
ubyte ASM_do_abort_2(ubyte click);
ubyte ASM_do_login_2(ubyte click);
ubyte ASM_main_do_map_editor(ubyte click);
ubyte ASM_brief_do_netscan_enhance(ubyte click);
ubyte ASM_do_unkn11_CANCEL(ubyte click);
ubyte ASM_do_buy_equip(ubyte click);
ubyte ASM_sell_equipment(ubyte click);
ubyte ASM_do_research_submit(ubyte click);
ubyte ASM_do_research_suspend(ubyte click);
ubyte ASM_do_unkn12_WEAPONS_MODS(ubyte click);

ubyte ASM_show_unkn32_box(struct ScreenBox *box);
ubyte ASM_show_unkn12(struct ScreenBox *box);
ubyte ASM_show_login_name(struct ScreenBox *box);
ubyte ASM_show_net_benefits_box(struct ScreenBox *box);
ubyte ASM_show_net_unkn21(struct ScreenBox *box);
ubyte ASM_show_net_comms_box(struct ScreenBox *box);
ubyte ASM_do_net_protocol_select(ubyte click);
ubyte ASM_show_net_protocol_box(struct ScreenBox *box);
ubyte ASM_show_net_faction_box(struct ScreenBox *box);
ubyte ASM_show_net_team_box(struct ScreenBox *box);
ubyte ASM_show_net_groups_box(struct ScreenBox *box);
ubyte ASM_show_net_users_box(struct ScreenBox *box);
ubyte ASM_show_mission_stats(struct ScreenBox *box);
ubyte ASM_show_unkn31_box(struct ScreenBox *box);
ubyte ASM_show_unkn20(struct ScreenBox *box);
ubyte ASM_show_unkn21_box(struct ScreenTextBox *box);
ubyte ASM_show_unkn04(struct ScreenBox *box);
ubyte ASM_show_unkn33_box(struct ScreenBox *box);
ubyte ASM_show_netgame_unkn1(struct ScreenBox *box);
ubyte ASM_show_menu_storage_unkn37_box(struct ScreenTextBox *box);
ubyte ASM_show_unkn29_box(struct ScreenBox *box);
ubyte ASM_display_weapon_info(struct ScreenTextBox *box);
ubyte ASM_show_weapon_name(struct ScreenTextBox *box);
ubyte ASM_show_weapon_list(struct ScreenTextBox *box);
ubyte ASM_show_weapon_slots(struct ScreenBox *box);
ubyte ASM_show_agent_list(struct ScreenTextBox *box);
ubyte ASM_show_blokey(struct ScreenBox *box);
ubyte ASM_show_unkn18_box(struct ScreenTextBox *box);
ubyte ASM_show_unkn36_box(struct ScreenTextBox *box);
ubyte ASM_show_unkn34_box(struct ScreenBox *box);
ubyte ASM_show_settings_controls_list(struct ScreenBox *box);


void init_screen_boxes(void)
{
    int i, w, h, val;
    const char *s;

    init_screen_text_box(&heading_box, 7u, 25u, 626u, 38, 6, big_font, 1);
    init_screen_text_box(&loading_INITIATING_box, 210u, 230u, 220u, 20, 6,
        med_font, 1);
    init_screen_box(&unkn32_box, 7u, 72u, 322u, 200, 6);
    init_screen_text_box(&unkn36_box, 7u, 281u, 322u, 145, 6, small_med_font,
        3);
    init_screen_text_box(&mission_text_box, 338u, 72u, 295u, 354, 6, small_font,
        3);
    init_screen_button(&unkn1_ACCEPT_button, 343u, 405u, gui_strings[436], 6,
        med2_font, 1, 0);
    init_screen_button(&unkn1_CANCEL_button, 616u, 405u, gui_strings[437], 6,
        med2_font, 1, 128);
    init_screen_button(&brief_NETSCAN_button, 312u, 405u, gui_strings[441], 6,
        med2_font, 1, 128);
    init_screen_info_box(&brief_NETSCAN_COST_box, 12u, 405u, 213u,
        gui_strings[442], unkn39_text, 6, med_font, small_med_font, 1);
    brief_NETSCAN_COST_box.Width = 312 - brief_NETSCAN_button.Width - 17;
    init_screen_box(&unkn30_box, 7u, 72u, 518u, 172, 6);
    init_screen_box(&unkn31_box, 7u, 253u, 518u, 173, 6);
    init_screen_box(&unkn29_box, 7u, 72u, 518u, 354, 6);
    init_screen_text_box(&unkn38_box, 534u, 72u, 99u, 354, 6, small_med_font,
        3);
    init_screen_button(&unkn2_ACCEPT_button, 548u, 384u, gui_strings[436], 6,
        med2_font, 1, 0);
    init_screen_button(&unkn2_CANCEL_button, 548u, 405u, gui_strings[437], 6,
        med2_font, 1, 0);
    init_screen_text_box(&unkn13_SYSTEM_button, 7u, 25u, 197u, 38, 6, big_font,
        1);
    init_screen_text_box(&unkn35_box, 213u, 25u, 420u, 38, 6, big_font, 1);
    init_screen_box(&unkn39_box, 213u, 72u, 420u, 354, 6);

    h = 72;
    for (i = 0; i < 3; i++)
    {
        init_screen_box(&unkn04_boxes[i], 213, h, 420, 62, 6);
        h += 71;
    }

    init_screen_box(&unkn33_box, 213u, 285u, 420u, 62, 6);
    init_screen_button(options_audio_buttons, 393u, 289u, gui_strings[531], 6,
        med2_font, 1, 0);
    init_screen_button(&options_audio_buttons[1], 458u, 289u, gui_strings[532],
        6, med2_font, 1, 0);
    init_screen_button(&options_audio_buttons[2], 523u, 289u, gui_strings[533],
        6, med2_font, 1, 0);
    init_screen_button(&options_audio_buttons[3], 458u, 307u, gui_strings[531],
        6, med2_font, 1, 0);
    init_screen_button(&options_audio_buttons[4], 523u, 307u, gui_strings[532],
        6, med2_font, 1, 0);
    init_screen_button(&options_audio_buttons[5], 458u, 325u, gui_strings[478],
        6, med2_font, 1, 0);
    init_screen_button(&options_audio_buttons[6], 523u, 325u, gui_strings[479],
        6, med2_font, 1, 0);

    val = 2;
    for (i = 0; i < 3; i++)
    {
        options_audio_buttons[i].Radio = &ingame.CDTrack;
        options_audio_buttons[i].RadioValue = val++;
        options_audio_buttons[i].Flags |= 0x0100;
    }

    val = 1;
    for (i = 3; i < 5; i++)
    {
        options_audio_buttons[i].Radio = &ingame.DangerTrack;
        options_audio_buttons[i].RadioValue = val++;
        options_audio_buttons[i].Flags |= 0x0100;
    }

    val = 0;
    for (i = 5; i < 7; i++)
    {
        options_audio_buttons[i].Radio = &ingame.UseMultiMedia;
        options_audio_buttons[i].RadioValue = val++;
        options_audio_buttons[i].Flags |= 0x0100;
    }

    init_screen_button(&options_gfx_buttons[0], 456u, 94u, gui_strings[465], 6,
        med2_font, 1, 0);
    init_screen_button(&options_gfx_buttons[1], 544u, 94u, gui_strings[466], 6,
        med2_font, 1, 0);
    init_screen_button(&options_gfx_buttons[2], 456u, 112u, gui_strings[473], 6,
        med2_font, 1, 0);
    init_screen_button(&options_gfx_buttons[3], 544u, 112u, gui_strings[474], 6,
        med2_font, 1, 0);
    init_screen_button(&options_gfx_buttons[4], 456u, 130u, gui_strings[475], 6,
        med2_font, 1, 0);
    init_screen_button(&options_gfx_buttons[5], 544u, 130u, gui_strings[477], 6,
        med2_font, 1, 0);
    init_screen_button(&options_gfx_buttons[6], 456u, 148u, gui_strings[478], 6,
        med2_font, 1, 0);
    init_screen_button(&options_gfx_buttons[7], 544u, 148u, gui_strings[479], 6,
        med2_font, 1, 0);
    init_screen_button(&options_gfx_buttons[8], 456u, 166u, gui_strings[478], 6,
        med2_font, 1, 0);
    init_screen_button(&options_gfx_buttons[9], 544u, 166u, gui_strings[479], 6,
        med2_font, 1, 0);
    init_screen_button(&options_gfx_buttons[10], 456u, 184u, gui_strings[478],
        6, med2_font, 1, 0);
    init_screen_button(&options_gfx_buttons[11], 544u, 184u, gui_strings[479],
        6, med2_font, 1, 0);
    init_screen_button(&options_gfx_buttons[12], 456u, 202u, gui_strings[478],
        6, med2_font, 1, 0);
    init_screen_button(&options_gfx_buttons[13], 544u, 202u, gui_strings[479],
        6, med2_font, 1, 0);

    val = abs(ingame.PanelPermutation);
    init_screen_button(&options_gfx_buttons[14], 320u, 274u,
        gui_strings[579 + val], 6, med2_font, 1, 0);

    val = ingame.TrenchcoatPreference;
    init_screen_button(&options_gfx_buttons[15], 320u, 310u,
        gui_strings[583 + val], 6, med2_font, 1, 0);

    options_gfx_buttons[14].CallBackFn = ASM_change_panel_permutation;
    options_gfx_buttons[15].CallBackFn = ASM_change_trenchcoat_preference;
    options_gfx_buttons[14].Width += 60;
    options_gfx_buttons[15].Width = options_gfx_buttons[14].Width;

    val = 0;
    for (i = 0; i < 2; i++)
    {
        options_gfx_buttons[i].Radio = &game_projector_speed;
        options_gfx_buttons[i].RadioValue = val;
        options_gfx_buttons[i].Flags |= 0x0100;
        val++;
    }

    val = 0;
    for (i = 2; i < 4; i++)
    {
        options_gfx_buttons[i].Radio = &game_high_resolution;
        options_gfx_buttons[i].RadioValue = val;
        options_gfx_buttons[i].Flags |= 0x0100;
        val++;
    }

    val = 0;
    for (i = 4; i < 6; i++)
    {
        options_gfx_buttons[i].Radio = &ingame.DetailLevel;
        options_gfx_buttons[i].RadioValue = val;
        options_gfx_buttons[i].Flags |= 0x0100;
        val++;
    }

    val = 0;
    for (i = 6; i < 8; i++)
    {
        options_gfx_buttons[i].Radio = &game_perspective;
        options_gfx_buttons[i].RadioValue = val;
        options_gfx_buttons[i].Flags |= 0x0100;
        val += 5;
    }

    val = 0;
    for (i = 8; i < 10; i++)
    {
        options_gfx_buttons[i].Radio = &unkn_gfx_option_2;
        options_gfx_buttons[i].RadioValue = val;
        options_gfx_buttons[i].Flags |= 0x0100;
        ingame.Flags |= 0x02;
        val++;
    }

    val = 0;
    for (i = 10; i < 12; i++)
    {
        options_gfx_buttons[i].Radio = &unkn_option_3;
        options_gfx_buttons[i].RadioValue = val;
        options_gfx_buttons[i].Flags |= 0x0100;
        ingame.Flags |= 0x01;
        val++;
    }

    val = 0;
    for (i = 12; i < 14; i++)
    {
        options_gfx_buttons[i].Radio = &unkn_option_4;
        options_gfx_buttons[i].RadioValue = val;
        options_gfx_buttons[i].Flags |= 0x0100;
        ingame.Flags &= ~0x0400;
        val++;
    }

    init_screen_text_box(&unkn37_box, 213u, 72u, 420u, 354, 6, med2_font, 1);

    val = 0;
    h = 72;
    for (i = 0; i < 6; i++)
    {
        init_screen_button(&sysmnu_buttons[i], 7, h, gui_strings[378 + val], 6,
            med2_font, 1, 0);
        sysmnu_buttons[i].Width = 197;
        sysmnu_buttons[i].Height = 21;
        sysmnu_buttons[i].CallBackFn = ASM_do_sysmnu_button;
        sysmnu_buttons[i].Flags |= 0x10;
        sysmnu_buttons[i].Border = 3;
        val++;
        h += 30;
    }

    init_screen_box(&unkn34_box, 7u, 252u, 197u, 174, 6);
    init_screen_button(&storage_LOAD_button, 219u, 405u, gui_strings[438], 6,
        med2_font, 1, 0);
    init_screen_button(&storage_SAVE_button, storage_LOAD_button.Width + 223,
        405u, gui_strings[439], 6, med2_font, 1, 0);
    init_screen_button(&storage_NEW_MORTAL_button, 627u, 405u, gui_strings[482],
        6, med2_font, 1, 128);
    init_screen_button(&net_INITIATE_button, 218u, 185u, gui_strings[385], 6,
        med2_font, 1, 0);
    init_screen_button(&net_groups_LOGON_button, 218u, 206u, gui_strings[386],
        6, med2_font, 1, 0);
    init_screen_button(&unkn8_EJECT_button, 308u, 206u, gui_strings[403], 6,
        med2_font, 1, 0);
    init_screen_button(&net_SET2_button, 562u, 251u, gui_strings[440], 6,
        med2_font, 1, 0);
    init_screen_button(&net_SET_button, 562u, 284u, gui_strings[440], 6,
        med2_font, 1, 0);
    init_screen_button(&net_protocol_select_button, 37u, 256u, gui_strings[498],
        6, med2_font, 1, 0);
    init_screen_button(&net_unkn40_button, 37u, 256u, net_unkn40_text, 6,
        med2_font, 1, 0);
    net_groups_LOGON_button.Width = 85;
    net_INITIATE_button.Width = 85;
    net_unkn40_button.Width = 21;
    net_protocol_select_button.Width = 157;
    init_screen_box(&net_groups_box, 213u, 72u, 171u, 155, 6);
    init_screen_box(&net_users_box, 393u, 72u, 240u, 155, 6);
    init_screen_box(&net_faction_box, 213u, 236u, 73u, 67, 6);
    init_screen_box(&net_team_box, 295u, 236u, 72u, 67, 6);
    init_screen_box(&net_benefits_box, 376u, 236u, 257u, 67, 6);
    init_screen_box(&net_comms_box, 295u, 312u, 336u, 104, 6);
    init_screen_box(&net_unkn21, 7u, 312u, 279u, 104, 6);
    init_screen_box(&net_protocol_box, 7u, 252u, 197u, 51, 6);
    init_screen_button(&net_protocol_option_button, 7u, 275u,
        unkn_opt_number_text, 6, med2_font, 1, 0);
    net_protocol_option_button.Width = net_protocol_select_button.Width;
    net_protocol_select_button.X = ((net_protocol_box.Width
        - net_protocol_select_button.Width) >> 1) + 7;
    net_protocol_option_button.X = ((net_protocol_box.Width
        - net_protocol_select_button.Width) >> 1) + 7;
    net_unkn40_button.X = net_protocol_select_button.Width
        + ((net_protocol_box.Width - net_protocol_select_button.Width) >> 1) + 7
        + 4;
    net_protocol_option_button.CallBackFn = ASM_do_net_protocol_option;
    init_screen_button(&unkn10_CALIBRATE_button, 219u, 405u, gui_strings[484],
        6, med2_font, 1, 0);
    init_screen_button(&unkn10_CONTROLS_button, 57u, 405u, gui_strings[485], 6,
        med2_font, 1, 0);
    init_screen_button(&unkn10_SAVE_button, 627u, 405u, gui_strings[439], 6,
        med2_font, 1, 128);
    init_screen_button(&main_map_editor_button, 260u, 387u, gui_strings[443], 6,
        med2_font, 1, 0);
    init_screen_button(&main_login_button, 260u, 300u, gui_strings[444], 6,
        med2_font, 1, 0);
    init_screen_button(&pause_continue_button, 260u, 300u, gui_strings[455], 6,
        med2_font, 1, 0);
    init_screen_button(&pause_abort_button, 260u, 329u, gui_strings[388], 6,
        med2_font, 1, 0);
    init_screen_button(&main_quit_button, 260u, 329u, gui_strings[445], 6,
        med2_font, 1, 0);
    init_screen_button(&main_load_button, 260u, 358u, gui_strings[496], 6,
        med2_font, 1, 0);
    init_screen_box(&pause_unkn11_box, 219u, 159u, 200u, 100, 6);
    init_screen_box(&pause_unkn12_box, 150u, 128u, 337u, 22, 6);
    init_screen_text_box(&slots_box, 7u, 122u, 191u, 22, 6, small_med_font, 1);
    init_screen_text_box(&equip_name_box, 425u, 122u, 208u, 22, 6,
        small_med_font, 1);
    init_screen_box(&weapon_slots, 7u, 153u, 191u, 272, 6);
    init_screen_text_box(&equip_list_box, 207u, 122u, 209u, 303, 6,
        small_med_font, 1);
    init_screen_text_box(&equip_display_box, 425u, 153u, 208u, 272, 6,
        small_font, 3);
    init_screen_button(&buy_equip_button, 430u, 404u, gui_strings[436], 6,
        med2_font, 1, 0);
    init_screen_button(&unkn11_CANCEL_button, 628u, 404u, gui_strings[437], 6,
        med2_font, 1, 128);
    init_screen_info_box(&equip_cost_box, 504u, 404u, 124u, gui_strings[442],
        misc_text[0], 6, med_font, small_med_font, 1);
    init_screen_text_box(&agent_list_box, 7u, 122u, 196u, 303, 6,
        small_med_font, 1);
    init_screen_text_box(&mod_list_box, 425u, 153u, 208u, 272, 6,
        small_med_font, 1);
    init_screen_box(&blokey_box, 212u, 122u, 203u, 303, 6);
    init_screen_button(&all_agents_button, 7u, 96u, gui_strings[534], 6,
        med2_font, 1, 0);
    all_agents_button.Width = 165;
    all_agents_button.RadioValue = 4;
    all_agents_button.Flags |= 0x0100;
    all_agents_button.Radio = &selected_agent;
    init_screen_box(&research_unkn20_box, 7u, 103u, 409u, 322, 6);
    init_screen_text_box(&research_progress_button, 7u, 72u, 409u, 23, 6,
        med_font, 1);
    init_screen_text_box(&research_unkn21_box, 425u, 72u, 208u, 353, 6,
        small_med_font, 3);
    init_screen_button(&research_submit_button, 430u, 302u, gui_strings[418], 6,
        med2_font, 1, 0);
    init_screen_button(&unkn12_WEAPONS_MODS_button, 616u, 302u,
        gui_strings[450], 6, med2_font, 1, 128);
    init_screen_button(research_list_buttons, 425u, 404u, gui_strings[478], 6,
        med2_font, 1, 0);
    init_screen_button(&research_list_buttons[1], 425u, 404u, gui_strings[479],
        6, med2_font, 1, 0);
    research_list_buttons[0].X = ((104 - research_list_buttons[0].Width) >> 1)
        + 425;
    research_list_buttons[1].X = ((104 - research_list_buttons[1].Width) >> 1)
        + 529;

    val = 0;
    for (i = 0; i < 2; i++)
    {
        research_list_buttons[i].Radio = &ingame.fld_unk7DE;
        research_list_buttons[i].RadioValue = val;
        research_list_buttons[i].Flags |= 0x0100;
        val++;
    }

    init_screen_box(&alert_box, 219u, 189u, 200u, 100, 6);
    init_screen_button(&alert_OK_button, 10u, 269u, gui_strings[458], 6,
        med2_font, 1, 0);
    heading_box.DrawTextFn = ASM_show_title_box;
    alert_OK_button.CallBackFn = ASM_alert_OK;
    loading_INITIATING_box.Text = gui_strings[376];
    heading_box.Text = options_title_text;
    lbFontPtr = med_font;
    alert_OK_button.X = 319 - (alert_OK_button.Width >> 1);
    loading_INITIATING_box.Height = font_height(0x41u) + 8;
    w = my_string_width(gui_strings[376]);
    unkn37_box.DrawTextFn = ASM_show_menu_storage_unkn37_box;
    unkn37_box.ScrollWindowHeight = 208;
    unkn37_box.Lines = 99;
    unkn34_box.SpecialDrawFn = ASM_show_unkn34_box;
    loading_INITIATING_box.Width = w + 9;
    unkn37_box.Flags |= 0x0300;
    unkn33_box.SpecialDrawFn = ASM_show_unkn33_box;
    mission_text_box.Buttons[0] = &unkn1_ACCEPT_button;
    mission_text_box.Buttons[1] = &unkn1_CANCEL_button;
    brief_NETSCAN_COST_box.Text2 = brief_netscan_cost_text;
    unkn37_box.BGColour = 26;
    mission_text_box.Flags |= 0x0300;
    unkn37_box.ScrollWindowOffset += 27;
    loading_INITIATING_box.X = 319 - ((w + 9) >> 1);
    unkn32_box.SpecialDrawFn = ASM_show_unkn32_box;
    loading_INITIATING_box.Y = 219 - (loading_INITIATING_box.Height >> 1);
    unkn04_boxes[0].SpecialDrawFn = ASM_show_unkn04;
    unkn04_boxes[1].SpecialDrawFn = ASM_show_unkn04;
    unkn04_boxes[2].SpecialDrawFn = ASM_show_unkn04;
    unkn31_box.SpecialDrawFn = ASM_show_unkn31_box;
    mission_text_box.Text = mission_briefing_text;
    unkn30_box.SpecialDrawFn = ASM_show_mission_stats;
    unkn36_box.Flags |= 0x0300;
    unkn36_box.DrawTextFn = ASM_show_unkn36_box;
    unkn2_ACCEPT_button.X = unkn38_box.X
        + ((unkn38_box.Width - unkn2_ACCEPT_button.Width) >> 1);
    unkn29_box.SpecialDrawFn = ASM_show_unkn29_box;
    unkn38_box.DrawTextFn = ASM_show_unkn38_box;
    slots_box.DrawTextFn = ASM_show_title_box;
    equip_display_box.DrawTextFn = ASM_display_weapon_info;
    equip_list_box.DrawTextFn = ASM_show_weapon_list;
    equip_cost_box.Text2 = equip_cost_text;
    research_unkn21_box.DrawTextFn = ASM_show_unkn21_box;
    unkn12_WEAPONS_MODS_button.CallBackFn = ASM_do_unkn12_WEAPONS_MODS;
    weapon_slots.SpecialDrawFn = ASM_show_weapon_slots;
    research_unkn21_box.ScrollWindowHeight = 180;
    research_unkn21_box.Buttons[0] = &research_submit_button;
    research_unkn21_box.Buttons[1] = &unkn12_WEAPONS_MODS_button;
    unkn2_CANCEL_button.X =
        ((unkn38_box.Width - unkn2_CANCEL_button.Width) >> 1) + unkn38_box.X;
    equip_name_box.DrawTextFn = ASM_show_weapon_name;
    unkn38_box.Flags |= 0x4000;
    slots_box.Text = gui_strings[408];
    slots_box.Font = med_font;
    equip_name_box.Text = unkn41_text;
    equip_list_box.ScrollWindowOffset += 27;
    equip_name_box.Font = med_font;
    research_unkn21_box.ScrollWindowOffset += 41;
    equip_display_box.Flags |= 0x0300;
    equip_display_box.ScrollWindowHeight = 117;
    equip_list_box.Flags |= 0x0300;
    research_submit_button.CallBackFn = ASM_do_research_submit;
    equip_list_box.BGColour = unk2_sprites[15].SHeight + 3;
    equip_list_box.ScrollWindowHeight -= 27;
    research_progress_button.DrawTextFn = ASM_show_title_box;
    research_submit_button.Text = gui_strings[417];
    research_progress_button.Text = gui_strings[449];
    research_unkn21_box.Flags |= 0x0300;
    unkn12_WEAPONS_MODS_button.Text = gui_strings[451];
    lbFontPtr = med2_font;
    research_unkn20_box.SpecialDrawFn = ASM_show_unkn20;

    if (my_string_width(gui_strings[418]) <= my_string_width(gui_strings[417]))
        s = gui_strings[417];
    else
        s = gui_strings[418];
    research_submit_button.Width = my_string_width(s) + 4;

    if (my_string_width(gui_strings[451]) <= my_string_width(gui_strings[450]))
        s = gui_strings[450];
    else
        s = gui_strings[451];
    unkn12_WEAPONS_MODS_button.Width = my_string_width(s) + 4;

    if (my_string_width(gui_strings[436]) <= my_string_width(gui_strings[407]))
        s = gui_strings[407];
    else
        s = gui_strings[436];
    buy_equip_button.Width = my_string_width(s) + 4;

    mod_list_box.DrawTextFn = ASM_show_unkn18_box;
    agent_list_box.BGColour = 25;
    net_groups_box.SpecialDrawFn = ASM_show_net_groups_box;
    net_users_box.SpecialDrawFn = ASM_show_net_users_box;
    equip_cost_box.X = buy_equip_button.Width + buy_equip_button.X + 4;
    net_INITIATE_button.CallBackFn = ASM_do_net_INITIATE;
    net_faction_box.SpecialDrawFn = ASM_show_net_faction_box;
    net_team_box.SpecialDrawFn = ASM_show_net_team_box;
    net_groups_box.Flags |= 0x0300;
    equip_cost_box.Width = 208 - buy_equip_button.Width - 14;
    agent_list_box.DrawTextFn = ASM_show_agent_list;
    net_benefits_box.SpecialDrawFn = ASM_show_net_benefits_box;
    net_unkn40_button.CallBackFn = ASM_do_net_unkn40;
    unkn1_ACCEPT_button.CallBackFn = ASM_accept_mission;
    mod_list_box.Flags |= 0x0300;
    net_SET_button.CallBackFn = ASM_do_net_SET;
    blokey_box.SpecialDrawFn = ASM_show_blokey;
    unkn8_EJECT_button.CallBackFn = ASM_do_unkn8_EJECT;
    unkn1_CANCEL_button.CallBackFn = ASM_do_unkn1_CANCEL;
    storage_SAVE_button.CallBackFn = ASM_save_game_slot;
    storage_NEW_MORTAL_button.CallBackFn = ASM_do_storage_NEW_MORTAL;
    mod_list_box.ScrollWindowHeight = 117;
    net_protocol_select_button.CallBackFn = ASM_do_net_protocol_select;
    unkn13_SYSTEM_button.Text = gui_strings[366];
    net_comms_box.SpecialDrawFn = ASM_show_net_comms_box;
    buy_equip_button.CallBackFn = ASM_do_buy_equip;
    storage_LOAD_button.CallBackFn = ASM_load_game_slot;
    net_users_box.Flags |= 0x0300;
    agent_list_box.ScrollWindowOffset += 27;
    net_groups_LOGON_button.CallBackFn = ASM_do_net_groups_LOGON;
    net_unkn21.SpecialDrawFn = ASM_show_net_unkn21;
    unkn2_CANCEL_button.CallBackFn = ASM_do_unkn2_CANCEL;
    unkn2_ACCEPT_button.CallBackFn = ASM_do_unkn2_ACCEPT;
    unkn11_CANCEL_button.CallBackFn = ASM_do_unkn11_CANCEL;
    unkn10_CALIBRATE_button.CallBackFn = ASM_do_unkn10_CALIBRATE;
    agent_list_box.Flags |= 0x0300;
    unkn10_CONTROLS_button.CallBackFn = ASM_do_unkn10_CONTROLS;
    main_map_editor_button.X = 319 - (main_map_editor_button.Width >> 1);
    unkn13_SYSTEM_button.DrawTextFn = ASM_show_title_box;
    unkn35_box.DrawTextFn = ASM_show_title_box;
    main_login_button.X = 319 - (main_login_button.Width >> 1);
    net_SET2_button.CallBackFn = ASM_do_net_SET2;
    pause_continue_button.X = 319 - (pause_continue_button.Width >> 1);
    agent_list_box.ScrollWindowHeight -= 27;
    net_protocol_box.SpecialDrawFn = ASM_show_net_protocol_box;
    pause_abort_button.X = 319 - (pause_abort_button.Width >> 1);
    brief_NETSCAN_button.CallBackFn = ASM_brief_do_netscan_enhance;
    main_quit_button.X = 319 - (main_quit_button.Width >> 1);
    unkn10_SAVE_button.CallBackFn = ASM_do_unkn10_SAVE;
    main_load_button.X = 319 - (main_load_button.Width >> 1);
    main_map_editor_button.Border = 3;
    pause_abort_button.Border = 3;
    pause_continue_button.Border = 3;
    main_login_button.Border = 3;
    main_quit_button.Border = 3;
    main_load_button.Border = 3;
    main_map_editor_button.CallBackFn = ASM_main_do_map_editor;
    main_login_button.CallBackFn = ASM_main_do_login_1;
    main_quit_button.CallBackFn = ASM_main_do_my_quit;
    pause_unkn11_box.SpecialDrawFn = ASM_show_unkn12;
    pause_unkn12_box.SpecialDrawFn = ASM_show_login_name;
    pause_continue_button.CallBackFn = ASM_do_login_2;
    main_load_button.CallBackFn = ASM_goto_savegame;
    pause_abort_button.CallBackFn = ASM_do_abort_2;
    pause_unkn12_box.Width = my_string_width(gui_strings[454]) + 254;
    pause_continue_button.AccelKey = 28;
    main_login_button.AccelKey = 28;
    alert_OK_button.AccelKey = 28;
    pause_unkn12_box.X = 319 - (pause_unkn12_box.Width >> 1);
    pause_abort_button.AccelKey = 1;
    main_quit_button.AccelKey = 1;
}

void update_menus(void)
{
    asm volatile ("call ASM_update_menus\n"
        :  :  : "eax" );
}

void load_city_txt(void)
{
    asm volatile ("call ASM_load_city_txt\n"
        :  :  : "eax" );
}

void load_city_data(ubyte type)
{
    TbFileHandle handle;

    handle = LbFileOpen("data/cities.dat", Lb_FILE_MODE_READ_ONLY);
    if (handle != (TbFileHandle)-1)
    {
        LbFileRead(handle, &num_cities, 1);
        LbFileRead(handle, cities, sizeof(struct City) * num_cities);
        LbFileClose(handle);
    }
}

void reload_background(void)
{
    asm volatile ("call ASM_reload_background\n"
        :  :  : "eax" );
}

void players_init_control_mode(void)
{
    int player;
    for (player = 0; player < 8; player++) {
      players[player].UserInput[0].ControlMode = 1;
    }
}

void srm_scanner_reset(void)
{
    int i;

    ingame.Scanner.X1 = 8;
    ingame.Scanner.Y2 = 270;
    ingame.Scanner.MX = 127;
    ingame.Scanner.MZ = 127;
    ingame.Scanner.Angle = 0;
    ingame.Scanner.X2 = 325;
    ingame.Scanner.Zoom = 256;
    ingame.Scanner.Y1 = 73;

    for (i = 0; i + ingame.Scanner.Y1 <= ingame.Scanner.Y2; i++)
    {
        ingame.Scanner.Width[i] = 318;
    }
    for (i = 0; i != 16; i++)
    {
        ingame.Scanner.BigBlip[i].Period = 0;
    }
    SCANNER_width = ingame.Scanner.Width;
    SCANNER_init();
}

void do_scroll_map(void)
{
    asm volatile ("call ASM_do_scroll_map\n"
        :  :  : "eax" );
}

void do_rotate_map(void)
{
    asm volatile ("call ASM_do_rotate_map\n"
        :  :  : "eax" );
}

void person_func_unknown_310(ubyte a1)
{
    asm volatile ("call ASM_person_func_unknown_310\n"
        :  : "a" (a1));
}

TbResult read_palette_file(void)
{
    TbResult ret;
    asm volatile ("call ASM_read_palette_file\n"
        : "=r" (ret) : );
    return ret;
}

TbBool pause_screen_handle(void)
{
    TbBool ret;
    asm volatile ("call ASM_pause_screen_handle\n"
        : "=r" (ret) : );
    return ret;
}

ubyte do_user_interface(void)
{
    PlayerInfo *p_locplayer;
    int n;

    p_locplayer = &players[local_player_no];
    person_func_unknown_310(0);
    do_scroll_map();
    do_rotate_map();
    if (in_network_game)
    {
        if (lbKeyOn[KC_RETURN])
        {
            lbKeyOn[KC_RETURN] = 0;
            if ((p_locplayer->PanelState[mouser] != 17) && (player_unkn0C9[local_player_no] <= 140))
            {
                p_locplayer->PanelState[mouser] = 17;
                reset_buffered_keys();
                player_unknCC9[local_player_no][0] = '\0';
                player_unkn0C9[local_player_no] = 0;
                scanner_unkn370 = 0;
                scanner_unkn3CC = 0;
            }
        }
    }
    if (p_locplayer->PanelState[mouser] == 17)
        return process_mouse_imputs() != 0;

    // screenshot
    if (lbKeyOn[KC_M])
        LbPngSaveScreen("synII", lbDisplay.WScreen, display_palette, 0);

    // TODO No idea what these are doing
    for (n = 0; n < 5; n++)
    {
        if (lbKeyOn[KC_F1+n])
        {
            if (lbShift & KMod_ALT)
            {
                lbKeyOn[KC_F1+n] = 0;
                my_build_packet(&packets[local_player_no], PAct_36, n, 0, 0, 0);
                return 1;
            }
            if (lbShift & KMod_SHIFT)
            {
                lbKeyOn[KC_F1+n] = 0;
                my_build_packet(&packets[local_player_no], PAct_35, n, 0, 0, 0);
                return 1;
            }
        }
    }

    // change panel style
    if (lbKeyOn[KC_F9] && (lbShift == KMod_NONE))
    {
        sbyte panperm;

        lbKeyOn[KC_F9] = 0;
        StopCD();
        if (ingame.PanelPermutation >= 0)
        {
            ingame.PanelPermutation++;
            if (ingame.PanelPermutation > 2)
                ingame.PanelPermutation = 0;
        }
        else
        {
            ingame.PanelPermutation--;
            if (ingame.PanelPermutation < -3)
                ingame.PanelPermutation = -1;
        }
        panperm = ingame.PanelPermutation;
        if ((panperm == 2) || (panperm == -3))
        {
            SCANNER_set_colour(1);
            SCANNER_fill_in();
        } else
        if ((panperm == 0) || (panperm == -1))
        {
            SCANNER_set_colour(2);
            SCANNER_fill_in();
        }
        if (lbDisplay.ScreenMode == 1)
            load_pop_sprites_lo();
        else
            load_pop_sprites_hi();
    }

    // change agents colours
    if (lbKeyOn[KC_F10] && (lbShift == KMod_NONE))
    {
        lbKeyOn[KC_F10] = 0;
        StopCD();
        if (++ingame.TrenchcoatPreference > 5)
            ingame.TrenchcoatPreference = 0;
        load_multicolor_sprites();
    }

    // adjust palette brightness
    if (lbKeyOn[KC_F11])
    {
        lbKeyOn[KC_F11] = 0;
        if (lbShift & KMod_CONTROL)
        {
            read_palette_file();
        }
        else if (lbShift & KMod_SHIFT)
        {
            change_brightness(-1);
            brightness--;
        }
        else if (lbShift == KMod_NONE)
        {
            change_brightness(1);
            brightness++;
        }
    }

    // TODO No idea what these are doing
    if (lbKeyOn[KC_F1] && (lbShift & KMod_CONTROL))
    {
        lbKeyOn[KC_F1] = 0;
        if (ingame.Flags & GamF_Unkn1)
            ingame.Flags &= ~GamF_Unkn1;
        else
            ingame.Flags |= GamF_Unkn1;
    }
    if (lbKeyOn[KC_F2] && (lbShift & KMod_CONTROL))
    {
        lbKeyOn[KC_F2] = 0;
        if (ingame.Flags & GamF_Unkn40)
            ingame.Flags &= ~GamF_Unkn40;
        else
            ingame.Flags |= GamF_Unkn40;
    }
    if (lbKeyOn[KC_F3] && (lbShift & KMod_CONTROL))
    {
        lbKeyOn[KC_F3] = 0;
        if (ingame.Flags & GamF_Unkn80)
            ingame.Flags &= ~GamF_Unkn80;
        else
            ingame.Flags |= GamF_Unkn80;
    }
    if (lbKeyOn[KC_F4] && (lbShift & KMod_CONTROL))
    {
        lbKeyOn[KC_F4] = 0;
        if (ingame.Flags & GamF_Unkn2)
            ingame.Flags &= ~GamF_Unkn2;
        else
            ingame.Flags |= GamF_Unkn2;
    }
    if (lbKeyOn[KC_F6] && (lbShift & KMod_CONTROL))
    {
        lbKeyOn[KC_F6] = 0;
        if (ingame.Flags & GamF_Unkn400)
            ingame.Flags &= ~GamF_Unkn400;
        else
            ingame.Flags |= GamF_Unkn400;
    }
    if ( lbKeyOn[KC_F10] && (lbShift & KMod_CONTROL))
    {
        lbKeyOn[KC_F10] = 0;
        if (ingame.Flags & GamF_Unkn2000)
            ingame.Flags &= ~GamF_Unkn2000;
        else
            ingame.Flags |= GamF_Unkn2000;
    }

    // TODO Speed control - make it work, maybe?
    if (lbKeyOn[KC_EQUALS])
    {
        lbKeyOn[KC_EQUALS] = 0;
        game_speed -= 2500;
        if (game_speed < 0)
            game_speed = 0;
    }
    if (lbKeyOn[KC_MINUS])
    {
        lbKeyOn[KC_MINUS] = 0;
        game_speed += 2500;
    }
#if 0 // What was that supposed to do?
    for (n = 1; n < game_speed; n++)
    {
        ulong k;

        k = n;
        while (k > 1)
        {
            if (k & 1)
                k = 3 * k + 1;
            else
                k = k >> 1;
        }
    }
#endif

    // Toggle Scanner beep
    if (lbKeyOn[KC_S])
    {
        if (ingame.Flags & GamF_Unkn200000)
            ingame.Flags &= ~GamF_Unkn200000;
        else
            ingame.Flags |= GamF_Unkn200000;
    }

    // Control map area to draw
    if (lbKeyOn[KC_E])
    {
        lbKeyOn[KC_E] = 0;

        if (lbShift & KMod_SHIFT)
            n = -2;
        else
            n = 2;
        render_area_a += n;

        if ( lbShift & KMod_SHIFT )
            n = -2;
        else
            n = 2;
        render_area_b += n;

        if (render_area_a < 2)
            render_area_a = 2;
        if (render_area_b < 2)
            render_area_b = 2;
        if (render_area_a > 28)
            render_area_a = 28;
        if (render_area_b > 28)
            render_area_b = 28;
    }

    // Entering pause screen
    if (!in_network_game)
    {
        if (lbKeyOn[kbkeys[GKey_PAUSE]] ||
            (jskeys[GKey_PAUSE] && jskeys[GKey_PAUSE] == joy.Buttons[0]))
        {
            if (pause_screen_handle()) {
                return -1;
            }
        }
    }

    // Scanner appearence control
    if (lbKeyOn[KC_NUMPAD6])
        ingame.Scanner.Brightness += 4;
    if (lbKeyOn[KC_NUMPAD4])
        ingame.Scanner.Brightness -= 4;
    if (ingame.Scanner.Brightness < 0)
        ingame.Scanner.Brightness = 0;
    if (ingame.Scanner.Brightness > 64)
        ingame.Scanner.Brightness = 64;

    // MIDI Music (tension) volume control
    if (lbKeyOn[KC_NUMPAD8])
    {
        if (lbShift & KMod_SHIFT)
            startscr_midivol += 1;
        else
            startscr_midivol += 10;
        if (startscr_midivol > 322)
            startscr_midivol = 322;
        SetMusicMasterVolume(127 * startscr_midivol / 322);
    }
    if (lbKeyOn[KC_NUMPAD2])
    {
        if (lbShift & KMod_SHIFT)
            startscr_midivol -= 1;
        else
            startscr_midivol -= 10;
        if (startscr_midivol < 0)
            startscr_midivol = 0;
        SetMusicMasterVolume(127 * startscr_midivol / 322);
    }

    // Sample volume control
    if (lbKeyOn[KC_NUMPAD7])
    {
        if (lbShift & KMod_SHIFT)
            startscr_samplevol += 1;
        else
            startscr_samplevol += 10;
        if (startscr_samplevol > 322)
            startscr_samplevol = 322;
        SetSoundMasterVolume(127 * startscr_samplevol / 322);
    }
    if (lbKeyOn[KC_NUMPAD1])
    {
        if (lbShift & KMod_SHIFT)
            startscr_samplevol -= 1;
        else
            startscr_samplevol -= 10;
        if (startscr_samplevol < 0)
            startscr_samplevol = 0;
        SetSoundMasterVolume(127 * startscr_samplevol / 322);
    }

    // CD Music volume control
    if (lbKeyOn[KC_NUMPAD9])
    {
        if (lbShift & KMod_SHIFT)
            startscr_cdvolume += 1;
        else
            startscr_cdvolume += 10;
        if (startscr_cdvolume > 322)
            startscr_cdvolume = 322;
        SetCDVolume(70 * (127 * startscr_cdvolume / 322) / 100);
    }
    if (lbKeyOn[KC_NUMPAD3])
    {
        if (lbShift & KMod_SHIFT)
            startscr_cdvolume -= 1;
        else
            startscr_cdvolume -= 10;
        if (startscr_cdvolume < 0)
            startscr_cdvolume = 0;
        SetCDVolume(70 * (127 * startscr_cdvolume / 322) / 100);
    }

    // Music track control
    if (lbKeyOn[KC_NUMPAD5])
    {
        lbKeyOn[KC_NUMPAD5] = 0;
        if (++ingame.CDTrack > 4)
            ingame.CDTrack = 2;
    }
    if (lbKeyOn[KC_NUMPAD0])
    {
        lbKeyOn[KC_NUMPAD0] = 0;
        ingame.DangerTrack = 2 - ingame.DangerTrack + 1;
    }

    // Restart level
    if (!in_network_game && !(ingame.Flags & GamF_Unkn10))
    {
        if (lbKeyOn[KC_R])
        {
            lbKeyOn[KC_R] = 0;
            mission_result = 0;
            StopCD();
            test_missions(1u);
            init_level_3d(1u);
            change_current_map(cmdln_param_current_map);
            unkn_lights_func_11();
            if (ingame.GameMode == GamM_Unkn2)
                execute_commands = 0;
            engn_yc = 0;
            init_game(1);
            lbSeed = 0xD15C1234;
            if (pktrec_mode == PktR_RECORD)
            {
                PacketRecord_Close();
                PacketRecord_OpenWrite();
            }
        }
    }

    if (ingame.TrackThing)
    {
        build_packet(&packets[local_player_no], 0, p_locplayer->DirectControl[0], 0, 0, 0);
        return 1;
    }

    static ushort sel_agent_gkeys[] = {
        GKey_SEL_AGENT_1, GKey_SEL_AGENT_2, GKey_SEL_AGENT_3, GKey_SEL_AGENT_4
    };
    static ulong last_sel_agent_turn[4] = {0};
    for (n = 0; n < (int)(sizeof(sel_agent_gkeys)/sizeof(sel_agent_gkeys[0])); n++)
    {
        ulong gkey = sel_agent_gkeys[n];
        if (lbKeyOn[kbkeys[gkey]] && (lbShift == KMod_NONE))
        {
            struct Thing *p_agent;

            p_agent = p_locplayer->MyAgent[n];
            if (p_agent != NULL)
            {
                if (((p_agent->Flag & 0x02) == 0) && ((p_agent->Flag2 & 0x10) == 0) && (p_agent->State != 36))
                {
                  lbKeyOn[kbkeys[gkey]] = 0;
                  if (p_locplayer->DoubleMode)
                  {
                    byte_153198 = n+1;
                  }
                  else
                  {
                    my_build_packet(&packets[local_player_no], PAct_17,
                        p_locplayer->DirectControl[n], p_agent->ThingOffset, 0, 0);
                    p_locplayer->UserInput[0].ControlMode |= 0x8000u;
                    // Double tapping - center view on the agent
                    if (gameturn - last_sel_agent_turn[n] < 7)
                    {
                      p_agent = p_locplayer->MyAgent[n];
                      ingame.TrackX = p_agent->X >> 8;
                      engn_yc = p_agent->Y >> 8;
                      ingame.TrackZ = p_agent->Z >> 8;
                      build_packet(&packets[local_player_no], PAct_17,
                          p_locplayer->DirectControl[mouser], p_agent->ThingOffset, 0, 0);
                      if (p_agent->ThingOffset == p_locplayer->DirectControl[mouser])
                      {
                          engn_xc = p_agent->X >> 8;
                          engn_zc = p_agent->Z >> 8;
                      }
                    }
                    last_sel_agent_turn[n] = gameturn;
                  }
                  return 1;
                }
            }
        }
    }

    if (ingame.Flags & GamF_Unkn100)
    {
        build_packet(&packets[local_player_no], 0, p_locplayer->DirectControl[0], 0, 0, 0);
        return 1;
    }

    // Resurrection and bes equipment cheat
    if (p_locplayer->DoubleMode && (ingame.Cheats & 0x04) && !in_network_game)
    {
        if (lbKeyOn[KC_Q] && ((lbShift == KMod_SHIFT) || (lbShift == KMod_NONE)))
        {
            lbKeyOn[KC_Q] = 0;
            beefup_all_agents(p_locplayer);
        }
    }

    // Final part of this function is left in ASM, for now. It requires updating
    // definition of SpecialUserInput for the rewrting to make sense.
    ubyte ret;
    asm volatile ("call ASM_do_user_interface\n"
        : "=r" (ret));
    return ret;
}

void show_main_screen(void)
{
    if ((game_projector_speed && (main_quit_button.Flags & 0x01)) ||
      (lbKeyOn[KC_SPACE] && !edit_flag))
    {
        lbKeyOn[KC_SPACE] = 0;
        main_quit_button.Flags |= 0x0002;
        main_load_button.Flags |= 0x0002;
        main_login_button.Flags |= 0x0002;
        main_map_editor_button.Flags |= 0x0002;
    }
    //main_quit_button.DrawFn(&main_quit_button); -- incompatible calling convention
    asm volatile ("call *%1\n"
        : : "a" (&main_quit_button), "g" (main_quit_button.DrawFn));
    //main_load_button.DrawFn(&main_load_button); -- incompatible calling convention
    asm volatile ("call *%1\n"
        : : "a" (&main_load_button), "g" (main_load_button.DrawFn));
    //main_login_button.DrawFn(&main_login_button); -- incompatible calling convention
    asm volatile ("call *%1\n"
        : : "a" (&main_login_button), "g" (main_login_button.DrawFn));
}

void show_pause_screen(void)
{
    if ((game_projector_speed && (pause_unkn12_box.Flags & 0x01)) ||
      (lbKeyOn[KC_SPACE] && !edit_flag))
    {
        lbKeyOn[KC_SPACE] = 0;
        pause_unkn11_box.Flags |= 0x0002;
        pause_unkn12_box.Flags |= 0x0002;
        pause_abort_button.Flags |= 0x0002;
        pause_continue_button.Flags |= 0x0002;
    }
    //pause_unkn12_box.DrawFn(&pause_unkn12_box); -- incompatible calling convention
    asm volatile ("call *%1\n"
        : : "a" (&pause_unkn12_box), "g" (pause_unkn12_box.DrawFn));
    //pause_unkn11_box.DrawFn(&pause_unkn11_box); -- incompatible calling convention
    asm volatile ("call *%1\n"
        : : "a" (&pause_unkn11_box), "g" (pause_unkn11_box.DrawFn));
    //pause_continue_button.DrawFn(&pause_continue_button); -- incompatible calling convention
    asm volatile ("call *%1\n"
        : : "a" (&pause_continue_button), "g" (pause_continue_button.DrawFn));
    //pause_abort_button.DrawFn(&pause_abort_button); -- incompatible calling convention
    asm volatile ("call *%1\n"
        : : "a" (&pause_abort_button), "g" (pause_abort_button.DrawFn));
}

void show_worldmap_screen(void)
{
    if ((game_projector_speed && (heading_box.Flags & 0x01)) ||
      (lbKeyOn[KC_SPACE] && !edit_flag))
    {
        lbKeyOn[KC_SPACE] = 0;
        unkn29_box.Flags |= 0x0002;
        heading_box.Flags |= 0x0002;
        unkn38_box.Flags |= 0x0002;
    }
    int ret = 1;
    if (ret) {
        //ret = heading_box.DrawFn(&heading_box); -- incompatible calling convention
        asm volatile ("call *%2\n"
            : "=r" (ret) : "a" (&heading_box), "g" (heading_box.DrawFn));
    }
    if (ret) {
        //ret = unkn29_box.DrawFn(&unkn29_box); -- incompatible calling convention
        asm volatile ("call *%2\n"
            : "=r" (ret) : "a" (&unkn29_box), "g" (unkn29_box.DrawFn));
    }
    if (ret) {
        //ret = unkn38_box.DrawFn(&unkn38_box); -- incompatible calling convention
        asm volatile ("call *%2\n"
            : "=r" (ret) : "a" (&unkn38_box), "g" (unkn38_box.DrawFn));
    }
}

void show_alert_box(void)
{
    asm volatile ("call ASM_show_alert_box\n"
        :  :  : "eax" );
}

void show_type11_screen(void)
{
    asm volatile ("call ASM_show_type11_screen\n"
        :  :  : "eax" );
}

void show_research_screen(void)
{
    asm volatile ("call ASM_show_research_screen\n"
        :  :  : "eax" );
}

void show_netgame_screen(void)
{
    asm volatile ("call ASM_show_netgame_screen\n"
        :  :  : "eax" );
}

void show_equipment_screen(void)
{
    asm volatile ("call ASM_show_equipment_screen\n"
        :  :  : "eax" );
}

void show_cryo_chamber_screen(void)
{
    asm volatile ("call ASM_show_cryo_chamber_screen\n"
        :  :  : "eax" );
}

void show_mission_screen(void)
{
    asm volatile ("call ASM_show_mission_screen\n"
        :  :  : "eax" );
}

void show_menu_screen_st0(void)
{
    debug_trace_place(16);

    lbInkeyToAscii[KC_OEM_102] = '\\';
    lbInkeyToAsciiShift[KC_OEM_102] = '|';

    players_init_control_mode();

    login_control__State = 6;
    sprintf(net_unkn2_text, "01234567890");

    hotspot_buffer = scratch_malloc_mem;
    mission_briefing_text = (char *)scratch_malloc_mem + 512;
    mem_unkn03 = (char *)scratch_malloc_mem + 16896;
    weapon_text = (char *)scratch_malloc_mem + 33280;
    memload = (ubyte *)scratch_malloc_mem + 66048;
    purple_draw_list = (struct PurpleDrawItem *)((ubyte *)scratch_malloc_mem + 82432);

    init_read_all_sprite_files();
    ingame.Credits = 50000;

    debug_trace_place(17);
    LbColourTablesLoad(display_palette, "data/bgtables.dat");
    LbGhostTableGenerate(display_palette, 66, "data/startgho.dat");
    init_screen_boxes();
    update_menus();
    players[local_player_no].MissionAgents = 0x0f;
    load_city_data(0);
    load_city_txt();

    debug_trace_place(18);
    if ( in_network_game )
        screentype = SCRT_PAUSE;
    else
        screentype = SCRT_MAINMENU;
    data_1c498d = 1;

    debug_trace_place(19);
    LbFileLoadAt("data/s-proj.pal", display_palette);
    show_black_screen();
    show_black_screen();
    LbPaletteSet(display_palette);
    reload_background();

    global_date.Day = 2;
    global_date.Year = 74;
    global_date.Month = 6;

    srm_scanner_reset();

    save_game_buffer = unkn_buffer_05;

    net_system_init0();
}

void update_options_screen_state(void)
{
    char *text;
    if (ingame.PanelPermutation < 0)
      text = gui_strings[abs(ingame.PanelPermutation) + 579];
    else
      text = gui_strings[ingame.PanelPermutation + 580];
    options_gfx_buttons[14].Text = text;
    text = gui_strings[ingame.TrenchcoatPreference + 583];
    options_gfx_buttons[15].Text = text;
}

void init_net_players(void)
{
    int i;
    for (i = 0; i != 125; i += 25)
    {
        net_players[i] = '\0';
    }
}

void delete_mail(ushort mailnum, ubyte type)
{
    asm volatile ("call ASM_delete_mail\n"
        : : "a" (mailnum), "d" (type));
}

ubyte load_mail_text(const char *filename)
{
    ubyte ret;
    asm volatile ("call ASM_load_mail_text\n"
        : "=r" (ret) : "a" (filename));
    return ret;
}

void brief_load_mission_info(void)
{
    char fname[FILENAME_MAX];

    heading_box.Text = gui_strings[372];
    data_1c4aa2 = 0;
    unkn36_box.Lines = 0;

    if (open_brief != 0)
    {
        if (open_brief < 0) {
            sprintf(fname, "%s/mail%03d.txt", "textdata", email_store[-open_brief - 1].Mission);
        } else if (open_brief > 0) {
            sprintf(fname, "%s/miss%03d.txt", "textdata", mission_list[brief_store[open_brief - 1].Mission].SourceID);
        }
        load_mail_text(fname);
    }
}

void activate_cities(ubyte brief)
{
    asm volatile ("call ASM_activate_cities\n"
        : : "a" (brief));
}

void init_weapon_text(void)
{
    asm volatile ("call ASM_init_weapon_text\n"
        :  :  : "eax" );
}

void srm_reset_research(void)
{
    asm volatile ("call ASM_srm_reset_research\n"
        :  :  : "eax" );
}

void init_agents(void)
{
    asm volatile ("call ASM_init_agents\n"
        :  :  : "eax" );
}

void draw_flic_purple_list(void (*fn)())
{
    asm volatile ("call ASM_draw_flic_purple_list\n"
        : : "a" (fn));
}

void update_mission_time(char a1)
{
    asm volatile ("call ASM_update_mission_time\n"
        : : "a" (a1));
}

void show_date_time(void)
{
    asm volatile ("call ASM_show_date_time\n"
        :  :  : "eax" );
}

void purple_unkn1_data_to_screen(void)
{
    memcpy(data_1c6de4, data_1c6de8, 0x5FA0u);
}

ubyte do_buy_equip(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_buy_equip\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

void init_weapon_anim(ubyte weapon)
{
    asm volatile ("call ASM_init_weapon_anim\n"
        : : "a" (weapon));
}

void research_unkn_func_002(void)
{
    asm volatile ("call ASM_research_unkn_func_002\n"
        :  :  : "eax" );
}

void unkn_research_func_006(void)
{
    asm volatile ("call ASM_unkn_research_func_006\n"
        :  :  : "eax" );
}

int research_unkn_func_005(char a1)
{
    int ret;
    asm volatile ("call ASM_research_unkn_func_005\n"
        : "=r" (ret) : "a" (a1));
    return ret;
}

void net_unkn_func_33(void)
{
    asm volatile ("call ASM_net_unkn_func_33\n"
        :  :  : "eax" );
}

void forward_research_progress(int num_days)
{
    new_mods_researched = 0;
    new_weapons_researched = 0;
    int i;
    for (i = 0; i < num_days; i++)
    {
        int prev;

        prev = research.CurrentWeapon;
        scientists_lost = research_unkn_func_005(0);
        if (research.CurrentWeapon != prev)
            new_weapons_researched |= 1 << prev;

        prev = research.CurrentMod;
        scientists_lost += research_unkn_func_005(1);
        if (research.CurrentMod != prev)
            new_mods_researched |= 1 << prev;
    }
    research.Scientists -= scientists_lost;
    if (research.Scientists < 0)
        research.Scientists = 0;
    research_unkn_func_002();
}

void draw_purple_screen(void)
{
    asm volatile ("call ASM_draw_purple_screen\n"
        :  :  : "eax" );
}

int save_game_write(ubyte slot, char *desc)
{
    int ret;
    asm volatile ("call ASM_save_game_write\n"
        : "=r" (ret) : "a" (slot), "d" (desc));
    return ret;
}

void clear_mission_status(ulong id)
{
    mission_status[id].CivsKilled = 0;
    mission_status[id].EnemiesKilled = 0;
    mission_status[id].CivsPersuaded = 0;
    mission_status[id].SecurityPersuaded = 0;
    mission_status[id].EnemiesPersuaded = 0;
    mission_status[id].AgentsGained = 0;
    mission_status[id].AgentsLost = 0;
    mission_status[id].SecurityKilled = 0;
    mission_status[id].CityDays = 0;
    mission_status[id].CityHours = 0;
}

void show_menu_screen_st2(void)
{
    if ( in_network_game )
    {
      local_player_no = 0;
      login_control__State = 6;
      net_INITIATE_button.Text = gui_strings[385];
      net_INITIATE_button.Flags = 1;
      ingame.Credits = 50000;
      ingame.CashAtStart = 50000;
      ingame.Expenditure = 0;
      net_groups_LOGON_button.Text = gui_strings[386];
      data_15516d = -1;
      data_15516c = -1;
      login_control__TechLevel = 4;
      unkn_city_no = -1;
      login_control__City = -1;
      unkn_flags_08 = 60;
      login_control__Money = starting_cash_amounts[0];
      init_agents();
      srm_reset_research();
      load_missions(0);
      memset(unkstruct04_arr, 0, 20 * sizeof(struct UnknStruct04)); //clear 4360 bytes
      data_1c6d48 = 0;
      selected_mod = -1;
      selected_weapon = -1;
      init_net_players();
      draw_flic_purple_list(purple_unkn1_data_to_screen);
      scientists_lost = 0;
      update_mission_time(0);
      in_network_game = 0;
      screentype = SCRT_B;
      redraw_screen_flag = 1;
      heading_box.Text = gui_strings[374];
    }
    else
    {
      update_mission_time(0);
      city_id = -1;
      data_1c4aa3 = brief_store[open_brief - 1].RefNum;
      if ((ingame.MissionStatus != 0) && (ingame.MissionStatus != 2))
      {
            memcpy(&mission_status[0], &mission_status[open_brief],
              sizeof(struct MissionStatus));
            delete_mail(open_brief - 1, 1u);
            open_brief = 0;
            old_mission_brief = 0;
            cities[unkn_city_no].Info = 0;
      }
      else
      {
            old_mission_brief = open_brief;
      }
      if ( ingame.fld_unk7DF )
      {
            screentype = SCRT_MAINMENU;
            if (ingame.Flags & 0x10)
                LbFileDelete("qdata/savegame/synwarsm.sav");
            ingame.fld_unk7DF = 0;
      }
      else
      {
            forward_research_progress(mission_status[open_brief].CityDays);
            if (ingame.Flags & 0x10)
                save_game_write(0, save_active_desc);
            screentype = SCRT_9;
            heading_box.Text = gui_strings[374];
            redraw_screen_flag = 1;
      }
    }

    LbColourTablesLoad(display_palette, "data/bgtables.dat");
    LbGhostTableGenerate(display_palette, 66, "data/startgho.dat");
    init_read_all_sprite_files();
    init_weapon_text();
    load_city_txt();
    data_1c498d = 1;
    LbMouseChangeSpriteOffset(0, 0);
    LbFileLoadAt("data/s-proj.pal", display_palette);

    update_options_screen_state();

    show_black_screen();
    show_black_screen();
    LbPaletteSet(display_palette);
    reload_background();

    srm_scanner_reset();

    if ( new_mail )
    {
        play_sample_using_heap(0, 119 + (LbRandomAnyShort() % 3), 127, 64, 100, 0, 3u);
    }
    net_system_init2();
}

void init_random_seed(void)
{
    if (in_network_game)
    {
        mission_open[1] = ingame.CurrentMission;
        mission_state[1] = 0;
        mission_open[2] = 0;
        mission_state[2] = 0;
        if (is_unkn_current_player())
        {
            lbSeed = time(0);
            network_players[net_host_player_no].npfield_1 = lbSeed;
            LbNetworkExchange(network_players, 26);
        } else {
            LbNetworkExchange(network_players, 26);
            lbSeed = network_players[net_host_player_no].npfield_1;
        }
    }
    else
    {
        lbSeed = time(0);
    }
    srand(lbSeed);
}

ushort find_mission_with_mapid(short mapID, short mission_limit)
{
    ushort i;
    for (i = 1; i < mission_limit; i++)
    {
        if (mission_list[i].MapNo == mapID) {
            return i;
        }
    }
    return 0;
}

void update_open_brief(void)
{
    int i;
    open_brief = 0;
    for (i = 0; i < next_brief; i++)
    {
      int k = brief_store[i].Mission;
      if (cities[unkn_city_no].MapID == mission_list[k].MapNo)
      {
          open_brief = i + 1;
      }
      else
      {
          while ( 1 )
          {
            k = mission_list[k].SpecialTrigger[0];
            if (k == 0)
                break;
            if (cities[unkn_city_no].MapID == mission_list[k].MapNo) {
                open_brief = i + 1;
                break;
            }
          }
      }
      if (open_brief != 0)
          break;
    }
}

/** Macro for returning given array of elements in random order.
 *
 * Provided input and output arrays, type of element and count of elements,
 * this routine will randomize the order of elements.
 */
#define array_elements_in_random_order(out_nubers, in_nubers, elem_type, count) \
{ \
    ushort pos, remain, next; \
    elem_type nums[count]; \
    memcpy(nums, in_nubers, sizeof(elem_type)*count); \
    remain = count; \
    for (pos = 0; pos < count; pos++) \
    { \
        elem_type nbak; \
        next = LbRandomAnyShort() % remain; \
        remain--; \
        out_nubers[pos] = nums[next]; \
        nbak = nums[remain]; \
        nums[remain] = nums[next]; \
        nums[next] = nbak; \
    } \
}

void randomize_playable_groups_order(void)
{
    static long incrementing_nubers[] = {0, 1, 2, 3, 4, 5, 6, 7,};
    array_elements_in_random_order(level_def.PlayableGroups, incrementing_nubers, long, 8);
}

void wait_for_sound_sample_finish(ushort sample_id)
{
    TbClockMSec last_loop_time = LbTimerClock();
    while (IsSamplePlaying(0, sample_id, NULL)) {
        game_update();
        TbClockMSec sleep_end = last_loop_time + 1000/GAME_FPS;
        LbSleepUntil(sleep_end);
        last_loop_time = LbTimerClock();
    }
}

void game_play_music(void)
{
    char file_name[FILENAME_MAX];

    snprintf (file_name, sizeof (file_name),
          "%s" FS_SEP_STR "music" FS_SEP_STR "track_%i.ogg",
          GetDirectoryHdd(), ingame.CDTrack - 1);

    sound_open_music_file(file_name);
    sound_play_music();
}

void frame_unkn_func_06(void)
{
    asm volatile ("call ASM_frame_unkn_func_06\n"
        :  :  : "eax" );
}

void load_netscan_data(ubyte city_id, ubyte a2)
{
    asm volatile ("call ASM_load_netscan_data\n"
        : : "a" (city_id), "d" (a2));
}

void load_all_text(ubyte a1)
{
    asm volatile ("call ASM_load_all_text\n"
        : : "a" (a1));
}

void show_mission_loading_screen(void)
{
    LbMouseChangeSprite(0);
    reload_background();
    play_sample_using_heap(0, 118, 127, 64, 100, 0, 3);

    DwBool stop;
    TbClockMSec last_loop_time = LbTimerClock();
    do
    {
        memcpy(lbDisplay.WScreen, back_buffer, lbDisplay.GraphicsScreenWidth * lbDisplay.GraphicsScreenHeight);
        text_buf_pos = lbDisplay.GraphicsScreenWidth * lbDisplay.GraphicsScreenHeight;
        if ((0 != game_projector_speed && (loading_INITIATING_box.Flags & 0x0001))
          || (0 != lbKeyOn[KC_SPACE] && 0 == edit_flag))
            loading_INITIATING_box.Flags |= 0x0002;
        //loading_INITIATING_box.DrawFn(&loading_INITIATING_box); -- incompatible calling convention
        asm volatile ("call *%1\n"
            : : "a" (&loading_INITIATING_box), "g" (loading_INITIATING_box.DrawFn));
        stop = loading_INITIATING_box.Flags & 0x1000;
        draw_purple_screen();
        swap_wscreen();

        game_update();
        TbClockMSec sleep_end = last_loop_time + 1000/GAME_FPS;
        LbSleepUntil(sleep_end);
        last_loop_time = LbTimerClock();
    }
    while (!stop);

    loading_INITIATING_box.Flags = 0x0001;
    wait_for_sound_sample_finish(118);
    // TODO the below is added as part of the vexillium port; to be removed when proper music enabling works
    game_play_music();
}

void show_load_and_prep_mission(void)
{
    init_random_seed();
    show_mission_loading_screen();

    if ( start_into_mission )
    {
        if (!in_network_game) {
            update_open_brief();
        }

        ingame.DisplayMode = DpM_UNKN_32;
        debug_trace_place(6);
        if ( in_network_game )
        {
          ushort mission;

          ingame.MissionNo = 1;
          mission = find_mission_with_mapid(cities[login_control__City].MapID, next_mission);
          if (mission > 0) {
              ingame.MissionNo = mission;
              ingame.CurrentMission = mission;
          }

          change_current_map(mission_list[ingame.MissionNo].MapNo);
          load_mad_0_console(-(int)mission_list[ingame.MissionNo].LevelNo, ingame.MissionNo);
          randomize_playable_groups_order();
        }
        else
        {
            load_all_text(brief_store[open_brief - 1].Mission);
            change_current_map(cities[unkn_city_no].MapID);
        }

        debug_trace_place(7);
        // The file name is formatted in original code, but doesn't seem to be used
        //sprintf(fname, "maps/map%03d.scn", cities[unkn_city_no].MapID);
        ingame.fld_unkC4F = 0;
        data_19ec6f = 1;
        execute_commands = 1;
        if ( !in_network_game )
        {
            if (cities[unkn_city_no].Level != 0)
                load_mad_0_console(-cities[unkn_city_no].Level, unkn_city_no);
        }
        debug_trace_place(8);
    }
    else
    {
        LbMouseChangeSprite(&pointer_sprites[1]);
        ingame.DisplayMode = DpM_UNKN_1;
    }

    debug_trace_place(9);
    data_1c498d = 2;
    reload_background_flag = 1;
    debug_trace_place(10);
    {
        screen_buffer_fill_black();
        frame_unkn_func_06();
        screen_buffer_fill_black();
        show_black_screen();
        swap_wscreen();
    }
    LbFileLoadAt("qdata/pal.pal", display_palette);
    LbPaletteSet(display_palette);
    debug_trace_place(11);
    if (game_high_resolution)
    {
        if (lbDisplay.ScreenMode != screen_mode_game_hi)
            setup_screen_mode(screen_mode_game_hi);
    }
    else
    {
        if (lbDisplay.ScreenMode != screen_mode_game_lo)
            setup_screen_mode(screen_mode_game_lo);
    }
    if (lbDisplay.GraphicsScreenWidth >= 640)
    {
        overall_scale = 400;
        render_area_a = 30;
        render_area_b = 30;
    }

    debug_trace_place(12);
    LbColourTablesLoad(display_palette, "data/tables.dat");
    LbGhostTableLoad(display_palette, 50, "data/synghost.tab");
    debug_trace_place(13);
    if ( start_into_mission )
    {
        load_multicolor_sprites();
        if (game_high_resolution)
            load_pop_sprites_hi();
        else
            load_pop_sprites_lo();

        if (ingame.GameMode == GamM_None)
            ingame.GameMode = GamM_Unkn2;
        init_player();
        flic_unkn03(1);
        func_6edb8(1);
        if ( in_network_game )
        {
            if (data_1811ae != 1)
                ingame.InNetGame_UNSURE = 3;
            ingame.DetailLevel = 0;
            bang_set_detail(1);
            update_mission_time(1);
            // why clear only 0x140 bytes?? the array is much larger
            memset(mission_status, 0, sizeof(struct MissionStatus) * 8);
            gameturn = 0;
        }
        else
        {
            int i;
            for (i = 0; i < 8; i++) {
                unkn2_names[i][0] = 0;
            }
            strncpy(unkn2_names[0], login_name, 16);

            clear_mission_status(open_brief);
            update_mission_time(1);
            cities[unkn_city_no].Info = 0;
            debug_trace_place(14);
            //TODO SpecialTrigger doesn't seem to be correct name for next mission
            for (i = brief_store[open_brief - 1].Mission; i != 0;
              i = mission_list[i].SpecialTrigger[0])
            {
              if (mission_list[i].MapNo == cities[unkn_city_no].MapID)
                  break;
            }
            ingame.CurrentMission = i;
            mission_result = 0;
            debug_trace_place(15);
        }
        lbDisplay.MLeftButton = 0;
        lbDisplay.LeftButton = 0;
    }

    map_editor = 0;
    start_into_mission = 0;
    reload_background_flag = 0;
    net_system_reset();
    stop_sample_using_heap(0, 122);
}

void setup_menu_screen_mode(void)
{
    TbScreenModeInfo *mdinfo;

    game_high_resolution = 0;
    LbMouseReset();
    screen_buffer_fill_black();
    mdinfo = LbScreenGetModeInfo(screen_mode_menu);
    if (mdinfo->Width == 0) return;
    LbScreenSetup(screen_mode_menu, mdinfo->Width, mdinfo->Height, display_palette);
    LbMouseSetup(&pointer_sprites[1], 1, 1);
    setup_vecs(lbDisplay.WScreen, vec_tmap, lbDisplay.PhysicalScreenWidth,
        lbDisplay.PhysicalScreenWidth, lbDisplay.PhysicalScreenHeight);
}

void ASM_show_menu_screen(void);
void show_menu_screen(void)
{
#if 0
    ASM_show_menu_screen();
#else
    switch (data_1c498d)
    {
    case 2:
        show_menu_screen_st2();
        play_sample_using_heap(0, 122, 127, 64, 100, -1, 3);
        break;
    case 0:
        show_menu_screen_st0();
        play_sample_using_heap(0, 122, 127, 64, 100, -1, 3);
        break;
    default:
        break;
    }
    if (lbDisplay.ScreenMode != screen_mode_menu)
    {
        setup_menu_screen_mode();
        reload_background();
        my_set_text_window(0, 0, lbDisplay.GraphicsScreenWidth, lbDisplay.GraphicsScreenHeight);
    }

    if (screentype == SCRT_MAINMENU)
    {
        replay_intro_timer++;
        if (replay_intro_timer > 1100)
        {
            replay_intro();
            replay_intro_timer = 0;
            data_1c498d = 0;
            return;
          }
    }

    if (screentype != SCRT_MAINMENU) {
        replay_intro_timer = 0;
    }
    text_buf_pos = lbDisplay.GraphicsScreenWidth * lbDisplay.GraphicsScreenHeight;

    if ( !joy.Buttons[0] || net_unkn_pos_02 )
    {
        if ( data_1c4991 )
            data_1c4991 = 0;
    }
    else if ( !data_1c4991 )
    {
        int i;
        data_1c4991 = 1;
        lbDisplay.LeftButton = 1;
        // Scale mouse position in high resolutions
        if (lbDisplay.GraphicsScreenWidth > 320)
            i = lbDisplay.MMouseX * lbDisplay.GraphicsScreenWidth / 320;
        else
            i = lbDisplay.MMouseX;
        lbDisplay.MouseX = i;
        if (lbDisplay.GraphicsScreenHeight > 200)
            i = lbDisplay.MMouseY * lbDisplay.GraphicsScreenHeight / 200;
        else
            i = lbDisplay.MMouseY;
        lbDisplay.MouseY = i;
    }

    data_1c498f = lbDisplay.LeftButton;
    data_1c4990 = lbDisplay.RightButton;
    show_date_time();
    if ((screentype != SCRT_MAINMENU) && (screentype != SCRT_PAUSE) && !restore_savegame)
          unkn_research_func_006();
    if ((screentype == SCRT_9 || screentype == SCRT_B) && change_screen == 7)
    {
        screentype = SCRT_MISSION;
        brief_load_mission_info();
        redraw_screen_flag = 1;
        edit_flag = 0;
        change_screen = 0;
    }

    switch (screentype)
    {
    case SCRT_MISSION:
        show_mission_screen();
        break;
    case SCRT_WORLDMAP:
        show_worldmap_screen();
        break;
    case SCRT_CRYO:
        show_cryo_chamber_screen();
        break;
    case SCRT_EQUIP:
        show_equipment_screen();
        break;
    case SCRT_MAINMENU:
        show_main_screen();
        break;
    case SCRT_NETGAME:
        show_netgame_screen();
        break;
    case SCRT_RESEARCH:
        show_research_screen();
        break;
    case SCRT_9:
        show_type11_screen();
        break;
    case SCRT_PAUSE:
        show_pause_screen();
        break;
    case SCRT_B:
        show_type11_screen();
        break;
    case SCRT_ALERTBOX:
        show_alert_box();
        break;
    }

    if (login_control__State == 5)
    {
        net_unkn_func_33();
    }
    else if (login_control__State == 8)
    {
        start_into_mission = 1;
        in_network_game = 1;
        redraw_screen_flag = 1;
        local_player_no = LbNetworkPlayerNumber();
        net_players_num = LbNetworkSessionNumberPlayers();
        net_INITIATE_button.Text = gui_strings[385];
        net_groups_LOGON_button.Text = gui_strings[386];
        network_players[local_player_no].npfield_0 = 14;
        net_unkn_func_33();
        network_players[local_player_no].npfield_0 = 15;
        net_unkn_func_33();
        init_net_players();
    }
    if (data_1c498f && lbDisplay.LeftButton)
    {
        data_1c498f = 0;
        lbDisplay.LeftButton = 0;
    }
    if (data_1c4990 && lbDisplay.RightButton)
    {
        data_1c4990 = 0;
        lbDisplay.RightButton = 0;
    }
    memcpy(lbDisplay.WScreen, back_buffer, lbDisplay.GraphicsScreenWidth * lbDisplay.GraphicsScreenHeight);
    draw_purple_screen();

    if ( screentype != SCRT_MAINMENU && screentype != SCRT_PAUSE && !restore_savegame )
    {
        if ( lbKeyOn[KC_F1] && screentype != SCRT_ALERTBOX && !net_unkn_pos_01b)
        {
            lbKeyOn[KC_F1] = 0;
            change_screen = 1;
        }
        if ( lbKeyOn[KC_F2] && screentype != SCRT_ALERTBOX && !net_unkn_pos_01b)
        {
            lbKeyOn[KC_F2] = 0;
            change_screen = 3;
        }
        if ( lbKeyOn[KC_F3] && screentype != SCRT_ALERTBOX && !net_unkn_pos_01b)
        {
            lbKeyOn[KC_F3] = 0;
            change_screen = 4;
        }
        if ( lbKeyOn[KC_F4] && screentype != SCRT_ALERTBOX && !net_unkn_pos_01b)
        {
            lbKeyOn[KC_F4] = 0;
            change_screen = 5;
        }
        if ( lbKeyOn[KC_F5] && screentype != SCRT_ALERTBOX && !net_unkn_pos_01b)
        {
            lbKeyOn[KC_F5] = 0;
            if (research.NumBases > 0)
                change_screen = 6;
        }
        if ( lbKeyOn[KC_F6] && screentype != SCRT_ALERTBOX && !net_unkn_pos_01b)
        {
            lbKeyOn[KC_F6] = 0;
            if (open_brief != 0)
                change_screen = 7;
        }
    }
    if (change_screen == 1)
    {
        screentype = SCRT_NETGAME;
        redraw_screen_flag = 1;
        heading_box.Text = "";
        edit_flag = 0;
        change_screen = 0;
    }
    if (change_screen == 2)
    {
        screentype = SCRT_2;
        redraw_screen_flag = 1;
        heading_box.Text = gui_strings[367];
        edit_flag = 0;
        change_screen = 0;
    }
    if (change_screen == 3)
    {
        heading_box.Text = gui_strings[368];
        redraw_screen_flag = 1;
        edit_flag = 0;
        change_screen = 0;
        screentype = SCRT_WORLDMAP;
        if (city_id != -1)
          unkn_city_no = city_id;
    }
    if (change_screen == 4)
    {
        screentype = SCRT_CRYO;
        heading_box.Text = gui_strings[369];
        equip_cost_box.X = 430;
        equip_cost_box.Width = 198;
        equip_cost_box.Y = 383;
        equip_name_box.Text = equip_name_text;
        if ( selected_mod < 0 )
            equip_name_text[0] = '\0';
        else
            init_weapon_anim(selected_mod + 32);
        buy_equip_button.Text = gui_strings[436];
        buy_equip_button.CallBackFn = do_buy_equip;

        sprintf(equip_cost_text, "%d", 10 * (int)mod_defs[selected_mod + 1].Cost);
        redraw_screen_flag = 1;
        int i;
        for (i = 0; i < 4; i++)
        {
            mod_draw_states[i] = 0;
            if (0 != flic_mods[i])
                mod_draw_states[i] = 8;
        }
        current_drawing_mod = 0;
        new_current_drawing_mod = 0;
        edit_flag = 0;
        change_screen = 0;
    }
    if (change_screen == 5)
    {
        screentype = SCRT_EQUIP;
        heading_box.Text = gui_strings[370];
        equip_cost_box.X = buy_equip_button.Width + buy_equip_button.X + 4;
        refresh_equip_list = 1;
        equip_cost_box.Width = 208 - buy_equip_button.Width - 14;
        equip_cost_box.Y = 404;
        if ( selected_weapon < 0 )
        {
            equip_name_box.Text = 0;
        }
        else
        {
            init_weapon_anim(selected_weapon);
            if ((research.WeaponsCompleted & (1 << selected_weapon)) || (login_control__State != 6))
            {
              if ( background_type == 1 )
                  equip_name_box.Text = gui_strings[selected_weapon + 30];
              else
                  equip_name_box.Text = gui_strings[selected_weapon];
            }
            else
            {
                equip_name_box.Text = gui_strings[65];
            }
        }
        if (buy_equip_button.CallBackFn == do_buy_equip)
            sprintf(equip_cost_text, "%d", 100 * weapon_defs[selected_weapon + 1].Category);
        else
            sprintf(equip_cost_text, "%d", 100 * weapon_defs[selected_weapon + 1].Category >> 1);
        redraw_screen_flag = 1;
        edit_flag = 0;
        change_screen = 0;
    }
    if (change_screen == 6)
    {
        screentype = SCRT_RESEARCH;
        heading_box.Text = gui_strings[371];
        research_unkn21_box.Lines = 0;
        edit_flag = 0;
        change_screen = 0;
        redraw_screen_flag = 1;
    }
    if (change_screen == 7)
    {
        city_id = -1;
        screentype = SCRT_MISSION;
        brief_load_mission_info();
        redraw_screen_flag = 1;
        edit_flag = 0;
        change_screen = 0;
    }
    if (show_alert)
    {
        alert_box.Flags = 1;
        edit_flag = 0;
        old_screentype = screentype;
        show_alert = 0;
        screentype = SCRT_ALERTBOX;
        alert_OK_button.Flags |= 0x0001;
        redraw_screen_flag = 1;
    }

    if (redraw_screen_flag && !edit_flag)
    {
        mo_weapon = -1;
        redraw_screen_flag = 0;
        reload_background_flag = 1;
        if (screentype == SCRT_WORLDMAP)
        {
            open_brief = old_mission_brief;
            activate_cities(0);
        }
        else if (screentype == SCRT_MISSION)
        {
            activate_cities(open_brief);
        }

        brief_NETSCAN_COST_box.Flags = 0x0001;
        unkn32_box.Flags = 0x0001;
        heading_box.Flags = 0x0001;
        unkn35_box.Flags = 0x0001;
        unkn13_SYSTEM_button.Flags = 0x0001;
        unkn39_box.Flags = 0x0001;
        unkn29_box.Flags = 0x0001;
        unkn31_box.Flags = 0x0001;
        research_unkn20_box.Flags = 0x0001;
        research_progress_button.Flags = 0x0001;
        unkn30_box.Flags = 0x0001;
        net_users_box.Flags = 0x0001;
        net_groups_box.Flags = 0x0001;
        net_benefits_box.Flags = 0x0001;
        net_team_box.Flags = 0x0001;
        net_faction_box.Flags = 0x0001;
        net_comms_box.Flags = 0x0001;
        net_unkn21.Flags = 0x0001;
        net_protocol_box.Flags = 0x0001;
        weapon_slots.Flags = 0x0001;
        equip_name_box.Flags = 0x0001;
        slots_box.Flags = 0x0001;
        blokey_box.Flags = 0x0001;
        pause_unkn12_box.Flags = 0x0001;
        pause_unkn11_box.Flags = 0x0001;
        equip_cost_box.Flags = 0x0001;
        unkn34_box.Flags = 0x0001;
        unkn37_box.Flags = 0x0001 | 0x0100 | 0x0200;
        mod_list_box.Flags = 0x0001 | 0x0100 | 0x0200;
        agent_list_box.Flags = 0x0001 | 0x0100 | 0x0200;
        equip_list_box.Flags = 0x0001 | 0x0100 | 0x0200;
        equip_display_box.Flags = 0x0001 | 0x0100 | 0x0200;
        research_unkn21_box.Flags = 0x0001 | 0x0100 | 0x0200;
        unkn36_box.Flags = 0x0001 | 0x0100 | 0x0200;
        mission_text_box.Flags = 0x0001 | 0x0100 | 0x0200;
        unkn38_box.Flags = 0x0001 | 0x4000;
        int i;
        for (i = 0; i < 6; i++) {
            sysmnu_buttons[i].Flags = 0x0011;
        }
        for (i = 0; i < 5; i++) {
            unk11_menu[i].Flags = 0x0001;
        }
        for (i = 0; i < 4; i++) {
            unkn04_boxes[i].Flags = 0x0001;
        }
        for (i = 0; i < 7; i++) {
            options_audio_buttons[i].Flags = 0x0101;
        }
        for (i = 0; i < 14; i++) {
          options_gfx_buttons[i].Flags = 0x0101;
        }
        for (; i < 16; i++) {
          options_gfx_buttons[i].Flags = 0x0001;
        }

        storage_LOAD_button.Flags |= 0x0001;
        storage_SAVE_button.Flags |= 0x0001;
        main_quit_button.Flags |= 0x0001;
        pause_continue_button.Flags |= 0x0001;
        storage_NEW_MORTAL_button.Flags |= 0x0001;
        main_login_button.Flags |= 0x0001;
        pause_abort_button.Flags |= 0x0001;
        main_load_button.Flags |= 0x0001;
        main_map_editor_button.Flags |= 0x0001;
        buy_equip_button.Flags |= 0x0001;
        research_submit_button.Flags |= 0x0001;
        research_list_buttons[1].Flags |= 0x0001;
        unkn11_CANCEL_button.Flags |= 0x0001;
        research_list_buttons[0].Flags |= 0x0001;
        unkn12_WEAPONS_MODS_button.Flags |= 0x0001;
        net_SET2_button.Flags |= 0x0001;
        net_SET_button.Flags |= 0x0001;
        net_INITIATE_button.Flags |= 0x0001;
        unkn8_EJECT_button.Flags |= 0x0001;
        unkn10_SAVE_button.Flags |= 0x0001;
        net_groups_LOGON_button.Flags |= 0x0001;
        unkn10_CALIBRATE_button.Flags |= 0x0001;
        unkn10_CONTROLS_button.Flags |= 0x0001;
        brief_NETSCAN_button.Flags |= 0x0001;
        unkn2_ACCEPT_button.Flags |= 0x0001;
        unkn2_CANCEL_button.Flags |= 0x0001;
        net_protocol_option_button.Flags |= 0x0001;
        all_agents_button.Flags |= 0x0001;
        net_protocol_select_button.Flags |= 0x0001;
        net_unkn40_button.Flags |= 0x0001;
        if (screentype == SCRT_CRYO)
            equip_cost_box.Flags |= 0x0008;
        if (!game_projector_speed && screentype != SCRT_99)
            play_sample_using_heap(0, 113, 127, 64, 100, 0, 3u);
    }

    if (gameturn & 1)
    {
      if (++data_1c498e > 7)
          data_1c498e = 0;
      LbMouseChangeSprite(&unk3_sprites[data_1c498e + 1]);
    }

    if (lbKeyOn[KC_F12]) {
        lbKeyOn[KC_F12] = 0;
        LbPngSaveScreen("synII", lbDisplay.WScreen, display_palette, 0);
    }

    if ( start_into_mission || map_editor )
    {
        show_load_and_prep_mission();
    }
    else if (reload_background_flag)
    {
        reload_background();
        reload_background_flag = 0;
    }

    if (exit_game)
    {
        wait_for_sound_sample_finish(111);
        stop_sample_using_heap(0, 122);
    }
#endif
}

void draw_game(void)
{
    //ASM_draw_game(); return;
    switch (ingame.DisplayMode)
    {
    case DpM_UNKN_1:
        // No action
        break;
    case DpM_UNKN_32:
        PlayCDTrack(ingame.CDTrack);
        if ( !(ingame.Flags & 0x20) || !(gameturn & 0xF) )
        {
            show_game_engine();
            if ( ingame.Flags & 0x800 )
              gproc3_unknsub2();
            BAT_play();
            if ( execute_commands )
            {
                long tmp;
                gamep_unknval_16 = gamep_unknval_13;
                gamep_unknval_13 = 0;
                ++gamep_unknval_12;
                gamep_unknval_10 += gamep_unknval_16;
                gamep_unknval_15 = gamep_unknval_14;
                tmp = gamep_unknval_14 + gamep_unknval_11;
                gamep_unknval_14 = 0;
                gamep_unknval_11 = tmp;
            }
        }
        break;
    case DpM_UNKN_37:
        show_menu_screen();
        break;
    case DpM_UNKN_3A:
        gproc3_unknsub3(0);
        break;
    default:
        LOGERR("DisplayMode %d empty\n", (int)ingame.DisplayMode);
        break;
    }
}

void load_packet(void);
void game_process_sub02(void);
void process_packets(void);
void joy_input(void);
void game_process_sub04(void);
void process_packets(void);

void game_process(void)
{
    debug_m_sprite(193);
    LOGDBG("WSCREEN 0x%lx", (ulong)lbDisplay.WScreen);
    while ( !exit_game )
    {
      process_sound_heap();
      if ( lbKeyOn[KC_F8] && (lbShift & KMod_CONTROL))
      {
          lbKeyOn[KC_F8] = 0;
          LbScreenSetup(lbDisplay.ScreenMode, 640, 480, display_palette);
      }
      navi2_unkn_counter -= 2;
      if (navi2_unkn_counter < 0)
          navi2_unkn_counter = 0;
      if (navi2_unkn_counter > navi2_unkn_counter_max)
          navi2_unkn_counter_max = navi2_unkn_counter;
      if (keyboard_mode_direct)
          input_char = LbKeyboard();
      if (ingame.DisplayMode == DpM_UNKN_37) {
          LOGDBG("id=%d  trial alloc = %d turn %lu", 0, triangulation, gameturn);
      }
      if (!LbScreenIsLocked()) {
          while (LbScreenLock() != Lb_SUCCESS)
              ;
      }
      input();
      game_process_sub01();
      draw_game();
      debug_trace_turn_bound(gameturn + 100);
      load_packet();
      if ( ((active_flags_general_unkn01 & 0x8000) != 0) !=
        ((ingame.Flags & 0x8000) != 0) )
          LbPaletteSet(display_palette);
      active_flags_general_unkn01 = ingame.Flags;
      if ((ingame.DisplayMode == DpM_UNKN_32) ||
          (ingame.DisplayMode == DpM_UNKN_1) ||
          (ingame.DisplayMode == DpM_UNKN_3B))
          game_process_sub02();
      if (ingame.DisplayMode != DpM_UNKN_37)
          process_packets();
      joy_input();
      if (ingame.DisplayMode == DpM_UNKN_37) {
          swap_wscreen();
      }
      else if ( !(ingame.Flags & 0x20) || ((gameturn & 0xF) == 0) ) {
          LbScreenSwapClear(0);
      }
      game_process_sub04();
      if (unkn01_downcount > 0) /* orbital station explosion code */
      {
        unkn01_downcount--;
        LOGDBG("unkn01_downcount = %ld", unkn01_downcount);
        if ( unkn01_downcount == 40 ) {
            mapwho_unkn01(unkn01_pos_x, unkn01_pos_y);
        }
        else if (unkn01_downcount < 40) {
            unsigned short stl_y;
            unsigned short stl_x;
            stl_y = unkn01_pos_y + (LbRandomAnyShort() & 0xF) - 7;
            stl_x = unkn01_pos_x + (LbRandomAnyShort() & 0xF) - 7;
            new_bang_3(stl_x << 16, 0, stl_y << 16, 95);
            stl_y = unkn01_pos_y + (LbRandomAnyShort() & 0xF) - 7;
            stl_x = unkn01_pos_x + (LbRandomAnyShort() & 0xF) - 7;
            new_bang_3(stl_x << 16, 0, stl_y << 16, 95);
        }
      }
      gameturn++;
      game_process_sub09();
    }
    PacketRecord_Close();
    LbPaletteFade(NULL, 0x10u, 1);
}

void
game_quit(void)
{
    sound_finalise();
    LbBaseReset();
    exit(0);
}

void
game_transform_path_full(const char *file_name, char *buffer, size_t size)
{
    if (strncasecmp (file_name, SAVEGAME_PATH,
             sizeof (SAVEGAME_PATH) - 1) == 0)
    {
        snprintf (buffer, size, "%s" FS_SEP_STR "%s", GetDirectoryUser(),
          file_name + sizeof (SAVEGAME_PATH) - 1);
        return;
    }

    /* abort on absolute paths */
    if (file_name[0] == '\\' || file_name[0] == '/'
        || (strlen (file_name) >= 2 && file_name[1] == ':'))
    {
        snprintf (buffer, size, "%s", file_name);
        return;
    }

    snprintf (buffer, size, "%s" FS_SEP_STR "%s", GetDirectoryHdd(), file_name);
}

void
game_transform_path(const char *file_name, char *result)
{
    game_transform_path_full (file_name, result, FILENAME_MAX);
}

static void
game_update_full(bool wait)
{
    static TbClockMSec last_loop_time = 0;

    display_unlock();

    game_handle_sdl_events();

    if (wait)
    {
        TbClockMSec curr_time = LbTimerClock();
        TbClockMSec sleep_end = last_loop_time + 1000/GAME_FPS;
        // If we missed the normal sleep target (ie. there was a slowdown), reset the value and do not sleep
        if ((sleep_end < curr_time) || (sleep_end > curr_time + 1000/GAME_FPS)) {
            LOGNO("missed FPS target, last frame time %ld too far from current %ld", (ulong)sleep_end, (ulong)curr_time);
            sleep_end = curr_time;
        }
        LbSleepUntil(sleep_end);
        last_loop_time = sleep_end;
    }

    display_lock();
}

int game_hacky_update(void)
{
    game_update_full(false);
    return 1;
}

void
game_update(void)
{
    game_update_full(true);
}

void engine_reset(void)
{
  LbMemoryFree(engine_mem_alloc_ptr);
}

void host_reset(void)
{
#if 0
    asm volatile ("call ASM_host_reset\n"
        :  :  : "eax" );
#else
    StopCD();
    setup_heaps(1);
    FreeAudio();
    engine_reset();
    LbSpriteReset(m_sprites, m_sprites_end, m_spr_data);
    LbSpriteReset(pointer_sprites, pointer_sprites_end, pointer_data);
    LbMouseReset();
    LbKeyboardClose();
    LbScreenReset();
    LbNetworkReset();
#endif
}

void
game_reset(void)
{
    host_reset();
    free_texturemaps();
    LbDataFreeAll(unk02_load_files);
}

