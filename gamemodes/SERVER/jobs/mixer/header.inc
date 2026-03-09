#if defined JOB_MIXER

      All script job mixer by ahmazuqi

#endif

#define jobs::    jobs_
enum e_mixer {
    mixerSelectCase,
    mixerAmount[5],
    mixerConfirm[5],
    mixerVehicle,
    mixerTimer,
    mixerSlumpTimer,
    mixerSlump,
    bool:mixerDuty[3],
};
new jobs_mixer[MAX_PLAYERS][e_mixer];

//batching
new Text: jobs::Gmixer[15], PlayerText: jobs::Pmixer[MAX_PLAYERS][11];
//bar
new Text: jobs::GBMixer[3], PlayerText: jobs::PBMixer[MAX_PLAYERS];


