#include <windows.h>
#include <stdio.h>
#include <pthread_time.h>

long long currentTimeMic(){
    struct timespec currentTime;
    clock_gettime(CLOCK_REALTIME, &currentTime);

    long long millisecond = (currentTime.tv_sec * 1000000LL) + (currentTime.tv_nsec / 1000LL);
    return millisecond;
}

int main() {

    int fileSize = 30 * 1024 * 1024;
    long long timeMicro = currentTimeMic();
    FILE *file = fopen("C\\Users\\User\\ClionProjects\\Lab2\\mapped_file.txt", "rw");

    HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,
            0,
            fileSize,L"MySharedMemory"
            );

    if(hMapFile == NULL){
        fprintf(stderr, "CurrentFileMapp filed (%d)\n", GetLastError());
        return 1;
    }
    char *pData = (char *) MapViewOfFile(
            hMapFile,
            FILE_MAP_ALL_ACCESS,
            0, 0,
            fileSize
            );

    if (pData == NULL){
        fprintf(stderr, "MapViewOfFile failed (%d)\n", GetLastError());
        return 1;
    }

    char *buffer = (char *) malloc(fileSize);
    fread(buffer, 1, fileSize, file);
    timeMicro = currentTimeMic();
    strcpy( pData, buffer);
    printf("Wrote data to file! It took %lld microsec\n", currentTimeMic() - timeMicro);

    printf("Shared Data \n Press Enter to exit - - - - -");
    getchar();

    UnmapViewOfFile(pData);
    CloseHandle(hMapFile);

    return 0;
}
