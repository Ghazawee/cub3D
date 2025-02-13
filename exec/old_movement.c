// void move_vertically(t_data *data, int direction)
// {
//     double new_x;
//     double new_y;
//     int curr_y;
//     int curr_x;

//     curr_y = (int)data->player.pos_y;
//     curr_x = (int)data->player.pos_x;

//     if(direction == MUP)
//     {
//         new_x = data->player.pos_x + data->player.dir_x * MOV_SPEED;
//         if(curr_y >= 0 && curr_y < data->map.rows && (int)new_x >= 0 && (int)new_x < (int)ft_strlen(data->map.map[curr_y]) && 
//             data->map.map[curr_y][(int)new_x] != '1')
//             data->player.pos_x = new_x;
//         new_y = data->player.pos_y + data->player.dir_y * MOV_SPEED;
//         if ((int)new_y >= 0 && (int)new_y < data->map.rows && curr_x >= 0 && curr_x < (int)ft_strlen(data->map.map[(int)new_y]) 
//             && data->map.map[(int)new_y][curr_x] != '1')
//             data->player.pos_y = new_y;
//     }
//     else
//     {
//         new_x = data->player.pos_x - data->player.dir_x * MOV_SPEED;
//         if(curr_y >= 0 && curr_y < data->map.rows && (int)new_x >= 0 && (int)new_x < (int)ft_strlen(data->map.map[curr_y]) && 
//             data->map.map[curr_y][(int)new_x] != '1')
//             data->player.pos_x = new_x;
//         new_y = data->player.pos_y - data->player.dir_y * MOV_SPEED;
//         if ((int)new_y >= 0 && (int)new_y < data->map.rows && curr_x >= 0 && curr_x < (int)ft_strlen(data->map.map[(int)new_y]) 
//             && data->map.map[(int)new_y][curr_x] != '1')
//             data->player.pos_y = new_y;
//     }
// }
// might need to change the way of checking  maybe check if new x first with current y and then check if new y with current x
// void move_horizontally(t_data *data, int direction)
// {
//     double new_x;
//     double new_y;
//     int curr_y;
//     int curr_x;

//     curr_y = (int)data->player.pos_y;
//     curr_x = (int)data->player.pos_x;
//     if (direction == MRIGHT)
//     {
//         new_x = data->player.pos_x + data->player.plane_x * MOV_SPEED;
//         if (curr_y >= 0 && curr_y < data->map.rows &&
//             (int)new_x >= 0 && (int)new_x < (int)ft_strlen(data->map.map[curr_y]) &&
//             data->map.map[curr_y][(int)new_x] != '1')
//             data->player.pos_x = new_x;
//         new_y = data->player.pos_y + data->player.plane_y * MOV_SPEED;
//         if ((int)new_y >= 0 && (int)new_y < data->map.rows &&
//         curr_x >= 0 && curr_x < (int)ft_strlen(data->map.map[(int)new_y]) &&
//         data->map.map[(int)new_y][curr_x] != '1')
//             data->player.pos_y = new_y;
//     }
//     else
//     {
//         new_x = data->player.pos_x - data->player.plane_x * MOV_SPEED;
//         if (curr_y >= 0 && curr_y < data->map.rows &&
//             (int)new_x >= 0 && (int)new_x < (int)ft_strlen(data->map.map[curr_y]) &&
//             data->map.map[curr_y][(int)new_x] != '1')
//             data->player.pos_x = new_x;
//         new_y = data->player.pos_y - data->player.plane_y * MOV_SPEED;    

//         if ((int)new_y >= 0 && (int)new_y < data->map.rows &&
//         curr_x >= 0 && curr_x < (int)ft_strlen(data->map.map[(int)new_y]) &&
//         data->map.map[(int)new_y][curr_x] != '1')
//             data->player.pos_y = new_y;
//     }  
// }