#include <Arduino.h>

#include "RCRecord.h"

void RCRecord::record_value(char value)
{
    if(recorded_data[last_record].value == value) {
        recorded_data[last_record].num_times += 1;
    } else if (last_record < MAX_NUM_RECORDS - 1) {
        // Case when no data is yet present in the 0th index
        if(recorded_data[last_record].value != 0) {
            last_record++;
        }
        recorded_data[last_record].value = value;
        recorded_data[last_record].num_times = 1;
    }
}

void RCRecord::clear()
{
    last_record = 0;
    recorded_data[last_record].value = 0;
    recorded_data[last_record].num_times = 0;
    do_playback = false;
}

void RCRecord::print_values()
{
    // Last record is an index, not a count
    for(int idx = 0; idx <= last_record; idx++) {
        Serial.print(idx);
        Serial.print(": ");
        Serial.print("Key: ");
        Serial.print(recorded_data[idx].value);
        Serial.print(" ("); 
        Serial.print((int) recorded_data[idx].value);
        Serial.print(")");
        Serial.print(" ");
        Serial.print(recorded_data[idx].num_times);
        Serial.println(" times");
    }
}

void RCRecord::play_back()
{
    do_playback = true;
    playback_idx = 0;
    playback_times_count = 0;
}

bool RCRecord::available()
{
    if(do_playback && playback_times_count > recorded_data[playback_idx].num_times) {
        playback_idx++;
        playback_times_count = 0;
    }

    if (playback_idx > last_record || playback_idx >= MAX_NUM_RECORDS) {
        do_playback = false;
    }

    if (do_playback) {
        return true;
    } else {
        return RCSwitch::available();
    }
}

unsigned long RCRecord::getReceivedValue()
{
    if (do_playback) {
        delay(PLAYBACK_DELAY);
        playback_times_count++;
        return recorded_data[playback_idx].value;
    } else {
        return RCSwitch::getReceivedValue();
    }
}

