#pragma once
#ifndef ui_colors_h
#define ui_colors_h

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ui_colorf_t {
    float r;
    float g;
    float b;
    float a;
} ui_colorf_t;

typedef struct ui_colors_t {
    struct {
        uint32_t alice_blue;
        uint32_t antique_white;
        uint32_t aqua;
        uint32_t aquamarine;
        uint32_t azure;
        uint32_t beige;
        uint32_t bisque;
        uint32_t black;
        uint32_t blanched_almond;
        uint32_t blue;
        uint32_t blue_violet;
        uint32_t brown;
        uint32_t burly_wood;
        uint32_t cadet_blue;
        uint32_t chartreuse;
        uint32_t chocolate;
        uint32_t coral;
        uint32_t cornflower_blue;
        uint32_t cornsilk;
        uint32_t crimson;
        uint32_t cyan;
        uint32_t dark_blue;
        uint32_t dark_cyan;
        uint32_t dark_goldenrod;
        uint32_t dark_gray;
        uint32_t dark_green;
        uint32_t dark_khaki;
        uint32_t dark_magenta;
        uint32_t dark_olive_green;
        uint32_t dark_orange;
        uint32_t dark_orchid;
        uint32_t dark_red;
        uint32_t dark_salmon;
        uint32_t dark_sea_green;
        uint32_t dark_slate_blue;
        uint32_t dark_slate_gray;
        uint32_t dark_turquoise;
        uint32_t dark_violet;
        uint32_t deep_pink;
        uint32_t deep_sky_blue;
        uint32_t dim_gray;
        uint32_t dodger_blue;
        uint32_t firebrick;
        uint32_t floral_white;
        uint32_t forest_green;
        uint32_t fuchsia;
        uint32_t gainsboro;
        uint32_t ghost_white;
        uint32_t gold;
        uint32_t goldenrod;
        uint32_t gray;
        uint32_t green;
        uint32_t green_yellow;
        uint32_t honeydew;
        uint32_t hot_pink;
        uint32_t indian_red;
        uint32_t indigo;
        uint32_t ivory;
        uint32_t khaki;
        uint32_t lavender;
        uint32_t lavender_blush;
        uint32_t lawn_green;
        uint32_t lemon_chiffon;
        uint32_t light_blue;
        uint32_t light_coral;
        uint32_t light_cyan;
        uint32_t light_goldenrod_yellow;
        uint32_t light_green;
        uint32_t light_gray;
        uint32_t light_pink;
        uint32_t light_salmon;
        uint32_t light_sea_green;
        uint32_t light_sky_blue;
        uint32_t light_slate_gray;
        uint32_t light_steel_blue;
        uint32_t light_yellow;
        uint32_t lime;
        uint32_t lime_green;
        uint32_t linen;
        uint32_t magenta;
        uint32_t maroon;
        uint32_t medium_aquamarine;
        uint32_t medium_blue;
        uint32_t medium_orchid;
        uint32_t medium_purple;
        uint32_t medium_sea_green;
        uint32_t medium_slate_blue;
        uint32_t medium_spring_green;
        uint32_t medium_turquoise;
        uint32_t medium_violet_red;
        uint32_t midnight_blue;
        uint32_t mint_cream;
        uint32_t misty_rose;
        uint32_t moccasin;
        uint32_t navajo_white;
        uint32_t navy;
        uint32_t old_lace;
        uint32_t olive;
        uint32_t olive_drab;
        uint32_t orange;
        uint32_t orange_red;
        uint32_t orchid;
        uint32_t pale_goldenrod;
        uint32_t pale_green;
        uint32_t pale_turquoise;
        uint32_t pale_violet_red;
        uint32_t papaya_whip;
        uint32_t peach_puff;
        uint32_t peru;
        uint32_t pink;
        uint32_t plum;
        uint32_t powder_blue;
        uint32_t purple;
        uint32_t red;
        uint32_t rosy_brown;
        uint32_t royal_blue;
        uint32_t saddle_brown;
        uint32_t salmon;
        uint32_t sandy_brown;
        uint32_t sea_green;
        uint32_t sea_shell;
        uint32_t sienna;
        uint32_t silver;
        uint32_t sky_blue;
        uint32_t slate_blue;
        uint32_t slate_gray;
        uint32_t snow;
        uint32_t spring_green;
        uint32_t steel_blue;
        uint32_t tan;
        uint32_t teal;
        uint32_t thistle;
        uint32_t tomato;
        uint32_t turquoise;
        uint32_t violet;
        uint32_t wheat;
        uint32_t white;
        uint32_t white_smoke;
        uint32_t yellow;
        uint32_t yellow_green;
    } bgra;
    ui_colorf_t (*f)(uint32_t bgra);
} ui_colors_t;

extern ui_colors_t ui_colors;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ui_color_h

