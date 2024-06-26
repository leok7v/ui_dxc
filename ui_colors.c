#include "ui_colors.h"

// based on <d2d1helpers.h> colors

static inline ui_colorf_t ui_colors_fp32(uint32_t argb) {
    ui_colorf_t cf = (ui_colorf_t){
        .a = (float)((argb & 0xFF000000) >> 24) / 255.f,
        .r = (float)((argb & 0x00FF0000) >> 16) / 255.f,
        .g = (float)((argb & 0x0000FF00) >>  8) / 255.f,
        .b = (float)((argb & 0x000000FF) >>  0) / 255.f
    };
    return cf;
}

ui_colors_t ui_colors = {
    .bgra = {
        .alice_blue             = 0xFFF0F8FF,
        .antique_white          = 0xFFFAEBD7,
        .aqua                   = 0xFF00FFFF,
        .aquamarine             = 0xFF7FFFD4,
        .azure                  = 0xFFF0FFFF,
        .beige                  = 0xFFF5F5DC,
        .bisque                 = 0xFFFFE4C4,
        .black                  = 0xFF000000,
        .blanched_almond        = 0xFFFFEBCD,
        .blue                   = 0xFF0000FF,
        .blue_violet            = 0xFF8A2BE2,
        .brown                  = 0xFFA52A2A,
        .burly_wood             = 0xFFDEB887,
        .cadet_blue             = 0xFF5F9EA0,
        .chartreuse             = 0xFF7FFF00,
        .chocolate              = 0xFFD2691E,
        .coral                  = 0xFFFF7F50,
        .cornflower_blue        = 0xFF6495ED,
        .cornsilk               = 0xFFFFF8DC,
        .crimson                = 0xFFDC143C,
        .cyan                   = 0xFF00FFFF,
        .dark_blue              = 0xFF00008B,
        .dark_cyan              = 0xFF008B8B,
        .dark_goldenrod         = 0xFFB8860B,
        .dark_gray              = 0xFFA9A9A9,
        .dark_green             = 0xFF006400,
        .dark_khaki             = 0xFFBDB76B,
        .dark_magenta           = 0xFF8B008B,
        .dark_olive_green       = 0xFF556B2F,
        .dark_orange            = 0xFFFF8C00,
        .dark_orchid            = 0xFF9932CC,
        .dark_red               = 0xFF8B0000,
        .dark_salmon            = 0xFFE9967A,
        .dark_sea_green         = 0xFF8FBC8F,
        .dark_slate_blue        = 0xFF483D8B,
        .dark_slate_gray        = 0xFF2F4F4F,
        .dark_turquoise         = 0xFF00CED1,
        .dark_violet            = 0xFF9400D3,
        .deep_pink              = 0xFFFF1493,
        .deep_sky_blue          = 0xFF00BFFF,
        .dim_gray               = 0xFF696969,
        .dodger_blue            = 0xFF1E90FF,
        .firebrick              = 0xFFB22222,
        .floral_white           = 0xFFFFFAF0,
        .forest_green           = 0xFF228B22,
        .fuchsia                = 0xFFFF00FF,
        .gainsboro              = 0xFFDCDCDC,
        .ghost_white            = 0xFFF8F8FF,
        .gold                   = 0xFFFFD700,
        .goldenrod              = 0xFFDAA520,
        .gray                   = 0xFF808080,
        .green                  = 0xFF008000,
        .green_yellow           = 0xFFADFF2F,
        .honeydew               = 0xFFF0FFF0,
        .hot_pink               = 0xFFFF69B4,
        .indian_red             = 0xFFCD5C5C,
        .indigo                 = 0xFF4B0082,
        .ivory                  = 0xFFFFFFF0,
        .khaki                  = 0xFFF0E68C,
        .lavender               = 0xFFE6E6FA,
        .lavender_blush         = 0xFFFFF0F5,
        .lawn_green             = 0xFF7CFC00,
        .lemon_chiffon          = 0xFFFFFACD,
        .light_blue             = 0xFFADD8E6,
        .light_coral            = 0xFFF08080,
        .light_cyan             = 0xFFE0FFFF,
        .light_goldenrod_yellow = 0xFFFAFAD2,
        .light_green            = 0xFF90EE90,
        .light_gray             = 0xFFD3D3D3,
        .light_pink             = 0xFFFFB6C1,
        .light_salmon           = 0xFFFFA07A,
        .light_sea_green        = 0xFF20B2AA,
        .light_sky_blue         = 0xFF87CEFA,
        .light_slate_gray       = 0xFF778899,
        .light_steel_blue       = 0xFFB0C4DE,
        .light_yellow           = 0xFFFFF8DC,
        .lime                   = 0xFF00FF00,
        .lime_green             = 0xFF32CD32,
        .linen                  = 0xFFFAF0E6,
        .magenta                = 0xFFFF00FF,
        .maroon                 = 0xFF800000,
        .medium_aquamarine      = 0xFF66CDAA,
        .medium_blue            = 0xFF0000CD,
        .medium_orchid          = 0xFFBA55D3,
        .medium_purple          = 0xFF9370DB,
        .medium_sea_green       = 0xFF3CB371,
        .medium_slate_blue      = 0xFF7B68EE,
        .medium_spring_green    = 0xFF00FA9A,
        .medium_turquoise       = 0xFF48D1CC,
        .medium_violet_red      = 0xFFC71585,
        .midnight_blue          = 0xFF191970,
        .mint_cream             = 0xFFF5FFFA,
        .misty_rose             = 0xFFFFE4E1,
        .moccasin               = 0xFFFFE4B5,
        .navajo_white           = 0xFFFFDEAD,
        .navy                   = 0xFF000080,
        .old_lace               = 0xFFFDF5E6,
        .olive                  = 0xFF808000,
        .olive_drab             = 0xFF6B8E23,
        .orange                 = 0xFFFFA500,
        .orange_red             = 0xFFFF4500,
        .orchid                 = 0xFFDA70D6,
        .pale_goldenrod         = 0xFFEEE8AA,
        .pale_green             = 0xFF98FB98,
        .pale_turquoise         = 0xFFAFEEEE,
        .pale_violet_red        = 0xFFDB7093,
        .papaya_whip            = 0xFFFFEFD5,
        .peach_puff             = 0xFFFFDAB9,
        .peru                   = 0xFFCD853F,
        .pink                   = 0xFFFFC0CB,
        .plum                   = 0xFFDDA0DD,
        .powder_blue            = 0xFFB0E0E6,
        .purple                 = 0xFF800080,
        .red                    = 0xFFFF0000,
        .rosy_brown             = 0xFFBC8F8F,
        .royal_blue             = 0xFF4169E1,
        .saddle_brown           = 0xFF8B4513,
        .salmon                 = 0xFFFA8072,
        .sandy_brown            = 0xFFF4A460,
        .sea_green              = 0xFF2E8B57,
        .sea_shell              = 0xFFFFF5EE,
        .sienna                 = 0xFFA0522D,
        .silver                 = 0xFFC0C0C0,
        .sky_blue               = 0xFF87CEEB,
        .slate_blue             = 0xFF6A5ACD,
        .slate_gray             = 0xFF708090,
        .snow                   = 0xFFFFFAFA,
        .spring_green           = 0xFF00FF7F,
        .steel_blue             = 0xFF4682B4,
        .tan                    = 0xFFD2B48C,
        .teal                   = 0xFF008080,
        .thistle                = 0xFFD8BFD8,
        .tomato                 = 0xFFFF6347,
        .turquoise              = 0xFF40E0D0,
        .violet                 = 0xFFEE82EE,
        .wheat                  = 0xFFF5DEB3,
        .white                  = 0xFFFFFFFF,
        .white_smoke            = 0xFFF5F5F5,
        .yellow                 = 0xFFFFFF00,
        .yellow_green           = 0xFF9ACD32,
    },
    .f = {                      //  .r =    .g =    .b =    .a
        .alice_blue             = { 0.941f, 0.973f, 1.000f, 1.000f },
        .antique_white          = { 0.980f, 0.922f, 0.843f, 1.000f },
        .aqua                   = { 0.000f, 1.000f, 1.000f, 1.000f },
        .aquamarine             = { 0.498f, 1.000f, 0.831f, 1.000f },
        .azure                  = { 0.941f, 1.000f, 1.000f, 1.000f },
        .beige                  = { 0.961f, 0.961f, 0.863f, 1.000f },
        .bisque                 = { 1.000f, 0.894f, 0.769f, 1.000f },
        .black                  = { 0.000f, 0.000f, 0.000f, 1.000f },
        .blanched_almond        = { 1.000f, 0.922f, 0.804f, 1.000f },
        .blue                   = { 0.000f, 0.000f, 1.000f, 1.000f },
        .blue_violet            = { 0.541f, 0.169f, 0.886f, 1.000f },
        .brown                  = { 0.647f, 0.165f, 0.165f, 1.000f },
        .burly_wood             = { 0.871f, 0.722f, 0.529f, 1.000f },
        .cadet_blue             = { 0.373f, 0.620f, 0.627f, 1.000f },
        .chartreuse             = { 0.498f, 1.000f, 0.000f, 1.000f },
        .chocolate              = { 0.824f, 0.412f, 0.118f, 1.000f },
        .coral                  = { 1.000f, 0.498f, 0.314f, 1.000f },
        .cornflower_blue        = { 0.392f, 0.584f, 0.929f, 1.000f },
        .cornsilk               = { 1.000f, 0.973f, 0.863f, 1.000f },
        .crimson                = { 0.863f, 0.078f, 0.235f, 1.000f },
        .cyan                   = { 0.000f, 1.000f, 1.000f, 1.000f },
        .dark_blue              = { 0.000f, 0.000f, 0.545f, 1.000f },
        .dark_cyan              = { 0.000f, 0.545f, 0.545f, 1.000f },
        .dark_goldenrod         = { 0.722f, 0.525f, 0.043f, 1.000f },
        .dark_gray              = { 0.663f, 0.663f, 0.663f, 1.000f },
        .dark_green             = { 0.000f, 0.392f, 0.000f, 1.000f },
        .dark_khaki             = { 0.741f, 0.718f, 0.420f, 1.000f },
        .dark_magenta           = { 0.545f, 0.000f, 0.545f, 1.000f },
        .dark_olive_green       = { 0.333f, 0.420f, 0.184f, 1.000f },
        .dark_orange            = { 1.000f, 0.549f, 0.000f, 1.000f },
        .dark_orchid            = { 0.600f, 0.196f, 0.800f, 1.000f },
        .dark_red               = { 0.545f, 0.000f, 0.000f, 1.000f },
        .dark_salmon            = { 0.914f, 0.588f, 0.478f, 1.000f },
        .dark_sea_green         = { 0.561f, 0.737f, 0.561f, 1.000f },
        .dark_slate_blue        = { 0.282f, 0.239f, 0.545f, 1.000f },
        .dark_slate_gray        = { 0.184f, 0.310f, 0.310f, 1.000f },
        .dark_turquoise         = { 0.000f, 0.808f, 0.820f, 1.000f },
        .dark_violet            = { 0.580f, 0.000f, 0.827f, 1.000f },
        .deep_pink              = { 1.000f, 0.078f, 0.576f, 1.000f },
        .deep_sky_blue          = { 0.000f, 0.749f, 1.000f, 1.000f },
        .dim_gray               = { 0.412f, 0.412f, 0.412f, 1.000f },
        .dodger_blue            = { 0.118f, 0.565f, 1.000f, 1.000f },
        .firebrick              = { 0.698f, 0.133f, 0.133f, 1.000f },
        .floral_white           = { 1.000f, 0.980f, 0.941f, 1.000f },
        .forest_green           = { 0.133f, 0.545f, 0.133f, 1.000f },
        .fuchsia                = { 1.000f, 0.000f, 1.000f, 1.000f },
        .gainsboro              = { 0.863f, 0.863f, 0.863f, 1.000f },
        .ghost_white            = { 0.973f, 0.973f, 1.000f, 1.000f },
        .gold                   = { 1.000f, 0.843f, 0.000f, 1.000f },
        .goldenrod              = { 0.855f, 0.647f, 0.125f, 1.000f },
        .gray                   = { 0.502f, 0.502f, 0.502f, 1.000f },
        .green                  = { 0.000f, 0.502f, 0.000f, 1.000f },
        .green_yellow           = { 0.678f, 1.000f, 0.184f, 1.000f },
        .honeydew               = { 0.941f, 1.000f, 0.941f, 1.000f },
        .hot_pink               = { 1.000f, 0.412f, 0.706f, 1.000f },
        .indian_red             = { 0.804f, 0.361f, 0.361f, 1.000f },
        .indigo                 = { 0.294f, 0.000f, 0.510f, 1.000f },
        .ivory                  = { 1.000f, 1.000f, 0.941f, 1.000f },
        .khaki                  = { 0.941f, 0.902f, 0.549f, 1.000f },
        .lavender               = { 0.902f, 0.902f, 0.980f, 1.000f },
        .lavender_blush         = { 1.000f, 0.941f, 0.961f, 1.000f },
        .lawn_green             = { 0.486f, 0.988f, 0.000f, 1.000f },
        .lemon_chiffon          = { 1.000f, 0.980f, 0.804f, 1.000f },
        .light_blue             = { 0.678f, 0.847f, 0.902f, 1.000f },
        .light_coral            = { 0.941f, 0.502f, 0.502f, 1.000f },
        .light_cyan             = { 0.878f, 1.000f, 1.000f, 1.000f },
        .light_goldenrod_yellow = { 0.980f, 0.980f, 0.824f, 1.000f },
        .light_green            = { 0.565f, 0.933f, 0.565f, 1.000f },
        .light_gray             = { 0.827f, 0.827f, 0.827f, 1.000f },
        .light_pink             = { 1.000f, 0.714f, 0.757f, 1.000f },
        .light_salmon           = { 1.000f, 0.627f, 0.478f, 1.000f },
        .light_sea_green        = { 0.125f, 0.698f, 0.667f, 1.000f },
        .light_sky_blue         = { 0.529f, 0.808f, 0.980f, 1.000f },
        .light_slate_gray       = { 0.467f, 0.533f, 0.600f, 1.000f },
        .light_steel_blue       = { 0.690f, 0.769f, 0.871f, 1.000f },
        .light_yellow           = { 1.000f, 1.000f, 0.878f, 1.000f },
        .lime                   = { 0.000f, 1.000f, 0.000f, 1.000f },
        .lime_green             = { 0.196f, 0.804f, 0.196f, 1.000f },
        .linen                  = { 0.980f, 0.941f, 0.902f, 1.000f },
        .magenta                = { 1.000f, 0.000f, 1.000f, 1.000f },
        .maroon                 = { 0.502f, 0.000f, 0.000f, 1.000f },
        .medium_aquamarine      = { 0.400f, 0.804f, 0.667f, 1.000f },
        .medium_blue            = { 0.000f, 0.000f, 0.804f, 1.000f },
        .medium_orchid          = { 0.729f, 0.333f, 0.827f, 1.000f },
        .medium_purple          = { 0.576f, 0.439f, 0.859f, 1.000f },
        .medium_sea_green       = { 0.235f, 0.702f, 0.443f, 1.000f },
        .medium_slate_blue      = { 0.482f, 0.408f, 0.933f, 1.000f },
        .medium_spring_green    = { 0.000f, 0.980f, 0.604f, 1.000f },
        .medium_turquoise       = { 0.282f, 0.820f, 0.800f, 1.000f },
        .medium_violet_red      = { 0.780f, 0.082f, 0.522f, 1.000f },
        .midnight_blue          = { 0.098f, 0.098f, 0.439f, 1.000f },
        .mint_cream             = { 0.961f, 1.000f, 0.980f, 1.000f },
        .misty_rose             = { 1.000f, 0.894f, 0.882f, 1.000f },
        .moccasin               = { 1.000f, 0.894f, 0.710f, 1.000f },
        .navajo_white           = { 1.000f, 0.871f, 0.678f, 1.000f },
        .navy                   = { 0.000f, 0.000f, 0.502f, 1.000f },
        .old_lace               = { 0.992f, 0.961f, 0.902f, 1.000f },
        .olive                  = { 0.502f, 0.502f, 0.000f, 1.000f },
        .olive_drab             = { 0.420f, 0.557f, 0.137f, 1.000f },
        .orange                 = { 1.000f, 0.647f, 0.000f, 1.000f },
        .orange_red             = { 1.000f, 0.271f, 0.000f, 1.000f },
        .orchid                 = { 0.855f, 0.439f, 0.839f, 1.000f },
        .pale_goldenrod         = { 0.933f, 0.910f, 0.667f, 1.000f },
        .pale_green             = { 0.596f, 0.984f, 0.596f, 1.000f },
        .pale_turquoise         = { 0.686f, 0.933f, 0.933f, 1.000f },
        .pale_violet_red        = { 0.859f, 0.439f, 0.576f, 1.000f },
        .papaya_whip            = { 1.000f, 0.937f, 0.835f, 1.000f },
        .peach_puff             = { 1.000f, 0.855f, 0.725f, 1.000f },
        .peru                   = { 0.804f, 0.522f, 0.247f, 1.000f },
        .pink                   = { 1.000f, 0.753f, 0.796f, 1.000f },
        .plum                   = { 0.867f, 0.627f, 0.867f, 1.000f },
        .powder_blue            = { 0.690f, 0.878f, 0.902f, 1.000f },
        .purple                 = { 0.502f, 0.000f, 0.502f, 1.000f },
        .red                    = { 1.000f, 0.000f, 0.000f, 1.000f },
        .rosy_brown             = { 0.737f, 0.561f, 0.561f, 1.000f },
        .royal_blue             = { 0.255f, 0.412f, 0.882f, 1.000f },
        .saddle_brown           = { 0.545f, 0.271f, 0.075f, 1.000f },
        .salmon                 = { 0.980f, 0.502f, 0.447f, 1.000f },
        .sandy_brown            = { 0.957f, 0.643f, 0.376f, 1.000f },
        .sea_green              = { 0.180f, 0.545f, 0.341f, 1.000f },
        .sea_shell              = { 1.000f, 0.961f, 0.933f, 1.000f },
        .sienna                 = { 0.627f, 0.322f, 0.176f, 1.000f },
        .silver                 = { 0.753f, 0.753f, 0.753f, 1.000f },
        .sky_blue               = { 0.529f, 0.808f, 0.922f, 1.000f },
        .slate_blue             = { 0.416f, 0.353f, 0.804f, 1.000f },
        .slate_gray             = { 0.439f, 0.502f, 0.565f, 1.000f },
        .snow                   = { 1.000f, 0.980f, 0.980f, 1.000f },
        .spring_green           = { 0.000f, 1.000f, 0.498f, 1.000f },
        .steel_blue             = { 0.275f, 0.510f, 0.706f, 1.000f },
        .tan                    = { 0.824f, 0.706f, 0.549f, 1.000f },
        .teal                   = { 0.000f, 0.502f, 0.502f, 1.000f },
        .thistle                = { 0.847f, 0.749f, 0.847f, 1.000f },
        .tomato                 = { 1.000f, 0.388f, 0.278f, 1.000f },
        .turquoise              = { 0.251f, 0.878f, 0.816f, 1.000f },
        .violet                 = { 0.933f, 0.510f, 0.933f, 1.000f },
        .wheat                  = { 0.961f, 0.871f, 0.702f, 1.000f },
        .white                  = { 1.000f, 1.000f, 1.000f, 1.000f },
        .white_smoke            = { 0.961f, 0.961f, 0.961f, 1.000f },
        .yellow                 = { 1.000f, 1.000f, 0.000f, 1.000f },
        .yellow_green           = { 0.604f, 0.804f, 0.196f, 1.000f },
    },
    .fp32 = ui_colors_fp32
};
