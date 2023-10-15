#include "core/core.h"
#include <stdio.h>
#include "glad.h"

hc_video_callback_t video_callback;
hc_read_other_callback_t read_other_callback;

hc_core_t hc_create()
{
    void* get_proc_address = read_other_callback(HC_OTHER_GL_GET_PROC_ADDRESS);
    if (!gladLoadGLLoader((GLADloadproc)get_proc_address)) {
        printf("Failed to get OpenGL functions\n");
        return 0;
    }
    return (void*)1;
}

void hc_destroy(hc_core_t core) {}
bool hc_load_file(hc_core_t core, const char *type, const char *path) { return true; }
void hc_reset(hc_core_t core) {}

void hc_run_frame(hc_core_t core)
{
    unsigned fbo = *(unsigned*)read_other_callback(HC_OTHER_GL_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Notifies the frontend of our window dimensions
    video_callback(NULL, 200, 200);
}

const char* hc_get_info(hc_info_e info) {
    switch (info) {
        case HC_INFO_CORE_NAME: return "minimal_gl";
        case HC_INFO_SYSTEM_NAME: return "N/A";
        case HC_INFO_VERSION: return "N/A";
        case HC_INFO_LICENSE: return "MIT";
        case HC_INFO_AUTHOR: return "OFFTKP";
        case HC_INFO_DESCRIPTION: return "Minimal OpenGL hydra core";
        case HC_INFO_EXTENSIONS: return "test";
        default: return "";
    }
}

void hc_set_video_callback(hc_core_t core, hc_video_callback_t callback) { video_callback = callback; }
void hc_set_audio_callback(hc_core_t core, hc_audio_callback_t callback) {}
void hc_set_read_input_callback(hc_core_t core, hc_read_input_callback_t callback) {}
void hc_set_poll_input_callback(hc_core_t core, hc_poll_input_callback_t callback) {}
void hc_set_read_other_callback(hc_read_other_callback_t callback) { read_other_callback = callback; }
void hc_add_log_callback(hc_core_t core, const char *target, hc_log_callback_t callback) {}
