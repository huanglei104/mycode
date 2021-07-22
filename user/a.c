#include <stdio.h>
#include <pwd.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *login;
    struct passwd *pw;

    login = getlogin();
    if(!login) return perror("getlogin"), -1;

    printf("login name: %s\n", login) ;

    pw = getpwnam(login);

    if(pw) {
	printf("name: %s\n", pw->pw_name);
	printf("home: %s\n", pw->pw_dir);
	printf("shell: %s\n", pw->pw_shell);
	printf("uid: %d\n", pw->pw_uid);
	printf("gid: %d\n", pw->pw_gid);
	printf("passwd: %s\n", pw->pw_passwd);
	printf("info: %s\n", pw->pw_gecos);
    }
    return 0;
}
