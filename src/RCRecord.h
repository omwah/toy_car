#ifndef RC_RECORD_H
#define RC_RECORD_H

#include "RCSwitch.h"

#define MAX_NUM_RECORDS 10
#define PLAYBACK_DELAY 50

class RCRecord : public RCSwitch {

public:

    RCRecord() : RCSwitch() {
        last_record = 0;
        recorded_data[last_record].value = 0;
        recorded_data[last_record].num_times = 0;
        do_playback = false;
        playback_idx = 0;
        playback_times_count = 0;
    }
    virtual bool available();
    virtual unsigned long getReceivedValue();

    virtual void record_value(char value);
    virtual void clear();

    virtual void print_values();
    virtual void play_back();

    virtual bool can_record() { return !do_playback; }

private:
    byte last_record;
    struct {
        char value;
        byte num_times;
    } recorded_data[MAX_NUM_RECORDS];
    bool do_playback;
    byte playback_idx;
    byte playback_times_count;
};

#endif
