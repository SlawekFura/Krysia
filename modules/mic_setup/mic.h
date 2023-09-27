#pragma once

#include <stdbool.h>


#define MAX_STR_INTENT_SIZE 100

void setup_microphone(int argc, char** argv);
int retrieve_mic_string(char*);
void shutdown_mic();
