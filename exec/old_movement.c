// void move_player(t_data *data, double move_x, double move_y, t_cord vars)
// {
//     int wall_ahead;
//     int wall_x;
//     int wall_y;
//     double buffer = 0.5;
//     static double prev_x = -1;
//     static double prev_y = -1;
    
//     // Initialize on first run
//     if (prev_x == -1) {
//         prev_x = data->player.pos_x;
//         prev_y = data->player.pos_y;
//     }

//     double new_x = data->player.pos_x + move_x;
//     double new_y = data->player.pos_y + move_y;

//     vars.new_x = (int)(data->player.pos_x + move_x);
//     vars.new_y = (int)(data->player.pos_y + move_y);
//     vars.curr_x = (int)data->player.pos_x;
//     vars.curr_y = (int)data->player.pos_y;
//     if (vars.new_y < 0 || vars.new_y >= data->map.rows || 
//         vars.curr_y < 0 || vars.curr_y >= data->map.rows) {
//         return;  // Invalid position, don't move
//     }
//     // if (new_y < buffer || new_y >= data->map.rows - buffer || 
//     //     new_x < buffer) {
//     //     printf("too close to edge");return;  // Too close to edge, don't move
//     // }
//     vars.row_length_y = (int)ft_strlen(data->map.map[vars.new_y]);
//     vars.row_length_cy = (int)ft_strlen(data->map.map[vars.curr_y]);
//     if (vars.new_x < 0 || vars.new_x >= vars.row_length_y || 
//         vars.curr_x < 0 || vars.curr_x >= vars.row_length_cy) {
//         printf("Outside row bounds\n");
//         return;
//     }
//     if (new_y < buffer || new_y >= data->map.rows - buffer || 
//         new_x < buffer || new_x >= vars.row_length_y - buffer) {
//         printf("Too close to edge\n");
//         return;
//     }
//     if (data->map.map[vars.new_y][vars.new_x] == ' ' || 
//         data->map.map[vars.curr_y][vars.new_x] == ' ' || 
//         data->map.map[vars.new_y][vars.curr_x] == ' ') {
//         printf("Cannot move through spaces\n");
//         return;
//     }
//     wall_ahead = (vars.new_y >= 0 && vars.new_y < data->map.rows && 
//         vars.new_x >= 0 && vars.new_x < vars.row_length_y &&
//         data->map.map[vars.new_y][vars.new_x] == '1');
//     wall_x = (vars.curr_y >= 0 && vars.curr_y < data->map.rows && 
//         vars.new_x >= 0 && vars.new_x < vars.row_length_cy &&
//         data->map.map[vars.curr_y][vars.new_x] == '1');
//     wall_y = (vars.new_y >= 0 && vars.new_y < data->map.rows && 
//         vars.curr_x >= 0 && vars.curr_x < vars.row_length_y &&
//         data->map.map[vars.new_y][vars.curr_x] == '1');
//     if (wall_ahead && (!wall_x && !wall_y))
//         return;
//     if (!wall_x)
//         data->player.pos_x += move_x;
//     if (!wall_y)
//         data->player.pos_y += move_y;

//     double dx = data->player.pos_x - prev_x;
//     double dy = data->player.pos_y - prev_y;
//     double distance = sqrt(dx*dx + dy*dy);
    
//     if (distance > 0.2) {
//         printf("Jump detected: %f,%f to %f,%f (distance: %f)\n", 
//                 prev_x, prev_y, data->player.pos_x, data->player.pos_y, distance);
//         data->player.pos_x = prev_x;
//         data->player.pos_y = prev_y;
//     } else {
//         prev_x = data->player.pos_x;
//         prev_y = data->player.pos_y;
//     }
//     printf("Player position: %f, %f\n", data->player.pos_x, data->player.pos_y);
// }


// void move_player(t_data *data, double move_x, double move_y, t_cord vars)
// {
//     int wall_ahead;
//     int wall_x;
//     int wall_y;

//     vars.new_x = (int)(data->player.pos_x + move_x);
//     vars.new_y = (int)(data->player.pos_y + move_y);
//     vars.curr_x = (int)data->player.pos_x;
//     vars.curr_y = (int)data->player.pos_y;
//     vars.row_length_y = (int)ft_strlen(data->map.map[vars.new_y]);
//     vars.row_length_cy = (int)ft_strlen(data->map.map[vars.curr_y]);
//     wall_ahead = (vars.new_y >= 0 && vars.new_y < data->map.rows && 
//         vars.new_x >= 0 && vars.new_x < vars.row_length_y &&
//         data->map.map[vars.new_y][vars.new_x] == '1');
//     wall_x = (vars.curr_y >= 0 && vars.curr_y < data->map.rows && 
//         vars.new_x >= 0 && vars.new_x < vars.row_length_cy &&
//         data->map.map[vars.curr_y][vars.new_x] == '1');
//     wall_y = (vars.new_y >= 0 && vars.new_y < data->map.rows && 
//         vars.curr_x >= 0 && vars.curr_x < vars.row_length_y &&
//         data->map.map[vars.new_y][vars.curr_x] == '1');
//     if (wall_ahead && (!wall_x && !wall_y))
//         return;
//     if (!wall_x)
//         data->player.pos_x += move_x;
//     if (!wall_y)
//         data->player.pos_y += move_y;
// }