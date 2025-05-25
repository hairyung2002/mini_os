#include "../header/Header.h"

char* findGroupById(int GID){
    GroupList *currentGroup = groupList;
    while (currentGroup != NULL){
        if (currentGroup->group && currentGroup->group->GID == GID){
            return currentGroup->group->name;
        }
        currentGroup = currentGroup->nextGroup;
    }
    return NULL;
}


//그룹 정보 로드
void loadGroup(){
    FILE* groupFile = fopen("information/Group.txt", "r");
    if (groupFile == NULL) {
        perror("Failed to open Group.txt");
        return;
    }

    groupList = NULL; // 항상 NULL로 초기화
    GroupList *last = NULL;
    char tmp[MAX_LENGTH];

    while(fgets(tmp, MAX_LENGTH, groupFile)){
        size_t len = strlen(tmp);
        if (len > 0 && tmp[len - 1] == '\n') tmp[len - 1] = '\0';

        Group *newGroup = (Group*)malloc(sizeof(Group));
        if (!newGroup) continue;

        char *ptr = strtok(tmp, " ");
        if (!ptr) { free(newGroup); continue; }
        strncpy(newGroup->name, ptr, MAX_NAME);

        ptr = strtok(NULL, " ");
        if (!ptr) { free(newGroup); continue; }
        newGroup->GID = atoi(ptr);

        GroupList *node = (GroupList*)malloc(sizeof(GroupList));
        if (!node) { free(newGroup); continue; }
        node->group = newGroup;
        node->nextGroup = NULL;

        if (!groupList) {
            groupList = node;
        } else {
            last->nextGroup = node;
        }
        last = node;
    }
    fclose(groupFile);
}
