
  char collections_file[128] = { 0 };
  snprintf(collections_file, sizeof(collections_file), "%s/collections.nova", data_path);

  i32 collections_descriptor = open(collections_file,
    O_RDONLY | O_CREAT,                     /* Open read only, create if not exists. */
    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); /* Grand 644 permissions. */

  if (collections_descriptor < 0) {
    fail("unable to load collections from `%s`: %s",
      collections_file, strerror(errno));
    return;
  }

  struct stat collections_file_stats;
  i32 stats_output = fstat(collections_descriptor, &collections_file_stats)

  if (stats_output < 0) {
    fail("unable to get collections stats from `%s`: %s",
      collections_file, strerror(errno));
    return;
  }

  u64 file_length = collections_file_stats.st_size;
