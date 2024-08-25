#include "mazemade.h"
using namespace std;
void Free_Memory() {
    for (int i = 0; i < maze.height; i++) {
        free(maze.maze_group[i]);
    }
    free(maze.maze_group);

    for (int i = 0; i < result.all_height; i++) {
        free(result.maze_info[i]);
    }
    free(result.maze_info);
}

void mazemade() {

    Free_Memory();
    int width, height;
    cout << "Enter maze width: ";
    cin >> width;
    cout << "Enter maze height: ";
    cin >> height;

    // ¹Ì·Î Å©±â ¼³Á¤
    maze.width = width;
    maze.height = height;

    srand(time(NULL));
    Init_Maze();

    for (int i = 1; i < maze.height; i++) {
        group_ornot();
        made_sero_group();
    }
    last_group_ornot();


    upload_maze_pic();

   

}


void Init_Maze() {

    result.all_width = maze.width * 2 + 1;
    result.all_height = maze.height * 2 + 1;

    maze.maze_group = (int**)malloc(sizeof(int*) * maze.height);
    for (int i = 0; i < maze.height; i++) {
        maze.maze_group[i] = (int*)malloc(sizeof(int) * maze.width);
    }

    for (; group_index <= maze.width; group_index++) {
        maze.maze_group[0][group_index - 1] = group_index;
    }

    result.maze_info = (int**)malloc(sizeof(int*) * result.all_height);
    for (int i = 0; i < result.all_height; i++) {
        result.maze_info[i] = (int*)malloc(sizeof(int) * result.all_width);
    }

    for (int i = 0; i < result.all_height; ) {
        for (int j = 0; j < result.all_width; ) {
            result.maze_info[i][j] = 3;
            j += 2;
        }
        i += 2;
    }

    for (int i = 1; i < result.all_height; ) {
        for (int j = 0; j < result.all_width; ) {
            result.maze_info[i][j] = 1;
            j += 2;
        }
        i += 2;
    }

    for (int i = 0; i < result.all_height; ) {
        for (int j = 1; j < result.all_width; ) {
            result.maze_info[i][j] = 2;
            j += 2;
        }
        i += 2;
    }

    for (int i = 1; i < result.all_height; ) {
        for (int j = 1; j < result.all_width; ) {
            result.maze_info[i][j] = 0;
            j += 2;
        }
        i += 2;
    }



}


void upload_maze_pic() {
    FILE* fp_result = fopen("C:\\Users\\±è¹ÎÁ¤\\Downloads\\of_v0.12.0_vs_release\\of_v0.12.0_vs_release\\apps\\myApps\\MAZE\\bin\\data\\result.maz", "w");
    for (int i = 0; i < result.all_height; i++) {
        for (int j = 0; j < result.all_width; j++) {
            switch (result.maze_info[i][j]) {
            case 0:
                fprintf(fp_result, "%c", ' ');
                break;

            case 1:
                fprintf(fp_result, "%c", '|');
                break;

            case 2:
                fprintf(fp_result, "%c", '-');
                break;

            case 3:
                fprintf(fp_result, "%c", '+');
            }
        }
        fprintf(fp_result, "%s", "\n");
    }

    fclose(fp_result);

}

void group_ornot() {
    int next_group, prev_group;
    int prev = 0;
    int next = 1;
    while (next < maze.width) {
        if (maze.maze_group[height_index][prev] == maze.maze_group[height_index][next]) {
            result.maze_info[2 * height_index + 1][2 * next] = 1;
            prev++;
            next++;
        }

        else {
            if (rand() % 2) {
                if (height_index > 0) {
                    next_group = maze.maze_group[height_index][next];
                    prev_group = maze.maze_group[height_index][prev];
                    maze.maze_group[height_index][next] = maze.maze_group[height_index][prev];
                    for (int i = 0; i <= height_index; i++) {
                        for (int j = 0; j < maze.width; j++) {
                            if (maze.maze_group[i][j] == next_group)
                                maze.maze_group[i][j] = prev_group;
                        }

                    }


                }
                else {
                    maze.maze_group[height_index][next] = maze.maze_group[height_index][prev];
                }
                result.maze_info[2 * height_index + 1][2 * next] = 0;
                prev++;
                next++;
            }

            prev++;
            next++;
        }


    }


    height_index++;
}

void last_group_ornot() {
    int next_group, prev_group;
    int prev = 0;
    int next = 1;
    while (next < maze.width) {
        if (maze.maze_group[height_index][prev] == maze.maze_group[height_index][next]) {
            result.maze_info[2 * height_index + 1][2 * next] = 1;
            prev++;
            next++;
        }

        else {
            if (height_index > 0) {
                next_group = maze.maze_group[height_index][next];
                prev_group = maze.maze_group[height_index][prev];
                maze.maze_group[height_index][next] = maze.maze_group[height_index][prev];
                for (int i = 0; i <= height_index; i++) {
                    for (int j = 0; j < maze.width; j++) {
                        if (maze.maze_group[i][j] == next_group)
                            maze.maze_group[i][j] = prev_group;
                    }
                }



            }
            else {
                maze.maze_group[height_index][next] = maze.maze_group[height_index][prev];
            }
            result.maze_info[2 * height_index + 1][2 * next] = 0;
            prev++;
            next++;



        }


    }


    height_index++;
}

void made_sero_group() {
    int* determine = (int*)malloc(sizeof(int) * maze.width);
    for (int i = 0; i < maze.width; i++) {
        determine[i] = 0;
    }

   
    int* only_one_index = (int*)malloc(sizeof(int) * (group_index + 1));
    int* above_index= (int*)malloc(sizeof(int) * (group_index + 1));
    int* use_index = (int*)malloc(sizeof(int) * (group_index + 1));

    for (int i = 0; i < group_index; i++) {
        above_index[i] = 0;
        use_index[i] = 0;
        only_one_index[i] = 0;
    }

    for (int i = 0; i < maze.width; i++) {
        above_index[maze.maze_group[height_index - 1][i]]++;
    }

    for (int i = 0; i < maze.width; i++) {
        if (above_index[maze.maze_group[height_index - 1][i]] == 1) only_one_index[maze.maze_group[height_index - 1][i]] = 1;
    }

    for (int i = 0; i < maze.width; i++) {
        if ((above_index[maze.maze_group[height_index - 1][i]] == 1 && !use_index[maze.maze_group[height_index - 1][i]]) || (above_index[maze.maze_group[height_index - 1][i]] == 1 && only_one_index[maze.maze_group[height_index - 1][i]] == 1)) {
            maze.maze_group[height_index][i] = maze.maze_group[height_index - 1][i];
            use_index[maze.maze_group[height_index - 1][i]] = 1;
            determine[i] = 1;
            above_index[maze.maze_group[height_index - 1][i]]--;
            result.maze_info[2 * height_index][2 * i + 1] = 0;
        }

        else {
            if (rand() % 2) {
                maze.maze_group[height_index][i] = maze.maze_group[height_index - 1][i];
                use_index[maze.maze_group[height_index - 1][i]] = 1;
                determine[i] = 1;
                result.maze_info[2 * height_index][2 * i + 1] = 0;

            }

            above_index[maze.maze_group[height_index - 1][i]]--;
        }


    }

    for (int i = 0; i < maze.width; i++) {
        if (!determine[i]) {
            maze.maze_group[height_index][i] = group_index++;
        }
    }

    free(only_one_index);
    free(above_index);
    free(use_index);
    free(determine);



}

