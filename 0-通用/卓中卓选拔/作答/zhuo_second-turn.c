#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_PATH 260

// 定义文件属性
//这些文件属性的定义来源于Windows API的约定。虽然在这个具体的例子中你可以使用其他数字来表示这些属性，但使用与Windows相同的数值有助于保持一致性和可读性。
// 如果你要替换这些数字，重要的是确保每个属性都用不同的数值表示，并且这些数值在你的应用程序中具有明确且唯一的含义。

#define FILE_ATTRIBUTE_DIRECTORY 0x10
#define FILE_ATTRIBUTE_NORMAL 0x80
#define FILE_ATTRIBUTE_NOT_FOUND 0xFFFFFFFF

// 函数功能： 将Windows路径转换为Linux路径
// 传入参数：win_path：Windows路径下的地址，linux_path：转化后Linux路径下的地址
// 返回值 ： 无
void convert_path(const char *win_path, char *linux_path) {
    int j = 0;
    for (int i = 0; win_path[i] != '\0' && j < MAX_PATH - 1; i++, j++) {
        if (win_path[i] == '\\') {
            linux_path[j] = '/';
        } else {
            linux_path[j] = win_path[i];
        }
    }
    linux_path[j] = '\0'; // 确保字符串以空字符结尾
}

// 函数功能：模拟Windows的CreateFile函数
// 传入参数：win_path：Windows路径下的地址，desired_access：文件权限 1为只读 2为只写 3为读写，如果没有文件则创建文件
// 返回值： 文件描述符
int CreateFile(const char *win_path, int desired_access) {
    char linux_path[MAX_PATH];
    convert_path(win_path, linux_path);
    printf("Converted path: %s\n", linux_path); // 打印转换后的路径

    //设置文件打开模式flags
    int flags = 0;
    if ((desired_access & 3) == 1) {
        flags = O_RDONLY;
    } else if ((desired_access & 3) == 2) {
        flags = O_WRONLY|O_CREAT;
    } else if ((desired_access & 3) == 3) {
        flags = O_RDWR | O_TRUNC|O_CREAT;    //O_RDWR、O_CREAT 和 O_TRUNC 是 open 函数的选项标志，它们定义了文件的打开方式
    }

    // 添加文件权限标志
    int fd = open(linux_path, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd < 0) {
        perror("CreateFile: open");
    }
    return fd;
}

//函数功能： 简化模拟Windows的ReadFile函数
//传入参数：fd：要读取数据的文件的文件描述符    void *buffer：这是一个指向内存缓冲区的指针，用于存储从文件中读取的数据。
//         size_t bytes_to_read：这个参数指定了要从文件中读取的字节数。size_t *bytes_read：这是一个指向 size_t 类型的指针，用于存储实际从文件中读取的字节数。
//返回值： ssize_t 类型的返回值表示 read 函数的结果，成功时是实际读取的字节数，出错时为 -1。
ssize_t ReadFile(int fd, void *buffer, size_t bytes_to_read, size_t *bytes_read) {
    ssize_t result = read(fd, buffer, bytes_to_read); // 从文件中读取数据
    if (result >= 0) {
        *bytes_read = result; // 更新实际读取的字节数
    } else {
        perror("ReadFile: read");
    }
    return result;
}

//函数功能： 简化模拟Windows的WriteFile
//传入参数：  fd：要读取数据的文件的文件描述符  const void *buffer：这是一个指向要写入的数据的内存缓冲区的指针。
//           size_t bytes_to_write：这个参数指定了要从 buffer 写入文件的字节数     size_t *bytes_written：用于存储实际写入文件的字节数
//返回值：  成功写入返回实际写入的字节数，写入失败，程序退出，打印"WriteFile: write"
ssize_t WriteFile(int fd, const void *buffer, size_t bytes_to_write, size_t *bytes_written) {
    ssize_t result = write(fd, buffer, bytes_to_write); //从文件描述符 fd 指向的文件中读取 bytes_to_read 字节的数据，并将这些数据存储到 buffer 指向的内存位置。
    if (result >= 0) {
        *bytes_written = result;                    // 更新实际写入的字节数
    } else {
        perror("WriteFile: write");
    }
    return result;
}

// 函数功能： 简化模拟Windows的CloseHandle
//传入参数： fd：要读取数据的文件的文件描述符
//返回值： 失败返回-1 成功返回0
int CloseHandle(int fd) {
    if (close(fd) < 0) {
        perror("CloseHandle: close");
        return -1;
    }
    return 0;
}

