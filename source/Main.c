#include <stdio.h>
#include <ogc/system.h>
#include <ogc/video.h>
#include <ogc/console.h>
#include <wiiuse/wpad.h>

int main(void)
{
    VIDEO_Init();
    WPAD_Init();

    GXRModeObj *video_mode = VIDEO_GetPreferredMode(NULL);

    void *framebuffer = MEM_K0_TO_K1(
        SYS_AllocateFramebuffer(video_mode)
    );

    console_init(
        framebuffer,
        20, 20,
        video_mode->fbWidth,
        video_mode->xfbHeight,
        video_mode->fbWidth * VI_DISPLAY_PIX_SZ
    );

    VIDEO_Configure(video_mode);
    VIDEO_SetNextFramebuffer(framebuffer);
    VIDEO_SetBlack(FALSE);
    VIDEO_Flush();
    VIDEO_WaitVSync();

    printf("\x1b[2J");
    printf("================================\n");
    printf("       COUNTER-STRIKE WII\n");
    printf("================================\n\n");

    printf("CS Wii Engine 0.1\n");
    printf("Platform: Nintendo Wii\n");
    printf("Graphics: GX ready\n");
    printf("Input: WPAD initialized\n\n");

    printf("FIRST ENGINE TEST\n\n");
    printf("Video initialized successfully.\n");
    printf("Controller system initialized.\n\n");
    printf("Press HOME to exit.\n");

    while (1)
    {
        WPAD_ScanPads();

        u32 buttons = WPAD_ButtonsDown(0);

        if (buttons & WPAD_BUTTON_HOME)
            break;

        VIDEO_WaitVSync();
    }

    return 0;
}

