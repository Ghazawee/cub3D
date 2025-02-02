int count_file_lines(const char *filename)
{
    int count = 0;
    int fd = open(filename, O_RDONLY);
    char *line;

    if (fd == -1)
        return (-1);

    while ((line = get_next_line(fd)) != NULL)
    {
        count++;
        free(line);
    }

    close(fd);
    return count;
}

char **read_cub_file(const char *filename, int line_count)
{
    int fd = open(filename, O_RDONLY);
    char **lines;
    char *line;
    int i = 0;

    if (fd == -1)
        return (NULL);

    lines = malloc(sizeof(char *) * (line_count + 1));
    if (!lines)
        return (NULL);

    while ((line = get_next_line(fd)) != NULL)
    {
		lines[i++] = line;
		//free(line);
	}

    lines[i] = NULL; // Null terminate
    close(fd); // Close the file after reading
    return (lines);
}