#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(){

    const char* filename = "archivo.dat"; // Creación de archivo
    int fd;
    struct stat file_info;
    void* mapped_file;

    printf("Inicio proyección de archivos!\n");

    // Abrir el archivo en modo lectura/escritura
    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error al abrir el archivo");
        exit(1);
    }
     // Obtener información sobre el archivo (tamaño, etc.)
    if (fstat(fd, &file_info) == -1) {
        perror("Error al obtener información del archivo");
        exit(1);
    }
    // Proyectar el archivo en memoria

    mapped_file = mmap(NULL, file_info.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    if (mapped_file == MAP_FAILED) {
        perror("Error al proyectar el archivo en memoria");
        exit(1);
    }

    
    printf(fstat(fd, &file_info));
    printf("Acabo\n");
    return 0;
}
