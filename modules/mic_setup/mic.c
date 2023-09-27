#include "mic.h"

#include <getopt.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <string.h>

#include "pv_recorder.h"
#include "pv_rhino.h"


volatile bool is_interrupted = false;
static pv_recorder_status_t recorder_status;
static pv_recorder_t *recorder = NULL;
static int16_t *pcm = NULL;
static pv_rhino_t *rhino = NULL;
void *rhino_library = NULL;
static pv_status_t (*pv_rhino_process_func)(pv_rhino_t *, const int16_t *, bool *);
static const char* (*pv_status_to_string_func)(pv_status_t);
static pv_status_t (*pv_rhino_get_intent_func)(const pv_rhino_t *, const char **, int32_t *, const char ***, const char ***);
static pv_status_t (*pv_rhino_is_understood_func)(const pv_rhino_t *, bool *);
static pv_status_t (*pv_rhino_free_slots_and_values_func)(const pv_rhino_t *, const char **, const char **);
static pv_status_t (*pv_rhino_reset_func)(pv_rhino_t *);
static void (*pv_rhino_delete_func)(pv_rhino_t *);

static void *open_dl(const char *dl_path) {    return dlopen(dl_path, RTLD_NOW);}
static void *load_symbol(void *handle, const char *symbol) { return dlsym(handle, symbol);}
static void close_dl(void *handle) { dlclose(handle);}
static void print_dl_error(const char *message) { fprintf(stderr, "%s with '%s'.\n", message, dlerror());}

static struct option long_options[] = {
        {"access_key",            required_argument, NULL, 'a'},
        {"library_path",          required_argument, NULL, 'l'},
        {"model_path",            required_argument, NULL, 'm'},
        {"context_path",          required_argument, NULL, 'c'},
        {"audio_device_index",    required_argument, NULL, 'd'},
        {"sensitivity",           required_argument, NULL, 't'},
        {"endpoint_duration_sec", required_argument, NULL, 'u'},
        {"require_endpoint",      required_argument, NULL, 'e'},
        {"show_audio_devices",    no_argument,       NULL, 's'},
};

static void print_usage(const char *program_name) {
    fprintf(stderr,
            "Usage : %s -a ACCESS_KEY -l LIBRARY_PATH -m MODEL_PATH -c CONTEXT_PATH [-d AUDIO_DEVICE_INDEX] "
            "[-t SENSITIVITY]  [-u, --endpoint_duration_sec] [-e, --require_endpoint (true,false)]\n"
            "        %s [-s, --show_audio_devices]\n",
            program_name,
            program_name);
}

void interrupt_handler(int _) {
    (void) _;
    is_interrupted = true;
}

void show_audio_devices(void) {
    char **devices = NULL;
    int32_t count = 0;

    pv_recorder_status_t status = pv_recorder_get_audio_devices(&count, &devices);
    if (status != PV_RECORDER_STATUS_SUCCESS) {
        fprintf(stderr, "Failed to get audio devices with: %s.\n", pv_recorder_status_to_string(status));
        exit(1);
    }

    fprintf(stdout, "Printing devices...\n");
    for (int32_t i = 0; i < count; i++) {
        fprintf(stdout, "index: %d, name: %s\n", i, devices[i]);
    }

    pv_recorder_free_device_list(count, devices);
}

