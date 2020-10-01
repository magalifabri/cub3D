#include "cub3d.h"

double get_distance(int y_dest, int x_dest, int y_src, int x_src)
{
    double x_dif;
    double y_dif;
    double angle;
    double distance;

    x_dif = x_src - x_dest;
    y_dif = y_src - y_dest;
    angle = fabs(atan(y_dif/x_dif));
    if ((angle > 0.25 && angle < 0.75) || (angle > 1.25 && angle < 1.75))
        distance = y_dif / sin(angle);
    else
        distance = x_dif / cos(angle);
    return (fabs(distance));
}

void move_enemy(t_cub3d *p, int i)
{
    static double time_last_move[10];
	clock_t	current_time;

    if (p->path_steps < 2)
        return ;
    // if (p->map[(int)(p->spr[i].y + (p->spr[i].y_draw * 10))][(int)(p->spr[i].x + (p->spr[i].x_draw * 10))] == '2')
    //     return ;
	current_time = clock();
    if ((double)(current_time - time_last_move[i]) / (double)CLOCKS_PER_SEC > 0.05)
    {
        if (p->spr[i].counter == 0)
        {
                p->spr[i].y_draw = 0;
                p->spr[i].x_draw = 0;

            if (p->l[p->path_steps].direction_of_origin == 'n')
                p->spr[i].y_draw = -0.1;
            else if (p->l[p->path_steps].direction_of_origin == 's')
                p->spr[i].y_draw = 0.1;
            else if (p->l[p->path_steps].direction_of_origin == 'e')
                p->spr[i].x_draw = 0.1;
            else if (p->l[p->path_steps].direction_of_origin == 'w')
                p->spr[i].x_draw = -0.1;
            
            // if (p->map[(int)(p->spr[i].y + (p->spr[i].y_draw * 10))][(int)(p->spr[i].x + (p->spr[i].x_draw * 10))] == '2'
            // || p->map[(int)(p->spr[i].y + (p->spr[i].y_draw * 10))][(int)(p->spr[i].x + (p->spr[i].x_draw * 10))] == 'P')
            // {
            //     p->spr[i].y_draw = 0;
            //     p->spr[i].x_draw = 0;
            //     // return ;
            // }
        
        }
        p->spr[i].counter++;
        if (p->spr[i].counter == 10)
        {
            p->map[(int)p->spr[i].y][(int)p->spr[i].x] = '0';
            p->spr[i].y = p->spr[i].y + (p->spr[i].y_draw * 10);
            p->spr[i].x = p->spr[i].x + (p->spr[i].x_draw * 10);
            p->map[(int)p->spr[i].y][(int)p->spr[i].x] = '2';
            p->spr[i].counter = 0;
        }
        time_last_move[i] = current_time;
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

    s = 0;
    while (s < p->sprite_n)
    {
        i = 0;
        p->l = malloc(sizeof(t_visited_squares) * 300);
        p->l[i].y = p->p_y;
        p->l[i].x = p->p_x;
        front_of_list = 0;
        // i = 0;
        if (p->spr[s].alive)
        {
            while (1)
            {
                current_y = p->l[i].y;
                current_x = p->l[i].x;
                // check if searched object is found in current location
                if (p->l[i].y == (int)p->spr[s].y && p->l[i].x == (int)p->spr[s].x)
                // if (get_distance(p->l[i].y, p->l[i].x, (int)p->spr[s].y, (int)p->spr[s].x) < 1.5)
                {
                    p->path_steps = i;
                    move_enemy(p, s);
                    if (s + 1 == p->sprite_n)
                        return ;
                    break ;
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
        }
        s++;
    }
}
