test( nova_start, load_data_path ) {

  given("a fresh 🇳💫🇻🇦 instance");
    verify(nova.collections == NULL);
    verify(nova.data_path == NULL);


  when("a collections vector is defined");
    struct string data_path = s("my/nova/data/directory");


  calling("nova_start()");
    nova_start(&data_path, NULL);


  must("correctly load the data path");
    verify(error.occurred == false);
    verify(streq(nova.data_path->content, data_path.content));


  success();
    nova_stop();
}
