#include "application.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    application_t* app = application_init();
    if (app == NULL) {
        printf("[ERROR]: Failed to initialize application\n");
        return 0;
    }
    application_run(app);
    application_quit(app);
}
