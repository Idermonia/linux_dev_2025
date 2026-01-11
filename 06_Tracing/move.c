#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

void cleanup(int in_fd, int out_fd, const char *infile, const char *outfile, char *buffer, int outfile_created) {
    if (buffer) free(buffer);
    if (in_fd >= 0) close(in_fd);
    if (out_fd >= 0) close(out_fd);
    if (outfile_created && outfile) unlink(outfile);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        return 1;
    }

    const char *infile = argv[1];
    const char *outfile = argv[2];
    int in_fd = -1, out_fd = -1;
    char *buffer = NULL;
    struct stat st;
    int outfile_created = 0;

    if (stat(infile, &st) == -1) {
        perror("stat infile");
        return 2;
    }

    in_fd = open(infile, O_RDONLY);
    if (in_fd == -1) {
        perror("open infile");
        return 3;
    }

    out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, st.st_mode & 0777);
    if (out_fd == -1) {
        perror("open outfile");
        cleanup(in_fd, -1, infile, outfile, NULL, 0);
        return 4;
    }
    outfile_created = 1;

    buffer = malloc(st.st_size);
    if (!buffer) {
        perror("malloc");
        cleanup(in_fd, out_fd, infile, outfile, NULL, outfile_created);
        return 5;
    }

    ssize_t bytes_read = read(in_fd, buffer, st.st_size);
    if (bytes_read != st.st_size) {
        perror("read");
        cleanup(in_fd, out_fd, infile, outfile, buffer, outfile_created);
        return 6;
    }

    ssize_t bytes_written = write(out_fd, buffer, st.st_size);
    if (bytes_written != st.st_size) {
        perror("write");
        cleanup(in_fd, out_fd, infile, outfile, buffer, outfile_created);
        return 7;
    }

    if (close(out_fd) == -1) {
        perror("close outfile");
        cleanup(in_fd, -1, infile, outfile, buffer, outfile_created);
        return 8;
    }
    out_fd = -1;

    if (close(in_fd) == -1) {
        perror("close infile");
        cleanup(-1, -1, infile, outfile, buffer, outfile_created);
        return 9;
    }
    in_fd = -1;

    if (unlink(infile) == -1) {
        perror("unlink infile");
        if (outfile_created) unlink(outfile);
        free(buffer);
        return 10;
    }

    free(buffer);
    return 0;
}
