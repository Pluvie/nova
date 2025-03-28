struct nova_collection;
struct nova_collection {
  void* data;
  const char* file;
  struct string* name;
  struct reflection* schema;
};
check_sizeof(struct nova_collection, 32);
