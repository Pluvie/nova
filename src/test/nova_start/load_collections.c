test( nova_start, load_collections ) {

  given("a fresh 🇳💫🇻🇦 instance");
    verify(nova.collections == NULL);
    verify(nova.data_path == NULL);


  when("a collections vector is defined");
    struct vector collections = vector_of(struct nova_collection, {
      { .name = &s("numbers"), .schema = &(struct reflection) { type(I32) } },
      { .name = &s("strings"), .schema = &(struct reflection) { type(STRING) } },
    });


  calling("nova_start()");
    nova_start(NULL, &collections);


  must("correctly load the collections");
    verify(error.occurred == false);


  success();
    nova_stop();
}
