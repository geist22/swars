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
#include "bfmath.h"
#include "bfline.h"
#include "rom.h"
#include "svesa.h"
#include "swlog.h"
#include "bflib_fmvids.h"
#include "bflib_snd_sys.h"
#include "bfscd.h"
#include "bflib_joyst.h"
#include "game_data.h"
#include "cybmod.h"
#include "display.h"
#include "dos.h"
#include "game.h"
#include "game_data.h"
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
#include "vehicle.h"
#include "weapon.h"

#include "timer.h"

#define SAVEGAME_PATH "qdata/savegame/"

#pragma pack(1)

struct GamePanel
{
  short X;
  short Y;
  short Spr;
  ushort Width;
  ushort Height;
  ushort Use;
  ushort Flags;
  ubyte ID;
  ubyte Type;
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
extern struct TbSprite *sprites_Icons0_0;
extern struct TbSprite *sprites_Icons0_0_end;
extern struct TbSprite *pop1_sprites;
extern struct TbSprite *pop1_sprites_end;
extern ubyte *pop1_data;

extern struct TbSprite *unk2_sprites;
extern struct TbSprite *unk2_sprites_end;
extern ubyte *m_spr_data;
extern ubyte *m_spr_data_end;
extern struct TbSprite *m_sprites;
extern struct TbSprite *m_sprites_end;

extern struct MyMapElement *game_my_big_map;
extern struct SingleFloorTexture *game_textures;
extern struct SingleTexture *game_face_textures;
extern struct SinglePoint *game_object_points;
extern ushort next_normal;
extern ushort next_quick_light;
extern ushort next_full_light;
extern ushort word_1531E0;
extern ushort next_face_texture;
extern ushort next_floor_texture;
extern ushort next_object_point;
extern ushort next_object_face;
extern ushort next_object_face4;
extern ushort next_object;
extern struct SingleObjectFace3 *game_object_faces;
extern struct SingleObject *game_objects;
extern struct QuickLight *game_quick_lights;
extern struct FullLight *game_full_lights;
extern struct Normal *game_normals;
extern ushort next_local_mat;
extern ushort next_special_face;
extern ushort next_special_face4;
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
extern ushort next_command;
extern ushort next_objective;
extern ushort next_used_lvl_objective;
extern ushort next_col_vect;
extern ubyte *game_user_heap;
extern struct SpecialPoint *game_screen_point_pool;
extern struct DrawItem *game_draw_list;
extern struct SortSprite *game_sort_sprites;
extern struct SortLine *game_sort_lines;
extern struct UnknBezEdit *bez_edit;
extern ubyte *spare_map_buffer;
extern struct Objective *game_used_lvl_objectives;
extern struct LevelMisc *game_level_miscs;
extern ushort same_type_head[290];
extern ushort word_176E38;

extern struct UnknGroup unkn_groups[32];

extern ulong stored_l3d_next_object[1];
extern ulong stored_l3d_next_object_face[1];
extern ulong stored_l3d_next_object_face4[1];
extern ulong stored_l3d_next_object_point[1];
extern ulong stored_l3d_next_normal[1];
extern ulong stored_l3d_next_face_texture[1];
extern ulong stored_l3d_next_floor_texture[1];
extern ulong stored_l3d_next_local_mat[1];
extern ulong stored_level3d_inuse;

extern ulong stored_g3d_next_object[1];
extern ulong stored_g3d_next_object_face[1];
extern ulong stored_g3d_next_object_face4[1];
extern ulong stored_g3d_next_object_point[1];
extern ulong stored_g3d_next_normal[1];
extern ulong stored_g3d_next_face_texture[1];
extern ulong stored_g3d_next_floor_texture[1];
extern ulong stored_g3d_next_local_mat[1];
extern ulong stored_global3d_inuse[1];

extern unsigned char *display_palette;
extern unsigned short unkn2_pos_x;
extern unsigned short unkn2_pos_y;
extern unsigned short unkn2_pos_z;
extern int data_1c8428;
extern const char *primvehobj_fname;
extern unsigned char textwalk_data[640];

extern ubyte byte_1CAB64[];
extern ubyte byte_1DB088[];
extern long dword_1DC36C;
extern long sound_heap_size;
extern struct SampleTable *sound_heap_memory;

extern ushort word_1810E4;
extern ubyte byte_1810E6[40];
extern ubyte byte_18110E[40];

extern ubyte research_on_weapons;// = true;

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
extern struct GamePanel *game_panel;
extern struct GamePanel game_panel_lo[];
extern struct GamePanel unknstrct7_arr2[];

extern ushort mission_strings_len;
extern ushort unkn3de_len;
extern ushort next_used_objective; // = 1;
extern ushort display_mode;
extern void *dword_177750;
extern ushort word_1C8446;

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
extern long dword_176D58;
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
  { "object_points",	&game_object_points,    10u, 20000, 0, 0, 0 },
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

// Original sizes of scanner in low res 64x62, high res 129x119

/** Width of the scanner map area, in percentage of screen. */
ubyte scanner_width_pct = 20;
/** Height of the scanner map area, in percentage of screen. */
ubyte scanner_height_pct = 25;

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

short angle_between_points(int x1, int z1, int x2, int z2)
{
  return LbArcTanAngle(x2 - x1, z1 - z2);
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

void bang_init(void)
{
    asm volatile ("call ASM_bang_init\n"
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

void debug_level(const char *text, int player)
{
    short thing;

    thing = things_used_head;
    while (thing != 0)
    {
        struct Thing *p_thing;

        p_thing = &things[thing];
        // TODO place debug/verification code
        thing = p_thing->LinkChild;
    }
}

void player_debug(int player)
{
    // TODO place debug/verification code
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

void draw_text(short x, short y, const char *text, ubyte colour)
{
    long scrn_w, scrn_h;
    ubyte *scr;

    if (x < 0 || y < 0)
        return;
    scrn_w = lbDisplay.GraphicsScreenWidth;
    scrn_h = lbDisplay.GraphicsScreenHeight;
    if (x > scrn_w - 1)
        return;
    if ( y > scrn_h - 1)
        return;

    scr = &lbDisplay.WScreen[x + scrn_w * y];
    prop_text(text, scr, scrn_w, colour);
}

void play_intro(void)
{
    char fname[FILENAME_MAX];

    LOGSYNC("Starting");
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

    LOGSYNC("Starting");
    mdinfo = LbScreenGetModeInfo(screen_mode_fmvid);
    if (mdinfo->Width == 0) {
        LOGERR("Movies video mode %d is invalid", (int)screen_mode_fmvid);
        return;
    }
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

int setup_heap_manager(struct SampleTable *smptable, size_t a2, const char *fname, unsigned int a4)
{
    int ret;
    asm volatile ("call ASM_setup_heap_manager\n"
        : "=r" (ret) : "a" (smptable), "d" (a2), "b" (fname), "c" (a4));
    return ret;
}

void reset_heaps(void)
{
}

void setup_heaps(int a1)
{
#if 0
    size_t ret;
    asm volatile ("call ASM_setup_heaps\n"
        : "=r" (ret) : "a" (a1));
    return ret;
#endif
    long sz;
    unsigned int n;

    if ((ingame.Flags & GamF_Unkn20000) == 0)
        return;

    switch (a1)
    {
    case 100:
        sz = sound_heap_size;
        setup_heap_manager(sound_heap_memory, sz, "sound/syncreds.dat", 1622);
        break;
    case 99:
        break;
    case 0:
        sz = 1500000;
        while ((sound_heap_memory == NULL) && (sz > 100))
        {
            sound_heap_memory = LbMemoryAlloc(sz);
            if (sound_heap_memory == NULL)
                sz -= 30000;
        }
        if ((sound_heap_memory == NULL) || sz < 120000) {
            ingame.Flags &= GamF_Unkn20000;
            break;
        }
        if (sz <= 500000)
            n = 822;
        else
            n = 1622;
        if (!setup_heap_manager(sound_heap_memory, sz, "sound/sound.dat", n))
            ingame.Flags &= GamF_Unkn20000;
        sound_heap_size = sz;
        break;
    case 2:
        sz = 1500000;
        if (!setup_heap_manager(sound_heap_memory, sz, "sound/sound.dat", 1622))
            ingame.Flags &= GamF_Unkn20000;
        sound_heap_size = sz;
        break;
    case 1:
    default:
        sz = 1500000;
        reset_heaps();
        LbMemoryFree(sound_heap_memory);
        sound_heap_size = sz;
        break;
    }
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

void global_3d_store(int action)
{
    if (action == 2)
    {
        if (stored_global3d_inuse[0])
            draw_text(100, 120, " GLOBAL 3d STORED ->INUSE", colour_lookup[2]);
    }
    else if (action == 1)
    {
        if (stored_global3d_inuse[0])
        {
            next_object = stored_g3d_next_object[0];
            next_object_face = stored_g3d_next_object_face[0];
            next_object_face4 = stored_g3d_next_object_face4[0];
            next_object_point = stored_g3d_next_object_point[0];
            next_normal = stored_g3d_next_normal[0];
            next_face_texture = stored_g3d_next_face_texture[0];
            next_floor_texture = stored_g3d_next_floor_texture[0];
            next_local_mat = stored_g3d_next_local_mat[0];
            stored_global3d_inuse[0] = 0;
        }
    } else
    {
        if (!stored_global3d_inuse[0])
        {
            stored_g3d_next_object[0] = next_object;
            stored_g3d_next_object_face[0] = next_object_face;
            stored_g3d_next_object_face4[0] = next_object_face4;
            stored_g3d_next_object_point[0] = next_object_point;
            stored_g3d_next_normal[0] = next_normal;
            stored_g3d_next_face_texture[0] = next_face_texture;
            stored_g3d_next_floor_texture[0] = next_floor_texture;
            stored_g3d_next_local_mat[0] = next_local_mat;
            stored_global3d_inuse[0] = 1;
        }
    }
}

TbBool is_command_any_until(struct Command *cmd)
{

    if (cmd->Type < PCmd_UNTIL_P_PERSUADED)
    {
        if (cmd->Type < PCmd_UNTIL_P_V_DEAD)
            return false;
        return true;
    }
    else if (cmd->Type > PCmd_UNTIL_OBJECT_DESTROYED)
    {
        if (cmd->Type < PCmd_UNTIL_OBJ)
        {
          if (cmd->Type != PCmd_UNTIL_TIME)
            return false;
        }
        else if (cmd->Type > PCmd_UNTIL_OBJ && cmd->Type != PCmd_UNTIL_G_NOT_SEEN)
        {
            return false;
        }
        return true;
    }
    return true;
}

void unkn_f_pressed_func(void)
{
    struct Command *gcmds;
    short thing;
    struct Thing *p_thing;
    short i;
    ushort cid;
    ushort prev_cid;

    gcmds = game_commands;
    thing = same_type_head[1];
    for (i = 0; true; i++)
    {
        if (thing == 0)
            break;
        if (i >= 1000) {
            LOGERR("Infinite loop in same type things list");
            break;
        }
        p_thing = &things[thing];
        cid = p_thing->U.UPerson.ComHead;
        prev_cid = 0;
        while (cid != 0)
        {
            if (!is_command_any_until(&gcmds[cid]))
            {
                if (prev_cid)
                    gcmds[prev_cid].Flags |= 0x20000;
                gcmds[cid].Flags |= 0x40000;
            }
            prev_cid = cid;
            cid = gcmds[cid].Next;
        }
        thing = p_thing->LinkSame;
    }
    game_commands = gcmds;
}

void fix_level_indexes(void)
{
    asm volatile ("call ASM_fix_level_indexes\n"
        :  :  : "eax" );
}

void build_same_type_headers(void)
{
    asm volatile ("call ASM_build_same_type_headers\n"
        :  :  : "eax" );
}

void level_misc_update(void)
{
    asm volatile ("call ASM_level_misc_update\n"
        :  :  : "eax" );
}

void load_mad_pc(ushort mapno)
{
    asm volatile ("call ASM_load_mad_pc\n"
        : : "a" (mapno));
}

void sanitize_cybmods_flags(short *modflg)
{
    asm volatile ("call ASM_sanitize_cybmods_flags\n"
        : : "a" (modflg));
}

void load_level_pc(ushort map, short level)
{
    asm volatile ("call ASM_load_level_pc\n"
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
    load_mad_pc(mapno);
    fill_floor_textures();
}

void change_brightness(ushort val)
{
    asm volatile ("call ASM_change_brightness\n"
        : : "a" (val));
}

int alt_at_point(ushort x, ushort z)
{
    int ret;
    asm volatile ("call ASM_alt_at_point\n"
        : "=r" (ret) : "a" (x), "d" (z));
    return ret;
}

void traffic_unkn_func_01(void)
{
    asm volatile ("call ASM_traffic_unkn_func_01\n"
        :  :  : "eax" );
}

void process_tank_turret(struct Thing *p_tank)
{
#if 0
    asm volatile ("call ASM_process_tank_turret\n"
        : : "a" (p_tank));
#else
    struct Thing *p_turret;
    int target_x, target_y;
    int turret;
    short angle;
    int dt_angle;

    turret = p_tank->U.UVehicle.SubThing;
    if (turret == 0) {
        p_tank->OldTarget = LbFPMath_PI+1;
        return;
    }
    p_turret = &things[turret];
    if ((p_tank->Flag & 0x20000000) != 0)
    {
        target_x = p_tank->U.UVehicle.TargetDX;
        target_y = p_tank->U.UVehicle.TargetDZ;
    }
    else
    {
        struct Thing *p_target;
        p_target = p_tank->PTarget;
        if (p_target == NULL)
        {
            p_tank->OldTarget = 20000;
            return;
        }
        target_x = p_target->X >> 8;
        target_y = p_target->Z >> 8;
    }
    angle = p_turret->U.UMGun.AngleY
        - angle_between_points(target_x, target_y, p_tank->X >> 8, p_tank->Z >> 8);
    if (angle < -LbFPMath_PI)
        angle += 2*LbFPMath_PI;
    else if (angle > LbFPMath_PI)
        angle -= 2*LbFPMath_PI;

    //TODO CONFIG how fast the tank can target could be a difficulty-related setting
    // Travel 1/8 of the distance in each game turn
    dt_angle = angle / 8;
    if (dt_angle > LbFPMath_PI/17)
        dt_angle = LbFPMath_PI/17;
    if (dt_angle < -LbFPMath_PI/17)
        dt_angle = -LbFPMath_PI/17;
    if (dt_angle == 0)
    {
        if (angle > 0)
            dt_angle = 1;
        if (angle < 0)
            dt_angle = -1;
    }

    // Despite being caused by the turret, we bind the sound samples to the vehicle part
    // of the tank. This is because turrets do not contain full position on map, so the
    // sound update would misplace the sound source if it was bound to the turret
    if ((p_turret->Flag2 & 0x0200) != 0)
    {
        if (dt_angle <= 1) {
            // Play rotation stop sample
            if (!IsSamplePlaying(p_tank->ThingOffset, 47, 0))
                play_dist_sample(p_tank, 47, 127, 0x40u, 100, 0, 1);
            p_turret->Flag2 &= ~0x0200;
        }
    }
    else
    {
        // Play rotation sample if moving over 1.2 degree per turn and the angle is not getting smaller.
        // Huge values of OldTarget (beyond pi) indicate that previously we had no target.
        if ((abs(dt_angle) >= LbFPMath_PI/75) && (p_tank->OldTarget < abs(angle) || p_tank->OldTarget > LbFPMath_PI)) {
            if (!IsSamplePlaying(p_tank->ThingOffset, 48, 0))
                play_dist_sample(p_tank, 48, 127, 0x40u, 100, 0, 1);
            p_turret->Flag2 |= 0x0200;
        }
    }

    p_turret->U.UMGun.AngleY -= dt_angle;
    p_tank->OldTarget = abs(angle);
    p_turret->U.UMGun.AngleY = (p_turret->U.UMGun.AngleY + 2*LbFPMath_PI) & LbFPMath_AngleMask;
#endif
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

void SCANNER_unkn_func_200(struct TbSprite *spr, int x, int y, ubyte col)
{
#if 0
    asm volatile (
      "call ASM_SCANNER_unkn_func_200\n"
        : : "a" (spr), "d" (x), "b" (y), "c" (col));
#else
    int xwind_beg;
    int xwind_end;
    int xwind_start;
    sbyte *inp;
    ubyte *oline;
    int opitch;
    int h;
    TbBool needs_window_bounding;

    xwind_beg = lbDisplay.GraphicsWindowX;
    xwind_end = lbDisplay.GraphicsWindowX + lbDisplay.GraphicsWindowWidth;
    xwind_start = lbDisplay.GraphicsWindowX + x;
    inp = (sbyte *)spr->Data;
    opitch = lbDisplay.GraphicsScreenWidth;
    oline = &lbDisplay.WScreen[opitch * (lbDisplay.GraphicsWindowY + y) + lbDisplay.GraphicsWindowX + x];
    if (xwind_start < lbDisplay.GraphicsWindowX) {
        if (xwind_start + 2 * spr->SWidth <= lbDisplay.GraphicsWindowX)
            return;
        needs_window_bounding = true;
    } else {
        if (xwind_start >= xwind_end)
            return;
        needs_window_bounding = (xwind_start + 2 * spr->SWidth > xwind_end);
    }

    if (!needs_window_bounding)
    {
        // Simplified and faster drawing when we do not have to check bounds
        for (h = 0; h < spr->SHeight; h++)
        {
            ubyte *o;

            o = oline;
            while (*inp)
            {
                int ival;
                int i;

                ival = *inp;
                if (ival < 0)
                {
                    inp++;
                    o -= 2 * ival;
                    continue;
                }
                inp += ival + 1;
                for (i = 0; i < ival; i++)
                {
                    o[0] = col;
                    o[opitch + 0] = col;
                    o[1] = col;
                    o[opitch + 1] = col;
                    o += 2;
                }
            }
            inp++;
            oline += 2 * opitch;
        }
    }
    else
    {
        for (h = 0; h < spr->SHeight; h++)
        {
            ubyte *o;
            int xwind_curr;

            o = oline;
            xwind_curr = xwind_start;
            while (*inp)
            {
                int ival;
                int i;

                ival = *inp;
                if (ival < 0)
                {
                    inp++;
                    o -= 2 * ival;
                    xwind_curr -= 2 * ival;
                    continue;
                }
                inp += ival + 1;
                for (i = 0; i < ival; i++)
                {
                    if (xwind_curr >= xwind_beg && xwind_curr < xwind_end) {
                        o[0] = col;
                        o[opitch] = col;
                    }
                    xwind_curr++;
                    o++;
                    if (xwind_curr >= xwind_beg && xwind_curr < xwind_end) {
                        o[0] = col;
                        o[opitch] = col;
                    }
                    xwind_curr++;
                    o++;
                }
            }
            inp++;
            oline += 2 * opitch;
        }
    }
#endif
}


void SCANNER_unkn_func_201(struct TbSprite *spr, int x, int y, ubyte *fade)
{
#if 0
    asm volatile (
      "call ASM_SCANNER_unkn_func_201\n"
        : : "a" (spr), "d" (x), "b" (y), "c" (fade));
#endif
    ubyte *oline;
    ubyte *dt;
    int ich;
    ubyte *o;

    oline = &lbDisplay.WScreen[lbDisplay.GraphicsScreenWidth * y + x];
    dt = spr->Data;
    for (ich = spr->SHeight; ich > 0; ich--)
    {
        o = oline;
        while (1)
        {
            ushort ftidx;
            sbyte len;

            len = *dt;
            if (!len)
                break;
            if (len > 0)
            {
                ++dt;
                while (len)
                {
                    ftidx = *dt;
                    *o = fade[ftidx];
                    ++dt;
                    ++o;
                    len--;
                }
            }
            else
            {
                len = -len;
                o += len;
                ++dt;
            }
        }
        ++dt;
        oline += lbDisplay.GraphicsScreenWidth;
    }
}

void SCANNER_unkn_func_202(struct TbSprite *spr, int x, int y, int ctr, int bri)
{
#if 0
    asm volatile (
      "push %4\n"
      "call ASM_SCANNER_unkn_func_202\n"
        : : "a" (spr), "d" (x), "b" (y), "c" (ctr), "g" (bri));
#endif
    ubyte *oline;
    ubyte *dt;
    int ich;
    ubyte *o;

    if ((x < 0) || (x > lbDisplay.PhysicalScreenWidth))
        return;
    if ((y < 0) || (y > lbDisplay.PhysicalScreenHeight))
        return;
    if ((x + spr->SWidth < 0) || (x + spr->SWidth > lbDisplay.PhysicalScreenWidth))
        return;
    if ((y + spr->SHeight < 0) || (y + spr->SHeight > lbDisplay.PhysicalScreenHeight))
        return;

    oline = &lbDisplay.WScreen[y * lbDisplay.GraphicsScreenWidth + x];
    dword_1DC36C = bri;
    dt = spr->Data;
    for (ich = spr->SHeight; ich > 0; ich--)
    {
        o = oline;
        while (1)
        {
            ushort ftsub, ftidx;
            sbyte len;

            len = *dt;
            if (!len)
                break;
            if (len > 0)
            {
                ++dt;
                while (len)
                {
                    ftidx = *dt++;
                    ftsub = dword_1DC36C + ((byte_1CAB64[ftidx] >> 1) + (byte_1CAB64[*o] >> 1));
                    ftidx |= byte_1DB088[ftsub] << 8;
                    *o++ = pixmap.fade_table[ftidx];
                    len--;
                }
            }
            else
            {
                len = -len;
                o += len;
                ++dt;
            }
        }
        ++dt;
        oline += lbDisplay.GraphicsScreenWidth;
    }
}

void SCANNER_unkn_func_203(int a1, int a2, int a3, int a4, ubyte a5, int a6, int a7)
{
    asm volatile (
      "push %6\n"
      "push %5\n"
      "push %4\n"
      "call ASM_SCANNER_unkn_func_203\n"
        : : "a" (a1), "d" (a2), "b" (a3), "c" (a4), "g" (a5), "g" (a6), "g" (a7));
}

void LbSpriteDraw_1(int x, int y, struct TbSprite *spr)
{
    asm volatile (
      "call ASM_LbSpriteDraw_1\n"
        : : "a" (x), "d" (y), "b" (spr));
}

void LbSpriteDraw_2(int x, int y, struct TbSprite *spr)
{
    asm volatile (
      "call ASM_LbSpriteDraw_2\n"
        : : "a" (x), "d" (y), "b" (spr));
}

void SCANNER_draw_new_transparent(void)
{
    asm volatile ("call ASM_SCANNER_draw_new_transparent\n"
        :  :  : "eax" );
}

void SCANNER_unkn_func_204(int a1, int a2, int a3)
{
    asm volatile (
      "call ASM_SCANNER_unkn_func_204\n"
        : : "a" (a1), "d" (a2), "b" (a3));
}

void SCANNER_unkn_func_205(void)
{
    asm volatile ("call ASM_SCANNER_unkn_func_205\n"
        :  :  : "eax" );
}

/**
 * Draw the button with standard palette, for selectable items.
 * @param px
 * @param py
 * @param spr_id
 */
void draw_new_panel_sprite_std(int px, int py, ulong spr_id)
{
    struct TbSprite *spr;
    int x, y;

    spr = &pop1_sprites[spr_id];
    if (lbDisplay.ScreenMode != 1) {
        x = px;
        y = py;
    } else {
        x = px >> 1;
        y = py >> 1;
    }
    if (ingame.PanelPermutation == -1)
        SCANNER_unkn_func_202(spr, x, y, ingame.Scanner.Contrast, ingame.Scanner.Brightness);
    else
        LbSpriteDraw_1(x, y, spr);
}

/**
 * Draw the button with darkened palette, like the item is unavailable.
 * @param px
 * @param py
 * @param spr_id
 */
void draw_new_panel_sprite_dark(int px, int py, ulong spr_id)
{
    struct TbSprite *spr;
    int x, y;

    spr = &pop1_sprites[spr_id];
    if (lbDisplay.ScreenMode != 1) {
        x = px;
        y = py;
    } else {
        x = px >> 1;
        y = py >> 1;
    }
    if (ingame.PanelPermutation == -1)
        SCANNER_unkn_func_202(spr, x, y, ingame.Scanner.Contrast, 8);
    else
        SCANNER_unkn_func_201(spr, x, y, &pixmap.fade_table[4096]);
}

/**
 * For weapons which contain up to four itemized parts, draw the items.
 *
 * @param a1
 * @param a2
 * @param a3
 * @param a4
 */
void draw_fourpack_items(int a1, ushort a2, short a3, short a4)
{
    asm volatile (
      "call ASM_draw_fourpack_items\n"
        : : "a" (a1), "d" (a2), "b" (a3), "c" (a4));
}

TbBool in_box(short x, short y, short box_x, short box_y, short box_w, short box_h)
{
    return x > box_x && x < box_x + box_w
        && y > box_y && y < box_y + box_h;
}

sbyte find_nth_weapon_held(ushort index, ubyte n)
{
    char ret;
    asm volatile ("call ASM_find_nth_weapon_held\n"
        : "=r" (ret) : "a" (index), "d" (n));
    return ret;
}

TbBool draw_panel_pickable_thing_below_agent(struct Thing *p_agent)
{
    struct SimpleThing *p_pickup;
    short thing;
    TbBool drawn;

    drawn = false;
    if (p_agent->Flag & 0x8000000)
    {
        ushort weptype;
        thing = p_agent->U.UPerson.Vehicle; // Seem to be weapon standing over rather than vehicle
        if (thing != 0)
            p_pickup = &sthings[thing];
        else
            p_pickup = NULL;
        if ((p_pickup != NULL) && (p_pickup->Type == 25)) {
            lbDisplay.DrawFlags = 0;
            weptype = p_pickup->U[0];
            if (weptype)
                draw_new_panel_sprite_std(548, 364, weapon_defs[weptype].Sprite & 0xFF);
            else
                draw_new_panel_sprite_std(540, 360, 70);
            draw_new_panel_sprite_std(540, 360, 12);
            drawn = true;
        } else {
            // FIXME a strange place for fixing state of an agent; should be moved to game world update
            p_agent->Flag &= ~0x8000000;
        }
    }
    return drawn;
}

TbBool draw_panel_pickable_thing_player_targeted(PlayerInfo *p_locplayer)
{
    ;
    struct SimpleThing *p_pickup;
    short thing;
    TbBool drawn;

    drawn = false;
    if (p_locplayer->TargetType == 5)
    {
        ushort weptype;
        thing = p_locplayer->field_102;
        if (thing < 0)
        {
            lbDisplay.DrawFlags = 0;
            p_pickup = &sthings[thing];
            weptype = p_pickup->U[0];
            if (weptype)
                draw_new_panel_sprite_std(548, 364, weapon_defs[weptype].Sprite & 0xFF);
            else
                draw_new_panel_sprite_std(548, 364, 70);
            draw_new_panel_sprite_std(540, 360, 12);
            drawn = true;
        }
    }
    return drawn;
}

/**
 * Counts weapons in given flags, returning total, amount below given weapon and above it.
 * To be used for displaying scrollable list of weapons where current weapon is always visible.
 *
 * @param p_ncarr_below
 * @param p_ncarr_above
 * @param weapons_carried
 * @param current_weapon
 * @return
 */
int count_weapons_in_flags(int *p_ncarr_below, int *p_ncarr_above, ulong weapons_carried, short current_weapon)
{
    int ncarried, ncarr_below, ncarr_above;
    ulong wepflags;
    ushort nweptype;

    ncarried = 0;
    ncarr_above = 0;
    ncarr_below = 0;
    wepflags = weapons_carried;

    for (nweptype = 0; nweptype < WEP_TYPES_COUNT; nweptype++)
    {
        if (!wepflags)
            break;
        if (wepflags & 1)
        {
            ncarried++;
            if (nweptype + 1 > current_weapon)
                ncarr_above++;
            if (nweptype + 1 < current_weapon)
                ncarr_below++;
        }
        wepflags >>= 1;
    }

    *p_ncarr_below = ncarr_below;
    *p_ncarr_above = ncarr_above;
    return ncarried;
}

TbBool draw_weapons_list_single(PlayerInfo *p_locplayer, ushort comcur, ulong weapons_carried, short current_weapon)
{
    ushort nshown;
    int weptype;
    int nchecked;
    ulong wepflags;
    int cy;
    int ncarried;
    int ncarr_below;
    int ncarr_above;
    TbBool ret;

    ret = false;
    ncarried = count_weapons_in_flags(&ncarr_below, &ncarr_above, weapons_carried, current_weapon);
    if (ncarried <= 6)
        ncarr_below = 0;
    else if (ncarr_below <= 4)
        ncarr_below = 0;
    else
        ncarr_below -= 4;

    nshown = 0;
    wepflags = weapons_carried;
    cy = 36;
    nchecked = 0;
    for (weptype = 0; weptype < WEP_TYPES_COUNT; weptype++, wepflags >>= 1)
    {
        if (wepflags == 0)
            break;
        if (wepflags & 1)
        {
            if (ncarr_below > nshown)
            {
                nshown++;
                if (nchecked == 6)
                    break;
                continue;
            }
            lbDisplay.DrawFlags = 0;

            if (!p_locplayer->WepDelays[comcur][weptype + 1] || (gameturn & 1))
            {
                if (nshown == 6)
                    draw_new_panel_sprite_std(22, cy, 13);
                else
                    draw_new_panel_sprite_std(22, cy, 12);
            }

            if (!p_locplayer->WepDelays[comcur][weptype + 1] || (gameturn & 1))
                draw_new_panel_sprite_std(30, cy + 4, weapon_defs[weptype+1].Sprite & 0xFF);
            if (weptype+1 == current_weapon)
            {
                lbDisplay.DrawFlags = 0;
                draw_new_panel_sprite_std(30, cy + 4, (weapon_defs[weptype+1].Sprite & 0xFF) + 27);
            }
            if (!lbDisplay.MRightButton)
            {
                short msy, msx;
                msy = lbDisplay.ScreenMode == 1 ? 2 * lbDisplay.RMouseY : lbDisplay.RMouseY;
                msx = lbDisplay.ScreenMode == 1 ? 2 * lbDisplay.RMouseX : lbDisplay.RMouseX;
                if (in_box(msx, msy, 22, cy, 76, 22))
                {
                    lbDisplay.DrawFlags = 0;
                    ret = true;
                    p_locplayer->PanelItem[mouser] = weptype + 1;
                    draw_new_panel_sprite_std(22, cy, 90);
                }
            }
            draw_fourpack_items(22, cy, comcur, weptype + 1);
            cy += 28;
            ++nchecked;
            ++nshown;
            if (nchecked == 6)
                break;
        }
    }
    return ret;
}

short draw_current_weapon_button(PlayerInfo *p_locplayer, short nagent)
{
    struct Thing *p_agent;
    ushort curwep, prevwep;
    short cx, cy;

    if (lbDisplay.ScreenMode == 1) {
        cy = 28;
        cx = 158 * nagent + 66;
    } else {
        cy = 29;
        cx = 157 * nagent + 65;
    }
    p_agent = p_locplayer->MyAgent[nagent];

    curwep = p_agent->U.UPerson.CurrentWeapon;
    prevwep = p_locplayer->PrevWeapon[nagent];
    if (!curwep && !prevwep) {
        prevwep = find_nth_weapon_held(p_agent->ThingOffset, 1);
        p_locplayer->PrevWeapon[nagent] = prevwep;
    }

    // Highlight button border on mouse over
    if (curwep || prevwep)
    {
        TbBool wep_highlight;
        short msx, msy;
        wep_highlight = false;
        if (!lbDisplay.MRightButton) {
            msx = lbDisplay.ScreenMode == 1 ? 2 * lbDisplay.RMouseX : lbDisplay.RMouseX;
            msy = lbDisplay.ScreenMode == 1 ? 2 * lbDisplay.RMouseY : lbDisplay.RMouseY;
            if (in_box(msx, msy, cx - 4, cy - 4, 76, 24))
                wep_highlight = true;
        }
        {
            msx = lbDisplay.ScreenMode == 1 ? 2 * lbDisplay.MMouseX : lbDisplay.MMouseX;
            msy = lbDisplay.ScreenMode == 1 ? 2 * lbDisplay.MMouseY : lbDisplay.MMouseY;
            if (in_box(msx, msy, cx - 4, cy - 4, 76, 24))
                wep_highlight = true;
        }
        if (wep_highlight)
        {
            if (curwep)
                p_locplayer->PanelItem[mouser] = curwep;
            else
                p_locplayer->PanelItem[mouser] = prevwep;
            draw_new_panel_sprite_std(cx - 8, cy - 4, 90);
        }
    }
    if (curwep) // Active weapon - draw lighted weapon shape
    {
        if (!p_locplayer->WepDelays[nagent][curwep] || (gameturn & 1))
        {
            struct Thing *p_agent;
            p_agent = p_locplayer->MyAgent[nagent];
            if (p_agent->State == PerSt_PROTECT_PERSON)
            {
                struct TbSprite *spr;
                if (ingame.PanelPermutation == -1)
                {
                    spr = &pop1_sprites[14];
                    if (lbDisplay.ScreenMode == 1)
                        SCANNER_unkn_func_202(spr, cx >> 1, cy >> 1,
                            ingame.Scanner.Contrast, ingame.Scanner.Brightness);
                    else
                        SCANNER_unkn_func_202(spr, cx, cy,
                            ingame.Scanner.Contrast, ingame.Scanner.Brightness);
                }
                draw_new_panel_sprite_dark(cx, cy, (weapon_defs[curwep].Sprite & 0xFF) + 27);
            }
            else
            {
                struct TbSprite *spr;
                if (ingame.PanelPermutation == -1)
                {
                    spr = &pop1_sprites[14];
                    if (lbDisplay.ScreenMode == 1)
                        SCANNER_unkn_func_202(spr, cx >> 1, cy >> 1,
                            ingame.Scanner.Contrast, ingame.Scanner.Brightness);
                    else
                        SCANNER_unkn_func_202(spr, cx, cy,
                            ingame.Scanner.Contrast, ingame.Scanner.Brightness);
                }
                draw_new_panel_sprite_std(cx, cy, (weapon_defs[curwep].Sprite & 0xFF) + 27);
            }
            draw_fourpack_items(cx - 8, cy - 4, nagent, curwep);
        }
    }
    else
    { // Weapon is hidden - draw with dark weapon shape
        curwep = prevwep;
        if (curwep && (!p_locplayer->WepDelays[nagent][curwep] || (gameturn & 1)))
        {
            struct Thing *p_agent;
            p_agent = p_locplayer->MyAgent[nagent];
            if (p_agent->State == PerSt_PROTECT_PERSON)
                draw_new_panel_sprite_dark(cx, cy, weapon_defs[curwep].Sprite & 0xFF);
            else
                draw_new_panel_sprite_std(cx, cy, weapon_defs[curwep].Sprite & 0xFF);
            draw_fourpack_items(cx - 8, cy - 4, nagent, curwep);
        }
    }
    return curwep;
}

TbBool draw_agent_weapons_selection(PlayerInfo *p_locplayer, struct Thing *p_agent, ubyte *cur_weapons, int nagent)
{
    int cx, cy;
    int weptype;
    int dcx, dcy;
    int nunk1;
    ulong wepflags;
    ushort comcur;
    ushort nshown;
    int nchecked;
    TbBool wep_highlight;
    TbBool ret;

    ret = false;
    nunk1 = 0;
    comcur = p_agent->U.UPerson.ComCur & 3;
    wepflags = p_agent->U.UPerson.WeaponsCarried;
    cy = 44;
    cx = 158 * nagent + 42;
    // Some weapons are not selectable
    wepflags &= ~(1 << (WEP_ENERGYSHLD-1));
    nshown = 0;
    nchecked = 0;
    for (weptype = 0; weptype < WEP_TYPES_COUNT; weptype++, wepflags >>= 1)
    {
        if (wepflags == 0)
            break;
        if ((wepflags & 1) == 0)
            continue;

        if (nunk1 > nshown || cur_weapons[comcur] == weptype + 1)
        {
            ++nshown;
            if (nchecked == 12)
                break;
            continue;
        }
        lbDisplay.DrawFlags = 0;
        if (!p_locplayer->WepDelays[comcur][weptype + 1] || (gameturn & 1))
        {
            if (!nchecked)
                draw_new_panel_sprite_std(cx, cy, 13);
            else
                draw_new_panel_sprite_std(cx, cy, 94);
        }

        if (!p_locplayer->WepDelays[comcur][weptype + 1] || (gameturn & 1))
        {
            if (!nchecked)
                draw_new_panel_sprite_std(cx + 24, cy + 12, weapon_defs[weptype + 1].Sprite & 0xFF);
            else
                draw_new_panel_sprite_std(cx + 8, cy + 8, weapon_defs[weptype + 1].Sprite & 0xFF);
        }
        dcx = 0;
        dcy = 0;
        if (!nchecked)
        {
            dcx = 14;
            dcy = 8;
        }

        wep_highlight = false;
        if (!lbDisplay.MRightButton) {
            short dch;
            short msx, msy;
            dch = nchecked ? 0 : 8;
            msx = lbDisplay.ScreenMode == 1 ? 2 * lbDisplay.RMouseX : lbDisplay.RMouseX;
            msy = lbDisplay.ScreenMode == 1 ? 2 * lbDisplay.RMouseY : lbDisplay.RMouseY;
            if (in_box(msx, msy, cx + dcx, cy + dcy, 76, 30 - dch))
                wep_highlight = true;
        }
        if (!wep_highlight) {
            short dch;
            short msx, msy;
            dch = nchecked ? 0 : 8;
            msx = lbDisplay.ScreenMode == 1 ? 2 * lbDisplay.MMouseX : lbDisplay.MMouseX;
            msy = lbDisplay.ScreenMode == 1 ? 2 * lbDisplay.MMouseY : lbDisplay.MMouseY;
            if (in_box(msx, msy, cx + dcx, cy + dcy, 76, 30 - dch))
                wep_highlight = true;
        }
        if (wep_highlight)
        {
            lbDisplay.DrawFlags = 0;
            p_locplayer->PanelItem[mouser] = weptype + 1;
            if (nchecked)
                draw_new_panel_sprite_std(cx, cy, 93);
            else
                draw_new_panel_sprite_std(cx, cy, 92);
            ret = 1;
        }

        if (nchecked)
            draw_fourpack_items(cx, cy + 4, comcur, weptype + 1);
        else
            draw_fourpack_items(cx + 16, cy + 8, comcur, weptype + 1);
        if (nchecked) {
            cy += 28;
        } else {
            cx += 16;
            cy += 32;
        }
        ++nchecked;
        ++nshown;
        if (nchecked == 12)
            break;
    }
    return ret;
}

TbBool func_1caf8(void)
{
#if 0
    TbBool ret;
    asm volatile ("call ASM_func_1caf8\n"
        : "=r" (ret) : );
    return ret;
#else
    TbBool ret;
    PlayerInfo *p_locplayer;
    struct Thing *p_agent;
    ubyte cur_weapons[4];
    int nagent;
    int panstate;

    p_locplayer = &players[local_player_no];
    if (p_locplayer->DoubleMode)
        p_agent = &things[p_locplayer->DirectControl[byte_153198-1]];
    else
        p_agent = &things[p_locplayer->DirectControl[0]];

    p_locplayer->PanelItem[mouser] = 0;
    ret = draw_panel_pickable_thing_below_agent(p_agent);
    if (!ret)
        draw_panel_pickable_thing_player_targeted(p_locplayer);

    if (ingame.PanelPermutation >= 0)
    {
        ushort comcur;
        comcur = p_agent->U.UPerson.ComCur & 3;
        ret = draw_weapons_list_single(p_locplayer, comcur,
            p_agent->U.UPerson.WeaponsCarried, p_agent->U.UPerson.CurrentWeapon);
    }
    else
    {
        for (nagent = 0; nagent < playable_agents; nagent++)
        {
            ushort curwep;
            p_agent = p_locplayer->MyAgent[nagent];
            if ((p_agent->Flag & 0x0002) != 0) {
                cur_weapons[nagent] = 0;
                continue;
            }
            curwep = draw_current_weapon_button(p_locplayer, nagent);
            cur_weapons[nagent] = curwep;
        }

        ret = false;
        panstate = p_locplayer->PanelState[mouser];
        if (panstate >= 1 && panstate <= 8)
        {
            nagent = (panstate - 1) & 3;
            p_agent = p_locplayer->MyAgent[nagent];
            ret |= draw_agent_weapons_selection(p_locplayer, p_agent, cur_weapons, nagent);

        }
    }

    lbDisplay.DrawFlags = 0;
    return ret;
#endif
}

void func_1efb8(void)
{
    asm volatile ("call ASM_func_1efb8\n"
        :  :  : "eax" );
}

void func_702c0(int a1, int a2, int a3, int a4, int a5, ubyte a6)
{
    asm volatile (
      "push %5\n"
      "push %4\n"
      "call ASM_func_702c0\n"
        : : "a" (a1), "d" (a2), "b" (a3), "c" (a4), "g" (a5), "g" (a6));
}

void draw_shield_level(short x, short y, ushort w, ushort h)
{
#if 0
    asm volatile (
      "call ASM_draw_shield_level\n"
        : : "a" (x), "d" (y), "b" (w), "c" (h));
#else
    ubyte m;
    long waftx, wafty;
    ushort tmx, tmy;
    struct EnginePoint point4;
    struct EnginePoint point2;
    struct EnginePoint point1;
    struct EnginePoint point3;

    m = 1;
    if (lbDisplay.ScreenMode == 1)
        m = 0;
    point1.pp.X = x << m;
    point1.pp.Y = y << m;
    point4.pp.X = (x + w) << m;
    point4.pp.Y = y << m;
    point2.pp.Y = (y + h) << m;
    point2.pp.X = (x + w - 3) << m;
    point3.pp.Y = (y + h) << m;
    point3.pp.X = (x - 3) << m;

    // The shield bar is animated, even if it's not possible to see
    waftx = waft_table[(gameturn >> 3) & 31];
    wafty = waft_table[(gameturn + 16) & 31];
    tmx = ((waftx + 30) >> 1);
    tmy = ((wafty + 30) >> 3) + 64;
    point1.pp.U = tmx << 16;
    point4.pp.U = (tmx + 64) << 16;
    point2.pp.U = (tmx + 64) << 16;
    point1.pp.V = tmy << 16;
    point4.pp.V = tmy << 16;
    point2.pp.V = (tmy + 8) << 16;
    point3.pp.U = tmx << 16;
    point3.pp.V = (tmy + 8) << 16;

    point1.pp.S = 0;
    point2.pp.S = 0;
    point3.pp.S = 0;
    point4.pp.S = 0;

    vec_mode = 18;
    vec_map = dword_1AA280;
    draw_trigpoly(&point1.pp, &point4.pp, &point3.pp);
    if (vec_mode == 2)
        vec_mode = 27;
    draw_trigpoly(&point4.pp, &point2.pp, &point3.pp);
#endif
}

void draw_health_level(short x, short y, ushort w, ushort h, short lv, ushort lvmax, ubyte col, ubyte a8)
{
#if 0
    asm volatile (
      "push %7\n"
      "push %6\n"
      "push %5\n"
      "push %4\n"
      "call ASM_draw_health_level\n"
        : : "a" (x), "d" (y), "b" (w), "c" (h), "g" (lv), "g" (lvmax), "g" (col), "g" (a8));
#else
    short cw, ch;

    if ((lv <= 0) || (lvmax == 0))
        return;

    cw = w * lv / lvmax;
    if (a8)
    {
        draw_shield_level(x, y, cw, h);
    }
    else if (lbDisplay.ScreenMode == 1)
    {
        short cx, cy;
        cx = x;
        cy = y;
        for (ch = h; ch > 0; ch--)
        {
            if (lbDisplay.ScreenMode == 1)
                LbDrawLine(2 * cx >> 1, 2 * cy >> 1, 2 * (cx + cw) >> 1, 2 * cy >> 1, col);
            else
                LbDrawLine(2 * cx, 2 * cy, 2 * (cx + cw), 2 * cy, col);
            --cx;
            ++cy;
        }
    }
    else
    {
        short cx, cy;
        cx = 2 * x;
        cy = 2 * y;
        cw *= 2;
        for (ch = 2 * h; ch > 0; ch--)
        {
            if (lbDisplay.ScreenMode == 1)
                LbDrawLine(cx >> 1, cy >> 1, (cx + cw) >> 1, cy >> 1, col);
            else
                LbDrawLine(cx, cy, cx + cw, cy, col);
            --cx;
            ++cy;
        }
    }
#endif
}

void func_1eae4(int x, short y, int w, ushort h, short lv, ushort lvmax, ubyte col, int a8)
{
#if 0
    asm volatile (
      "push %7\n"
      "push %6\n"
      "push %5\n"
      "push %4\n"
      "call ASM_func_1eae4\n"
        : : "a" (x), "d" (y), "b" (w), "c" (h), "g" (lv), "g" (lvmax), "g" (col), "g" (a8));
#else
    short cw, ch;

    if ((lv <= 0) || (lvmax == 0))
        return;

    ch = h * lv / lvmax;
    if (lbDisplay.ScreenMode == 1)
    {
        short cx, cy;
        cx = x;
        cy = y;
        for (cw = w; cw > 0; cw--)
        {
            short cy1, cy2;
            cy1 = cy + h;
            cy2 = cy + h - ch;
            if (lbDisplay.ScreenMode == 1)
                SCANNER_unkn_func_203(2 * cx >> 1, 2 * cy1 >> 1, 2 * cx >> 1, 2 * cy2 >> 1, col,
                    ingame.Scanner.Contrast, ingame.Scanner.Brightness);
            else
                SCANNER_unkn_func_203(2 * cx, 2 * cy1, 2 * cx, 2 * cy2, col,
                    ingame.Scanner.Contrast, ingame.Scanner.Brightness);
            ++cx;
            ++cy;
        }
    }
    else
    {
        short cx, cy;
        cx = 2 * x;
        cy = 2 * y;
        for (cw = 2 * w; cw > 0; cw--)
        {
            short cy1, cy2;
            cy1 = 2*h + cy;
            cy2 = 2*h + cy - 2*ch;
            if (lbDisplay.ScreenMode == 1)
                LbDrawLine(cx >> 1, cy1 >> 1, cx >> 1, cy2 >> 1, col);
            else
                LbDrawLine(cx, cy1, cx, cy2, col);
            ++cx;
            ++cy;
        }
    }
#endif
}

void func_1ec68(short a1, short a2, ushort a3, int a4, int a5)
{
    asm volatile (
      "push %4\n"
      "call ASM_func_1ec68\n"
        : : "a" (a1), "d" (a2), "b" (a3), "c" (a4), "g" (a5));
}

void func_1ee14(short a1, short a2, short a3, short a4, int a5, int a6)
{
    asm volatile (
      "push %5\n"
      "push %4\n"
      "call ASM_func_1ee14\n"
        : : "a" (a1), "d" (a2), "b" (a3), "c" (a4), "g" (a5), "g" (a6));
}

void draw_unkn1_rect(int x1, int y1, int len_mul, int len_div)
{
    asm volatile (
      "call ASM_draw_unkn1_rect\n"
        : : "a" (x1), "d" (y1), "b" (len_mul), "c" (len_div));
}

void draw_new_panel()
{
#if 0
    asm volatile ("call ASM_draw_new_panel\n"
        :  :  : "eax" );
#else
    int i;
    PlayerInfo *p_locplayer;

    p_locplayer = &players[local_player_no];
    // If an agent has a medkit, use the sprite with lighted cross
    for (i = 0; i < playable_agents; i++)
    {
        struct Thing *p_agent;
        p_agent = p_locplayer->MyAgent[i];
        if (person_carries_weapon(p_agent, WEP_MEDI2) || person_carries_weapon(p_agent, WEP_MEDI1))
            game_panel[8+i].Spr = 96;
        else
            game_panel[8+i].Spr = 95;
    }

    { // If supershield is enabled for the current agent, draw energy bar in red
        struct Thing *p_agent;
        p_agent = &things[p_locplayer->DirectControl[0]];
        if ((p_agent->Flag & 0x100) != 0)
        {
            game_panel[16].Spr = 99;
            if (lbDisplay.ScreenMode != 1)
                game_panel[17].Spr = 106;
        }
        else
        {
            game_panel[16].Spr = 10;
            if (lbDisplay.ScreenMode != 1)
                game_panel[17].Spr = 105;
        }
    }

    for (i = 0; true; i++)
    {
        struct GamePanel *panel;

        panel = &game_panel[i];
        if (panel->Spr < 0)
          break;
        if (panel->Spr == 0)
          continue;
        lbDisplay.DrawFlags = 0;

        if ( panel->Type != 1 && panel->Type != 6 && panel->Type != 5 )
        {
            draw_new_panel_sprite_std(panel->X, panel->Y, panel->Spr);
        }
        else
        {
            TbBool is_visible;

            is_visible = true;
            if (panel->Type == 5 && panel->ID < playable_agents)
            {
                struct Thing *p_agent;
                ubyte weapon;

                p_agent = p_locplayer->MyAgent[panel->ID];
                if (p_agent < &things[0] || p_agent > &things[1000])
                    break;
                weapon = p_agent->U.UPerson.CurrentWeapon;
                if (weapon == 0)
                    weapon = p_locplayer->PrevWeapon[panel->ID];
                is_visible = !p_locplayer->WepDelays[panel->ID][weapon] || (gameturn & 1);
            }

            if (p_locplayer->DoubleMode)
            {
                struct Thing *p_agent;
                if (!is_visible)
                    continue;
                if (panel->ID >= playable_agents)
                    continue;
                p_agent = p_locplayer->MyAgent[panel->ID];
                if (p_agent->Flag & 0x0002)
                    continue;
                draw_new_panel_sprite_std(panel->X, panel->Y, panel->Spr);
            }
            else
            {
                struct Thing *p_agent;
                if (!is_visible)
                    continue;
                if (panel->ID >= playable_agents)
                    continue;
                p_agent = p_locplayer->MyAgent[panel->ID];
                if (p_agent->Flag & 0x0002)
                    continue;

                if (panel->Type == 5) {
                    ubyte weapon;

                    weapon = p_agent->U.UPerson.CurrentWeapon;
                    if (weapon == 0)
                        weapon = p_locplayer->PrevWeapon[panel->ID];
                    if (weapon == 0)
                        continue;
                }

                if ((p_agent->State == PerSt_PROTECT_PERSON) || (p_agent->Flag2 & 0x10000000))
                    draw_new_panel_sprite_dark(panel->X, panel->Y, panel->Spr);
                else
                    draw_new_panel_sprite_std(panel->X, panel->Y, panel->Spr);
            }
        }
    }

    if (gameturn & 4)
    {
        int x, cc;
        int agent;
        struct Thing *p_agent;

        x = 0;
        agent = p_locplayer->DoubleMode ? p_locplayer->DirectControl[byte_153198-1] : p_locplayer->DirectControl[0];
        p_agent = &things[agent];
        if ((p_agent->Flag & 2) == 0 && (p_agent->Flag2 & 0x800) == 0)
        {
            cc = p_agent->U.UPerson.ComCur & 3;
            if (lbDisplay.ScreenMode == 1)
            {
                switch (cc)
                {
                case 0:
                  x = 4;
                  break;
                case 1:
                  x = 154;
                  break;
                case 2:
                  x = 308;
                  break;
                case 3:
                  x = 472;
                  break;
                }
            }
            else
            {
                switch (cc)
                {
                case 0:
                  x = 4;
                  break;
                case 1:
                  x = 153;
                  break;
                case 2:
                  x = 306;
                  break;
                case 3:
                  x = 469;
                  break;
                }
            }
            draw_new_panel_sprite_std(x, 2, 6 + cc);
        }
    }
    lbDisplay.DrawFlags = 0;

    if (!func_1caf8())
    {
        if (ingame.Flags & 0x200) {
            ulong md, y;
            md = p_locplayer->UserInput[0].ControlMode & 0x1FFF;
            if (md == 1 && pktrec_mode != PktR_PLAYBACK) {
                y = alt_at_point(mouse_map_x, mouse_map_z);
                func_702c0(mouse_map_x, y >> 5, mouse_map_z, 64, 64, colour_lookup[2]);
            }
        }
    }
    func_1efb8();

    // Fill the left energy bar
    {
        int agent;
        struct Thing *p_agent;
        int lv, lvmax, col, w;

        agent = p_locplayer->DoubleMode ? p_locplayer->DirectControl[byte_153198-1] : p_locplayer->DirectControl[0];
        p_agent = &things[agent];
        if ((p_agent->U.UPerson.Energy < 50) && (gameturn & 1))
            col = 2;
        else
            col = 1;
        lvmax = p_agent->U.UPerson.MaxEnergy;
        lv = p_agent->U.UPerson.Energy;
        if (lbDisplay.ScreenMode == 1)
            w = 0;
        else
            w = 45;
        func_1eae4(3, 30, 4, 54+w, lv, lvmax, colour_lookup[col], 0);
    }

    // Fill the agents bar at top
    for (i = 0; i < playable_agents; i++)
    {
        struct Thing *p_agent;
        int lv, lvmax, x, w;

        p_agent = p_locplayer->MyAgent[i];
        if ((p_agent->Flag & 0x2000) == 0) {
            LOGERR("Agent %d unexpected flags", i);
            return;
        }
        if ((p_agent->Flag & 0x0002) == 0)
        {
            x = 79 * i + 27;
            // Draw health level
            lv = p_agent->Health;
            lvmax = p_agent->U.UPerson.MaxHealth;
            if (lv <= lvmax) { // Normal health amount
                draw_health_level(x, 2, 44, 2, lv, lvmax, colour_lookup[1], 0);
            } else { // Health reinforced beyond max is drawn in red
                draw_health_level(x, 2, 44, 2, lvmax, lvmax, colour_lookup[1], 0);
                draw_health_level(x, 2, 44, 2, lv - lvmax, lvmax, colour_lookup[2], 0);
            }
            // Draw shield level over health
            lv = p_agent->U.UPerson.ShieldEnergy;
            draw_health_level(x, 2, 44, 2, lv, 0x400, colour_lookup[1], 1);
            // Draw drug level aka mood (or just a red line if no drugs)
            w = game_panel[4+i].Width;
            x = game_panel[4+i].X >> 1;
            func_1ec68(x, 6, w, 3, p_agent->U.UPerson.Mood);
            // Draw stamina level which caps the mood level
            lv = p_agent->U.UPerson.Stamina;
            lvmax = p_agent->U.UPerson.MaxStamina;
            func_1ee14(x, 6, w, 2, lv, lvmax);
            if (lbDisplay.ScreenMode == 1)
                x = 158 * i + 54;
            else
                x = 157 * i + 54;
            lv = p_agent->U.UPerson.Energy;
            lvmax = p_agent->U.UPerson.MaxEnergy;
            draw_unkn1_rect(x + 80, 18, lv, lvmax);
        }
    }

    ingame.Scanner.MX = engn_xc >> 7;
    ingame.Scanner.MZ = engn_zc >> 7;
    ingame.Scanner.Angle = 2047 - ((dword_176D58 >> 5) & 0x7FF);
    SCANNER_draw_new_transparent();

    // Objective text, or net players list
    {
        int x, y, w;
        x = ingame.Scanner.X1 - 1;
        if (x < 0)
            x = 0;
        if (lbDisplay.GraphicsScreenWidth >= 640)
            y = lbDisplay.GraphicsScreenHeight - 18;
        else
            y = lbDisplay.GraphicsScreenHeight - 9;
        if (in_network_game) {
            SCANNER_unkn_func_205();
            w = lbDisplay.PhysicalScreenWidth;
        } else {
            // original width 67 low res, 132 high res
            w = ingame.Scanner.X2 - ingame.Scanner.X1 + 3;
        }
        SCANNER_unkn_func_204(x, y, w);
    }

    // Thermal vision button light
    if ((ingame.Flags & 0x8000) != 0) {
        int x;
        x = 238;
        if (lbDisplay.ScreenMode != 1)
            x += 89;
        draw_new_panel_sprite_std(4, x, 91);
    }
#endif
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
        // Play applause sample
        if (((LbRandomAnyShort() & 0xF) == 0) && (data_155704 == -1 || !IsSamplePlaying(0, data_155704, NULL)) )
        {
            //TODO Why we're not storing new value of data_155704 ??
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
    int hlimit, cutout;

    hlimit = sizeof(ingame.Scanner.Width)/sizeof(ingame.Scanner.Width[0]);
    if (height >= hlimit)
        height = hlimit - 1;
    cutout = 24;

    ingame.Scanner.X1 = 1;
    ingame.Scanner.Y1 = lbDisplay.GraphicsScreenHeight - margin - height;
    ingame.Scanner.X2 = ingame.Scanner.X1 + width;
    ingame.Scanner.Y2 = ingame.Scanner.Y1 + height;

    for (i = 0; i + ingame.Scanner.Y1 <= ingame.Scanner.Y2; i++) {
        ingame.Scanner.Width[i] = min(width - cutout + i, width);
    }
}

void srm_scanner_size_update(void)
{
    int margin, width, height;

    width = lbDisplay.GraphicsScreenWidth * scanner_width_pct / 100;
    height = lbDisplay.GraphicsScreenHeight * scanner_height_pct / 100;
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

void init_scanner(void)
{
    ubyte col;

    if (ingame.PanelPermutation != 2 && ingame.PanelPermutation != -3)
        col = 2;
    else
        col = 1;
    SCANNER_set_colour(col);
    dword_1AA5C4 = 0;
    dword_1AA5C8 = 0;
    SCANNER_fill_in();
    ingame.Scanner.Brightness = 8;
    ingame.Scanner.Contrast = 5;
    SCANNER_width = ingame.Scanner.Width;
    ingame.Scanner.Zoom = 128;
    ingame.Scanner.Angle = 0;
    srm_scanner_size_update();
    SCANNER_init();
}

/**
 * Updates engine parameters for best display for current video mode within the tactical mission.
 */
void adjust_mission_engine_to_video_mode(void)
{
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
    srm_scanner_size_update();
}

void video_mode_switch_to_next(void)
{
    TbScreenMode nmode;

    if (lbDisplay.ScreenMode == screen_mode_game_lo)
        nmode = screen_mode_game_hi;
    else
        nmode = screen_mode_game_lo;
    LOGSYNC("Switching to mode %d", (int)nmode);

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
    p_person->State = PerSt_WAIT;
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

            p_agent->U.UPerson.MaxHealth = PERSON_MAX_HEALTH_LIMIT;
            p_agent->Health = 2 * p_agent->U.UPerson.MaxHealth; // double health - fill red bar
            p_agent->U.UPerson.MaxEnergy = 32000;
            p_agent->U.UPerson.Energy = p_agent->U.UPerson.MaxEnergy;
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

    LOGSYNC("Starting");
    //sprintf(locstr, "%sSound", cd_drive); -- unused

    audOpts.SoundDataPath = "Sound";
    audOpts.SoundDriverPath = "Sound";
    audOpts.IniPath = "Sound";
    audOpts.AutoScan = 1;
    audOpts.StereoOption = 1;
    audOpts.DisableLoadSounds = 1;
    audOpts.InitRedbookAudio = 2;
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
#if 0
    asm volatile ("call ASM_load_missions\n"
        : : "a" (num));
#else
    TbFileHandle fh;
    char locstr[52];
    ulong fmtver;
    int i;

    fmtver = 1;
    sprintf(locstr, "%s/all%03d.mis", game_dirs[DirPlace_Levels].directory, num);
    fh = LbFileOpen(locstr, Lb_FILE_MODE_READ_ONLY);
    if (fh != INVALID_FILE)
    {
        LbFileRead(fh, &fmtver, sizeof(ulong));
        LbFileRead(fh, &mission_strings_len, sizeof(ushort));
        LbFileRead(fh, engine_mem_alloc_ptr + engine_mem_alloc_size - 64000, mission_strings_len);
        LbFileRead(fh, &next_mission, sizeof(ushort));
        LbFileRead(fh, mission_list, sizeof(struct Mission) * next_mission);
        LbFileRead(fh, &next_used_objective, sizeof(ushort));
        LbFileRead(fh, game_used_objectives, sizeof(struct Objective) * next_used_objective);
        if (fmtver > 30)
            LbFileRead(fh, engine_mem_alloc_ptr + engine_mem_alloc_size - 1320 - 33, 1320);
        LbFileClose(fh);
        display_mode = 0;
    }
    else
    {
        LOGERR("Missions file could not be opened");
    }

    if (!in_network_game)
        LbMemorySet(mission_status, 0, 120 * sizeof(struct MissionStatus));
    if (fmtver < 2)
    {
        for (i = 1; i < next_mission; i++)
          mission_list[i].ReLevelNo = 0;
    }
    for (i = 1; i < next_mission; i++)
        mission_list[i].Complete = 0;
#endif
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
                p_person->State = PerSt_DEAD;
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
        p_person->State = PerSt_NONE;
        { // Why are we tripling the health?
            uint health;
            health = 3 * p_person->Health;
            if (health > PERSON_MAX_HEALTH_LIMIT)
                health = PERSON_MAX_HEALTH_LIMIT;
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

    load_level_pc(-new_level_no, mission_no);
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
    read_weapons_conf_file();
    read_cybmods_conf_file();
    bang_init();
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
            ubyte *ptr;
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

void gproc3_unknsub3(int a1)
{
    // Empty
}

void draw_line_purple_list(int x1, int y1, int x2, int y2, int colour)
{
    asm volatile (
      "push %4\n"
      "call ASM_draw_line_purple_list\n"
        : : "a" (x1), "d" (y1), "b" (x2), "c" (y2), "g" (colour));
}

void draw_box_purple_list(int x, int y, ulong width, ulong height, int colour)
{
    asm volatile (
      "push %4\n"
      "call ASM_draw_box_purple_list\n"
        : : "a" (x), "d" (y), "b" (width), "c" (height), "g" (colour));
}

void draw_text_purple_list2(int x, int y, const char *text, ushort line)
{
    asm volatile (
      "call ASM_draw_text_purple_list2\n"
        : : "a" (x), "d" (y), "b" (text), "c" (line));
}

void draw_sprite_purple_list(int x, int y, struct TbSprite *sprite)
{
    asm volatile (
      "call ASM_draw_sprite_purple_list\n"
        : : "a" (x), "d" (y), "b" (sprite));
}

void copy_box_purple_list(long x, long y, ulong width, ulong height)
{
    asm volatile (
      "call ASM_copy_box_purple_list\n"
        : : "a" (x), "d" (y), "b" (width), "c" (height));
}

void draw_unkn20_subfunc_01(int x, int y, char *text, ubyte a4)
{
    asm volatile (
      "call ASM_draw_unkn20_subfunc_01\n"
        : : "a" (x), "d" (y), "b" (text), "c" (a4));
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

ubyte show_title_box(struct ScreenTextBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_title_box\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_unkn38_box(struct ScreenTextBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_unkn38_box\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte ac_show_title_box(struct ScreenTextBox *box);
ubyte ac_show_unkn38_box(struct ScreenTextBox *box);

void check_buy_sell_button(void)
{
    asm volatile ("call ASM_check_buy_sell_button\n"
        :  :  : "eax" );
}

ubyte select_all_agents(ubyte click)
{
    selected_agent = 4;
    check_buy_sell_button();
    return 1;
}

ubyte do_net_protocol_option(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_net_protocol_option\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_net_unkn40(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_net_unkn40\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_serial_speed_switch(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_serial_speed_switch\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte change_panel_permutation(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_change_panel_permutation\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte change_trenchcoat_preference(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_change_trenchcoat_preference\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_unkn10_CALIBRATE(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_unkn10_CALIBRATE\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_unkn10_SAVE(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_unkn10_SAVE\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_unkn10_CONTROLS(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_unkn10_CONTROLS\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte alert_OK(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_alert_OK\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_net_SET2(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_net_SET2\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_net_SET(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_net_SET\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_net_INITIATE(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_net_INITIATE\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_net_groups_LOGON(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_net_groups_LOGON\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_unkn8_EJECT(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_unkn8_EJECT\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte accept_mission(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_accept_mission\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_unkn1_CANCEL(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_unkn1_CANCEL\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_unkn2_CANCEL(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_unkn2_CANCEL\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_unkn2_ACCEPT(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_unkn2_ACCEPT\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_sysmnu_button(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_sysmnu_button\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_storage_NEW_MORTAL(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_storage_NEW_MORTAL\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte load_game_slot(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_load_game_slot\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte save_game_slot(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_save_game_slot\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte main_do_my_quit(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_main_do_my_quit\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte main_do_login_1(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_main_do_login_1\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte goto_savegame(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_goto_savegame\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_abort_2(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_abort_2\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_login_2(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_login_2\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte main_do_map_editor(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_main_do_map_editor\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte brief_do_netscan_enhance(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_brief_do_netscan_enhance\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_unkn11_CANCEL(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_unkn11_CANCEL\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_buy_equip(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_buy_equip\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte sell_equipment(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_sell_equipment\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_research_submit(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_research_submit\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_research_suspend(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_research_suspend\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte do_unkn12_WEAPONS_MODS(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_unkn12_WEAPONS_MODS\n"
        : "=r" (ret) : "a" (click));
    return ret;
}
ubyte ac_select_all_agents(ubyte click);
ubyte ac_do_net_protocol_option(ubyte click);
ubyte ac_do_net_unkn40(ubyte click);
ubyte ac_do_serial_speed_switch(ubyte click);
ubyte ac_change_panel_permutation(ubyte click);
ubyte ac_change_trenchcoat_preference(ubyte click);
ubyte ac_do_unkn10_CALIBRATE(ubyte click);
ubyte ac_do_unkn10_SAVE(ubyte click);
ubyte ac_do_unkn10_CONTROLS(ubyte click);
ubyte ac_alert_OK(ubyte click);
ubyte ac_do_net_SET2(ubyte click);
ubyte ac_do_net_SET(ubyte click);
ubyte ac_do_net_INITIATE(ubyte click);
ubyte ac_do_net_groups_LOGON(ubyte click);
ubyte ac_do_unkn8_EJECT(ubyte click);
ubyte ac_accept_mission(ubyte click);
ubyte ac_do_unkn1_CANCEL(ubyte click);
ubyte ac_do_unkn2_CANCEL(ubyte click);
ubyte ac_do_unkn2_ACCEPT(ubyte click);
ubyte ac_do_sysmnu_button(ubyte click);
ubyte ac_do_storage_NEW_MORTAL(ubyte click);
ubyte ac_load_game_slot(ubyte click);
ubyte ac_save_game_slot(ubyte click);
ubyte ac_main_do_my_quit(ubyte click);
ubyte ac_main_do_login_1(ubyte click);
ubyte ac_goto_savegame(ubyte click);
ubyte ac_do_abort_2(ubyte click);
ubyte ac_do_login_2(ubyte click);
ubyte ac_main_do_map_editor(ubyte click);
ubyte ac_brief_do_netscan_enhance(ubyte click);
ubyte ac_do_unkn11_CANCEL(ubyte click);
ubyte ac_do_buy_equip(ubyte click);
ubyte ac_sell_equipment(ubyte click);
ubyte ac_do_research_submit(ubyte click);
ubyte ac_do_research_suspend(ubyte click);
ubyte ac_do_unkn12_WEAPONS_MODS(ubyte click);


ubyte show_unkn32_box(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_unkn32_box\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_unkn12(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_unkn12\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_login_name(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_login_name\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_net_benefits_box(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_net_benefits_box\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_net_unkn21(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_net_unkn21\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_net_comms_box(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_net_comms_box\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte do_net_protocol_select(ubyte click)
{
    ubyte ret;
    asm volatile ("call ASM_do_net_protocol_select\n"
        : "=r" (ret) : "a" (click));
    return ret;
}

ubyte show_net_protocol_box(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_net_protocol_box\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_net_faction_box(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_net_faction_box\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_net_team_box(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_net_team_box\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_net_groups_box(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_net_groups_box\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_net_users_box(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_net_users_box\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_mission_stats(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_mission_stats\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_unkn31_box(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_unkn31_box\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

void draw_chartxy_axis_y_values(int x, int y, int height, int ax_min, int ax_max, int tot_values)
{
    char str[8];
    int i;
    int ax_val;
    int cy;

    ax_val = ax_max;
    cy = y;
    for (i = 0; i < tot_values; i++)
    {
        int twidth;
        char *text;
        ulong spr_id;
        struct TbSprite *spr;

        lbDisplay.DrawFlags = 0;
        if (i != tot_values/2 && i != 0)
            spr_id = 146;
        else
            spr_id = 145;
        spr = &sprites_Icons0_0[spr_id];
        sprintf(str, "%d", ax_val);
        twidth = LbTextStringWidth(str) + spr->SWidth;
        strcpy((char *)(back_buffer + text_buf_pos), str);
        text = (char *)(back_buffer + text_buf_pos);
        text_buf_pos += strlen(str) + 1;
        draw_text_purple_list2(x - twidth - 1, cy, text, 0);
        cy += height / tot_values;
        ax_val -= (ax_max - ax_min) / tot_values;
    }
}

void draw_chartxy_axis_x_values(int x, int y, int width, int ax_min, int ax_max, int tot_values)
{
    char str[8];
    int i;
    int ax_val;
    int cx;

    ax_val = ax_min;
    cx = x + 32;
    for (i = 0; i < tot_values; i++)
    {
        int twidth;
        char *text;
        ulong spr_id;
        struct TbSprite *spr;
        int final_x;

        lbDisplay.DrawFlags = 0;
        if (i != tot_values / 2 - 1 && i != tot_values - 1)
            spr_id = 146;
        else
            spr_id = 147;
        spr = &sprites_Icons0_0[spr_id];
        sprintf(str, "%d", ax_val);
        twidth = LbTextStringWidth(str);
        strcpy((char *)(back_buffer + text_buf_pos), str);
        text = (char *)(back_buffer + text_buf_pos);
        text_buf_pos += strlen(str) + 1;
        if (ax_val == 1)
            final_x = cx - (twidth - 2) + 3;
        else
            final_x = cx - (twidth - 2) + 1;
        draw_text_purple_list2(final_x, y + 4 + spr->SHeight, text, 0);
        cx += width / tot_values;
        ax_val += (ax_max - ax_min) / tot_values;
    }
}

void draw_chartxy_axis_y_grid(int x, int y, int width, int height, int tot_values)
{
    int i;
    int cy;

    cy = y;
    for (i = 0; i < tot_values; i++)
    {
        ulong spr_id;
        struct TbSprite *spr;

        lbDisplay.DrawFlags = 0x0004;
        draw_line_purple_list(x + 1, cy, x + width, cy, height + 7);
        lbDisplay.DrawFlags = 0;
        if (i != tot_values/2 && i != 0)
            spr_id = 146;
        else
            spr_id = 145;
        spr = &sprites_Icons0_0[spr_id];
        draw_sprite_purple_list(x - spr->SWidth - 1, cy, spr);
        cy += height / tot_values;
    }
}

void draw_chartxy_axis_x_grid(int x, int y, int width, int height, int tot_values)
{
    int i;
    int cx;

    cx = x;
    for (i = 0; i < tot_values; i++)
    {
        ulong spr_id;
        struct TbSprite *spr;

        lbDisplay.DrawFlags = 0x0004;
        draw_line_purple_list(cx, 128, cx, y + height - 1, height + 7);
        lbDisplay.DrawFlags = 0;
        if (i != tot_values / 2 - 1 && i != tot_values - 1)
            spr_id = 146;
        else
            spr_id = 147;
        spr = &sprites_Icons0_0[spr_id];
        draw_sprite_purple_list(cx - spr->SWidth + 1, y + height + 2, spr);
        cx += width / tot_values;
    }
}

void draw_line_purple_thick(int x1, int y1, int x2, int y2, ubyte colour, ubyte bkcolor)
{
    draw_line_purple_list(x1, y1, x2, y2, 87);
    if (y1 - y2 <= x2 - x1)
    {
        draw_line_purple_list(x1, y1 + 1, x2, y2 + 1, colour);
        draw_line_purple_list(x1, y1 - 1, x2, y2 - 1, colour);
        draw_line_purple_list(x1, y1 + 2, x2, y2 + 2, bkcolor);
        draw_line_purple_list(x1, y1 + 3, x2, y2 + 3, bkcolor);
        draw_line_purple_list(x1, y1 + 4, x2, y2 + 4, bkcolor);
    }
    else
    {
        draw_line_purple_list(x1 + 1, y1, x2 + 1, y2, colour);
        draw_line_purple_list(x1 - 1, y1, x2 - 1, y2, colour);
        draw_line_purple_list(x1 + 2, y1, x2 + 2, y2, bkcolor);
        draw_line_purple_list(x1 + 3, y1, x2 + 3, y2, bkcolor);
        draw_line_purple_list(x1 + 4, y1, x2 + 4, y2, bkcolor);
    }
}

void draw_chartxy_curve(int x, int y, int width, int height, ushort *y_vals, int n_y_vals, int y_scale, ushort y_trend_delta, int tot_values)
{
    int cday, progress, prev_progress, progress_scale;
    int cx, cy, mcy;
    int next_cx, next_cy, next_mcy;
    int delta_x, delta_y, delta_u;
    int remain_day;

    // Draw existing points curve
    delta_x = width / tot_values;
    delta_y = height / tot_values;
    delta_u = delta_x;
    progress_scale = y_scale / tot_values;
    cday = 0;
    progress = y_vals[cday];
    cx = x;
    // To increase accuracy, we keep y value multiplied by progress_scale
    mcy = (y + height) * progress_scale - (delta_y * progress);
    for (cday++; cday < n_y_vals; cday++)
    {
        progress = y_vals[cday];
        prev_progress = y_vals[cday-1];
        next_mcy = mcy - delta_y * (progress - prev_progress);
        next_cx = cx + delta_x;
        cy = mcy / progress_scale;
        next_cy = next_mcy / progress_scale;
        draw_line_purple_thick(cx, cy, next_cx, next_cy, 87, 0);
        cx = next_cx;
        mcy = next_mcy;
    }
    // Draw trend curve
    lbDisplay.DrawFlags = 0x0004;
    remain_day = 11 - cday;
    {
        progress = y_trend_delta;
        next_mcy = mcy - (delta_y * progress * remain_day);
        cy = mcy / progress_scale;
        next_cy = next_mcy / progress_scale;
        delta_u = delta_x * remain_day;
        if (next_cy >= y) {
            // Everything fits on the chart
            next_cx = cx + delta_u;
        } else {
            // Cap cy, and adjust cx accordingly
            next_cx = cx + cy * delta_u / (cy - next_cy);
            if (next_cx > width)
                next_cx = width;
            next_cy = y;
        }
        draw_line_purple_thick(cx, cy, next_cx, next_cy, 87, 0);
    }
    lbDisplay.DrawFlags = 0;
}

ubyte show_research_graph(struct ScreenBox *box)
{
#if 0
    ubyte ret;
    asm volatile ("call ASM_show_research_graph\n"
        : "=r" (ret) : "a" (box));
    return ret;
#endif
    struct TbSprite *spr;
    char *text;
    ushort *y_vals;
    ushort y_trend_delta;
    int n_y_vals;
    int graph_days, done_days;

    if ((box->Flags & 0x8000) == 0)
    {
        int twidth;

        lbFontPtr = small_med_font;
        my_set_text_window(0, 0, 640, 480);

        draw_chartxy_axis_y_values(64, 128, 240, 0, 100, 10);

        draw_chartxy_axis_y_grid(64, 128, 320, 240, 10);
        draw_chartxy_axis_x_grid(96, 128, 320, 240, 10);

        spr = &sprites_Icons0_0[145];
        draw_sprite_purple_list(66 - spr->SWidth - 1, 368, spr);
        spr = &sprites_Icons0_0[147];
        draw_sprite_purple_list(61, 368, spr);
        draw_text_purple_list2(52, 374, misc_text[0], 0);
        lbFontPtr = med_font;
        my_set_text_window(box->X + 4, box->Y + 4, box->Width - 8,  box->Height - 8);
        text = gui_strings[453];
        twidth = my_string_width(text);
        draw_text_purple_list2((box->Width - 8 - twidth) >> 1, 290, text, 0);
        text = gui_strings[452];
        draw_unkn20_subfunc_01(10, 31, text, 2);
        box->Flags |= 0x8000;
        copy_box_purple_list(box->X, box->Y, box->Width, box->Height);
    }

    graph_days = 0;
    if (research_on_weapons)
        done_days = research.WeaponDaysDone[research.CurrentWeapon];
    else
        done_days = research.ModDaysDone[research.CurrentMod];
    if (done_days >= 10) {
        graph_days = done_days - 9;
        n_y_vals = 10;
    } else {
        n_y_vals = done_days + 1;
    }
    lbFontPtr = small_med_font;
    my_set_text_window(0, 0, 640, 480);
    draw_chartxy_axis_x_values(64, 128 + 240, 320, graph_days+1, graph_days+11, 10);

    LbScreenSetGraphicsWindow(64 - 1, 128, 320 + 3, 240 + 2);
    if (research_on_weapons)
    {
        if (research.CurrentWeapon != -1)
        {
            struct WeaponDef *wdef;

            y_vals = &research.WeaponProgress[research.CurrentWeapon][0];
            wdef = &weapon_defs[research.CurrentWeapon + 1];
            y_trend_delta = research_unkn_func_004(wdef->PercentPerDay, wdef->Funding, research.WeaponFunding);

            draw_chartxy_curve(1, 0, 320, 240, y_vals, n_y_vals, RESEARCH_COMPLETE_POINTS, y_trend_delta, 10);
        }
    }
    else
    {
        if (research.CurrentMod != -1)
        {
            struct ModDef *mdef;

            y_vals = &research.ModProgress[research.CurrentMod][0];
            mdef = &mod_defs[research.CurrentMod + 1];
            y_trend_delta = research_unkn_func_004(mdef->PercentPerDay, mdef->Funding, research.ModFunding);

            draw_chartxy_curve(1, 0, 320, 240, y_vals, n_y_vals, RESEARCH_COMPLETE_POINTS, y_trend_delta, 10);
        }
    }

    LbScreenSetGraphicsWindow(0, 0, 640, 480);
    draw_box_purple_list(64, 368, 321,   2, 247);
    draw_box_purple_list(63, 128,   2, 241, 247);
    return 0;
}

ubyte show_unkn21_box(struct ScreenTextBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_unkn21_box\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_unkn04(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_unkn04\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_unkn33_box(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_unkn33_box\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_netgame_unkn1(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_netgame_unkn1\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_menu_storage_unkn37_box(struct ScreenTextBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_menu_storage_unkn37_box\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_unkn29_box(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_unkn29_box\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte display_weapon_info(struct ScreenTextBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_display_weapon_info\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_weapon_name(struct ScreenTextBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_weapon_name\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_weapon_list(struct ScreenTextBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_weapon_list\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_weapon_slots(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_weapon_slots\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_agent_list(struct ScreenTextBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_agent_list\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_blokey(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_blokey\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_unkn18_box(struct ScreenTextBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_unkn18_box\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_unkn36_box(struct ScreenTextBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_unkn36_box\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_unkn34_box(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_unkn34_box\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte show_settings_controls_list(struct ScreenBox *box)
{
    ubyte ret;
    asm volatile ("call ASM_show_settings_controls_list\n"
        : "=r" (ret) : "a" (box));
    return ret;
}

ubyte ac_show_unkn32_box(struct ScreenBox *box);
ubyte ac_show_unkn12(struct ScreenBox *box);
ubyte ac_show_login_name(struct ScreenBox *box);
ubyte ac_show_net_benefits_box(struct ScreenBox *box);
ubyte ac_show_net_unkn21(struct ScreenBox *box);
ubyte ac_show_net_comms_box(struct ScreenBox *box);
ubyte ac_do_net_protocol_select(ubyte click);
ubyte ac_show_net_protocol_box(struct ScreenBox *box);
ubyte ac_show_net_faction_box(struct ScreenBox *box);
ubyte ac_show_net_team_box(struct ScreenBox *box);
ubyte ac_show_net_groups_box(struct ScreenBox *box);
ubyte ac_show_net_users_box(struct ScreenBox *box);
ubyte ac_show_mission_stats(struct ScreenBox *box);
ubyte ac_show_unkn31_box(struct ScreenBox *box);
ubyte ac_show_research_graph(struct ScreenBox *box);
ubyte ac_show_unkn21_box(struct ScreenTextBox *box);
ubyte ac_show_unkn04(struct ScreenBox *box);
ubyte ac_show_unkn33_box(struct ScreenBox *box);
ubyte ac_show_netgame_unkn1(struct ScreenBox *box);
ubyte ac_show_menu_storage_unkn37_box(struct ScreenTextBox *box);
ubyte ac_show_unkn29_box(struct ScreenBox *box);
ubyte ac_display_weapon_info(struct ScreenTextBox *box);
ubyte ac_show_weapon_name(struct ScreenTextBox *box);
ubyte ac_show_weapon_list(struct ScreenTextBox *box);
ubyte ac_show_weapon_slots(struct ScreenBox *box);
ubyte ac_show_agent_list(struct ScreenTextBox *box);
ubyte ac_show_blokey(struct ScreenBox *box);
ubyte ac_show_unkn18_box(struct ScreenTextBox *box);
ubyte ac_show_unkn36_box(struct ScreenTextBox *box);
ubyte ac_show_unkn34_box(struct ScreenBox *box);
ubyte ac_show_settings_controls_list(struct ScreenBox *box);


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
    init_screen_button(&options_audio_buttons[0], 393u, 289u, gui_strings[531], 6,
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

    options_gfx_buttons[14].CallBackFn = ac_change_panel_permutation;
    options_gfx_buttons[15].CallBackFn = ac_change_trenchcoat_preference;
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
        sysmnu_buttons[i].CallBackFn = ac_do_sysmnu_button;
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
    net_protocol_option_button.CallBackFn = ac_do_net_protocol_option;
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
    heading_box.DrawTextFn = ac_show_title_box;
    alert_OK_button.CallBackFn = ac_alert_OK;
    loading_INITIATING_box.Text = gui_strings[376];
    heading_box.Text = options_title_text;
    lbFontPtr = med_font;
    alert_OK_button.X = 319 - (alert_OK_button.Width >> 1);
    loading_INITIATING_box.Height = font_height(0x41u) + 8;
    w = my_string_width(gui_strings[376]);
    unkn37_box.DrawTextFn = ac_show_menu_storage_unkn37_box;
    unkn37_box.ScrollWindowHeight = 208;
    unkn37_box.Lines = 99;
    unkn34_box.SpecialDrawFn = ac_show_unkn34_box;
    loading_INITIATING_box.Width = w + 9;
    unkn37_box.Flags |= 0x0300;
    unkn33_box.SpecialDrawFn = ac_show_unkn33_box;
    mission_text_box.Buttons[0] = &unkn1_ACCEPT_button;
    mission_text_box.Buttons[1] = &unkn1_CANCEL_button;
    brief_NETSCAN_COST_box.Text2 = brief_netscan_cost_text;
    unkn37_box.BGColour = 26;
    mission_text_box.Flags |= 0x0300;
    unkn37_box.ScrollWindowOffset += 27;
    loading_INITIATING_box.X = 319 - ((w + 9) >> 1);
    unkn32_box.SpecialDrawFn = ac_show_unkn32_box;
    loading_INITIATING_box.Y = 219 - (loading_INITIATING_box.Height >> 1);
    unkn04_boxes[0].SpecialDrawFn = ac_show_unkn04;
    unkn04_boxes[1].SpecialDrawFn = ac_show_unkn04;
    unkn04_boxes[2].SpecialDrawFn = ac_show_unkn04;
    unkn31_box.SpecialDrawFn = ac_show_unkn31_box;
    mission_text_box.Text = mission_briefing_text;
    unkn30_box.SpecialDrawFn = ac_show_mission_stats;
    unkn36_box.Flags |= 0x0300;
    unkn36_box.DrawTextFn = ac_show_unkn36_box;
    unkn2_ACCEPT_button.X = unkn38_box.X
        + ((unkn38_box.Width - unkn2_ACCEPT_button.Width) >> 1);
    unkn29_box.SpecialDrawFn = ac_show_unkn29_box;
    unkn38_box.DrawTextFn = ac_show_unkn38_box;
    slots_box.DrawTextFn = ac_show_title_box;
    equip_display_box.DrawTextFn = ac_display_weapon_info;
    equip_list_box.DrawTextFn = ac_show_weapon_list;
    equip_cost_box.Text2 = equip_cost_text;
    research_unkn21_box.DrawTextFn = ac_show_unkn21_box;
    unkn12_WEAPONS_MODS_button.CallBackFn = ac_do_unkn12_WEAPONS_MODS;
    weapon_slots.SpecialDrawFn = ac_show_weapon_slots;
    research_unkn21_box.ScrollWindowHeight = 180;
    research_unkn21_box.Buttons[0] = &research_submit_button;
    research_unkn21_box.Buttons[1] = &unkn12_WEAPONS_MODS_button;
    unkn2_CANCEL_button.X =
        ((unkn38_box.Width - unkn2_CANCEL_button.Width) >> 1) + unkn38_box.X;
    equip_name_box.DrawTextFn = ac_show_weapon_name;
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
    research_submit_button.CallBackFn = ac_do_research_submit;
    equip_list_box.BGColour = unk2_sprites[15].SHeight + 3;
    equip_list_box.ScrollWindowHeight -= 27;
    research_progress_button.DrawTextFn = ac_show_title_box;
    research_submit_button.Text = gui_strings[417];
    research_progress_button.Text = gui_strings[449];
    research_unkn21_box.Flags |= 0x0300;
    unkn12_WEAPONS_MODS_button.Text = gui_strings[451];
    lbFontPtr = med2_font;
    research_unkn20_box.SpecialDrawFn = ac_show_research_graph;

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

    mod_list_box.DrawTextFn = ac_show_unkn18_box;
    agent_list_box.BGColour = 25;
    net_groups_box.SpecialDrawFn = ac_show_net_groups_box;
    net_users_box.SpecialDrawFn = ac_show_net_users_box;
    equip_cost_box.X = buy_equip_button.Width + buy_equip_button.X + 4;
    net_INITIATE_button.CallBackFn = ac_do_net_INITIATE;
    net_faction_box.SpecialDrawFn = ac_show_net_faction_box;
    net_team_box.SpecialDrawFn = ac_show_net_team_box;
    net_groups_box.Flags |= 0x0300;
    equip_cost_box.Width = 208 - buy_equip_button.Width - 14;
    agent_list_box.DrawTextFn = ac_show_agent_list;
    net_benefits_box.SpecialDrawFn = ac_show_net_benefits_box;
    net_unkn40_button.CallBackFn = ac_do_net_unkn40;
    unkn1_ACCEPT_button.CallBackFn = ac_accept_mission;
    mod_list_box.Flags |= 0x0300;
    net_SET_button.CallBackFn = ac_do_net_SET;
    blokey_box.SpecialDrawFn = ac_show_blokey;
    unkn8_EJECT_button.CallBackFn = ac_do_unkn8_EJECT;
    unkn1_CANCEL_button.CallBackFn = ac_do_unkn1_CANCEL;
    storage_SAVE_button.CallBackFn = ac_save_game_slot;
    storage_NEW_MORTAL_button.CallBackFn = ac_do_storage_NEW_MORTAL;
    mod_list_box.ScrollWindowHeight = 117;
    net_protocol_select_button.CallBackFn = ac_do_net_protocol_select;
    unkn13_SYSTEM_button.Text = gui_strings[366];
    net_comms_box.SpecialDrawFn = ac_show_net_comms_box;
    buy_equip_button.CallBackFn = ac_do_buy_equip;
    storage_LOAD_button.CallBackFn = ac_load_game_slot;
    net_users_box.Flags |= 0x0300;
    agent_list_box.ScrollWindowOffset += 27;
    net_groups_LOGON_button.CallBackFn = ac_do_net_groups_LOGON;
    net_unkn21.SpecialDrawFn = ac_show_net_unkn21;
    unkn2_CANCEL_button.CallBackFn = ac_do_unkn2_CANCEL;
    unkn2_ACCEPT_button.CallBackFn = ac_do_unkn2_ACCEPT;
    unkn11_CANCEL_button.CallBackFn = ac_do_unkn11_CANCEL;
    unkn10_CALIBRATE_button.CallBackFn = ac_do_unkn10_CALIBRATE;
    agent_list_box.Flags |= 0x0300;
    unkn10_CONTROLS_button.CallBackFn = ac_do_unkn10_CONTROLS;
    main_map_editor_button.X = 319 - (main_map_editor_button.Width >> 1);
    unkn13_SYSTEM_button.DrawTextFn = ac_show_title_box;
    unkn35_box.DrawTextFn = ac_show_title_box;
    main_login_button.X = 319 - (main_login_button.Width >> 1);
    net_SET2_button.CallBackFn = ac_do_net_SET2;
    pause_continue_button.X = 319 - (pause_continue_button.Width >> 1);
    agent_list_box.ScrollWindowHeight -= 27;
    net_protocol_box.SpecialDrawFn = ac_show_net_protocol_box;
    pause_abort_button.X = 319 - (pause_abort_button.Width >> 1);
    brief_NETSCAN_button.CallBackFn = ac_brief_do_netscan_enhance;
    main_quit_button.X = 319 - (main_quit_button.Width >> 1);
    unkn10_SAVE_button.CallBackFn = ac_do_unkn10_SAVE;
    main_load_button.X = 319 - (main_load_button.Width >> 1);
    main_map_editor_button.Border = 3;
    pause_abort_button.Border = 3;
    pause_continue_button.Border = 3;
    main_login_button.Border = 3;
    main_quit_button.Border = 3;
    main_load_button.Border = 3;
    main_map_editor_button.CallBackFn = ac_main_do_map_editor;
    main_login_button.CallBackFn = ac_main_do_login_1;
    main_quit_button.CallBackFn = ac_main_do_my_quit;
    pause_unkn11_box.SpecialDrawFn = ac_show_unkn12;
    pause_unkn12_box.SpecialDrawFn = ac_show_login_name;
    pause_continue_button.CallBackFn = ac_do_login_2;
    main_load_button.CallBackFn = ac_goto_savegame;
    pause_abort_button.CallBackFn = ac_do_abort_2;
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

void move_camera(int x, int y, int z)
{
    asm volatile (
      "call ASM_move_camera\n"
        : : "a" (x), "d" (y), "b" (z));
}

void track_player(int thing)
{
    asm volatile ("call ASM_track_player\n"
        : : "a" (thing));
}

void track_angle(void)
{
    asm volatile ("call ASM_track_angle\n"
        :  :  : "eax" );
}

void track_y(int y)
{
    engn_yc += (y - engn_yc) >> 3;
}

void local_to_worldr(int *dx, int *dy, int *dz)
{
    asm volatile (
      "call ASM_local_to_worldr\n"
        : : "a" (dx), "d" (dy), "b" (dz));
}

void do_scroll_map(void)
{
#if 0
    asm volatile ("call ASM_do_scroll_map\n"
        :  :  : "eax" );
#else
    PlayerInfo *p_locplayer;
    long engn_xc_orig, engn_zc_orig;
    ushort md;
    long abase, angle;
    int dx, dy;
    int dampr;

    dx = 0;
    dy = 0;
    dampr = 10;
    if (ingame.fld_unkCA6)
        track_angle();
    p_locplayer = &players[local_player_no];
    if (p_locplayer->State[0] == 1)
    {
        ushort bitx, bity;
        int dz;
        // TODO check if this makes sense
        bitx = (p_locplayer->UserInput[0].Bits >> 0);
        bity = (p_locplayer->UserInput[0].Bits >> 8);
        dx = (bitx & 0xFF) << 8;
        dz = (bity & 0xFF) << 8;
        local_to_worldr(&dx, &dy, &dz);
        engn_xc += dx;
        engn_zc += dz;
    }
    else
    {
        ulong dcthing;
        if (p_locplayer->DoubleMode)
        {
            if (byte_153198)
                dcthing = p_locplayer->DirectControl[byte_153198-1];
            else
                dcthing = p_locplayer->DirectControl[0];
            track_player(dcthing);
            return;
        }
        dcthing = p_locplayer->DirectControl[0];
        if (dcthing)
        {
            md = p_locplayer->UserInput[0].ControlMode & 0x1FFF;
            if (md == 1 || pktrec_mode == PktR_PLAYBACK)
                move_camera(ingame.TrackX, engn_yc, ingame.TrackZ);
            else
                track_player(dcthing);
        }
    }
    dy = 0;
    dx = 0;
    md = p_locplayer->UserInput[byte_153198-1].ControlMode & 0x1FFF;
    engn_xc_orig = engn_xc;
    engn_zc_orig = engn_zc;
    if (md == 1 || pktrec_mode == PktR_PLAYBACK)
    {
        if (!p_locplayer->PanelState[mouser])
        {
            long cumm_alt;
            int mv_border;

            // Define a move border, getting the mouse beyond it causes map scroll
            if (lbDisplay.GraphicsScreenWidth >= 640)
                mv_border = 3;
            else
                mv_border = 2;

            if (!p_locplayer->DoubleMode)
            {
                dx = (lbKeyOn[kbkeys[GKey_RIGHT]] & 1) - (lbKeyOn[kbkeys[GKey_LEFT]] & 1);
                dy = (lbKeyOn[kbkeys[GKey_DOWN]] & 1) - (lbKeyOn[kbkeys[GKey_UP]] & 1);
            }

            if (dx == 0)
            {
                int mx;
                mx = lbDisplay.MMouseX;
                if (mx >= lbDisplay.GraphicsScreenWidth - mv_border)
                    dx = 1;
                if (mx < mv_border)
                    dx = -1;
            }
            if (dy == 0)
            {
                int my;
                my = lbDisplay.MMouseY;
                if (my >= lbDisplay.GraphicsScreenHeight - mv_border)
                    dy = 1;
                if (my < mv_border)
                    dy = -1;
            }
            cumm_alt = alt_at_point(engn_xc, engn_zc) >> 8;
            cumm_alt += alt_at_point(engn_xc + 2048, engn_zc + 2048) >> 8;
            cumm_alt += alt_at_point(engn_xc + 2048, engn_zc - 2048) >> 8;
            cumm_alt += alt_at_point(engn_xc - 2048, engn_zc + 2048) >> 8;
            cumm_alt += alt_at_point(engn_xc - 2048, engn_zc - 2048) >> 8;
            track_y(cumm_alt / 5);
            dampr = 9;
        }
    }

    abase = -dword_176D58 >> 5;
    angle = -1;
    if (dx > 0)
        angle = (abase + 3583) & 0x7FF;
    if (dx < 0)
        angle = (abase + 2559) & 0x7FF;
    if (angle >= 0) {
        int wibl_x, wibl_y;
        wibl_x = dword_153194 * lbSinTable[angle] >> 8 >> dampr;
        wibl_y = dword_153194 * lbSinTable[angle + 512] >> 8 >> dampr;
        ingame.TrackX -= wibl_x;
        ingame.TrackZ += wibl_y;
        engn_xc -= wibl_x;
        engn_zc += wibl_y;
    }
    angle = -1;
    if (dy > 0)
        angle = (abase + 3071) & 0x7FF;
    if (dy < 0)
        angle = (abase + 2047) & 0x7FF;
    if (angle >= 0) {
        int wibl_x, wibl_y;
        wibl_x = dword_153194 * lbSinTable[angle] >> 8 >> dampr;
        wibl_y = dword_153194 * lbSinTable[angle + 512] >> 8 >> dampr;
        ingame.TrackX -= wibl_x;
        ingame.TrackZ += wibl_y;
        engn_xc -= wibl_x;
        engn_zc += wibl_y;
    }

    if (engn_xc < 0)
        engn_xc = 0;
    else if (engn_xc >= 0x8000)
        engn_xc = 0x7FFF;
    if (engn_zc < 0)
        engn_zc = 0;
    else if (engn_zc >= 0x8000)
        engn_zc = 0x7FFF;
    if (ingame.TrackX > 0xC000)
        ingame.TrackX = 0;
    else if (ingame.TrackX >= 0x8000)
        ingame.TrackX = 0x7FFF;
    if (ingame.TrackZ > 0xC000)
        ingame.TrackZ = 0;
    else if (ingame.TrackZ >= 0x8000)
        ingame.TrackZ = 0x7FFF;

    if (dx) {
        dword_153194 += 4 + ((dword_153194 - 252) >> 5);
        if (dword_153194 > 800)
            dword_153194 = 800;
    } else {
        dword_153194 -= (dword_153194 - 256) >> 2;
    }
    if ((engn_zc - engn_zc_orig) || (engn_xc - engn_xc_orig)) {
        dword_17710C = engn_xc - engn_xc_orig;
        dword_177110 = engn_zc - engn_zc_orig;
    } else {
        dword_17710C >>= 2;
        dword_177110 >>= 2;
        if (abs(dword_17710C) < 5)
            dword_17710C = 0;
        if (abs(dword_177110) < 5)
            dword_177110 = 0;
        engn_xc += dword_17710C;
        engn_zc += dword_177110;
    }
#endif
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
                if (((p_agent->Flag & 0x02) == 0) && ((p_agent->Flag2 & 0x10) == 0) && (p_agent->State != PerSt_PERSON_BURNING))
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
        scientists_lost = research_daily_progress_for_type(0);
        if (research.CurrentWeapon != prev)
            new_weapons_researched |= 1 << prev;

        prev = research.CurrentMod;
        scientists_lost += research_daily_progress_for_type(1);
        if (research.CurrentMod != prev)
            new_mods_researched |= 1 << prev;
    }
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

void wait_for_sound_sample_finish(ushort smpl_id)
{
    TbClockMSec last_loop_time = LbTimerClock();
    while (IsSamplePlaying(0, smpl_id, NULL)) {
        game_update();
        TbClockMSec sleep_end = last_loop_time + 1000/GAME_FPS;
        LbSleepUntil(sleep_end);
        last_loop_time = LbTimerClock();
    }
}

void copy_to_screen_ani(ubyte *buf)
{
    int y;
    const ubyte *inp;
    ubyte *o;

    inp = buf;
    o = lbDisplay.WScreen;
    for (y = 0; y < 256; y++)
    {
        memcpy(o, inp, 256);
        inp += 256;
        o += lbDisplay.GraphicsScreenWidth;
    }
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
          load_level_pc(-(int)mission_list[ingame.MissionNo].LevelNo, ingame.MissionNo);
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
                load_level_pc(-cities[unkn_city_no].Level, unkn_city_no);
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
            sprintf(equip_cost_text, "%d", 100 * weapon_defs[selected_weapon + 1].Cost);
        else
            sprintf(equip_cost_text, "%d", 100 * weapon_defs[selected_weapon + 1].Cost >> 1);
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
    host_reset();
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

