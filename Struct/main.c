#include <stdio.h>
#include <stdint.h>
#include <string.h>
struct User
{
    uint32_t uid;
    uint8_t flags;
    int angle; // значения в диапазоне [-180..180) с точностью в 1 градус
    float mass;
    char* name;
    char* email;
};

    

void save(FILE* output, struct User* user) {
    size_t a=fwrite(user, 4*sizeof(uint32_t), 1, output);
    if (a != 1) printf("Save error!");
    a = fwrite(user->name, strlen(user->name)+1, 1, output);
    if (a != 1) printf("Save error!");
    a = fwrite(user->email, strlen(user->email)+1, 1, output);
    if (a != 1) printf("Save error!");



}
void read(FILE* output, struct User* user) {
    size_t a = fread(user, 4*sizeof(uint32_t), 1, output);
   if (a != 1) printf("Read error!");
    for (int i = 0; i < 256;i++) {
        user->name[i]=fgetc(output);
        if (user->name[i] == '\0') break;
    }
    for (int i = 0; i < 256; i++) {
        user->email[i] = fgetc(output);
        if (user->email[i] == '\0') break;
    }
    printf("Uid: %d\nFlags: %hho\nAngle: %d\nMass: %f\nName: %s\nEmail: %s\n",user->uid, user->flags, user->angle, user->mass, user->name, user->email);
}

int get_struct(struct User* user) {
    struct User temp;
    int a;
    printf("Input uid:\n");
    a = scanf("%lo", &temp.uid);
    if (a <= 0) return -1;

    printf("Input flags:\n");
    a = scanf("%hho", &temp.flags);
    if (a <= 0) return -1;

    printf("Input angle:\n");
    a = scanf("%d", &temp.angle);
    if (a <= 0 || temp.angle<-180 ||temp.angle>=180) return -1;

    printf("Input mass:\n");
    a = scanf("%f", &temp.mass);  
    if (a <= 0) return -1;

    char name[256], email[256];
    printf("Input name:\n");
    a = scanf("%s", name);
    if (a <= 0) return -1;
    printf("Input email:\n");
    a = scanf("%s",email);
    if (a <= 0) return -1;

    user->uid = temp.uid;
    user->flags = temp.flags;
    user->angle = temp.angle;
    user->mass = temp.mass;
    strcpy(user->name,name);
    strcpy(user->email,email);
    
    return 0;
}
int main()
{
    struct User user;
    char name[256]="", email[256]="";
    user.name = name;
    user.email = email;
    FILE* output = NULL;
    output = fopen("book.dat", "rb");
    if (output != NULL) {
        printf("book.dat:\n");
        read(output, &user);
        return fclose(output);
        
    }
    else {
        printf("book.dat not found.\n");
        if (!get_struct(&user)) {
             output = fopen("book.dat", "wb");

             save(output, &user);
            return fclose(output);
        }
    }
}
