#! /bin/bash

printf "\033[1;31mTESTING MAPS THAT SHOULD FAIL\033[0m\n\n"

# printf "executing map: error_chars_after_map.cub\n"
# ./cub3D maps/test_cubs/error_chars_after_map.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_bad_texture_path.cub\n"
# ./cub3D maps/test_cubs/error_bad_texture_path.cub 
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_chars_after_map.cub\n"
# ./cub3D maps/test_cubs/error_chars_after_map.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_double_char.cub\n"
# ./cub3D maps/test_cubs/error_double_char.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_duplicate_colours.cub\n"
# ./cub3D maps/test_cubs/error_duplicate_colours.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_duplicate_resolution.cub\n"
# ./cub3D maps/test_cubs/error_duplicate_resolution.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_duplicate_texture.cub\n"
# ./cub3D maps/test_cubs/error_duplicate_texture.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_hole_in_wall.cub\n"
# ./cub3D maps/test_cubs/error_hole_in_wall.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_map_not_at_end.cub\n"
# ./cub3D maps/test_cubs/error_map_not_at_end.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_missing_color_1.cub\n"
# ./cub3D maps/test_cubs/error_missing_color_1.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_missing_color_2.cub\n"
# ./cub3D maps/test_cubs/error_missing_color_2.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_missing_map.cub\n"
# ./cub3D maps/test_cubs/error_missing_map.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_missing_res.cub\n"
# ./cub3D maps/test_cubs/error_missing_res.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_missing_texture.cub\n"
# ./cub3D maps/test_cubs/error_missing_texture.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_no_char.cub\n"
# ./cub3D maps/test_cubs/error_no_char.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_split_map_1.cub\n"
# ./cub3D maps/test_cubs/error_split_map_1.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_split_map_2.cub\n"
# ./cub3D maps/test_cubs/error_split_map_2.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_too_many_sprites.cub\n"
# ./cub3D maps/test_cubs/error_too_many_sprites.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_unexpected_char_1.cub\n"
# ./cub3D maps/test_cubs/error_unexpected_char_1.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_unexpected_char_2.cub\n"
# ./cub3D maps/test_cubs/error_unexpected_char_2.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_unexpected_char_3.cub\n"
# ./cub3D maps/test_cubs/error_unexpected_char_3.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_unexpected_char_4.cub\n"
# ./cub3D maps/test_cubs/error_unexpected_char_4.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_unexpected_char_5.cub\n"
# ./cub3D maps/test_cubs/error_unexpected_char_5.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_unexpected_char_6.cub\n"
# ./cub3D maps/test_cubs/error_unexpected_char_6.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_unexpected_char_7.cub\n"
# ./cub3D maps/test_cubs/error_unexpected_char_7.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_unexpected_char_8.cub\n"
# ./cub3D maps/test_cubs/error_unexpected_char_8.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_unexpected_char_9.cub\n"
# ./cub3D maps/test_cubs/error_unexpected_char_9.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_unexpected_char_10.cub\n"
# ./cub3D maps/test_cubs/error_unexpected_char_10.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: error_unknown_symbol.cub\n"
# ./cub3D maps/test_cubs/error_unknown_symbol.cub
# cat leaks.txt | grep '0 leaks'

printf '\n'
printf "executing map: none\n"
./cub3D
cat leaks.txt | grep '0 leaks'

printf '\n'
printf "executing map: bad path\n"
./cub3D maps/test_cubs/bad_path
cat leaks.txt | grep '0 leaks'

printf '\n'
printf "executing map: template.cub arg1\n"
./cub3D maps/test_cubs/template.cub arg1
cat leaks.txt | grep '0 leaks'

printf '\n'
printf "executing map: template.cub arg1 arg2\n"
./cub3D maps/test_cubs/template.cub arg1 arg2
cat leaks.txt | grep '0 leaks'

printf '\n'
printf "executing map: template.cub -save\n"
./cub3D maps/test_cubs/template.cub -save
cat leaks.txt | grep '0 leaks'

printf '\n'
printf "executing map: no_cub_extension\n"
./cub3D maps/test_cubs/no_cub_extension
cat leaks.txt | grep '0 leaks'

printf '\n'

printf "\033[1;32mTESTING MAPS THAT SHOULD PASS\033[0m\n\n"

printf '\n'
printf "executing map: template.cub --save\n"
./cub3D maps/test_cubs/template.cub --save
cat leaks.txt | grep '0 leaks'

# printf "executing map: pass_res_high.cub\n"
# ./cub3D maps/test_cubs/pass_res_high.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: pass_res_low.cub\n"
# ./cub3D maps/test_cubs/pass_res_low.cub
# cat leaks.txt | grep '0 leaks'

# printf '\n'
# printf "executing map: pass_spaces.cub\n"
# ./cub3D maps/test_cubs/pass_spaces.cub
# cat leaks.txt | grep '0 leaks'
printf '\n'