#define MAX_DYNAMIC_ICON    (100)

enum iconInfo {
    iconID,
    iconModel,
    Float:iconLocation[3],
    iconExists,
    iconInterior,
    iconWorld,
    iconObject
}
new IconInfo[MAX_DYNAMIC_ICON][iconInfo];

JavaTR:OnIconCreated(iconid)
{
    if (iconid == -1 || !IconInfo[iconid][iconExists])
        return 0;
    
    IconInfo[iconid][iconID] = cache_insert_id();
    SaveDynamicIcon(iconid);
    return 1;
}