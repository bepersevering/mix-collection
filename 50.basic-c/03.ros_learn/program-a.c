#include <stdio.h>
#include <unistd.h>

int main() {

    sleep(5);

    const char* hello_string = "Hello World!\n";

    printf(hello_string);

    FILE *output_file = fopen("program-a.txt", "w");

    fputs(hello_string, output_file);

    fclose(output_file);

    return 0;
}
