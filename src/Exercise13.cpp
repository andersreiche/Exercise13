#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#define COLOR_BLUE "\x1b[34m"
#define COLOR_RED "\x1b[31m"
#define COLOR_DEFAULT "\x1b[0m"
using namespace std;

// Formats a struct timespec into a buffer.
int timespec2str(char *buf, uint len, struct timespec *ts) {
	int ret;
	struct tm t;
	tzset();
	if (localtime_r(&(ts->tv_sec), &t) == NULL) {
		return 1;
	}
	ret = strftime(buf, len, "%F %T", &t);
	if (ret == 0) {
		return 2;
	}
	len -= ret - 1;
	return 0;
}

void show_folder_content(const char* path) {
	const uint TIME_FMT = strlen("2012-12-31 12:59:59.123456789") + 1;
	struct stat buf;
	char timespec[TIME_FMT];
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(path)) != NULL) {
		// print all the files and directories within directory
		printf(COLOR_RED
				"\t\t\t\t\t name\t\tsize (bytes)\t  last modified\n"
				COLOR_DEFAULT);
		while ((ent = readdir(dir)) != NULL) {
			stat(ent->d_name, &buf);
			printf(COLOR_BLUE"%45s"COLOR_DEFAULT, ent->d_name);
			printf("%15ld bytes", buf.st_size);
			timespec2str(timespec, sizeof(timespec), &buf.st_mtim);
			printf("%25s\n", timespec);
		}
		closedir(dir);
	} else {
		// could not open directory
		perror("Could not open file");

	}
}

int main(int argc, char ** argv) {
if (argc < 2) {
	cout << endl << endl;
	printf(COLOR_RED
			"Usage:   ./Exercise13 <Folder path starting from root>\n"
			COLOR_DEFAULT);
	printf(COLOR_RED
			"Example: ./Exercise13 /home/Anders/workspaces/Exercise13"
			COLOR_DEFAULT);
	cout << endl << endl;
	return (1);
}
const char* path = argv[1];
show_folder_content(path);
return (0);
}