void setup_microphone(int argc, char** argv)
{
    signal(SIGINT, interrupt_handler);

    const char *access_key = NULL;
    const char *library_path = NULL;
    const char *model_path = NULL;
    const char *context_path = NULL;
    int32_t device_index = -1;
    float sensitivity = 0.5f;
    float endpoint_duration_sec = 1.f;
    bool require_endpoint = true;

    int c;
    while ((c = getopt_long(argc, argv, "a:l:m:c:d:t:u:e:s", long_options, NULL)) != -1) {
        switch (c) {
            case 'a':
                access_key = optarg;
                break;
            case 'l':
                library_path = optarg;
                break;
            case 'm':
                model_path = optarg;
                break;
            case 'c':
                context_path = optarg;
                break;
            case 'd':
                device_index = (int32_t) strtol(optarg, NULL, 10);
                break;
            case 't':
                sensitivity = strtof(optarg, NULL);
                break;
            case 'u':
                endpoint_duration_sec = strtof(optarg, NULL);
                break;
            case 'e':
                require_endpoint = (strcmp(optarg, "false") != 0);
                break;
            case 's':
                show_audio_devices();
                return;
            default:
                exit(1);
        }
    }

    if (!access_key || !library_path || !model_path || !context_path) {
        print_usage(argv[0]);
        exit(1);
    }

    rhino_library = open_dl(library_path);
    if (!rhino_library) {
        fprintf(stderr, "failed to open library.\n");
        exit(1);
    }

    pv_status_to_string_func = load_symbol(rhino_library, "pv_status_to_string");
    if (!pv_status_to_string_func) {
        print_dl_error("failed to load 'pv_status_to_string'");
        exit(1);
    }

    int32_t (*pv_sample_rate_func)() = load_symbol(rhino_library, "pv_sample_rate");
    if (!pv_sample_rate_func) {
        print_dl_error("failed to load 'pv_sample_rate'");
        exit(1);
    }

    pv_status_t (*pv_rhino_init_func)( const char *, const char *, const char *, float, float, bool, pv_rhino_t **) = load_symbol(rhino_library, "pv_rhino_init");
    if (!pv_rhino_init_func) {
        print_dl_error("failed to load 'pv_rhino_init'");
        exit(1);
    }

    pv_rhino_delete_func = load_symbol(rhino_library, "pv_rhino_delete");
    if (!pv_rhino_delete_func) {
        print_dl_error("failed to load 'pv_rhino_delete'");
        exit(1);
    }

    pv_rhino_process_func = load_symbol(rhino_library, "pv_rhino_process");
    if (!pv_rhino_process_func) {
        print_dl_error("failed to load 'pv_rhino_process'");
        exit(1);
    }

    pv_rhino_is_understood_func = load_symbol(rhino_library, "pv_rhino_is_understood");
    if (!pv_rhino_is_understood_func) {
        print_dl_error("failed to load 'pv_rhino_is_understood'");
        exit(1);
    }

    pv_rhino_get_intent_func = load_symbol(rhino_library, "pv_rhino_get_intent");
    if (!pv_rhino_get_intent_func) {
        print_dl_error("failed to load 'pv_rhino_get_intent'");
        exit(1);
    }

    pv_rhino_free_slots_and_values_func = load_symbol(rhino_library, "pv_rhino_free_slots_and_values");
    if (!pv_rhino_free_slots_and_values_func) {
        print_dl_error("failed to load 'pv_rhino_free_slots_and_values'");
        exit(1);
    }

    pv_rhino_reset_func = load_symbol(rhino_library, "pv_rhino_reset");
    if (!pv_rhino_reset_func) {
        print_dl_error("failed to load 'pv_rhino_reset'");
        exit(1);
    }

    pv_status_t (*pv_rhino_context_info_func)(const pv_rhino_t *, const char **) = load_symbol(rhino_library, "pv_rhino_context_info");
    if (!pv_rhino_context_info_func) {
        print_dl_error("failed to load 'pv_rhino_context_info'");
        exit(1);
    }

    int32_t (*pv_rhino_frame_length_func)() = load_symbol(rhino_library, "pv_rhino_frame_length");
    if (!pv_rhino_frame_length_func) {
        print_dl_error("failed to load 'pv_rhino_frame_length'n");
        exit(1);
    }

    const char *(*pv_rhino_version_func)() = load_symbol(rhino_library, "pv_rhino_version");
    if (!pv_rhino_version_func) {
        print_dl_error("failed to load 'pv_rhino_version'");
        exit(1);
    }

    pv_status_t status = pv_rhino_init_func( access_key, model_path, context_path, sensitivity, endpoint_duration_sec, require_endpoint, &rhino);
    if (status != PV_STATUS_SUCCESS) {
        fprintf(stderr, "'pv_rhino_init' failed with '%s'\n", pv_status_to_string_func(status));
        exit(1);
    }

    fprintf(stdout, "Picovoice Rhino Speech-to-Intent (%s)\n\n", pv_rhino_version_func());

    const int32_t frame_length = pv_rhino_frame_length_func();
    recorder_status = pv_recorder_init(device_index, frame_length, 100, true, true, &recorder);
    if (recorder_status != PV_RECORDER_STATUS_SUCCESS) {
        fprintf(stderr, "Failed to initialize device with %s.\n", pv_recorder_status_to_string(recorder_status));
        exit(1);
    }

    const char *context_info = NULL;
    status = pv_rhino_context_info_func(rhino, &context_info);
    if (status != PV_STATUS_SUCCESS) {
        fprintf(stderr, "'pv_rhino_context_info' failed with '%s'\n", pv_status_to_string_func(status));
        exit(1);
    }
    fprintf(stdout, "%s\n\n", context_info);

    const char *selected_device = pv_recorder_get_selected_device(recorder);
    fprintf(stdout, "Selected device: %s.\n", selected_device);
    fprintf(stdout, "Listening...\n\n");

    recorder_status = pv_recorder_start(recorder);
    if (recorder_status != PV_RECORDER_STATUS_SUCCESS) {
        fprintf(stderr, "Failed to start device with %s.\n", pv_recorder_status_to_string(recorder_status));
        exit(1);
    }

    pcm = malloc(frame_length * sizeof(int16_t));
    if (!pcm) {
        fprintf(stderr, "Failed to allocate pcm memory.\n");
        exit(1);
    }
}


