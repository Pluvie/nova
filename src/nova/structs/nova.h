struct nova;
struct nova {
  struct string* data_path;
  struct vector* collections;
};
check_sizeof(struct nova, 16);
