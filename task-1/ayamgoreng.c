#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_LINE_LENGTH 1024
#define MAX_HERO_COUNT 112

typedef struct {
    char name[50];
    char role[50];
    char tipe[50];
    int tahun_rilis;
} Identity;

typedef struct {
    char name[50];
    int hp;
    float hp_regen;
    int physical_attack;
    int physical_defense;
    float attack_speed;
    int attack_speed_pc;
    int mana;
    int mana_regen;
    int magic_power;

} Attributes;

typedef struct {
    char name[50];
    float skillpoints;
} HeroScore;

// Function prototypes
void download_and_extract();
int isDirectoryExists(const char *path);
int read_identities(const char* filename, Identity identities[]);
int read_attributes(const char* filename, Attributes attributes[]);
HeroScore calculate_best_hero(const char* role, Identity identities[], int id_count, Attributes attributes[], int att_count);

int main(int argc, char *argv[]) {
    // Download and unzip dataset
    if(isDirectoryExists("Data Mobile Legend")){
    	printf("Directory already exists, continue executing the program\n");
    }
    else{
    	download_and_extract();
    }

    Identity identities[MAX_HERO_COUNT];
    Attributes attributes[MAX_HERO_COUNT];
    HeroScore best_hero;
    const char* roles[] = {"TANK", "ASSASSIN", "FIGHTER", "MM", "MAGE", "SUPPORT"};
    int role_count = sizeof(roles) / sizeof(roles[0]);

    int id_count = read_identities("Data Mobile Legend/identitas.csv", identities);
    int att_count = read_attributes("Data Mobile Legend/Atribut/atribut-hero.csv", attributes);

    if (argc > 1) {
        best_hero = calculate_best_hero(argv[1], identities, id_count, attributes, att_count);
        printf("The best %s is %s with skillpoints %.2f\n", argv[1], best_hero.name, best_hero.skillpoints);
    } else {
        for (int i = 0; i < role_count; i++) {
            best_hero = calculate_best_hero(roles[i], identities, id_count, attributes, att_count);
            printf("The best %s is %s with skillpoints %.2f\n", roles[i], best_hero.name, best_hero.skillpoints);
        }
    }

    return 0;
}

//Functions
void download_and_extract() {
    system("kaggle datasets download -d irwansyah10010/mobilelegend -p .");
    system("unzip -o mobilelegend.zip");
}

int read_identities(const char* filename, Identity identities[]) {
    FILE* file = fopen(filename, "r");
    char buffer[MAX_LINE_LENGTH];
    int count = 0;

    if (!file) {
        printf("Failed to open file: %s\n", filename);
        return 0;
    }

    while (fgets(buffer, MAX_LINE_LENGTH, file) && count < MAX_HERO_COUNT) {
        sscanf(buffer, "%[^;];%[^;];%[^;];%d", identities[count].name, identities[count].role, identities[count].tipe, &identities[count].tahun_rilis);
        count++;
    }

    fclose(file);
    return count;
}

int read_attributes(const char* filename, Attributes attributes[]) {
    FILE* file = fopen(filename, "r");
    char buffer[MAX_LINE_LENGTH];
    int count = 0;

    if (!file) {
        printf("Failed to open file: %s\n", filename);
        return 0;
    }

    while (fgets(buffer, MAX_LINE_LENGTH, file) && count < MAX_HERO_COUNT) {
        sscanf(buffer, "%[^;];%d;%f;%d;%d;%f;%d;%d;%d;%d", attributes[count].name, &attributes[count].hp, &attributes[count].hp_regen, &attributes[count].physical_attack, &attributes[count].physical_defense, 
               &attributes[count].attack_speed, &attributes[count].attack_speed_pc, &attributes[count].mana, &attributes[count].mana_regen, &attributes[count].magic_power);
        count++;
    }
 
    fclose(file);
    return count;
}

HeroScore calculate_best_hero(const char* role, Identity identities[], int id_count, Attributes attributes[], int att_count) {
    HeroScore best_hero = {"", 0.0};
    float max_score = -1.0;
    float score;

    for (int i = 0; i < att_count; i++) {
        if (strcmp(identities[i].role, role) == 0) {
            if (strcmp(role, "TANK") == 0) {
                score = attributes[i].hp;
            } else if (strcmp(role, "ASSASSIN") == 0) {
                score = attributes[i].physical_attack;
            } else if (strcmp(role, "FIGHTER") == 0) {
                score = attributes[i].hp + attributes[i].physical_attack;
            } else if (strcmp(role, "MM") == 0) {
                score = attributes[i].physical_attack * attributes[i].attack_speed;
            } else if (strcmp(role, "MAGE") == 0) {
                score = attributes[i].mana / attributes[i].mana_regen;
            } else if (strcmp(role, "SUPPORT") == 0) {
                score = attributes[i].mana_regen + attributes[i].hp;
            } else {
                score = 0;
            }

            if (score > max_score) {
                max_score = score;
                if(strcmp(best_hero.name, "MM") == 0) strcpy(best_hero.name, "MARKSMAN");
                else strcpy(best_hero.name, identities[i].name);
                best_hero.skillpoints = score;
            }
        }
    }

    return best_hero;
}

int isDirectoryExists(const char *path) {
    struct stat stats;
    stat(path, &stats);
    if (S_ISDIR(stats.st_mode))
        return 1;

    return 0;
}