// 函数功能： 模拟模Windows的GetFileAttributes 函数
// 传入参数： Windows下的路径
// 返回值： 是目录则返回FILE_ATTRIBUTE_DIRECTORY，不是则返回 FILE_ATTRIBUTE_NORMAL
unsigned int GetFileAttributes(const char *win_path) {
    char linux_path[MAX_PATH];
    convert_path(win_path, linux_path); // 转换Windows路径为Linux路径

    struct stat st;                                             //定义一个 stat 结构体变量 st。这个结构体用于存储文件状态信息。
    if (stat(linux_path, &st) < 0) {              //调用 stat 函数获取 linux_path 指向的文件或目录的状态信息，并将结果存储在 st 中。
                    // 如果 stat 函数返回值小于0，说明获取文件状态信息失败。此时，使用 perror 函数输出错误信息，并返回 FILE_ATTRIBUTE_NOT_FOUND，表示文件未找到。
        perror("GetFileAttributes: stat");
        return FILE_ATTRIBUTE_NOT_FOUND;
    }


    if (S_ISDIR(st.st_mode)) {                                      //检查 st.st_mode 中的文件类型信息
        return FILE_ATTRIBUTE_DIRECTORY;                        //如果 S_ISDIR(st.st_mode) 为真，说明路径指向的是一个目录，返回 FILE_ATTRIBUTE_DIRECTORY。
    } else {
        return FILE_ATTRIBUTE_NORMAL;                                //否则，返回 FILE_ATTRIBUTE_NORMAL，表示路径指向的是一个普通文件。
    }
}

// 函数功能： 重命名文件（目标路径与源路径不统一）或者移动文件（目标路径与源路径统一）
// 传入参数：  const char *src_win_path：表示源文件的Windows风格的文件路径。
//           const char *dest_win_path：表示目标文件的Windows风格的文件路径
//返回值： 成功返回1 失败返回-1
int MoveFile(const char *src_win_path, const char *dest_win_path) {
    char src_linux_path[MAX_PATH];
    char dest_linux_path[MAX_PATH];
    convert_path(src_win_path, src_linux_path); // 转换源Windows路径为Linux路径
    convert_path(dest_win_path, dest_linux_path); // 转换目标Windows路径为Linux路径

    if (rename(src_linux_path, dest_linux_path) < 0) {
        perror("MoveFile: rename");
        return -1;
    }
    return 0;
}

// 函数功能： 模拟删除文件
//传入参数： 文件在 windows下的路径
//返回值： 成功返回0 失败返回-1
int DeleteFile(const char *win_path) {
    char linux_path[MAX_PATH];
    convert_path(win_path, linux_path); // 转换Windows路径为Linux路径

    if (unlink(linux_path) < 0) {
        perror("DeleteFile: unlink");
        return -1;
    }
    return 0;
}


int main() {
    char file_path[MAX_PATH];               // 分配缓冲区用于存储文件路径
    printf("指定文件路径: \n");
    if (scanf("%259s", file_path) != 1) {   //测试路径为"text\text.txt"
        fprintf(stderr, "Error: Invalid input.\n");
        return 1;
    }

    //1.打开/创建文件
    int fd = CreateFile(file_path, 3); // 打开文件以读写模式
    if (fd < 0) {
        return 1;
    }

    //2.将data的数据写入文件
    const char *data = "Hello,World";
    size_t bytes_written; // 声明变量，用于存储实际写入的字节数
    if (WriteFile(fd, data, strlen(data), &bytes_written) < 0) {
        CloseHandle(fd);
        return 1;
    }
    printf("Bytes Written: %zu\n", bytes_written); // 打印实际写入的字节数

    //3 读取文件内容
    char buffer[100];               //从文件中读取数据的缓冲区。
    size_t bytes_read;              //存储实际从文件中读取的字节数。
    if (lseek(fd, 0, SEEK_SET) < 0) { // 重置文件偏移量到文件开始
        perror("lseek");
        CloseHandle(fd);
        return 1;
    }
    if (ReadFile(fd, buffer, sizeof(buffer) - 1, &bytes_read) < 0) {        //读取文件
        CloseHandle(fd);
        return 1;
    }
    buffer[bytes_read] = '\0'; // 确保缓冲区以NULL结尾
    printf("Bytes Read: %zu\n", bytes_read);
    printf("Data: %s\n", buffer);

    //4. 关闭文件
    if (CloseHandle(fd) < 0) {
        return 1;
    }

    //5.检查文件的属性
    unsigned int attrs = GetFileAttributes(file_path);
    if (attrs == FILE_ATTRIBUTE_NOT_FOUND) {
        fprintf(stderr, "File not found.\n");
        return 1;
    } else if (attrs == FILE_ATTRIBUTE_DIRECTORY) {
        printf("The path is a directory.\n");
        return 1;
    } else {
        printf("The path is a normal file.\n");
    }

    // 6. 测试删除文件
    if (DeleteFile(file_path) == 0) {
        printf("File deleted successfully.\n");
    } else {
        printf("Failed to delete file.\n");
    }

    // 7. 测试移动文件
    if (MoveFile("source.txt", "destination.txt") == 0) {
        printf("File moved successfully.\n");
    } else {
        printf("Failed to move file.\n");
    }
    return 0;
}
