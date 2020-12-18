## Bonuses
- Wall collisions.
- A skybox.
- Floor and/or ceiling texture.
- An HUD.
- A distance related shadow effect.
- Life bar.
- More items in the maze.
- Object collisions.
- Earning points and/or losing life by picking up objects/traps.
- Animations of a gun shot or animated sprite
- Sounds and music.
- Rotate the point of view with the mouse
- Weapons and bad guys to fight!
- Unmentioned bonus: moving skybox
- Unmentioned bonus: actual functional combat
- Unmentioned bonus: pathing


### Sources
[video: Wolfenstein 3D's map renderer](https://www.youtube.com/watch?v=eOCQfxRQ2pY)
[article: pathfinding](https://www.redblobgames.com/pathfinding/a-star/introduction.html)
[written: Ray-Casting Tutorial on permadi.com](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
[documentation: getting started with minilibx](https://harm-smits.github.io/42docs/libs/minilibx/introduction.html)
[tommy's resources](https://github.com/dichotommy49/cub3d/blob/master/cub3d%20resources.txt)
[Lode's Computer Graphics Tutorial: Raycasting](https://lodev.org/cgtutor/raycasting.html)

ERROR & MALLOC PROTECTION CHECK
start.c √√ (malloc t->td[])
draw_sprites.c
draw_walls.c
move.c

hooks.c
parse_cub_file.c
    compare_resolutions √
    get_screen_resolution √
    get_window_resolution √
    get_texture_path √√ (malloc t->td[].tex_path)
    get_map_config > get_colour √ / parse_map 
parse_cub_file_2.c
    check_tex_path √
    check_colour √
    get_value -
    get_colour - 
    check_arguments - 
parse_map.c
    check_charset -
    get_map_dimensions √
    find_player_part_2 -
    find_player √
    parse_map √√ (malloc t->map)
parse_map_2.c
    check_map_horizontally [√]
    check_map_vertically [√]
    initialise_sprite -
    find_sprites_part_2 √√ (malloc t->spr)
    find_sprites -
copy_file.c √
ft_split_var.c √
get_textures.c -
draw_floor.c √
draw_skybox.c √
move_2.c √
enemy_pathfinding_utils.c √
enemy_pathfinding.c √√ (malloc t->l)
draw_ui_elements.c √
draw_ui_elements_2.c √
shoot.c √
get_sprite_frame.c √
auxiliary.c
    ft_getpxl √
    shader √
    ft_putpxl √
    get_pxl_for_bmp √
    shader_red √
auxiliary_2.c
    error_and_exit √
    draw_background √
    print_terminal_map √
    get_distance √
    play_music √
sprite_control.c √
get_bmp.c
    initialise √ (malloc b->image)
    create_bmp
    create_bmp_info_h
    create_bmp_file_h



MAGIC NUMBER CHECK