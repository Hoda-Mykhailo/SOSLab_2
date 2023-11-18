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

    HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"MySharedMemory");

    if (hMapFile == NULL){
        fprintf( stderr, "OpenFileMapping field (%d)\n", GetLastError());
        return 1;
    }

    printf("opened Mapping fole! It took %lld micros\n", currentTimeMic() - timeMicro);
    timeMicro = currentTimeMic();

    char* pData = (char*) MapViewOfFile(
            hMapFile, FILE_MAP_READ, 0, 0, fileSize
            );

    printf("Fetched data to current process! It took %lld micros\n", currentTimeMic() - timeMicro);
    timeMicro = currentTimeMic();

    if (pData == NULL){
        fprintf(stderr, "MapViewOfFile failed (%d)\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    char *buffer = (char *) malloc(fileSize);
    strcpy( buffer,pData);
    printf("Read data to local variable! It took %lld microsec\n", currentTimeMic() - timeMicro);

    printf("Shared Data from the other process\n");

    UnmapViewOfFile(pData);
    CloseHandle(hMapFile);

    return 0;
}
