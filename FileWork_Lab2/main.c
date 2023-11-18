#include <stdio.h>
#include <pthread_time.h>
#include <windows.h>


long long currentTimeMic(){
    struct timespec currentTime;
    clock_gettime(CLOCK_REALTIME, &currentTime);

    long long millisecond = (currentTime.tv_sec * 1000000LL) + (currentTime.tv_nsec / 1000LL);
    return millisecond;

}
int main() {
    int fileSize = 30 * 1024 * 1024;
    long long timeMicro = currentTimeMic();

    FILE *file = fopen("C\\Users\\User\\ClionProjects\\FileWork_Lab2\\test_file.txt", "rw");

//    if (file == NULL){
//        printf("Unable to open the file.\n");
//        return 1;
//    }

    printf("Open filed! It took %lld micros\n", currentTimeMic() - timeMicro);
    timeMicro = currentTimeMic();

    char *buffer = (char *) malloc(fileSize);
    fread(buffer, 1, fileSize, file);
    printf("Read file to local variable! It took %lld micros\n", currentTimeMic() - timeMicro);
    timeMicro = currentTimeMic();

    fclose(file);
    printf("Close file! It took %lld micros\n", currentTimeMic() - timeMicro);
    timeMicro = currentTimeMic();

    file = fopen("C\\Users\\User\\ClionProjects\\FileWork_Lab2\\file_Other.txt", "rw+");
    printf("Open filed! It took %lld micros\n", currentTimeMic() - timeMicro);
    timeMicro = currentTimeMic();

    fwrite(buffer, 1, fileSize, file);

    fclose(file);
    file = fopen("C\\Users\\User\\ClionProjects\\FileWork_Lab2\\file_Other.txt", "rw+");
    fclose(file);
    printf("Write to file! It took %lld micros\n", currentTimeMic() - timeMicro);
    return 0;
}