int retrieve_mic_string(char* mic_char_intent)
{
    recorder_status = pv_recorder_read(recorder, pcm);
    if (recorder_status != PV_RECORDER_STATUS_SUCCESS) {
        fprintf(stderr, "Failed to read with %s.\n", pv_recorder_status_to_string(recorder_status));
        exit(1);
    }

    bool is_finalized = false;

    pv_recorder_status_t status = pv_rhino_process_func( rhino, pcm, &is_finalized);

    if (status != PV_STATUS_SUCCESS) {
        fprintf(stderr, "'pv_rhino_process' failed with '%s'\n", pv_status_to_string_func(status));
        exit(1);
    }

    if (is_finalized) {
        bool is_understood = false;
        status = pv_rhino_is_understood_func(rhino, &is_understood);
        if (status != PV_STATUS_SUCCESS) {
            fprintf(stderr, "'pv_rhino_is_understood' failed with '%s'\n", pv_status_to_string_func(status));
            exit(1);
        }

        const char *intent = NULL;
        int32_t num_slots = 0;
        const char **slots = NULL;
        const char **values = NULL;

        if (is_understood) {
            status = pv_rhino_get_intent_func( rhino, &intent, &num_slots, &slots, &values);
            if (status != PV_STATUS_SUCCESS) {
                fprintf(stderr, "'pv_rhino_get_intent' failed with '%s'\n", pv_status_to_string_func(status));
                exit(1);
            }
            else
            {
                strcpy(mic_char_intent, intent);
            }
        }

        fprintf(stdout, "{\n");
        fprintf(stdout, "    'is_understood' : '%s',\n", is_understood ? "true" : "false");
        if (is_understood) {
            fprintf(stdout, "    'intent' : '%s',\n", intent);
            if (num_slots > 0) {
                fprintf(stdout, "    'slots' : {\n");
                for (int32_t i = 0; i < num_slots; i++) {
                    fprintf(stdout, "        '%s' : '%s',\n", slots[i], values[i]);
                }
                fprintf(stdout, "    }\n");
            }
        }
        fprintf(stdout, "}\n");
        fflush(stdout);

        if (is_understood) {
            status = pv_rhino_free_slots_and_values_func(rhino, slots, values);
            if (status != PV_STATUS_SUCCESS) {
                fprintf(stderr, "'pv_rhino_free_slots_and_values' failed with '%s'\n", pv_status_to_string_func(status));
                exit(1);
            }
        }

        status = pv_rhino_reset_func(rhino);
        if (status != PV_STATUS_SUCCESS) {
            fprintf(stderr, "'pv_rhino_reset' failed with '%s'\n", pv_status_to_string_func(status));
            exit(1);
        }
    }
}

void shutdown_mic()
{
    recorder_status = pv_recorder_stop(recorder);
    if (recorder_status != PV_RECORDER_STATUS_SUCCESS) {
        fprintf(stderr, "Failed to stop device with %s.\n", pv_recorder_status_to_string(recorder_status));
        exit(1);
    }

    free(pcm);
    pv_recorder_delete(recorder);
    pv_rhino_delete_func(rhino);
    close_dl(rhino_library);
}
