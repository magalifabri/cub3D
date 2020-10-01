#include "cub3d.h"

void move_enemy(t_cub3d *p)
{
    int i;
    static double time_last_move;
	clock_t	current_time;

	current_time = clock();
    i = 0;
    while ((int)p->spr[i].y != p->map_h)
    {
        if ((double)(current_time - time_last_move) / (double)CLOCKS_PER_SEC > 0.1)
        {
            p->map[(int)p->spr[i].y][(int)p->spr[i].x] = '0';
            if (p->l[p->path_steps].direction_of_origin == 'n')
                p->spr[i].y = p->spr[i].y - 1;
            else if (p->l[p->path_steps].direction_of_origin == 's')
                p->spr[i].y = p->spr[i].y + 1;
            else if (p->l[p->path_steps].direction_of_origin == 'e')
                p->spr[i].x = p->spr[i].x + 1;
            else if (p->l[p->path_steps].direction_of_origin == 'w')
                p->spr[i].x = p->spr[i].x - 1;
            //     if (p->l[p->path_steps].direction_of_origin == 'n'
            // && p->map[(int)(p->spr[i].y - 1)][(int)p->spr[i].x] == '0')
            //     p->spr[i].y = p->spr[i].y - 1;
            // else if (p->l[p->path_steps].direction_of_origin == 's'
            // && p->map[(int)(p->spr[i].y + 1)][(int)p->spr[i].x] == '0')
            //     p->spr[i].y = p->spr[i].y + 1;
            // else if (p->l[p->path_steps].direction_of_origin == 'e'
            // && p->map[(int)(p->spr[i].y)][(int)(p->spr[i].x + 1)] == '0')
            //     p->spr[i].x = p->spr[i].x + 1;
            // else if (p->l[p->path_steps].direction_of_origin == 'w'
            // && p->map[(int)(p->spr[i].y)][(int)(p->spr[i].x - 1)] == '0')
            //     p->spr[i].x = p->spr[i].x - 1;
            time_last_move = current_time;
            p->map[(int)p->spr[i].y][(int)p->spr[i].x] = '2';
        }
        i++;
    }
}

void find_path(t_cub3d *p)
{
    int current_y;
    int current_x;
    int i;
    int s;
    int check;
    int front_of_list;

    p->l = malloc(sizeof(t_visited_squares) * 300);
    i = 0;
    p->l[i].y = p->p_y;
    p->l[i].x = p->p_x;
    front_of_list = 0;
    s = 0;
    while (p->spr[s].y != p->map_h)
    {
        while (1)
        {
            current_y = p->l[i].y;
            current_x = p->l[i].x;
            // check if player is found in current location
            if (p->l[i].y == (int)p->spr[s].y && p->l[i].x == (int)p->spr[s].x)
            {
                p->path_steps = i;
                return ;
            }
            // check if adjacent north square is a wall
            if (p->map[current_y - 1][current_x] != '1')
            {
                // check if adjacent north square is on the list
                check = front_of_list + 1;
                while (--check >= 0 && !(p->l[check].y == current_y - 1 && p->l[check].x == current_x))
                {
                    if (check == 0) // if check reaches 0, that means the coords aren't on the list
                    {
                        // it has not been visited, 
                        p->l[++front_of_list].y = current_y - 1;
                        p->l[front_of_list].x = current_x;
                        p->l[front_of_list].direction_of_origin = 's';
                    }
                }
            }
            if (p->map[current_y + 1][current_x] != '1') // check adjacent south square
            {
                check = front_of_list + 1;
                while (--check >= 0 && !(p->l[check].y == current_y + 1 && p->l[check].x == current_x))
                {
                    if (check == 0)
                    {
                        p->l[++front_of_list].y = current_y + 1;
                        p->l[front_of_list].x = current_x;
                        p->l[front_of_list].direction_of_origin = 'n';
                    }
                }
            }
            if (p->map[current_y][current_x - 1] != '1') // check adjacent west square
            {
                check = front_of_list + 1;
                while (--check >= 0 && !(p->l[check].y == current_y && p->l[check].x == current_x - 1))
                {
                    if (check == 0)
                    {
                        p->l[++front_of_list].y = current_y;
                        p->l[front_of_list].x = current_x - 1;
                        p->l[front_of_list].direction_of_origin = 'e';
                    }
                }
            }
            if (p->map[current_y][current_x + 1] != '1') // check adjacent east square
            {
                check = front_of_list + 1;
                while (--check >= 0 && !(p->l[check].y == current_y && p->l[check].x == current_x + 1))
                {
                    if (check == 0)
                    {
                        p->l[++front_of_list].y = current_y;
                        p->l[front_of_list].x = current_x + 1;
                        p->l[front_of_list].direction_of_origin = 'w';
                    }
                }
            }
            i++;
        }
        s++;
    }
}

