void suite_register (
    void
)
{
  test_add( nova_start, load_collections );
  test_add( nova_start, load_data_path );
}
