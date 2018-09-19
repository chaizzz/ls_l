#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int ls_l(const char* path)
{	
	int i = 0;
	struct stat st;
	DIR* dirp = opendir(path);
	struct dirent* pde = NULL;
	char old_cwd[301];
	struct passwd *getpwuid(uid_t uid);
	struct group *getgrgid(gid_t gid);


	if(dirp == NULL)
	{
		perror("opendir");
		return -1;
	}

	getcwd(old_cwd, sizeof(old_cwd));
	chdir(path);

	while(pde = readdir(dirp))
	{
		//printf("%s\n", pde->d_name);
		if(0 == stat(pde->d_name, &st))
		{
			if(S_ISDIR(st.st_mode))
			{
				//std::cout<< " 1 " <<std::endl;
				if(strcmp(pde->d_name, ".") != 0 && strcmp(pde->d_name, "..") != 0)
				{
					i += st.st_size/1024;

					std::cout<< 'd';
					if(st.st_mode&S_IRUSR)
						std::cout<< 'r';
					else
						std::cout<< '-';
					if(st.st_mode&S_IWUSR)
                                                std::cout<< 'w';
                                        else
                                                std::cout<< '-';
					if(st.st_mode&S_IXUSR)
                                                std::cout<< 'x';
                                        else
                                                std::cout<< '-';
					if(st.st_mode&S_IRGRP)
                                                std::cout<< 'r';
                                        else
                                                std::cout<< '-';
                                        if(st.st_mode&S_IWGRP)
                                                std::cout<< 'w';
                                        else
                                                std::cout<< '-';
                                        if(st.st_mode&S_IXGRP)
                                                std::cout<< 'x';
                                        else
                                                std::cout<< '-';	
					if(st.st_mode&S_IROTH)
                                                std::cout<< 'r';
                                        else
                                                std::cout<< '-';
                                        if(st.st_mode&S_IWOTH)
                                                std::cout<< 'w';
                                        else
                                                std::cout<< '-';
                                        if(st.st_mode&S_IXOTH)
                                                std::cout<< 'x';
                                        else
                                                std::cout<< '-';
					std::cout << ' ' << st.st_nlink << ' ';
					std::cout << getpwuid(st.st_uid)->pw_name << ' ';
					std::cout << getgrgid(st.st_gid)->gr_name << ' ';
					//std::cout << st.st_size << ' ';	

					struct tm* pt = localtime(&(st.st_mtime));
					const char* mon[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

					printf("%5d %s %d %d:%d", st.st_size, mon[pt->tm_mon], pt->tm_mday, pt->tm_hour, pt->tm_min);
					
					std::cout<< ' ' <<pde->d_name<<std::endl;

				}
				
			}
			else
			{
				//std::cout<< " 2 " <<std::endl;
				i += ((st.st_size/4096)+1)*4096/1024;
				std::cout<< '-';
				if(st.st_mode&S_IRUSR)
					std::cout<< 'r';
				else
					std::cout<< '-';
				if(st.st_mode&S_IWUSR)
					std::cout<< 'w';
				else
					std::cout<< '-';
				if(st.st_mode&S_IXUSR)
					std::cout<< 'x';
				else
					std::cout<< '-';
				if(st.st_mode&S_IRGRP)
					std::cout<< 'r';
				else
					std::cout<< '-';
				if(st.st_mode&S_IWGRP)
					std::cout<< 'w';
				else
					std::cout<< '-';
				if(st.st_mode&S_IXGRP)
					std::cout<< 'x';
				else
					std::cout<< '-';
				if(st.st_mode&S_IROTH)
					std::cout<< 'r';
				else
					std::cout<< '-';
				if(st.st_mode&S_IWOTH)
					std::cout<< 'w';
				else
					std::cout<< '-';
				if(st.st_mode&S_IXOTH)
					std::cout<< 'x';
				else
					std::cout<< '-';
				std::cout<< " 1 ";
				std::cout << getpwuid(st.st_uid)->pw_name << ' ';
				std::cout << getgrgid(st.st_gid)->gr_name << ' ';
				//std::cout << st.st_size << ' ';

				//printf("%4d", st.st_size);

				struct tm* pt = localtime(&(st.st_mtime));

				const char* mon[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

				printf("%5d %s %d %d:%d", st.st_size, mon[pt->tm_mon], pt->tm_mday, pt->tm_hour, pt->tm_min);			

				std::cout<< ' ' <<pde->d_name<<std::endl
;
			}
		}
	}

	chdir(old_cwd);
	closedir(dirp);
	
	//i = i*4;

	std::cout << "total " << i << std::endl;

	return 0;
}



int main(int argc, char** argv)
{

	if(argc != 2)
	{
		std::cout << "错误" <<std::endl;
	}

	
	ls_l(argv[1]);

	return 0;
}