// void move_enemy(t_cub3d *p)
// {
//     int i;
//     static double time_last_move;
// 	clock_t	current_time;

// 	current_time = clock();
//     i = 0;
//     while ((int)p->spr[i].y != p->map_h)
//     {
//         if ((double)(current_time - time_last_move) / (double)CLOCKS_PER_SEC > 0.01)
//         {
//             p->map[(int)p->spr[i].y][(int)p->spr[i].x] = '0';
//             if (p->l[p->path_steps].direction_of_origin == 'n')
//                 p->spr[i].y = p->spr[i].y - 0.1;
//             else if (p->l[p->path_steps].direction_of_origin == 's')
//                 p->spr[i].y = p->spr[i].y + 0.1;
//             else if (p->l[p->path_steps].direction_of_origin == 'e')
//                 p->spr[i].x = p->spr[i].x + 0.1;
//             else if (p->l[p->path_steps].direction_of_origin == 'w')
//                 p->spr[i].x = p->spr[i].x - 0.1;
//             p->map[(int)p->spr[i].y][(int)p->spr[i].x] = '2';
//             time_last_move = current_time;
//         }
//         i++;
//     }
// }

// void find_path(t_cub3d *p)
// {
//     int current_y;
//     int current_x;
//     int i;
//     int s;
//     int check;
//     int front_of_list;

//     p->l = malloc(sizeof(t_visited_squares) * 300);
//     i = 0;
//     p->l[i].y = p->p_y;
//     p->l[i].x = p->p_x;
//     front_of_list = 0;
//     s = 0;
//     while (p->spr[s].y != p->map_h)
//     {
//         while (1)
//         {
//             current_y = p->l[i].y;
//             current_x = p->l[i].x;
//             // check if player is found in current location
//             if (p->l[i].y == (int)p->spr[s].y && p->l[i].x == (int)p->spr[s].x)
//             {
//                 // printf("%d, %d\n", p->l[i].y, p->l[i].x);
//                 p->path_steps = i;
//                 return ;
//             }
//             // check if adjacent north square is a wall
//             if (p->map[current_y - 1][current_x] != '1' 
//             && p->map[current_y - 1][current_x] != '2')
//             {
//                 // check if adjacent north square is on the list
//                 check = front_of_list + 1;
//                 while (--check >= 0 && !(p->l[check].y == current_y - 1 && p->l[check].x == current_x))
//                 {
//                     if (check == 0) // if check reaches 0, that means the coords aren't on the list
//                     {
//                         // it has not been visited, 
//                         p->l[++front_of_list].y = current_y - 1;
//                         p->l[front_of_list].x = current_x;
//                         p->l[front_of_list].direction_of_origin = 's';
//                     }
//                 }
//             }
//             if (p->map[current_y + 1][current_x] != '1'
//             && p->map[current_y + 1][current_x] != '2') // check adjacent south square
//             {
//                 check = front_of_list + 1;
//                 while (--check >= 0 && !(p->l[check].y == current_y + 1 && p->l[check].x == current_x))
//                 {
//                     if (check == 0)
//                     {
//                         p->l[++front_of_list].y = current_y + 1;
//                         p->l[front_of_list].x = current_x;
//                         p->l[front_of_list].direction_of_origin = 'n';
//                     }
//                 }
//             }
//             if (p->map[current_y][current_x - 1] != '1'
//             && p->map[current_y][current_x - 1] != '2') // check adjacent west square
//             {
//                 check = front_of_list + 1;
//                 while (--check >= 0 && !(p->l[check].y == current_y && p->l[check].x == current_x - 1))
//                 {
//                     if (check == 0)
//                     {
//                         p->l[++front_of_list].y = current_y;
//                         p->l[front_of_list].x = current_x - 1;
//                         p->l[front_of_list].direction_of_origin = 'e';
//                     }
//                 }
//             }
//             if (p->map[current_y][current_x + 1] != '1'
//             && p->map[current_y][current_x + 1] != '2') // check adjacent east square
//             {
//                 check = front_of_list + 1;
//                 while (--check >= 0 && !(p->l[check].y == current_y && p->l[check].x == current_x + 1))
//                 {
//                     if (check == 0)
//                     {
//                         p->l[++front_of_list].y = current_y;
//                         p->l[front_of_list].x = current_x + 1;
//                         p->l[front_of_list].direction_of_origin = 'w';
//                     }
//                 }
//             }
//             i++;
//         }
//         s++;
//     }
// }