#include <YSI\y_hooks>

enum e_jobkargo
{
    STREAMER_TAG_MAP_ICON:KargoIcon,
    STREAMER_TAG_AREA:KargoStartArea,
    STREAMER_TAG_3D_TEXT_LABEL:KargoLabel
};
new PlayerKargoVars[MAX_PLAYERS][e_jobkargo];